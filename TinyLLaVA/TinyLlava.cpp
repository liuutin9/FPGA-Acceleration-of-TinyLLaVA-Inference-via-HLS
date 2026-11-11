// TinyLLaVA end-to-end on the CPU (reference for the FPGA version in tinyllava_fpga.cpp):
//   image  -> modules/image_preprocess  preprocess()                 3x384x384
//          -> modules/Siglip            Siglip_Transformer_forward()  729x1152
//          -> drop token 0 ("patch" strategy)                         728x1152
//          -> modules/connector         Connector_forward()           728x2560
//   prompt -> tokenizer, "<image>" -> IMAGE_TOKEN_INDEX (-200)
//          -> text ids: modules/phi-2 phi_embed_token(), -200: the 728 image rows
//          -> modules/phi-2             PhiForCausalLM_generate()     -> ids -> text
//
// Usage:
//   tinyllava_cpu <image.jpg> <tokenizer.json> <weight_dir> [question] [max_new_tokens]
//   <weight_dir>: fp16 .bin exports named after the HF tensors (e.g. Weight/model_bins1/):
//     vision_tower._vision_tower.vision_model.*, connector._connector.*, language_model.*
//   If [question] is omitted it is read from stdin.
// Environment variables (optional):
//   TINYLLAVA_PIXELS   : float32 3x384x384 preprocessed image (image_tensor.bin from
//                        modules/Siglip/test/Siglip_test.py) instead of the OpenCV preprocessing
//   TINYLLAVA_DUMP_DIR : write siglip_output.bin, image_features.bin, inputs_embeds.bin (float32);
//                        inputs_embeds.bin matches modules/phi-2/test/test_data/
//                        prepare_inputs_labels_for_multimodal_output_golden.txt

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "modules/tinyllava_modules.hpp"
#include "modules/TinyLlava_config.hpp"
#include "modules/image_preprocess/image_processor.hpp"
#include "tokenizers_cpp.h"

using namespace tinyllava;

namespace {

constexpr int kDefaultNewTokens = 64;

const std::string kSystemPrompt =
    "A chat between a curious user and an artificial intelligence assistant. "
    "The assistant gives helpful, detailed, and polite answers to the user's questions.";

void dump_f32(const char* dir, const std::string& name, const std::vector<float>& data) {
    if (!dir) return;
    std::string path = dir;
    if (!path.empty() && path.back() != '/') path += '/';
    path += name;
    std::ofstream fout(path, std::ios::binary);
    fout.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(float));
    std::cout << "Wrote " << path << "\n";
}

std::unique_ptr<tokenizers::Tokenizer> init_tokenizer(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) {
        std::cerr << "Failed to open tokenizer json: " << path << "\n";
        return nullptr;
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return tokenizers::Tokenizer::FromBlobJSON(buffer.str());
}

// Same as tokenizer_image_token() in the Python reference.
std::vector<int32_t> tokenizer_image_token(const std::string& prompt, tokenizers::Tokenizer& tokenizer) {
    const std::string sep = DEFAULT_IMAGE_TOKEN;
    std::vector<int32_t> ids;
    size_t start = 0;
    while (true) {
        const size_t end = prompt.find(sep, start);
        const std::string chunk = prompt.substr(start, end == std::string::npos ? std::string::npos : end - start);
        if (!chunk.empty()) {
            std::vector<int32_t> chunk_ids = tokenizer.Encode(chunk);
            ids.insert(ids.end(), chunk_ids.begin(), chunk_ids.end());
        }
        if (end == std::string::npos) break;
        ids.push_back(IMAGE_TOKEN_INDEX);
        start = end + sep.size();
    }
    return ids;
}

bool image_to_pixels(const std::string& image_path, std::vector<float>& pixels) {
    pixels.assign(static_cast<size_t>(kNumChannels) * kImageSize * kImageSize, 0.0f);
    if (const char* pixel_file = std::getenv("TINYLLAVA_PIXELS")) {
        std::ifstream fin(pixel_file, std::ios::binary);
        fin.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * sizeof(float));
        if (!fin) {
            std::cerr << "Failed to read " << pixels.size() << " floats from " << pixel_file << "\n";
            return false;
        }
        std::cout << "Using preprocessed pixels from " << pixel_file << "\n";
        return true;
    }
    cv::Mat bgr = cv::imread(image_path, cv::IMREAD_COLOR);
    if (bgr.empty()) {
        std::cerr << "Failed to load image: " << image_path << "\n";
        return false;
    }
    preprocess(*reinterpret_cast<float (*)[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]>(pixels.data()), bgr);
    return true;
}

// model.encode_images: SigLIP -> image_features[:, 1:] -> connector. Returns 728 x 2560.
std::vector<float> encode_images(std::vector<float>& pixels, const char* dump_dir) {
    std::vector<float> siglip_out(static_cast<size_t>(kSiglipTokens) * kVisionHidden, 0.0f);
    Siglip_Transformer_forward(siglip_out.data(), pixels.data());
    dump_f32(dump_dir, "siglip_output.bin", siglip_out);

    std::vector<float> features(static_cast<size_t>(kImageTokens) * kPhiHidden, 0.0f);
    Connector_forward(features.data(), siglip_out.data() + kVisionHidden, kImageTokens);
    dump_f32(dump_dir, "image_features.bin", features);
    return features;
}

// prepare_inputs_labels_for_multimodal: text ids -> word embeddings, -200 -> image rows.
bool build_inputs_embeds(const std::vector<int32_t>& input_ids, const std::vector<float>& image_features,
                         std::vector<float>& embeds) {
    embeds.clear();
    std::vector<float> row(kPhiHidden);
    int num_images = 0;
    for (int32_t id : input_ids) {
        if (id == IMAGE_TOKEN_INDEX) {
            ++num_images;
            embeds.insert(embeds.end(), image_features.begin(), image_features.end());
        } else if (id >= 0 && id < kPhiVocab) {
            phi_embed_token(id, row.data());
            embeds.insert(embeds.end(), row.begin(), row.end());
        } else {
            std::cerr << "Token id out of range: " << id << "\n";
            return false;
        }
    }
    if (num_images != 1) {
        std::cerr << "Expected exactly one <image> in the prompt, got " << num_images << "\n";
        return false;
    }
    return true;
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <image.jpg> <tokenizer.json> <weight_dir> [question] [max_new_tokens]\n";
        return EXIT_FAILURE;
    }
    const std::string image_path     = argv[1];
    const std::string tokenizer_path = argv[2];
    const std::string weight_dir     = argv[3];
    std::string question;
    if (argc > 4) {
        question = argv[4];
    } else {
        std::cout << "Question: ";
        std::getline(std::cin, question);
    }
    const int max_new_tokens = argc > 5 ? std::atoi(argv[5]) : kDefaultNewTokens;
    const char* dump_dir = std::getenv("TINYLLAVA_DUMP_DIR");

    set_siglip_weight_dir(weight_dir);
    set_connector_weight_dir(weight_dir);
    set_phi_weight_dir(weight_dir);
    if (!load_connector_weight() || !load_phi_weight()) return EXIT_FAILURE;

    auto tokenizer = init_tokenizer(tokenizer_path);
    if (!tokenizer) return EXIT_FAILURE;
    // Template from TinyLlavaForConditionalGeneration.chat
    const std::string prompt = kSystemPrompt + " USER: " + DEFAULT_IMAGE_TOKEN + "\n" + question + " ASSISTANT:";
    const std::vector<int32_t> input_ids = tokenizer_image_token(prompt, *tokenizer);

    std::vector<float> pixels;
    if (!image_to_pixels(image_path, pixels)) return EXIT_FAILURE;
    const std::vector<float> image_features = encode_images(pixels, dump_dir);

    std::vector<float> embeds;
    if (!build_inputs_embeds(input_ids, image_features, embeds)) return EXIT_FAILURE;
    dump_f32(dump_dir, "inputs_embeds.bin", embeds);
    const int input_len = static_cast<int>(embeds.size() / kPhiHidden);
    std::cout << "prompt length = " << input_len << " (text " << input_len - kImageTokens
              << " + image " << kImageTokens << ")\n";

    std::vector<int> output_ids(max_new_tokens > 0 ? max_new_tokens : 0);
    const int n = PhiForCausalLM_generate(embeds.data(), input_len, max_new_tokens, output_ids.data());
    const std::vector<int32_t> answer(output_ids.begin(), output_ids.begin() + n);

    std::cout << "\nUSER: " << question << "\nASSISTANT: " << tokenizer->Decode(answer) << std::endl;
    return EXIT_SUCCESS;
}
