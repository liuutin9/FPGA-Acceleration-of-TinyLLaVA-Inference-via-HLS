#include <string.h>
// #include <hls_math.h>
// #include <ap_fixed.h>
// #include <ap_int.h>
#include "./phi-2_config.hpp"
//#include "../../Siglip/Siglip_config.hpp"
//#include "../../connector/connector_config.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
//#include <cstdint>
#include <cmath>

#define CONNECTOR_HIDDEN_SIZE 2560
#define INPUT_DIM 729
#define IMAGE_TOKEN_INDEX -200
#define MAX_NUM 10
#define NUM_CHANNELS 3
#define IMAGE_SIZE 384


// "language_model.lm_head.bias"
// "language_model.lm_head.weight"
// "language_model.model.embed_tokens.weight"
// "language_model.model.final_layernorm.bias"
// "language_model.model.final_layernorm.weight"
float language_model_model_embed_tokens_weight[VOCAB_SIZE * HIDDEN_SIZE];
float language_model_model_final_layernorm_weight[HIDDEN_SIZE];
float language_model_model_final_layernorm_bias[HIDDEN_SIZE];
float language_model_model_lm_head_weight[VOCAB_SIZE * HIDDEN_SIZE];
float language_model_model_lm_head_bias[VOCAB_SIZE];

float language_model_model_layers_0_input_layernorm_weight[HIDDEN_SIZE];
float language_model_model_layers_0_input_layernorm_bias[HIDDEN_SIZE];
float language_model_model_layers_0_mlp_fc1_weight[INTERMEDIATE_SIZE * HIDDEN_SIZE];
float language_model_model_layers_0_mlp_fc1_bias[INTERMEDIATE_SIZE];
float language_model_model_layers_0_mlp_fc2_weight[HIDDEN_SIZE * INTERMEDIATE_SIZE];
float language_model_model_layers_0_mlp_fc2_bias[HIDDEN_SIZE];
float language_model_model_layers_0_self_attn_dense_weight[HIDDEN_SIZE * HIDDEN_SIZE];
float language_model_model_layers_0_self_attn_dense_bias[HIDDEN_SIZE];
float language_model_model_layers_0_self_attn_q_proj_weight[HIDDEN_SIZE * HIDDEN_SIZE];
float language_model_model_layers_0_self_attn_q_proj_bias[HIDDEN_SIZE];
float language_model_model_layers_0_self_attn_k_proj_weight[HIDDEN_SIZE * HIDDEN_SIZE];
float language_model_model_layers_0_self_attn_k_proj_bias[HIDDEN_SIZE];
float language_model_model_layers_0_self_attn_v_proj_weight[HIDDEN_SIZE * HIDDEN_SIZE];
float language_model_model_layers_0_self_attn_v_proj_bias[HIDDEN_SIZE];

float rotate_half_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
float rotate_half_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
float qkt[SLEN];
float qkt_softmax[SLEN];
float linear_q[NUM_KEY_VALUE_HEADS * HEAD_DIM];
float linear_k[NUM_KEY_VALUE_HEADS * HEAD_DIM];
float linear_v[NUM_KEY_VALUE_HEADS * HEAD_DIM];

float rotary_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
float rotary_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
float embed_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
float embed_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
//float attn_output[NUM_ATTENTION_HEADS * HEAD_DIM];
float attn_k[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM];
float attn_v[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM];

float linear_out[SLEN * INTERMEDIATE_SIZE];
float gelu_out[INTERMEDIATE_SIZE];

float residual[HIDDEN_SIZE];

float attn_output[HIDDEN_SIZE];
float feed_forward_hidden_states[HIDDEN_SIZE];
// float inv_freq[ROTARY_DIM / 2];
// float inv_freq_expanded[ROTARY_DIM / 2][1];
float position_ids_expanded[SLEN];
float inv_freq_expanded[ROTARY_DIM / 2];
float freqs_transposed[(ROTARY_DIM / 2) * SLEN];
float freqs[SLEN * ROTARY_DIM / 2];
float emb[SLEN*ROTARY_DIM];
float hidden_state[HIDDEN_SIZE];

float cos_arr[SLEN * ROTARY_DIM];
float sin_arr[SLEN * ROTARY_DIM];
int position_ids[SLEN];
float input_embed[HIDDEN_SIZE];

#define VISION_HIDDEN_SIZE 1152
float vision_tower_outputs[MAX_NUM][INPUT_DIM*HIDDEN_SIZE];
float preprocessed_images[MAX_NUM][NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE];
float connector_output[INPUT_DIM*HIDDEN_SIZE];
float embedding[SLEN*HIDDEN_SIZE];
int phi_output_ids[SLEN];

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

bool load_input(const std::string& filename, float* target_array, size_t array_size) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return false;
    }

    fin.read(reinterpret_cast<char*>(target_array), array_size * sizeof(float));
    fin.close();
    return true;
}

void rotate_half(
    float out[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    float in[NUM_KEY_VALUE_HEADS * ROTARY_DIM]
) {
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < HALF_ROTARY_DIM; j++) {
            out[i * ROTARY_DIM + j] = -in[i * ROTARY_DIM + j + HALF_ROTARY_DIM];
            out[i * ROTARY_DIM + j + HALF_ROTARY_DIM] = in[i * ROTARY_DIM + j];
        }
    }
}

void apply_rotary_pos_emb(
    float out_q_embed[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    float out_k_embed[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    float in_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    float in_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    int position_idx // for given position_idx
) {
    // float rotate_half_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    // float rotate_half_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    float rotate_cos[ROTARY_DIM];
    float rotate_sin[ROTARY_DIM];
    float freq[HALF_ROTARY_DIM] = {1, 0.562341, 0.316228, 0.177828, 0.1, 0.0562341, 0.0316228, 0.0177828, 0.01, 0.00562341, 0.00316228, 0.00177828, 0.001, 0.000562341, 0.000316228, 0.000177828};
    for (int i = 0; i < HALF_ROTARY_DIM; i++) {
        rotate_cos[i] = cos(position_idx * freq[i]);
        rotate_sin[i] = sin(position_idx * freq[i]);
    }
    for (int i = HALF_ROTARY_DIM; i < ROTARY_DIM; i++) {
        rotate_cos[i] = rotate_cos[i - HALF_ROTARY_DIM];
        rotate_sin[i] = rotate_sin[i - HALF_ROTARY_DIM];
    }
    
    rotate_half(rotate_half_q, in_q);
    rotate_half(rotate_half_k, in_k);
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < ROTARY_DIM; j++) {
            out_q_embed[i * ROTARY_DIM + j] = in_q[i * ROTARY_DIM + j] * rotate_cos[j] + rotate_half_q[i * ROTARY_DIM + j] * rotate_sin[j];
            out_k_embed[i * ROTARY_DIM + j] = in_k[i * ROTARY_DIM + j] * rotate_cos[j] + rotate_half_k[i * ROTARY_DIM + j] * rotate_sin[j];
        }
    }
}

void write_kv_cache(
    int layer_id,
    int position_idx,
    float in_k[NUM_KEY_VALUE_HEADS * HEAD_DIM],
    float in_v[NUM_KEY_VALUE_HEADS * HEAD_DIM]
) {
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < HEAD_DIM; j++) {
            k_cache[layer_id][i][position_idx][j] = in_k[i * HEAD_DIM + j];
            v_cache[layer_id][i][position_idx][j] = in_v[i * HEAD_DIM + j];
        }
    }
}

void qkv_with_cache(
    float out_attention[HEAD_DIM], // 1-dimension
    float in_q[HEAD_DIM], // 1-dimension
    float in_k[SLEN * HEAD_DIM], // 2-dimension
    float in_v[SLEN * HEAD_DIM], // 2-dimension
    float scale,
    int curr_len
) {
    // float qkt[SLEN];
    memset(out_attention, 0, sizeof(float) * HEAD_DIM);
    memset(qkt, 0, sizeof(float) * SLEN);
    for (int i = 0; i < curr_len; i++) {
        float sum = 0;
        for (int j = 0; j < HEAD_DIM; j++) {
            sum += in_q[j] * in_k[i * HEAD_DIM + j];
        }
        qkt[i] = sum / scale;
    }

    float maxval = qkt[0];
    for (int i = 1; i < curr_len; i++) {
        if (qkt[i] > maxval) {
            maxval = qkt[i];
        }
    }
    float sum_exp = 0;
    // float qkt_softmax[SLEN];
    memset(qkt_softmax, 0, sizeof(float) * SLEN);
    for (int i = 0; i < curr_len; i++) {
        qkt_softmax[i] = std::exp(qkt[i] - maxval);
        sum_exp += qkt_softmax[i];
    }
    for (int i = 0; i < curr_len; i++) {
        qkt_softmax[i] /= sum_exp;
    }

    for (int i = 0; i < curr_len; i++) {
        for (int j = 0; j < HEAD_DIM; j++) {
            out_attention[j] += qkt_softmax[i] * in_v[i * HEAD_DIM + j];
        }
    }
}

void eager_attention_forward_with_kv_cache(
    float out_attention[NUM_ATTENTION_HEADS * HEAD_DIM],
    float in_q[NUM_KEY_VALUE_HEADS * HEAD_DIM],
    float in_k[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM],
    float in_v[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM],
    float in_scaling,
    int position_idx
) {
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        float head_q[HEAD_DIM];
        float head_k[SLEN * HEAD_DIM];
        float head_v[SLEN * HEAD_DIM];
        memcpy(head_q, in_q + i * NUM_KEY_VALUE_HEADS, sizeof(float) * HEAD_DIM);
        memcpy(head_k, in_k + i * NUM_KEY_VALUE_HEADS, sizeof(float) * SLEN * HEAD_DIM);
        memcpy(head_v, in_v + i * NUM_KEY_VALUE_HEADS, sizeof(float) * SLEN * HEAD_DIM);
        qkv_with_cache(out_attention + i * HEAD_DIM, head_q, head_k, head_v, in_scaling, position_idx + 1);
    }
}

void phi_linear(
    float out[HIDDEN_SIZE],
    float in[HIDDEN_SIZE],
    float weight[HIDDEN_SIZE * HIDDEN_SIZE],
    float bias[HIDDEN_SIZE]
) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        out[i] = bias[i];
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            out[i] += in[j] * weight[i * HIDDEN_SIZE + j];
        }
    }
}

void phi_mlp_linear_1(
    float out[INTERMEDIATE_SIZE],
    float in[HIDDEN_SIZE],
    float weight[INTERMEDIATE_SIZE * HIDDEN_SIZE],
    float bias[INTERMEDIATE_SIZE]
) {
    for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
        out[i] = bias[i];
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            out[i] += in[j] * weight[i * HIDDEN_SIZE + j];
        }
    }
}

void phi_mlp_linear_2(
    float out[HIDDEN_SIZE],
    float in[INTERMEDIATE_SIZE],
    float weight[HIDDEN_SIZE * INTERMEDIATE_SIZE],
    float bias[HIDDEN_SIZE]
) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        out[i] = bias[i];
        for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
            out[i] += in[j] * weight[i * INTERMEDIATE_SIZE + j];
        }
    }
}

void phi_vocab_linear_argmax(
    int* output_id,
    float in[HIDDEN_SIZE],
    float weight[VOCAB_SIZE * HIDDEN_SIZE],
    float bias[VOCAB_SIZE]
) {
    int out = 0;
    float max_value = bias[0];
    for (int j = 0; j < HIDDEN_SIZE; j++) {
        max_value += in[j] * weight[j];
    }

    float sum;
    for (int i = 1; i < VOCAB_SIZE; i++) {
        sum = bias[i];
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            sum += in[j] * weight[i * HIDDEN_SIZE + j];
        }
        if (sum > max_value) {
            max_value = sum;
            out = i;
        }
    }
}

void PhiAttention_forward(
    float out_attn_output[NUM_ATTENTION_HEADS * HEAD_DIM],
    int layer_id,
    int position_idx,
    float in_hidden_state[HIDDEN_SIZE]
) {
    // float linear_q[NUM_KEY_VALUE_HEADS * HEAD_DIM];
    // float linear_k[NUM_KEY_VALUE_HEADS * HEAD_DIM];
    // float linear_v[NUM_KEY_VALUE_HEADS * HEAD_DIM];

    // flag: load_weight
    // 要看 layer_id
    // q_proj
    // float language_model_model_layers_0_self_attn_q_proj_weight[HIDDEN_SIZE * HIDDEN_SIZE];
    // float language_model_model_layers_0_self_attn_q_proj_bias[HIDDEN_SIZE];
    phi_linear(
        linear_q,
        in_hidden_state,
        language_model_model_layers_0_self_attn_q_proj_weight,
        language_model_model_layers_0_self_attn_q_proj_bias
    );
    // k_proj
    // float language_model_model_layers_0_self_attn_k_proj_weight[HIDDEN_SIZE * HIDDEN_SIZE];
    // float language_model_model_layers_0_self_attn_k_proj_bias[HIDDEN_SIZE];
    phi_linear(
        linear_k,
        in_hidden_state,
        language_model_model_layers_0_self_attn_k_proj_weight,
        language_model_model_layers_0_self_attn_k_proj_bias
    );
    // v_proj
    // float language_model_model_layers_0_self_attn_v_proj_weight[HIDDEN_SIZE * HIDDEN_SIZE];
    // float language_model_model_layers_0_self_attn_v_proj_bias[HIDDEN_SIZE];
    phi_linear(
        linear_v,
        in_hidden_state,
        language_model_model_layers_0_self_attn_v_proj_weight,
        language_model_model_layers_0_self_attn_v_proj_bias
    );


    // float rotary_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    // float rotary_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    // 將 linear_q, linear_k 轉成 rotary_q, rotary_k
    memcpy(rotary_q, linear_q, sizeof(float) * NUM_KEY_VALUE_HEADS * ROTARY_DIM);
    memcpy(rotary_k, linear_k, sizeof(float) * NUM_KEY_VALUE_HEADS * ROTARY_DIM);

    // 將 rotary_q, rotary_k 進行 apply_rotary_pos_emb
    // float embed_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    // float embed_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    apply_rotary_pos_emb(embed_q, embed_k, linear_q, linear_k, position_idx);

    // 接回去
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < ROTARY_DIM; j++) {
            linear_q[i * ROTARY_DIM + j] = embed_q[i * ROTARY_DIM + j];
            linear_k[i * ROTARY_DIM + j] = embed_k[i * ROTARY_DIM + j];
        }
    }

    write_kv_cache(
        layer_id,
        position_idx,
        linear_k, // 這裡的 linear_k 是 in_k
        linear_v  // 這裡的 linear_v 是 in_v
    );

    // attention 實作可選擇：eager_attention_forward, flash_attention_2, sdpa

    // 進 attention，拿出 attn_output, attn_weights
    // float scaling = 1.0 / std::sqrt(HEAD_DIM);
    float scaling = 0.1118033989f;
    // float attn_output[NUM_ATTENTION_HEADS * HEAD_DIM];
    // float attn_k[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM];
    // float attn_v[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM];
    memcpy(attn_k, k_cache[layer_id], sizeof(float) * NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM);
    memcpy(attn_v, v_cache[layer_id], sizeof(float) * NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM);
    eager_attention_forward_with_kv_cache(
        attn_output,
        linear_q,
        attn_k,
        attn_v,
        scaling,
        position_idx
    );

    // flag: load_weight
    // 要看 layer_id
    // float language_model_model_layers_0_self_attn_dense_weight[HIDDEN_SIZE * HIDDEN_SIZE];
    // float language_model_model_layers_0_self_attn_dense_bias[HIDDEN_SIZE];
    phi_linear(
        out_attn_output, // 1-dimension
        attn_output, // 1-dimension
        language_model_model_layers_0_self_attn_dense_weight,
        language_model_model_layers_0_self_attn_dense_bias
    );    
}

// TODO: 要優化
float new_gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f; // √(2/π)
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = std::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}

void PhiMLP_forward(
    float out[HIDDEN_SIZE],
    float in[HIDDEN_SIZE],
    int layer_id
) {
    // flag: load_weight
    // 要看 layer_id
    // float language_model_model_layers_0_mlp_fc1_weight[INTERMEDIATE_SIZE * HIDDEN_SIZE];
    // float language_model_model_layers_0_mlp_fc1_bias[INTERMEDIATE_SIZE];
    // float linear_out[SLEN * INTERMEDIATE_SIZE];
    // phi_mlp_linear_1
    phi_mlp_linear_1(
        linear_out,
        in,
        language_model_model_layers_0_mlp_fc1_weight,
        language_model_model_layers_0_mlp_fc1_bias
    );
    
    // TODO GeLU Function 先用 hls 的
    // float gelu_out[INTERMEDIATE_SIZE];
    for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
        gelu_out[i] = new_gelu(linear_out[i]);
    }

    // flag: load_weight
    // 要看 layer_id
    // float language_model_model_layers_0_mlp_fc2_weight[HIDDEN_SIZE * INTERMEDIATE_SIZE];
    // float language_model_model_layers_0_mlp_fc2_bias[HIDDEN_SIZE];
    phi_mlp_linear_2(
        out,
        gelu_out,
        language_model_model_layers_0_mlp_fc2_weight,
        language_model_model_layers_0_mlp_fc2_bias
    );
}

void phi_layernorm(
    float out[HIDDEN_SIZE],
    float in[HIDDEN_SIZE],
    float weight[HIDDEN_SIZE],
    float bias[HIDDEN_SIZE],
    float eps
) {
    float mean = 0.0f;
    float variance = 0.0f;

    // 計算 mean
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        mean += in[i];
    }
    mean /= HIDDEN_SIZE;

    // 計算 variance
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        variance += (in[i] - mean) * (in[i] - mean);
    }
    variance /= HIDDEN_SIZE;

    // 計算標準差
    float stddev = std::sqrt(variance + eps);

    // 正規化並應用權重和偏置
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        out[i] = weight[i] * ((in[i] - mean) / stddev) + bias[i];
    }
}

void PhiDecoderLayer_forward(
    float out[HIDDEN_SIZE],
    int layer_id,
    int position_idx,
    float in_hidden_state[HIDDEN_SIZE]
) {
    // float residual[HIDDEN_SIZE];
    memcpy(residual, in_hidden_state, sizeof(float) * HIDDEN_SIZE);

    // flag: load_weight
    // 要看 layer_id
    // float language_model_model_layers_0_input_layernorm_weight[HIDDEN_SIZE];
    // float language_model_model_layers_0_input_layernorm_bias[HIDDEN_SIZE];
    phi_layernorm(
        in_hidden_state,
        residual,
        language_model_model_layers_0_input_layernorm_weight,
        language_model_model_layers_0_input_layernorm_bias,
        LAYER_NORM_EPS
    );

    float attn_output[HIDDEN_SIZE];
    PhiAttention_forward(attn_output, layer_id, position_idx, in_hidden_state);

    float feed_forward_hidden_states[HIDDEN_SIZE];
    PhiMLP_forward(feed_forward_hidden_states, attn_output, layer_id);

    // float tmp[SLEN][HIDDEN_SIZE];
    // matadd<SLEN, HIDDEN_SIZE, float>(tmp, attn_output, feed_forward_hidden_states);
    // matadd<SLEN, HIDDEN_SIZE, float>(out, tmp, residual);
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        out[i] = attn_output[i] + feed_forward_hidden_states[i] + residual[i];
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


//might have bug!!!!!
// void PhiRotaryEmbedding_forward(
//     float out_cos[SLEN * ROTARY_DIM],
//     float out_sin[SLEN * ROTARY_DIM],
//     int position_ids[SLEN]
// ) {
//     // rope type = "default"
//     // attention_scaling default is 1
//     // float attention_scaling = 1.0;

//     // float inv_freq[ROTARY_DIM / 2];
//     // compute_default_rope_parameters(inv_freq);
//     // //float inv_freq_expanded[ROTARY_DIM / 2][1];
//     // memcpy(inv_freq_expanded, inv_freq, sizeof(float) * ROTARY_DIM / 2);
//     // // float position_ids_expanded[1][SLEN];
//     // for (int i = 0; i < 1; i++) {
//     //     for (int j = 0; j < SLEN; j++) {
//     //         position_ids_expanded[i * SLEN + j] = (float) position_ids[j];
//     //     }
//     // }
//     // // float freqs_transposed[ROTARY_DIM / 2][SLEN];
//     // matmul<ROTARY_DIM / 2, 1, SLEN>(freqs_transposed, inv_freq_expanded, position_ids_expanded);
//     // // float freqs[SLEN][ROTARY_DIM / 2];
//     // transpose<ROTARY_DIM / 2, SLEN>(freqs, freqs_transposed);

//     float inv_freq[ROTARY_DIM / 2] = {1, 0.562341, 0.316228, 0.177828, 0.1, 0.0562341, 0.0316228, 0.0177828, 0.01, 0.00562341, 0.00316228, 0.00177828, 0.001, 0.000562341, 0.000316228, 0.000177828};

//     //float emb[SLEN][ROTARY_DIM];
//     for (int i = 0; i < SLEN; i++) {
//         for (int j = 0; j < ROTARY_DIM / 2; j++) {
//             emb[i * ROTARY_DIM + j] = i * inv_freq[j];
//             emb[i * ROTARY_DIM + j + ROTARY_DIM / 2] = i * inv_freq[j];
//         }
//     }
//     for (int i = 0; i < SLEN; i++) {
//         for (int j = 0; j < ROTARY_DIM; j++) {
//             // cosf -> f means float not double
//             // out_cos = cosf(emb[i][j]) * attention_scaling;
//             // out_sin = sinf(emb[i][j]) * attention_scaling;

//             // attention_scaling is 1
//             out_cos[i * ROTARY_DIM + j] = cosf(emb[i * ROTARY_DIM + j]);//hls
//             out_sin[i * ROTARY_DIM + j] = sinf(emb[i * ROTARY_DIM + j]);//hls
//         }
//     }
// }

// void PhiPreTrainedModel_init_weights() {
    // 用來定義 linear, embedding, layernorm 訓練初始參數
    // 推論用不到
// }

// phi-2 不用 pad
// 應該不用合成
// default num_embddings is VOCAB_SIZE
// default embedding_dim is HIDDEN_SIZE
// default padding_idx is None
// 只是查表 language_model_model_embed_tokens_weight
// void Embedding_forward(
//     float out[SLEN][HIDDEN_SIZE],
//     int input_ids[SLEN]
// ) {
//     // 從 language_model_model_embed_tokens_weight 拿
//     float language_model_model_embed_tokens_weight[VOCAB_SIZE][HIDDEN_SIZE];
//     for (int i = 0; i < SLEN; ++i) {
//         int idx = input_ids[i];

//         // 直接查表，不檢查越界
//         for (int j = 0; j < HIDDEN_SIZE; ++j) {
//             out[i][j] = language_model_model_embed_tokens_weight[idx][j];
//         }
//     }
// }

void load_phi_encoder_weight(int layer){
    std::string input_layernorm_bias = std::to_string(layer) + ".input_layernorm.bias";
    std::string input_layernorm_weight = std::to_string(layer) + ".input_layernorm.weight";
    std::string mlp_fc1_bias = std::to_string(layer) + ".mlp.fc1.bias";
    std::string mlp_fc1_weight = std::to_string(layer) + ".mlp.fc1.weight";
    std::string mlp_fc2_bias = std::to_string(layer) + ".mlp.fc2.bias";
    std::string mlp_fc2_weight = std::to_string(layer) + ".mlp.fc2.weight";
    std::string self_attn_dense_bias = std::to_string(layer) + ".self_attn.dense.bias";
    std::string self_attn_dense_weight = std::to_string(layer) + ".self_attn.dense.weight";
    std::string self_attn_k_proj_bias = std::to_string(layer) + ".self_attn.k_proj.bias";
    std::string self_attn_k_proj_weight = std::to_string(layer) + ".self_attn.k_proj.weight";
    std::string self_attn_q_proj_bias = std::to_string(layer) + ".self_attn.q_proj.bias";
    std::string self_attn_q_proj_weight = std::to_string(layer) + ".self_attn.q_proj.weight";
    std::string self_attn_v_proj_bias = std::to_string(layer) + ".self_attn.v_proj.bias";
    std::string self_attn_v_proj_weight = std::to_string(layer) + ".self_attn.v_proj.weight";
    load_weight("language.model.model.layers." + input_layernorm_bias, language_model_model_layers_0_input_layernorm_bias , HIDDEN_SIZE);
    load_weight("language.model.model.layers." + input_layernorm_weight, language_model_model_layers_0_input_layernorm_weight , HIDDEN_SIZE);
    load_weight("language.model.model.layers." + self_attn_q_proj_bias, language_model_model_layers_0_self_attn_q_proj_weight , HIDDEN_SIZE);
    load_weight("language.model.model.layers." + self_attn_q_proj_weight, language_model_model_layers_0_self_attn_q_proj_bias , HIDDEN_SIZE * HIDDEN_SIZE);
    load_weight("language.model.model.layers." + self_attn_k_proj_bias, language_model_model_layers_0_self_attn_k_proj_weight , HIDDEN_SIZE);
    load_weight("language.model.model.layers." + self_attn_k_proj_weight, language_model_model_layers_0_self_attn_k_proj_bias , HIDDEN_SIZE * HIDDEN_SIZE);
    load_weight("language.model.model.layers." + self_attn_v_proj_bias, language_model_model_layers_0_self_attn_v_proj_weight , HIDDEN_SIZE);
    load_weight("language.model.model.layers." + self_attn_v_proj_weight, language_model_model_layers_0_self_attn_v_proj_bias , HIDDEN_SIZE * HIDDEN_SIZE);
    load_weight("language.model.model.layers." + self_attn_dense_bias, language_model_model_layers_0_self_attn_dense_bias , HIDDEN_SIZE);
    load_weight("language.model.model.layers." + self_attn_dense_weight, language_model_model_layers_0_self_attn_dense_weight , HIDDEN_SIZE * HIDDEN_SIZE);
    load_weight("language.model.model.layers." + mlp_fc1_bias, language_model_model_layers_0_mlp_fc1_bias , INTERMEDIATE_SIZE);
    load_weight("language.model.model.layers." + mlp_fc1_weight, language_model_model_layers_0_mlp_fc1_weight , INTERMEDIATE_SIZE * HIDDEN_SIZE);
    load_weight("language.model.model.layers." + mlp_fc2_bias, language_model_model_layers_0_mlp_fc2_bias , HIDDEN_SIZE);
    load_weight("language.model.model.layers." + mlp_fc2_weight, language_model_model_layers_0_mlp_fc2_weight , HIDDEN_SIZE * INTERMEDIATE_SIZE);
}

void PhiModel_forward(
    int* output_id,
    float input_embed[HIDDEN_SIZE],
    bool should_predict,
    int position_idx,
    float in_cos[ROTARY_DIM],
    float in_sin[ROTARY_DIM]
) {

    // float input_embed[HIDDEN_SIZE];
    // float language_model_model_embed_tokens_weight[VOCAB_SIZE][HIDDEN_SIZE];
    // memcpy(input_embed, language_model_model_embed_tokens_weight[input_id], sizeof(float) * HIDDEN_SIZE);

    // flag: on board
    // float hidden_state[HIDDEN_SIZE];
    for (int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
        memcpy(hidden_state, input_embed, sizeof(float) * HIDDEN_SIZE);
        load_phi_encoder_weight(i);
        PhiDecoderLayer_forward(input_embed, i, position_idx, hidden_state);
    }

    if (should_predict) {
        // flag: load_weight
        // float language_model_model_final_layernorm_weight[HIDDEN_SIZE];
        // float language_model_model_final_layernorm_bias[HIDDEN_SIZE];
        phi_layernorm(
            hidden_state,
            input_embed,
            language_model_model_final_layernorm_weight,
            language_model_model_final_layernorm_bias,
            LAYER_NORM_EPS
        );
        // flag: load_weight
        // float language_model_model_lm_head_weight[VOCAB_SIZE * HIDDEN_SIZE];
        // float language_model_model_lm_head_bias[VOCAB_SIZE];
        phi_vocab_linear_argmax(
            output_id,
            hidden_state,
            language_model_model_lm_head_weight,
            language_model_model_lm_head_bias
        );
    } else {
        *output_id = -1;
    }
}

void PhiForCausalLM_forward(
    int output_ids[SLEN],
    float input_embeds[SLEN * HIDDEN_SIZE],
    int input_len
) {

    for (int i = 0; i < SLEN; i++) {
        output_ids[i] = END_OF_TEXT_ID; // 初始化為結束符號
    }

    // float cos[SLEN][ROTARY_DIM];
    // float sin[SLEN][ROTARY_DIM];
    // int position_ids[SLEN];
    for (int i = 0; i < SLEN; i++) {
        position_ids[i] = i;
    }

    //PhiRotaryEmbedding_forward(cos_arr, sin_arr, position_ids);

    bool should_predict;
    int output_id;
    int output_len = 0;
    // float input_embed[HIDDEN_SIZE];
    for (int i = 0; i < SLEN; i++) {
        should_predict = (i >= (input_len - 1));
        if (i >= input_len) {
            memcpy(input_embed, input_embeds + i * HIDDEN_SIZE, sizeof(float) * HIDDEN_SIZE);
        } else {
            // float language_model_model_embed_tokens_weight[VOCAB_SIZE][HIDDEN_SIZE];
            memcpy(input_embed, language_model_model_embed_tokens_weight + output_ids[output_len - 1] * HIDDEN_SIZE, sizeof(float) * HIDDEN_SIZE);
        }
        PhiModel_forward(&output_id, input_embed, should_predict, i/*, cos_arr + i * ROTARY_DIM, sin_arr + i * ROTARY_DIM*/);
        if (output_id == END_OF_TEXT_ID) break;
        if (should_predict) {
            output_ids[output_len++] = output_id;
        }
    }
}

// [0, 1, 2] id

// [1, 2, 3] hidden state
// [4, 5, 6]
// [7, 8, 9]

// 算完之後的值應該就固定了，可能可以寫死
// void compute_default_rope_parameters(
//     // out_inv_freq = {1, 0.562341, 0.316228, 0.177828, 0.1, 0.0562341, 0.0316228, 0.0177828, 0.01, 0.00562341, 0.00316228, 0.00177828, 0.001, 0.000562341, 0.000316228, 0.000177828};
//     float out_inv_freq[ROTARY_DIM / 2]
// ) {
//     int dim = ROTARY_DIM;
//     for (int i = 0; i < dim / 2; i++) {
//         float exponent = (2.0f * i) / (float)dim;
//         float power = powf(ROPE_THETA, exponent); // base^(2i/dim) //hls
//         out_inv_freq[i] = 1.0f / power;
//     }
// }

// void load_phi_embedding_weight(){
//     load_weight("language_model.lm_head.bias", language_model_model_lm_head_bias, VOCAB_SIZE);
//     // std::cout << "*vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight:" << std::endl;
//     // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight[i] << " ";
//     // std::cout << std::endl;

//     load_weight("language_model.lm_head.weight", language_model_model_lm_head_weight, VOCAB_SIZE * HIDDEN_SIZE);
//     // std::cout << "*vision_tower._vision_tower.vision_model.embeddings.patch_embedding.weight" << std::endl;
//     // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_patch_embedding_weight[i] << " ";
//     // std::cout << std::endl;

//     load_weight("language_model.model.embed_tokens.weight", language_model_model_embed_tokens_weight, VOCAB_SIZE * HIDDEN_SIZE);
//     // std::cout << "*vision_tower._vision_tower.vision_model.embeddings.patch_embedding.weight" << std::endl;
//     // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_patch_embedding_weight[i] << " ";
//     // std::cout << std::endl;

//     load_weight("language_model.model.final_layernorm.bias", language_model_model_final_layernorm_bias, HIDDEN_SIZE);
//     // std::cout << "*vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight:" << std::endl;
//     // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight[i] << " ";
//     // std::cout << std::endl;

//     load_weight("language_model.model.final_layernorm.weight", language_model_model_final_layernorm_weight, HIDDEN_SIZE);
//     // std::cout << "*vision_tower._vision_tower.vision_model.embeddings.patch_embedding.weight" << std::endl;
//     // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_patch_embedding_weight[i] << " ";
//     // std::cout << std::endl;

// }

void load_llm_weight(){
    load_weight("language_model.lm_head.bias", language_model_model_lm_head_bias, VOCAB_SIZE);
    // std::cout << "*vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight:" << std::endl;
    // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight[i] << " ";
    // std::cout << std::endl;

    load_weight("language_model.lm_head.weight", language_model_model_lm_head_weight, VOCAB_SIZE * HIDDEN_SIZE);
    // std::cout << "*vision_tower._vision_tower.vision_model.embeddings.patch_embedding.weight" << std::endl;
    // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_patch_embedding_weight[i] << " ";
    // std::cout << std::endl;

    load_weight("language_model.model.embed_tokens.weight", language_model_model_embed_tokens_weight, VOCAB_SIZE * HIDDEN_SIZE);
    // std::cout << "*vision_tower._vision_tower.vision_model.embeddings.patch_embedding.weight" << std::endl;
    // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_patch_embedding_weight[i] << " ";
    // std::cout << std::endl;

    load_weight("language_model.model.final_layernorm.bias", language_model_model_final_layernorm_bias, HIDDEN_SIZE);
    // std::cout << "*vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight:" << std::endl;
    // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight[i] << " ";
    // std::cout << std::endl;

    load_weight("language_model.model.final_layernorm.weight", language_model_model_final_layernorm_weight, HIDDEN_SIZE);
    // std::cout << "*vision_tower._vision_tower.vision_model.embeddings.patch_embedding.weight" << std::endl;
    // for (int i = 0; i < 10; i++) std::cout << vision_tower_vision_tower_vision_model_embeddings_patch_embedding_weight[i] << " ";
    // std::cout << std::endl;
}

void load_previous_output(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Error opening input file: " << filename << std::endl;
        exit(1);
    }
    for (int i = 0; i < 729 * CONNECTOR_HIDDEN_SIZE; i++) {
        fin >> connector_output[i];
        fin >> vision_tower_outputs[0][i];
    }
}

void load_image_processor_output(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Error opening input file: " << filename << std::endl;
        exit(1);
    }
    for (int i = 0; i < NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE; i++) {
        fin >> preprocessed_images[0][i];
    }
}



// void encode_images(
//     float output[SLEN * HIDDEN_SIZE],
//     float input[NUM_CHANNELS * IMAGE_SIZE * IMAGE_SIZE]
// ){  
//     float siglip_output[INPUT_DIM * VISION_HIDDEN_SIZE] = {0};
//     Siglip_Transformer_forward(siglip_output, input);
//     float connector_input[SLEN * VISION_HIDDEN_SIZE] = {0};
//     memcpy(connector_input, siglip_output, sizeof(float) * INPUT_DIM * VISION_HIDDEN_SIZE);
//     Connector_forward(output, connector_input);
// }

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

            std::vector<float> embedding(language_model_model_embed_tokens_weight[token_id], language_model_model_embed_tokens_weight[token_id] + HIDDEN_SIZE);
            // for (int k = 0; k < HIDDEN_SIZE; ++k) {
            //     embedding[k] = language_model_model_embed_tokens_weight[token_id][k];
            // }
            segment_embed.push_back(embedding);
        }

        input_embeds_split.push_back(segment_embed);
    }
    
    return input_embeds_split;
}

std::pair<std::vector<std::vector<float>>, int> prepare_input_for_multimodel(
    std::vector<int> input_ids,
    float images[MAX_NUM][NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE],
    const int num_images = 1
){  
    
    //std::vector<int> cur_input_ids(*input_ids);
    std::vector<std::vector<std::vector<float>>> input_embeds_split;
    

    input_embeds_split = process_input_ids(input_ids);
    // float embeds_split[num_images + 1][MAX_LEN][HIDDEN_SIZE];
    // for(int i = 0; i < num_images; i++){
    //     encode_images(vision_tower_outputs[i], images[i]);
    // }
    load_previous_output("connector_cpp_output.txt");

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
    
    std::vector<std::vector<float>> output_embedding;
    for(int i = 0; i < num_images + 1; i++){
        for(const auto& vec : input_embeds_split[i]){
           output_embedding.push_back(vec);
        }
        if(i != num_images){
            for(int j = 0; j < SLEN; j++){ //SLEN? MAX?
                std::vector<float> image_feature(vision_tower_outputs[i][j], vision_tower_outputs[i][j] + HIDDEN_SIZE);
                output_embedding.push_back(image_feature);
            }
        }
    }
            
    std::pair<std::vector<std::vector<float>>, int> out = {output_embedding, max_len};
    //memcpy(output_embedding, input_ids, TOKENIZER_MODEL_MAX_LENGTH);
    return out;
}



int main(){
    // load_siglip_embedding_weight();
    // load_input("image_tensor.bin", input, NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE);
    // std::cout << " - preprocessed image" << std::endl;
    // for (int i = 0; i < 5; i++) std::cout << input[i] << " ";
    // std::cout << std::endl << std::endl;

    // Siglip_Transformer_forward(output, input);
    std::vector<std::string> test_sentences = {
        "What is next to the parking meter? What is it doing?"
    };
    std::vector<int> input_ids_vector = {-200, 2061, 318, 1306, 284, 262, 7647, 16430, 30, 1867, 318, 340, 1804, 30};
    // load_previous_output("connector_cpp_output.txt");
    load_image_processor_output("preprocessed_implementation_cpp.bin");
    int input_len = 2560;

    std::pair<std::vector<std::vector<float>>, int> pair_out = prepare_input_for_multimodel(input_ids_vector, preprocessed_images, 1);
    for(int i = 0; i < pair_out.first.size(); i++){
        for(int j = 0; j < HIDDEN_SIZE; j++){
            embedding[i * HIDDEN_SIZE +  j] = pair_out.first[i][j];
        }
    }
    
    input_len = pair_out.second;
    load_llm_weight();

    PhiForCausalLM_forward(
        phi_output_ids,
        embedding,
        input_len
    );

    // Output
    // std::cout << "First 10 values of output:" << std::endl;
    // for (int i = 0; i < 10; i++) std::cout << output[i] << " ";
    // std::cout << std::endl;
    // return 0;
     // 將 output 寫入檔案 (純文字)
    std::ofstream fout("phi_cpp_output.txt");
    if (!fout) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
    }
    for (int i = 0; i < SLEN; i++) {
        fout << phi_output_ids[i] << "\n";
    }
    fout.close();
    
    std::cout << "Output saved to cpp_output.txt" << std::endl;
    return 0;
}