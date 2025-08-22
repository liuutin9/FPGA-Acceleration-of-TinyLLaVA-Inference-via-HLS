#include<string.h>
#include "./Siglip/Siglip_config.hpp"
#include "./phi-2/phi-2_config.hpp"
#include "./connector/connector_config.hpp"
//#include "./utils/transformer.hpp"
#include "./image_preprocess/image_processor.hpp"
#include "TinyLlava_config.hpp"
#include "./tokenizer/include/tokenizers_cpp.h"
#include "vector"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/tokenizers_c.h"
#include "../include/tokenizers_cpp.h"

using namespace tokenizers;

void TinyLlava(){
    std::string begin_prompt = "A chat between a curious user and an artificial intelligence assistant. The assistant gives helpful, detailed, and polite answers to the user's questions. USER: ";
    std::string prompt; 
    std::string end_prompt = " ASSISTANT:";
    std::string image_path = "../test.jpg";
    chat(prompt, image_path);
    std::vector<int> begin_prompt_ids_vector = {32, 8537, 1022, 257, 11040, 2836, 290, 281, 11666, 4430, 8796, 13, 383, 8796, 3607, 7613, 11, 6496, 11, 290, 23507, 7429, 284, 262, 2836, 338, 2683, 13, 1294, 1137, 25, 220};
    std::vector<int> input_ids_vector = {2061, 318, 1306, 284, 262, 7647, 16430, 30, 1867, 318, 340, 1804, 30};
    std::vector<int> end_prompt_ids_vector = {24994, 8808, 8643, 25};
    prompt = begin_prompt + prompt + end_prompt;
    auto tokenizer = init_tokenizer();
    // int * input_ids;
    // std::vector<int> input_ids_vector;
    float preprocessed_image[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE];
    float preprocessed_image_1D[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE];
    int max_len;
    // float embedding[SLEN][HIDDEN_SIZE]; //MAX_LEN??
    // std::fill(&embedding[0][0], &embedding[0][0] + SLEN * HIDDEN_SIZE, 0.0f);
    float embedding[SLEN*HIDDEN_SIZE]; //MAX_LEN??
    std::fill(&embedding[0], &embedding[0] + SLEN * HIDDEN_SIZE, 0.0f);
    if (image_path.empty()){
        input_ids_vector = tokenizer->Encode(prompt); //INT 32
        // input_ids = input_ids_vector.data();
    }else{
        cv::Mat image;
        load_image(image, image_path);
        preprocess(preprocessed_image, image);
        memcpy(preprocessed_image_1D, preprocessed_image, NUM_CHANNELS * IMAGE_SIZE * IMAGE_SIZE * sizeof(float));
        input_ids_vector = tokenizer->Encode(prompt);
        std::vector<std::vector<float>> input_for_multimodel = prepare_input_for_multimodel(input_ids_vector, preprocessed_image_1D);
        for(int i = 0; i < input_for_multimodel.size(); i++){
            for(int j = 0; j < HIDDEN_SIZE; j++){
                embedding[i * HIDDEN_SIZE +  j] = input_for_multimodel[i][j];
            }
        }
        max_len = input_for_multimodel.size();
    }
    int output_ids[SLEN];
    PhiForCausalLM_forward(
        output_ids,
        embedding,
        max_len
    );
    std::vector<int> phi_token(output_ids, output_ids+SLEN);
    std::string output = tokenizer->Decode(phi_token);
}

void encode_images(
    float output[SLEN*HIDDEN_SIZE],
    float input[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE]
){  
    float siglip_output[INPUT_DIM*VISION_HIDDEN_SIZE] = {0};
    Siglip_Transformer_forward(siglip_output, input);
    float connector_input[SLEN*VISION_HIDDEN_SIZE] = {0};
    memcpy(connector_input, siglip_output, sizeof(float) * INPUT_DIM * VISION_HIDDEN_SIZE);
    Connector_forward(output, connector_input);
}

std::vector<std::vector<float>> prepare_input_for_multimodel(
    std::vector<int> input_ids,
    float image[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE]
){  
    float vision_tower_output[SLEN*HIDDEN_SIZE];
    std::pair<std::vector<std::vector<float>>, std::vector<std::vector<float>>> process_input_ids_output_pair;
    int image_token_idx = 0;

    process_input_ids_output_pair = process_input_ids(input_ids);
    std::vector<std::vector<float>> front_input_embeds = process_input_ids_output_pair.first;
    std::vector<std::vector<float>> back_input_embeds = process_input_ids_output_pair.second;
    //image_token_idx = process_input_ids_output_pair.second;

    encode_images(vision_tower_output, image);
    
    std::vector<std::vector<float>> output_embedding;
    for(const auto& vec : front_input_embeds){
        output_embedding.push_back(vec);
    }
    for(int j = 0; j < SLEN; j++){
        std::vector<float> image_feature(
            vision_tower_output + j * HIDDEN_SIZE,
            vision_tower_output + (j + 1) * HIDDEN_SIZE
        );
        output_embedding.push_back(image_feature);
        if(output_embedding.size() >= TOKENIZER_MODEL_MAX_LENGTH) 
            break;
    }
    for(const auto& vec : back_input_embeds){
        if(output_embedding.size() >= TOKENIZER_MODEL_MAX_LENGTH) 
            break;
        else
            output_embedding.push_back(vec);
    }

    return output_embedding;
}

std::pair<std::vector<std::vector<float>>, std::vector<std::vector<float>>> process_input_ids(const std::vector<int>& cur_input_ids) {
    std::vector<int> front;
    std::vector<int> back;
    auto i = cur_input_ids.begin();
    int image_token_idx = 0;
    while(i != cur_input_ids.end()) {
        if (*i == IMAGE_TOKEN_INDEX) {
            i++;
            break;
        }else{
            front.push_back(*i);
            i++;
            image_token_idx++;
        }
    }
    while(i != cur_input_ids.end()) {
        back.push_back(*i);
        i++;
    }

    std::vector<std::vector<float>> front_input_embeds;
    for (int i = 0; i < front.size(); i++) {
        std::vector<std::vector<float>> segment_embed;
        int token_id = front[i];
        std::vector<float> embedding(language_model_model_embed_tokens_weight[token_id], language_model_model_embed_tokens_weight[token_id] + HIDDEN_SIZE);
        front_input_embeds.push_back(embedding);
    }
    std::vector<std::vector<float>> back_input_embeds;
    for (int i = 0; i < back.size(); i++) {
        std::vector<std::vector<float>> segment_embed;
        int token_id = back[i];
        std::vector<float> embedding(language_model_model_embed_tokens_weight[token_id], language_model_model_embed_tokens_weight[token_id] + HIDDEN_SIZE);
        back_input_embeds.push_back(embedding);
    }
    std::pair<std::vector<std::vector<float>>, std::vector<std::vector<float>>> out_pair = {front_input_embeds, back_input_embeds};
    return out_pair;
}

int load_image(
    cv::Mat& img,
    std::string image_path
){
    // load image in BGR & HWC format => [Height, Width, Channels]
    img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Failed to load image from file: " << image_path << "\n";
        return 1;
    }
}

auto init_tokenizer(){
    std::string tokenizer_json_path = "D:/NTHU/大三下/專題/Project/modules/tokenizer/src/tokenizer.json";
    std::ifstream ifs(tokenizer_json_path);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string json_content = buffer.str();
    return tokenizers::Tokenizer::FromBlobJSON(json_content);
}//fix

void chat(std::string& prompt, std::string &image_paths){
    std::getline(std::cin, prompt);
}