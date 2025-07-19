#include<string.h>
#include "./Siglip/Siglip_config.hpp"
#include "./phi-2/phi-2_config.hpp"
#include "./connector/connector_config.hpp"
#include "./utils/transformer.hpp"
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
    char prompt[MAX_LEN]; 
    std::string image_path = "D:/NTHU/大三下/專題/Project/test.jpg";
    std::vector<std::string> image_paths;
    chat(prompt, image_paths);
    auto tokenizer = init_tokenizer();
    int * input_ids;
    std::vector<int> input_ids_vector;
    float preprocessed_images[MAX_NUM][NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE];
    const int num_image = image_paths.size();
    int max_len;
    int * output_ids;
    if (num_image == 0){
        input_ids_vector = tokenizer->Encode(prompt);
        input_ids = input_ids_vector.data();
        //return input_ids, position_ids, attention_mask, past_key_values, None, labels
    }else{
        for(int i = 0; i < num_image; i++){
            cv::Mat image;
            load_image(image, image_path);
            float preprocessed_image[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE];
            preprocess(preprocessed_image, image);
            tokenizer_image_token(input_ids_vector, prompt, &tokenizer);
            input_ids = input_ids_vector.data();
              
            memcpy(preprocessed_images[i], preprocessed_image, NUM_CHANNELS * IMAGE_SIZE * IMAGE_SIZE * sizeof(float));
        }
        std::pair<int *, int> pair_out = prepare_input_for_multimodel(input_ids_vector, preprocessed_images, num_image);
        output_ids = pair_out.first;
        max_len = pair_out.second;
    }

    PhiForCausalLM_forward(
        output_ids,
        input_ids,
        max_len
    );
    std::vector<int> phi_token(output_ids, output_ids+SLEN);
    std::string output = tokenizer->Decode(phi_token);
}

void encode_images(
    float output[SLEN][HIDDEN_SIZE],
    float input[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
){  
    float siglip_output[INPUT_DIM][VISION_HIDDEN_SIZE] = {0};
    Siglip_Transformer_forward(siglip_output, input);
    float connector_input[SLEN][VISION_HIDDEN_SIZE] = {0};
    memcpy(connector_input, siglip_output, sizeof(float) * INPUT_DIM * VISION_HIDDEN_SIZE);
    Connector_forward(output, connector_input);
}

std::pair<int *, int> prepare_input_for_multimodel(
    std::vector<int> input_ids,
    float images[MAX_NUM][NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE],
    const int num_images
){  
    std::vector<int> output_embedding;
    //std::vector<int> cur_input_ids(*input_ids);
    std::vector<std::vector<std::vector<float>>> input_embeds_split;
    float vision_tower_outputs[num_images][SLEN][HIDDEN_SIZE];

    input_embeds_split = process_input_ids(input_ids);
    // float embeds_split[num_images + 1][MAX_LEN][HIDDEN_SIZE];
    for(int i = 0; i < num_images; i++){
        encode_images(vision_tower_outputs[i], images[i]);
    }

    int max_len = 0;
    for(int i = 0; i < num_images + 1; i++){
        if(max_len < input_embeds_split[i].size()){
            max_len = input_embeds_split[i].size();
        }
    }

    for(int i = 0; i < num_images + 1; i++){
        int pad_num = max_len - input_embeds_split[i].size();
        for(int t = 0 ; t < pad_num; t++){
            input_embeds_split[i].push_back(std::vector<float>(HIDDEN_SIZE, 0.0f));
        }
    }

    for(int i = 0; i < num_images + 1; i++){
        for(const auto& vec : input_embeds_split[i]){
            output_embedding.insert(output_embedding.end(), vec.begin(), vec.end());
        }
        if(i != num_images){
            for(int j = 0; j < SLEN; j++){
                for(int k = 0; k < HIDDEN_SIZE; k++){
                    output_embedding.push_back(vision_tower_outputs[i][j][k]);
                }
            }
        }
    }
            
    std::pair<int *, int> out = {output_embedding.data(), max_len};
    //memcpy(output_embedding, input_ids, TOKENIZER_MODEL_MAX_LENGTH);
    return out;
}

// std::vector<int> cur_input_ids = {123, 456, IMAGE_TOKEN_INDEX, 789, 321, IMAGE_TOKEN_INDEX, 999, 888};

// 輸出：不包含 image token 的文字段落，每段是一個 embedding 序列
// std::vector<std::vector<std::vector<float>>> input_embeds_split;

std::vector<std::vector<std::vector<float>>> process_input_ids(const std::vector<int>& cur_input_ids) {
    std::vector<std::vector<std::vector<float>>> input_embeds_split;
    std::vector<int> image_token_indices = {-1};

    // 找到所有 image token 的 index
    for (int i = 0; i < cur_input_ids.size(); ++i) {
        if (cur_input_ids[i] == IMAGE_TOKEN_INDEX) {
            image_token_indices.push_back(i);
        }
    }
    image_token_indices.push_back(cur_input_ids.size());

    // 對每段非 image 區段進行處理
    for (int i = 0; i < image_token_indices.size() - 1; ++i) {
        int start = image_token_indices[i] + 1;
        int end = image_token_indices[i + 1];

        if (start >= end) continue;  // 空段落跳過

        std::vector<std::vector<float>> segment_embed;

        for (int j = start; j < end; ++j) {
            int token_id = cur_input_ids[j];

            // // 安全檢查
            // if (token_id < 0 || token_id >= VOCAB_SIZE) {
            //     std::cerr << "Invalid token ID: " << token_id << std::endl;
            //     continue;
            // }

            // // lookup 嵌入向量
            std::vector<float> embedding(HIDDEN_SIZE);
            for (int k = 0; k < HIDDEN_SIZE; ++k) {
                embedding[k] = language_model_model_embed_tokens_weight[token_id][k];
            }
            segment_embed.push_back(embedding);
        }

        input_embeds_split.push_back(segment_embed);
    }
    
    return input_embeds_split;
}

int load_image(
    cv::Mat img,
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

void tokenizer_image_token(
    std::vector<int>& input_ids,
    char prompt[MAX_LEN],
    auto tokenizer
){
    char prompt_chunks[MAX_LEN][TOKEN_LEN];
    int * len;
    prompt_split(prompt_chunks, len, prompt, "<image>");
    std::vector<std::vector<int>> tokenize_prompt_chunks;
    for(int i = 0; i < MAX_LEN; i++) {
        if (strlen(prompt_chunks[i]) == 0) {
            break; // 停止處理空的 chunk
        }
        std::vector<int> chunk_ids = *tokenizer->Encode(prompt_chunks[i]);
        tokenize_prompt_chunks.push_back(chunk_ids);
    }
    int offset = 0;
    //bos_token??
    //if...
    std::vector<int> sep = {IMAGE_TOKEN_INDEX};
    // for(int i = 0; i < MAX_LEN; i++) {
    // //    sep.insert(IMAGE_TOKEN_INDEX);
    //     sep.push_back(IMAGE_TOKEN_INDEX);
    // }

    std::vector<std::vector<int>> ids = insert_separator(tokenize_prompt_chunks, sep);
    for(int i = 0; i < MAX_LEN; i++) {
       input_ids.insert(input_ids.end(), ids.begin() + offset, ids.end());
    }
}

void prompt_split(
    char prompt_chunks[MAX_LEN][TOKEN_LEN],
    int * len,
    char prompt[MAX_LEN],
    const char split[MAX_LEN]
){
    int idx = 0;
    char* token = strtok(prompt, split);
    while (token != nullptr && idx < MAX_LEN) {
        strncpy(prompt_chunks[idx], token, MAX_LEN - 1);
        prompt_chunks[idx][MAX_LEN - 1] = '\0'; // 確保字串結尾
        idx++;
        token = strtok(nullptr, split);
    }
    *len = idx;
}

std::vector<std::vector<int>> insert_separator(const std::vector<std::vector<int>>& X, const std::vector<int>& sep) {
    std::vector<std::vector<int>> result;

    for (int i = 0; i < X.size(); ++i) {
        // 插入原始元素
        result.push_back(X[i]);

        // 插入 separator（除了最後一組之後不插入）
        if (i != X.size() - 1) {
            result.push_back(sep);
        }
    }

    return result;
}

void chat(char prompt[MAX_LEN], std::vector<std::string> image_paths){
    // char input[MAX_LEN];
    // std :: cin >> input;
    // strcpy(prompt, DEFAULT_IMAGE_TOKEN + '\n');
    // strcpy(prompt + 8, input);
    std::string input;
    std::getline(std::cin, input);
    strcpy(prompt, "<image>\n");
    strcat(prompt, input.c_str());
}