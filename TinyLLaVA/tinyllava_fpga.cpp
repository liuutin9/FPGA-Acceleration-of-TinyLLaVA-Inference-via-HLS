// TinyLLaVA end-to-end on the Alveo U280:
//   image --(CPU) modules/image_preprocess: preprocess()          --> 3x384x384
//         --(CPU) modules/Siglip: Embedding() (patch + position)  --> 729x1152
//         --(FPGA) SigLIP 26 layers + Connector                    --> 728x2560 image features
//   prompt --(CPU) tokenizer, "<image>" -> IMAGE_TOKEN_INDEX (-200)
//         --(FPGA) Phi-2, image features spliced in at -200        --> generated ids --(CPU) decode
//
// Usage:
//   tinyllava_fpga <Platform_Vendor> <Device_Name> <siglip.xclbin> <phi.xclbin>
//                  <image.jpg> <tokenizer.json> <siglip_weight_dir> <phi_weight_dir>
//                  [question] [max_new_tokens]
//   If [question] is omitted it is read from stdin.
//
// Environment variables (optional):
//   TINYLLAVA_PIXELS   : float32 3x384x384 preprocessed image (e.g. image_tensor.bin written by
//                        modules/Siglip/test/Siglip_test.py) used instead of the OpenCV
//                        preprocessing, for bit-exact comparison with the Python reference.
//   TINYLLAVA_DUMP_DIR : also write siglip_embeddings.bin and image_features.bin (float32);
//                        image_features.bin is comparable with Siglip/py_baseline/encoded_output.bin.
//
// <siglip_weight_dir> holds the fp16 .bin exports used by both modules/Siglip (embeddings) and
// the SigLIP FPGA host (encoder layers + connector), e.g.
//   vision_tower._vision_tower.vision_model.embeddings.patch_embedding.weight.bin
//   vision_tower._vision_tower.vision_model.encoder.layers.0.layer_norm1.weight.bin
//   connector._connector.0.weight.bin

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "modules/Siglip/Siglip_config.hpp"                  // SigLIP dims, Embedding()
#include "modules/image_preprocess/image_processor.hpp"      // preprocess()
#include "tokenizers_cpp.h"
#include "tinyllava_fpga.h"

namespace {

// SigLIP (from modules/Siglip/Siglip_config.hpp)
constexpr int kSiglipTokens = INPUT_DIM;          // 729
constexpr int kVisionHidden = HIDDEN_SIZE;        // 1152
constexpr int kImageTokens  = kSiglipTokens - 1;  // 728, "patch" strategy drops token 0
constexpr int kPixels       = NUM_CHANNELS * IMAGE_SIZE * IMAGE_SIZE;
static_assert(kSiglipTokens == 729 && kVisionHidden == 1152, "unexpected SigLIP config");

// Phi-2 (modules/phi-2/phi-2_config.hpp is not included: it redefines HIDDEN_SIZE/SLEN/VOCAB_SIZE)
constexpr int kPhiHidden        = 2560;
constexpr int kImageTokenIndex  = -200;   // IMAGE_TOKEN_INDEX in modules/TinyLlava_config.hpp
constexpr int kEosTokenId       = 50256;
constexpr int kDefaultNewTokens = 64;

const std::string kSystemPrompt =
    "A chat between a curious user and an artificial intelligence assistant. "
    "The assistant gives helpful, detailed, and polite answers to the user's questions.";

// ---------------------------------------------------------------------------
// File helpers
// ---------------------------------------------------------------------------
std::string join_path(std::string dir, const std::string& name) {
    if (!dir.empty() && dir.back() != '/') dir += '/';
    return dir + name;
}

bool load_f32(const std::string& path, std::vector<float>& out, size_t count) {
    std::ifstream fin(path, std::ios::binary);
    if (!fin) {
        std::cerr << "Failed to open " << path << "\n";
        return false;
    }
    out.resize(count);
    fin.read(reinterpret_cast<char*>(out.data()), count * sizeof(float));
    if (!fin) {
        std::cerr << "File too short (expected " << count << " float32 values): " << path << "\n";
        return false;
    }
    return true;
}

void dump_f32(const std::string& path, const std::vector<float>& data) {
    std::ofstream fout(path, std::ios::binary);
    fout.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(float));
    std::cout << "Wrote " << path << "\n";
}

// ---------------------------------------------------------------------------
// Tokenizer
// ---------------------------------------------------------------------------
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
    const std::string sep = "<image>";
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
        ids.push_back(kImageTokenIndex);
        start = end + sep.size();
    }
    return ids;
}

// ---------------------------------------------------------------------------
// Image -> SigLIP embeddings (CPU, modules/)
// ---------------------------------------------------------------------------
bool image_to_pixels(const std::string& image_path, std::vector<float>& pixels) {
    if (const char* pixel_file = std::getenv("TINYLLAVA_PIXELS")) {
        std::cout << "Using preprocessed pixels from " << pixel_file << "\n";
        return load_f32(pixel_file, pixels, kPixels);
    }
    cv::Mat bgr = cv::imread(image_path, cv::IMREAD_COLOR);
    if (bgr.empty()) {
        std::cerr << "Failed to load image: " << image_path << "\n";
        return false;
    }
    pixels.assign(kPixels, 0.0f);
    preprocess(*reinterpret_cast<float (*)[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]>(pixels.data()), bgr);
    return true;
}

bool pixels_to_embeddings(std::vector<float>& pixels, const std::string& weight_dir, std::vector<float>& embeddings) {
    set_siglip_weight_dir(weight_dir);
    if (!load_siglip_embedding_weight()) return false;
    embeddings.assign(static_cast<size_t>(kSiglipTokens) * kVisionHidden, 0.0f);
    Embedding(embeddings.data(), pixels.data());  // Conv2d(3->1152, k14, s14) + position embedding
    return true;
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc < 9) {
        std::cerr << "Usage: " << argv[0]
                  << " <Platform_Vendor> <Device_Name> <siglip.xclbin> <phi.xclbin> <image.jpg>"
                     " <tokenizer.json> <siglip_weight_dir> <phi_weight_dir> [question] [max_new_tokens]\n";
        return EXIT_FAILURE;
    }
    const char* vendor               = argv[1];
    const char* device               = argv[2];
    const char* siglip_xclbin        = argv[3];
    const char* phi_xclbin           = argv[4];
    const std::string image_path     = argv[5];
    const std::string tokenizer_path = argv[6];
    const std::string siglip_weights = argv[7];
    const std::string phi_weights    = argv[8];

    std::string question;
    if (argc > 9) {
        question = argv[9];
    } else {
        std::cout << "Question: ";
        std::getline(std::cin, question);
    }
    const int max_new_tokens = argc > 10 ? std::atoi(argv[10]) : kDefaultNewTokens;
    const char* dump_dir = std::getenv("TINYLLAVA_DUMP_DIR");

    // 1. Prompt -> ids (template from TinyLlavaForConditionalGeneration.chat)
    auto tokenizer = init_tokenizer(tokenizer_path);
    if (!tokenizer) return EXIT_FAILURE;
    const std::string prompt = kSystemPrompt + " USER: <image>\n" + question + " ASSISTANT:";
    const std::vector<int32_t> input_ids = tokenizer_image_token(prompt, *tokenizer);

    // 2. Image -> SigLIP embeddings (CPU)
    std::vector<float> pixels, embeddings;
    if (!image_to_pixels(image_path, pixels)) return EXIT_FAILURE;
    if (!pixels_to_embeddings(pixels, siglip_weights, embeddings)) return EXIT_FAILURE;
    if (dump_dir) dump_f32(join_path(dump_dir, "siglip_embeddings.bin"), embeddings);

    // 3. SigLIP encoder + Connector (FPGA)
    std::vector<float> image_features(static_cast<size_t>(kImageTokens) * kPhiHidden, 0.0f);
    if (siglip_host::run_siglip_connector(vendor, device, siglip_xclbin, embeddings.data(),
                                          image_features.data(), siglip_weights) != EXIT_SUCCESS) {
        std::cerr << "SigLIP/Connector FPGA run failed\n";
        return EXIT_FAILURE;
    }
    if (dump_dir) dump_f32(join_path(dump_dir, "image_features.bin"), image_features);

    // 4. Phi-2 with the image features spliced in (FPGA)
    std::vector<int32_t> output_ids;
    if (phi_host::phi_generate(vendor, device, phi_xclbin, input_ids, image_features.data(), kImageTokens,
                               max_new_tokens, output_ids, phi_weights) != EXIT_SUCCESS) {
        std::cerr << "Phi-2 FPGA run failed\n";
        return EXIT_FAILURE;
    }

    // 5. Decode (phi_generate already stops at EOS)
    std::vector<int32_t> answer;
    for (int32_t id : output_ids) {
        if (id == kEosTokenId) break;
        answer.push_back(id);
    }
    std::cout << "\nUSER: " << question << "\nASSISTANT: " << tokenizer->Decode(answer) << std::endl;
    return EXIT_SUCCESS;
}
