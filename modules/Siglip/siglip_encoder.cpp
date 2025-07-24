#include <string.h>
#include <hls_math.h>
#include <ap_fixed.h>
#include "Siglip_config.hpp"

float gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f;
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = hls::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}

void SiglipMLP(
    float out[SLEN][HIDDEN_SIZE], 
    float hidden_state[SLEN][HIDDEN_SIZE],
    int layer_id
) { 
    // TODO: load weights by layer_id
    float vision_tower_vision_tower_vision_model_head_mlp_fc1_weight[INTERMEDIATE_SIZE][HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_head_mlp_fc1_bias[INTERMEDIATE_SIZE];
    float vision_tower_vision_tower_vision_model_head_mlp_fc2_weight[HIDDEN_SIZE][INTERMEDIATE_SIZE];
    float vision_tower_vision_tower_vision_model_head_mlp_fc2_bias[HIDDEN_SIZE];

    float linear_out[SLEN][INTERMEDIATE_SIZE];   
    linear<HIDDEN_SIZE, INTERMEDIATE_SIZE, SLEN, float>(
        linear_out, hidden_state, 
        vision_tower_vision_tower_vision_model_head_mlp_fc1_weight, vision_tower_vision_tower_vision_model_head_mlp_fc1_bias
    );

    float gelu_out[SLEN][INTERMEDIATE_SIZE];
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
            gelu_out[i][j] = gelu(linear_out[i][j]);
        }
    }
    
    linear<INTERMEDIATE_SIZE, HIDDEN_SIZE, SLEN, float>(
        out, gelu_out,
        vision_tower_vision_tower_vision_model_head_mlp_fc2_weight, vision_tower_vision_tower_vision_model_head_mlp_fc2_bias
    );
}

// void matmul_with_scale(
//     float out[SLEN][SLEN], 
//     float in1[SLEN][HEAD_DIM], float in2[HEAD_DIM][SLEN], 
//     float scaling
// ) {
//     for (int i = 0; i < SLEN; i++) {
//         for (int j = 0; j < SLEN; j++) {
//             float sum = 0;
//             for (int k = 0; k < HEAD_DIM; k++) {
//                 sum += in1[i][k] * in2[k][j];
//             }
//             out[i][j] = sum * scaling;
//         }
//     }
// }

void matmul_with_scale_no_transpose(
    float out[SLEN][SLEN], 
    float in1[SLEN][HEAD_DIM],
    float in2[HEAD_DIM][SLEN],
    float scaling
) {
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < SLEN; j++) {
            float sum = 0;
            for (int k = 0; k < HEAD_DIM; k++) {
                sum += in1[i][k] * in2[j][k];
            }
            out[i][j] = sum * scaling;
        }
    }
}

void eager_attention_per_head(
    float out[SLEN][HEAD_DIM],
    float query[SLEN][HEAD_DIM],
    float key[SLEN][HEAD_DIM],
    float value[SLEN][HEAD_DIM],
    float scaling
) {   
    // float transposed_key[HEAD_DIM][SLEN];
    // transpose<SLEN, HEAD_DIM, float>(transposed_key, key);

    float scaled_attn_weights[SLEN][SLEN];
    // matmul_with_scale(scaled_attn_weights, query, transposed_key, scaling);
    matmul_with_scale_no_transpose(scaled_attn_weights, query, key, scaling);
    
    float softmax_attn_weights[SLEN][SLEN];
    softmax<SLEN, SLEN>(softmax_attn_weights, scaled_attn_weights);
    
    float attn_scores[SLEN][HEAD_DIM];
    matmul<SLEN, SLEN, HEAD_DIM, float>(out, softmax_attn_weights, value);
}

void SiglipAttention(
    float out[SLEN][HIDDEN_SIZE],
    float hidden_states[SLEN][HIDDEN_SIZE],
    int layer_id
) {
    // TODO: load weights by layer_id
    float vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_q_proj_weight[HIDDEN_SIZE][HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_q_proj_bias[HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_k_proj_weight[HIDDEN_SIZE][HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_k_proj_bias[HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_v_proj_weight[HIDDEN_SIZE][HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_v_proj_bias[HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_out_proj_weight[HIDDEN_SIZE][HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_out_proj_bias[HIDDEN_SIZE];
    
    // Project Q, K, V
    float q_proj[SLEN][NUM_ATTENTION_HEADS * HEAD_DIM];
    float k_proj[SLEN][NUM_ATTENTION_HEADS * HEAD_DIM];
    float v_proj[SLEN][NUM_ATTENTION_HEADS * HEAD_DIM];
    linear<HIDDEN_SIZE, NUM_ATTENTION_HEADS * HEAD_DIM, SLEN>(q_proj, hidden_states, vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_q_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_q_proj_bias);
    linear<HIDDEN_SIZE, NUM_ATTENTION_HEADS * HEAD_DIM, SLEN>(k_proj, hidden_states, vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_k_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_k_proj_bias);
    linear<HIDDEN_SIZE, NUM_ATTENTION_HEADS * HEAD_DIM, SLEN>(v_proj, hidden_states, vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_v_proj_weight, vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_v_proj_bias);
    
    // Reshape Q, K, V to (source_length, num_heads, head_dim) 
    float reshaped_q_proj[SLEN][NUM_ATTENTION_HEADS][HEAD_DIM];
    float reshaped_k_proj[SLEN][NUM_ATTENTION_HEADS][HEAD_DIM];
    float reshaped_v_proj[SLEN][NUM_ATTENTION_HEADS][HEAD_DIM];
    memcpy(reshaped_q_proj, q_proj, sizeof(float) * SLEN * NUM_ATTENTION_HEADS * HEAD_DIM);
    memcpy(reshaped_k_proj, k_proj, sizeof(float) * SLEN * NUM_ATTENTION_HEADS * HEAD_DIM);
    memcpy(reshaped_v_proj, v_proj, sizeof(float) * SLEN * NUM_ATTENTION_HEADS * HEAD_DIM);

    // Transpose to (num_heads, source_length, head_dim)
    float query[NUM_ATTENTION_HEADS][SLEN][HEAD_DIM];
    float key[NUM_ATTENTION_HEADS][SLEN][HEAD_DIM];
    float value[NUM_ATTENTION_HEADS][SLEN][HEAD_DIM];
    for (int i = 0; i < NUM_ATTENTION_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < HEAD_DIM; k++) {
                query[i][j][k] = reshaped_q_proj[j][i][k];
                key[i][j][k] = reshaped_k_proj[j][i][k];
                value[i][j][k] = reshaped_v_proj[j][i][k];
            }
        }
    }

    // TODO: Compute attention => 考慮合併(避免讀寫)/平行(多head同時)
    float scaling = 1 / hls::sqrt(HEAD_DIM);
    float attn_scores[NUM_ATTENTION_HEADS][SLEN][HEAD_DIM];
    for (int h = 0; h < NUM_ATTENTION_HEADS; h++) {
        eager_attention_per_head(attn_scores[h], query[h], key[h], value[h], scaling);
    }

    // Transpose
    float attn_out[SLEN][NUM_ATTENTION_HEADS][HEAD_DIM];
    for (int s = 0; s < SLEN; s++) {
        for (int h = 0; h < NUM_ATTENTION_HEADS; h++) {
            for (int d = 0; d < HEAD_DIM; d++) {
                attn_out[s][h][d] = attn_scores[h][s][d];
            }
        }
    }

    // Reshape
    float reshaped_attn_out[SLEN][NUM_ATTENTION_HEADS * HEAD_DIM];
    memcpy(reshaped_attn_out, attn_out, sizeof(float) * SLEN * NUM_ATTENTION_HEADS * HEAD_DIM);
    
    // Project the attention output
    linear<HIDDEN_SIZE, HIDDEN_SIZE, SLEN, float>(
        out, reshaped_attn_out,
        vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_out_proj_weight, 
        vision_tower_vision_tower_vision_model_encoder_layers_0_self_attn_out_proj_bias
    );
}
