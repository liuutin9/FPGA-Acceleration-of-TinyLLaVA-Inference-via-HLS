#include <string.h>
#include <hls_math.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include "Siglip_config.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

float vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight[INPUT_DIM*HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_embeddings_patch_embedding_weight[HIDDEN_SIZE*NUM_CHANNELS*PATCH_SIZE*PATCH_SIZE];
float vision_tower_vision_tower_vision_model_embeddings_patch_embedding_bias[HIDDEN_SIZE];

float vision_tower_vision_tower_vision_model_encoder_layers_layer_norm1_weight[HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_layer_norm1_bias[HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_layer_norm2_weight[HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_layer_norm2_bias[HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_q_proj_weight[HIDDEN_SIZE*HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_q_proj_bias[HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_k_proj_weight[HIDDEN_SIZE*HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_k_proj_bias[HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_v_proj_weight[HIDDEN_SIZE*HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_v_proj_bias[HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_out_proj_weight[HIDDEN_SIZE*HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_out_proj_bias[HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_head_mlp_fc1_weight[INTERMEDIATE_SIZE*HIDDEN_SIZE];
float vision_tower_vision_tower_vision_model_head_mlp_fc1_bias[INTERMEDIATE_SIZE];
float vision_tower_vision_tower_vision_model_head_mlp_fc2_weight[HIDDEN_SIZE*INTERMEDIATE_SIZE];
float vision_tower_vision_tower_vision_model_head_mlp_fc2_bias[HIDDEN_SIZE];

float output[INPUT_DIM*HIDDEN_SIZE];
float input[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE];

float embedded_vector[INPUT_DIM*HIDDEN_SIZE];
float patched_pixel_values[HIDDEN_SIZE*num_patch_x*num_patch_y];
float flatten_patched_pixel_values[(num_patch_x * num_patch_y)*HIDDEN_SIZE];

float hidden_state[INPUT_DIM*HIDDEN_SIZE];
float q_proj[SLEN*(NUM_ATTENTION_HEADS*HEAD_DIM)];
float k_proj[SLEN*(NUM_ATTENTION_HEADS*HEAD_DIM)];
float v_proj[SLEN*(NUM_ATTENTION_HEADS*HEAD_DIM)];
float reshaped_q_proj[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
float reshaped_k_proj[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
float reshaped_v_proj[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
float query[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
float key[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
float value[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
float attn_scores[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
// float attn_out[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
float reshaped_attn_out[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];

//linear
float weight_transpose1[HIDDEN_SIZE*INTERMEDIATE_SIZE];
float weight_transpose2[HIDDEN_SIZE*NUM_ATTENTION_HEADS * HEAD_DIM];
float weight_transpose3[HIDDEN_SIZE*HIDDEN_SIZE];

//eager
float scaled_attn_weights[SLEN*SLEN];
float softmax_attn_weights[SLEN*SLEN];
float eager_attn_scores[SLEN*HEAD_DIM];

//MLP
float linear_out[SLEN*INTERMEDIATE_SIZE];
float gelu_out[SLEN*INTERMEDIATE_SIZE];

float residual[INPUT_DIM*HIDDEN_SIZE];
float layer_norm_out[INPUT_DIM*HIDDEN_SIZE];
float attn_out[INPUT_DIM*HIDDEN_SIZE];
float mlp_out[INPUT_DIM*HIDDEN_SIZE];

static float float16_to_float32(uint16_t h) {
    uint16_t sign = (h & 0x8000) >> 15;
    uint16_t exp  = (h & 0x7C00) >> 10;
    uint16_t frac =  h & 0x03FF;

    if (exp == 0) {
        // subnormal or zero
        if (frac == 0) {
            return sign ? -0.0f : 0.0f;
        } else {
            // subnormal number
            return (sign ? -1.0f : 1.0f) *
                   std::ldexp(static_cast<float>(frac), -24); // 2^(-14 - 10)
        }
    } else if (exp == 0x1F) {
        // Inf or NaN
        if (frac == 0) {
            return sign ? -INFINITY : INFINITY;
        } else {
            return NAN;
        }
    } else {
        // normal number
        return (sign ? -1.0f : 1.0f) *
               std::ldexp(static_cast<float>(frac) / 1024.0f + 1.0f, exp - 15);
    }
}

bool load_weight(const std::string& weight_name, float* target_array, size_t array_size) {
    //"D:/NTHU/大三下/專題/Project/Weight/model_bins/siglip/"
    // std::string filename = "D:/NTHU/大三下/專題/Project/Weight/model_bins/siglip/" + weight_name + ".bin";
    std::string filename = "../../../Weight/model_bins1/" + weight_name + ".bin";

    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return false;
    }

    fin.seekg(0, std::ios::end);
    size_t file_size = fin.tellg();
    fin.seekg(0, std::ios::beg);

    if (file_size != array_size * sizeof(uint16_t)) {
        std::cerr << "Error: file size mismatch for " << filename
                  << " (expected " << array_size * sizeof(uint16_t)
                  << " bytes, got " << file_size << " bytes)" << std::endl;
        return false;
    }

    // 暫存 float16 (uint16_t) 資料
    std::vector<uint16_t> half_data(array_size);
    fin.read(reinterpret_cast<char*>(half_data.data()), file_size);
    fin.close();

    // 轉換成 float32
    for (size_t i = 0; i < array_size; ++i) {
        target_array[i] = float16_to_float32(half_data[i]);
    }

    return true;
}

void Patch_Embedding(
    float patch_embeds[HIDDEN_SIZE*NUM_PATCH*NUM_PATCH],
    float pixel_values[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE]
){
    Conv2D(patch_embeds, pixel_values);
    std::cout << " - patch_embeds" << std::endl;
    for (int i = 0; i < 5; i++) std::cout << patch_embeds[i] << " ";
    std::cout << std::endl << std::endl;
}

void flatten_and_transpose(
    float output[(NUM_PATCH*NUM_PATCH)*HIDDEN_SIZE],
    float input[HIDDEN_SIZE*NUM_PATCH*NUM_PATCH]
) {
    for (int i = 0; i < NUM_PATCH; i++) {
        for (int j = 0; j < NUM_PATCH; j++) {
            int patch_idx = i * NUM_PATCH + j;
            for (int c = 0; c < HIDDEN_SIZE; c++) {
                output[patch_idx*HIDDEN_SIZE+c] = input[c*(NUM_PATCH*NUM_PATCH) + i*NUM_PATCH + j];
            }
        }
    }
    std::cout << " - flatten_patched_pixel_values" << std::endl;
    for (int i = 0; i < 5; i++) std::cout << output[i] << " ";
    std::cout << std::endl << std::endl;
}

void Pos_Embedding(
    float embedded_vector[INPUT_DIM*HIDDEN_SIZE],
    float flatten_patched_pixel_values[INPUT_DIM*HIDDEN_SIZE]
) {
    for (int i = 0; i < NUM_PATCH; i++) {
        for (int j = 0; j < NUM_PATCH; j++) {
            int patch_id = i * NUM_PATCH + j;
            for (int c = 0; c < HIDDEN_SIZE; c++) {
                embedded_vector[patch_id*HIDDEN_SIZE+c] = (float)flatten_patched_pixel_values[patch_id*HIDDEN_SIZE+c]
                + vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight[patch_id*HIDDEN_SIZE+c];
            }
        }
    }
    std::cout << " - embedded_vector" << std::endl;
    for (int i = 0; i < 5; i++) std::cout << embedded_vector[i] << " ";
    std::cout << std::endl << std::endl;
}

void Conv2D(
    float output[HIDDEN_SIZE*NUM_PATCH*NUM_PATCH],         // out_channel * out_height * out_width
    float pixel_values[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE] // in_channel * in_height * in_width
){     
    for(int k = 0; k < HIDDEN_SIZE; k++){
        for(int i = 0; i < NUM_PATCH; i++){
            for(int j = 0; j < NUM_PATCH; j++){
                output[k * (NUM_PATCH * NUM_PATCH) + i * NUM_PATCH + j] = mult_with_kernel(
                    pixel_values, 
                    vision_tower_vision_tower_vision_model_embeddings_patch_embedding_weight + k*NUM_CHANNELS*PATCH_SIZE*PATCH_SIZE, 
                    i * PATCH_SIZE, 
                    j * PATCH_SIZE
                ) + vision_tower_vision_tower_vision_model_embeddings_patch_embedding_bias[k];
            }
        }
    }
}

float mult_with_kernel(
    float input[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE], 
    float kernel[NUM_CHANNELS*PATCH_SIZE*PATCH_SIZE], 
    int kernel_x, 
    int kernel_y
){
    float result = 0;
    for(int c = 0; c < NUM_CHANNELS; c++){
        for(int i = 0; i < PATCH_SIZE; i++){
            for(int j = 0; j < PATCH_SIZE; j++){
                result += input[c * (IMAGE_SIZE * IMAGE_SIZE) + (kernel_x + i) * IMAGE_SIZE + (kernel_y + j)] * kernel[c * (PATCH_SIZE * PATCH_SIZE) + i * PATCH_SIZE + j];
            }
        }
    }
    return result;
}

void Embedding(
    float embedded_vector[INPUT_DIM*HIDDEN_SIZE],
    float pixel_values[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE]
){  
    // float patched_pixel_values[HIDDEN_SIZE*num_patch_x*num_patch_y];
    // float flatten_patched_pixel_values[(num_patch_x * num_patch_y)*HIDDEN_SIZE];
    //std::cout << "input_dim: " << INPUT_DIM << ", num_patch ** 2: " << NUM_PATCH * NUM_PATCH << std::endl;
    Patch_Embedding(patched_pixel_values, pixel_values);
    flatten_and_transpose(flatten_patched_pixel_values, patched_pixel_values);
    Pos_Embedding(embedded_vector, flatten_patched_pixel_values);
}

////////////////////////////////////////////////////////////////////////////
float gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f;
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = std::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}

template <int M, int N, class T>
//void transpose(T out[N * M],const T in[M * N]) {
void transpose(T* out,const T* in) {
    // #pragma HLS INTERFACE port=return mode=s_axilite
    // #pragma HLS INTERFACE port=out mode=bram
    // #pragma HLS INTERFACE port=in mode=bram
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[j * M + i] = in[i * N + j];
        }
    }
}

template <int in_features, int out_features, int n_samples>
void linear1(float out[n_samples*out_features], float in[n_samples*in_features], float weight[out_features*in_features], float bias[out_features]) {
    // float weight_transpose1[in_features*out_features];
    transpose<out_features, in_features>(weight_transpose1, weight);
    matmul<n_samples, in_features, out_features>(out, in, weight_transpose1);
    for (int i = 0; i < n_samples; i++) {
        for (int j = 0; j < out_features; j++) {
            out[i*out_features + j] += bias[j];
        }
    }
}

template <int in_features, int out_features, int n_samples>
void linear2(float out[n_samples*out_features], float in[n_samples*in_features], float weight[out_features*in_features], float bias[out_features]) {
    //float weight_transpose2[in_features*out_features];
    transpose<out_features, in_features>(weight_transpose2, weight);
    matmul<n_samples, in_features, out_features>(out, in, weight_transpose2);
    for (int i = 0; i < n_samples; i++) {
        for (int j = 0; j < out_features; j++) {
            out[i*out_features + j] += bias[j];
        }
    }
}

template <int in_features, int out_features, int n_samples>
void linear3(float out[n_samples*out_features], float in[n_samples*in_features], float weight[out_features*in_features], float bias[out_features]) {
    //float weight_transpose3[in_features*out_features];
    transpose<out_features, in_features>(weight_transpose3, weight);
    matmul<n_samples, in_features, out_features>(out, in, weight_transpose3);
    for (int i = 0; i < n_samples; i++) {
        for (int j = 0; j < out_features; j++) {
            out[i*out_features + j] += bias[j];
        }
    }
}

template <int N, class T>
void maxval_1D(T* max_val, T in[N]) {
    // #pragma HLS INTERFACE port=return mode=s_axilite bundle=CTRL
    // #pragma HLS INTERFACE port=max_val mode=s_axilite bundle=CTRL
    // #pragma HLS INTERFACE port=in mode=bram
    
    *max_val = in[0];
    for (int i = 1; i < N; i++) {
        if (in[i] > *max_val) {
            *max_val = in[i];
        }
    }
}

template <int M, int N>
void softmax(float out[M*N], float in[M*N]) {
    for (int i = 0; i < M; i++) {
        float max_val = in[i*N];
        maxval_1D<N, float>(&max_val, in + i*N);
        float sum_exp = 0;
        for (int j = 0; j < N; j++) {
            out[i*N + j] = std::exp(in[i*N + j] - max_val);
            sum_exp += out[i*N + j];
        }
        for (int j = 0; j < N; j++) {
            out[i*N + j] /= sum_exp;
        }
    }
}

template <int M, int K, int N>
void matmul(float out[M*N], float in1[M*K], float in2[K*N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0;
            for (int k = 0; k < K; k++) {
                #pragma HLS UNROLL factor=2
                sum += in1[i*K + k] * in2[k*N + j];
            }
            out[i*N + j] = sum;
        }
    }
}

void SiglipMLP(
    float out[SLEN*HIDDEN_SIZE], 
    float hidden_state[SLEN*HIDDEN_SIZE],
    int layer_id
) { 
    // TODO: load weights by layer_id

    // float linear_out[SLEN*INTERMEDIATE_SIZE];   
    linear1<HIDDEN_SIZE, INTERMEDIATE_SIZE, SLEN>(
        linear_out, hidden_state, 
        vision_tower_vision_tower_vision_model_head_mlp_fc1_weight, vision_tower_vision_tower_vision_model_head_mlp_fc1_bias
    );

    // float gelu_out[SLEN*INTERMEDIATE_SIZE];
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
            gelu_out[i*INTERMEDIATE_SIZE + j] = gelu(linear_out[i*INTERMEDIATE_SIZE + j]);
        }
    }

    linear1<INTERMEDIATE_SIZE, HIDDEN_SIZE, SLEN>(
        out, gelu_out,
        vision_tower_vision_tower_vision_model_head_mlp_fc2_weight, vision_tower_vision_tower_vision_model_head_mlp_fc2_bias
    );
}

void matmul_with_scale_no_transpose(
    float out[SLEN*SLEN], 
    float in1[SLEN*HEAD_DIM],
    float in2[SLEN*HEAD_DIM],
    float scaling
) {
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < SLEN; j++) {
            float sum = 0;
            for (int k = 0; k < HEAD_DIM; k++) {
                sum += in1[i*HEAD_DIM + k] * in2[j*HEAD_DIM + k];
            }
            out[i*SLEN + j] = sum * scaling;
        }
    }
}

void eager_attention_per_head(
    float out[SLEN*HEAD_DIM],
    float query[SLEN*HEAD_DIM],
    float key[SLEN*HEAD_DIM],
    float value[SLEN*HEAD_DIM],
    float scaling
) {   
    // float scaled_attn_weights[SLEN*SLEN];
    matmul_with_scale_no_transpose(scaled_attn_weights, query, key, scaling);
    
    // float softmax_attn_weights[SLEN*SLEN];
    softmax<SLEN, SLEN>(softmax_attn_weights, scaled_attn_weights);

    // float attn_scores[SLEN*HEAD_DIM];
    matmul<SLEN, SLEN, HEAD_DIM>(out, softmax_attn_weights, value);
}

void SiglipAttention(
    float out[SLEN*HIDDEN_SIZE],
    float hidden_states[SLEN*HIDDEN_SIZE],
    int layer_id
) { 
    //std::cout << "a" << std::endl;
    // TODO: load weights by layer_id

    // Project Q, K, V
    // float q_proj[SLEN*(NUM_ATTENTION_HEADS*HEAD_DIM)];
    // float k_proj[SLEN*(NUM_ATTENTION_HEADS*HEAD_DIM)];
    // float v_proj[SLEN*(NUM_ATTENTION_HEADS*HEAD_DIM)];
    linear2<HIDDEN_SIZE, NUM_ATTENTION_HEADS * HEAD_DIM, SLEN>(q_proj, hidden_states, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_q_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_q_proj_bias);
    linear2<HIDDEN_SIZE, NUM_ATTENTION_HEADS * HEAD_DIM, SLEN>(k_proj, hidden_states, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_k_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_k_proj_bias);
    linear2<HIDDEN_SIZE, NUM_ATTENTION_HEADS * HEAD_DIM, SLEN>(v_proj, hidden_states, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_v_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_v_proj_bias);
    //std::cout << "b" << std::endl;
    // Reshape Q, K, V to (source_length, num_heads, head_dim) 
    // float reshaped_q_proj[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
    // float reshaped_k_proj[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
    // float reshaped_v_proj[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
    memcpy(reshaped_q_proj, q_proj, sizeof(float) * SLEN * NUM_ATTENTION_HEADS * HEAD_DIM);
    memcpy(reshaped_k_proj, k_proj, sizeof(float) * SLEN * NUM_ATTENTION_HEADS * HEAD_DIM);
    memcpy(reshaped_v_proj, v_proj, sizeof(float) * SLEN * NUM_ATTENTION_HEADS * HEAD_DIM);
    //std::cout << "c" << std::endl;
    // Transpose to (num_heads, source_length, head_dim)
    // float query[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
    // float key[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
    // float value[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
    for (int i = 0; i < NUM_ATTENTION_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < HEAD_DIM; k++) {
                query[i*SLEN*HEAD_DIM + j*HEAD_DIM + k] = reshaped_q_proj[j*NUM_ATTENTION_HEADS*HEAD_DIM + i*HEAD_DIM + k];
                key[i*SLEN*HEAD_DIM + j*HEAD_DIM + k] = reshaped_k_proj[j*NUM_ATTENTION_HEADS*HEAD_DIM + i*HEAD_DIM + k];
                value[i*SLEN*HEAD_DIM + j*HEAD_DIM + k] = reshaped_v_proj[j*NUM_ATTENTION_HEADS*HEAD_DIM + i*HEAD_DIM + k];
            }
        }
    }
    //std::cout << "d" << std::endl;
    // TODO: Compute attention => 考慮合併(避免讀寫)/平行(多head同時)
    float scaling = 1 / std::sqrt(HEAD_DIM);
    // float attn_scores[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
    for (int h = 0; h < NUM_ATTENTION_HEADS; h++) {
        eager_attention_per_head(attn_scores+h*SLEN*HEAD_DIM, query+h*SLEN*HEAD_DIM, key+h*SLEN*HEAD_DIM, value+h*SLEN*HEAD_DIM, scaling);
    }
    //std::cout << "e" << std::endl;
    // Transpo  se
    // float attn_out[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
    for (int s = 0; s < SLEN; s++) {
        for (int h = 0; h < NUM_ATTENTION_HEADS; h++) {
            for (int d = 0; d < HEAD_DIM; d++) {
                attn_out[s*NUM_ATTENTION_HEADS*HEAD_DIM + h*HEAD_DIM + d] = attn_scores[h*SLEN*HEAD_DIM + s*HEAD_DIM + d];
            }
        }
    }
    //std::cout << "f" << std::endl;
    // Reshape
    // float reshaped_attn_out[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
    memcpy(reshaped_attn_out, attn_out, sizeof(float) * SLEN * NUM_ATTENTION_HEADS * HEAD_DIM);
    
    // Project the attention output
    linear3<HIDDEN_SIZE, HIDDEN_SIZE, SLEN>(
        out, reshaped_attn_out,
        vision_tower_vision_tower_vision_model_encoder_layers_self_attn_out_proj_weight, 
        vision_tower_vision_tower_vision_model_encoder_layers_self_attn_out_proj_bias
    );
    //std::cout << "h" << std::endl;
}

void Siglip_layer_norm(
    float out[INPUT_DIM*HIDDEN_SIZE],
    float in[INPUT_DIM*HIDDEN_SIZE],
    float eps,
    float weight[HIDDEN_SIZE],
    float bias[HIDDEN_SIZE]
) {
    for (int i = 0; i < INPUT_DIM; i++) {
        float mean = 0.0;
        float variance = 0.0;

        // Step 1: 計算均值
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            mean += in[i*HIDDEN_SIZE+j];
        }
        mean /= HIDDEN_SIZE;

        // Step 2: 計算變異數
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            float diff = in[i*HIDDEN_SIZE+j] - mean;
            variance += diff * diff;
        }
        variance /= HIDDEN_SIZE;

        // Step 3: 標準化
        float stddev_inv = 1.0 / std::sqrt(variance + eps);
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            out[i*HIDDEN_SIZE+j] = (in[i*HIDDEN_SIZE+j] - mean) * stddev_inv * weight[j] + bias[j];
        }
    }
}

void SiglipEncoderLayer(
    float output[INPUT_DIM*HIDDEN_SIZE], 
    float hidden_state[INPUT_DIM*HIDDEN_SIZE],
    int layer_id
) {
    //std::cout << 1 << std::endl;
    // TODO: load weights by layer_id
    memcpy(residual, hidden_state, sizeof(float) * INPUT_DIM * HIDDEN_SIZE);
    //std::cout << 2 << std::endl;
    Siglip_layer_norm(
        layer_norm_out, hidden_state, LAYER_NORM_EPS,
        vision_tower_vision_tower_vision_model_encoder_layers_layer_norm1_weight,
        vision_tower_vision_tower_vision_model_encoder_layers_layer_norm1_bias
    );
    //std::cout << 3 << std::endl;
    SiglipAttention(attn_out, layer_norm_out, layer_id);
    //std::cout << 4 << std::endl;
    for (int i = 0; i < INPUT_DIM; i++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            hidden_state[i*HIDDEN_SIZE+j] = residual[i*HIDDEN_SIZE+j] + attn_out[i*HIDDEN_SIZE+j];
        }
    }
    //std::cout << 5 << std::endl;
    memcpy(residual, hidden_state, sizeof(float) * INPUT_DIM * HIDDEN_SIZE);
    //std::cout << 6 << std::endl;
    Siglip_layer_norm(
        layer_norm_out, hidden_state, LAYER_NORM_EPS,
        vision_tower_vision_tower_vision_model_encoder_layers_layer_norm2_weight,
        vision_tower_vision_tower_vision_model_encoder_layers_layer_norm2_bias
    );  
    //std::cout << 7 << std::endl;
    SiglipMLP(mlp_out, layer_norm_out, layer_id);
    //std::cout << 8 << std::endl;
    for (int i = 0; i < INPUT_DIM; i++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            output[i*HIDDEN_SIZE+j] = residual[i*HIDDEN_SIZE+j] + mlp_out[i*HIDDEN_SIZE+j];
        }
    }
    //std::cout << 9 << std::endl;
}


void load_siglip_encoder_weight(int layer){
    std::string layer_norm1_bias = std::to_string(layer) + ".layer_norm1.bias";
    std::string layer_norm1_weight = std::to_string(layer) + ".layer_norm1.weight";
    std::string layer_norm2_bias = std::to_string(layer) + ".layer_norm2.bias";
    std::string layer_norm2_weight = std::to_string(layer) + ".layer_norm2.weight";
    std::string mlp_fc1_bias = std::to_string(layer) + ".mlp.fc1.bias";
    std::string mlp_fc1_weight = std::to_string(layer) + ".mlp.fc1.weight";
    std::string mlp_fc2_bias = std::to_string(layer) + ".mlp.fc2.bias";
    std::string mlp_fc2_weight = std::to_string(layer) + ".mlp.fc2.weight";
    std::string self_attn_k_proj_bias = std::to_string(layer) + ".self_attn.k_proj.bias";
    std::string self_attn_k_proj_weight = std::to_string(layer) + ".self_attn.k_proj.weight";
    std::string self_attn_out_proj_bias = std::to_string(layer) + ".self_attn.out_proj.bias";
    std::string self_attn_out_proj_weight = std::to_string(layer) + ".self_attn.out_proj.weight";
    std::string self_attn_q_proj_bias = std::to_string(layer) + ".self_attn.q_proj.bias";
    std::string self_attn_q_proj_weight = std::to_string(layer) + ".self_attn.q_proj.weight";
    std::string self_attn_v_proj_bias = std::to_string(layer) + ".self_attn.v_proj.bias";
    std::string self_attn_v_proj_weight = std::to_string(layer) + ".self_attn.v_proj.weight";
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + layer_norm1_bias, vision_tower_vision_tower_vision_model_encoder_layers_layer_norm1_bias , HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + layer_norm1_weight, vision_tower_vision_tower_vision_model_encoder_layers_layer_norm1_weight , HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + layer_norm2_bias, vision_tower_vision_tower_vision_model_encoder_layers_layer_norm2_bias , HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + layer_norm2_weight, vision_tower_vision_tower_vision_model_encoder_layers_layer_norm2_weight , HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + self_attn_q_proj_bias, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_q_proj_bias , HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + self_attn_q_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_q_proj_weight , HIDDEN_SIZE * HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + self_attn_k_proj_bias, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_k_proj_bias , HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + self_attn_k_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_k_proj_weight , HIDDEN_SIZE * HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + self_attn_v_proj_bias, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_v_proj_bias , HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + self_attn_v_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_v_proj_weight , HIDDEN_SIZE * HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + self_attn_out_proj_bias, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_out_proj_bias , HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + self_attn_out_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_self_attn_out_proj_weight , HIDDEN_SIZE * HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + mlp_fc1_bias, vision_tower_vision_tower_vision_model_head_mlp_fc1_bias , INTERMEDIATE_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + mlp_fc1_weight, vision_tower_vision_tower_vision_model_head_mlp_fc1_weight , INTERMEDIATE_SIZE * HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + mlp_fc2_bias, vision_tower_vision_tower_vision_model_head_mlp_fc2_bias , HIDDEN_SIZE);
    load_weight("vision_tower._vision_tower.vision_model.encoder.layers." + mlp_fc2_weight, vision_tower_vision_tower_vision_model_head_mlp_fc2_weight , HIDDEN_SIZE * INTERMEDIATE_SIZE);
}


void Siglip_Encoder(
    float encoder_output[INPUT_DIM*HIDDEN_SIZE],
    float embedded_vector[INPUT_DIM*HIDDEN_SIZE]
) {
    std::cout << "start encoder" << std::endl;
    // copy input to working buffer
    for (int layer = 0; layer < NUM_HIDDEN_LAYERS - 1; layer++) {
        memcpy(hidden_state, embedded_vector, sizeof(float) * INPUT_DIM * HIDDEN_SIZE);
        std::cout << "load layer " << layer << std :: endl;
        load_siglip_encoder_weight(layer);
        std::cout << "finish load layer " << layer << std :: endl;
        SiglipEncoderLayer(embedded_vector, hidden_state, layer);
        std::cout << "finish layer " << layer << std :: endl;
        // Output
        std::cout << "First 10 values of layer" << layer << std::endl;
        for (int i = 0; i < 10; i++) std::cout << embedded_vector[i] << " ";
        std::cout << std::endl;
    }

    // write final output
    memcpy(encoder_output, embedded_vector, sizeof(float) * INPUT_DIM * HIDDEN_SIZE);
}

////////////////////////////////////////////////////////////////////////////
void Siglip_Transformer_forward(
    float output[INPUT_DIM*HIDDEN_SIZE],
    float input[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE]
) { 
    //float embedded_vector[INPUT_DIM*HIDDEN_SIZE];
    // Step 1: Patch + Position Embedding
    Embedding(embedded_vector, input);

    // // Step 2: Encoder
    //memcpy(output, embedded_vector, sizeof(float) * INPUT_DIM * HIDDEN_SIZE);
    std::cout << "finish embedding" << std::endl;
    Siglip_Encoder(output, embedded_vector);
}