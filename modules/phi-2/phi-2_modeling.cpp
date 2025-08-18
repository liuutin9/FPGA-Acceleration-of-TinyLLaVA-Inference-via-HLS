#include <string.h>
#include <hls_math.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include "./phi-2_config.hpp"

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
    int position_idx
) {
    float rotate_half_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    float rotate_half_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    float rotate_cos[ROTARY_DIM];
    float rotate_sin[ROTARY_DIM];
    float freq[HALF_ROTARY_DIM] = {1, 0.562341, 0.316228, 0.177828, 0.1, 0.0562341, 0.0316228, 0.0177828, 0.01, 0.00562341, 0.00316228, 0.00177828, 0.001, 0.000562341, 0.000316228, 0.000177828};
    for (int i = 0; i < HALF_ROTARY_DIM; i++) {
        rotate_cos[i] = hls::cos(position_idx * freq[i]);
        rotate_sin[i] = hls::sin(position_idx * freq[i]);
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
    float qkt[SLEN];
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
    float qkt_softmax[SLEN];
    memset(qkt_softmax, 0, sizeof(float) * SLEN);
    for (int i = 0; i < curr_len; i++) {
        qkt_softmax[i] = hls::exp(qkt[i] - maxval);
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
    float linear_q[NUM_KEY_VALUE_HEADS * HEAD_DIM];
    float linear_k[NUM_KEY_VALUE_HEADS * HEAD_DIM];
    float linear_v[NUM_KEY_VALUE_HEADS * HEAD_DIM];

    // flag: load_weight
    // 要看 layer_id
    // q_proj
    float language_model_model_layers_0_self_attn_q_proj_weight[HIDDEN_SIZE * HIDDEN_SIZE];
    float language_model_model_layers_0_self_attn_q_proj_bias[HIDDEN_SIZE];
    phi_linear(
        linear_q,
        in_hidden_state,
        language_model_model_layers_0_self_attn_q_proj_weight,
        language_model_model_layers_0_self_attn_q_proj_bias
    );
    // k_proj
    float language_model_model_layers_0_self_attn_k_proj_weight[HIDDEN_SIZE * HIDDEN_SIZE];
    float language_model_model_layers_0_self_attn_k_proj_bias[HIDDEN_SIZE];
    phi_linear(
        linear_k,
        in_hidden_state,
        language_model_model_layers_0_self_attn_k_proj_weight,
        language_model_model_layers_0_self_attn_k_proj_bias
    );
    // v_proj
    float language_model_model_layers_0_self_attn_v_proj_weight[HIDDEN_SIZE * HIDDEN_SIZE];
    float language_model_model_layers_0_self_attn_v_proj_bias[HIDDEN_SIZE];
    phi_linear(
        linear_v,
        in_hidden_state,
        language_model_model_layers_0_self_attn_v_proj_weight,
        language_model_model_layers_0_self_attn_v_proj_bias
    );


    float rotary_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    float rotary_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    // 將 linear_q, linear_k 轉成 rotary_q, rotary_k
    memcpy(rotary_q, linear_q, sizeof(float) * NUM_KEY_VALUE_HEADS * ROTARY_DIM);
    memcpy(rotary_k, linear_k, sizeof(float) * NUM_KEY_VALUE_HEADS * ROTARY_DIM);

    // 將 rotary_q, rotary_k 進行 apply_rotary_pos_emb
    float embed_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
    float embed_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM];
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
    // float scaling = 1.0 / hls::sqrt(HEAD_DIM);
    float scaling = 0.1118033989f;
    float attn_output[NUM_ATTENTION_HEADS * HEAD_DIM];
    float attn_k[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM];
    float attn_v[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM];
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
    float language_model_model_layers_0_self_attn_dense_weight[HIDDEN_SIZE * HIDDEN_SIZE];
    float language_model_model_layers_0_self_attn_dense_bias[HIDDEN_SIZE];
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
    float tanh_inner = hls::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}

void PhiMLP_forward(
    float out[HIDDEN_SIZE],
    float in[HIDDEN_SIZE],
    int layer_id
) {
    // flag: load_weight
    // 要看 layer_id
    float language_model_model_layers_0_mlp_fc1_weight[INTERMEDIATE_SIZE * HIDDEN_SIZE];
    float language_model_model_layers_0_mlp_fc1_bias[INTERMEDIATE_SIZE];
    float linear_out[SLEN * INTERMEDIATE_SIZE];
    // phi_mlp_linear_1
    phi_mlp_linear_1(
        linear_out,
        in,
        language_model_model_layers_0_mlp_fc1_weight,
        language_model_model_layers_0_mlp_fc1_bias
    );
    
    // TODO GeLU Function 先用 hls 的
    float gelu_out[INTERMEDIATE_SIZE];
    for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
        gelu_out[i] = new_gelu(linear_out[i]);
    }

    // flag: load_weight
    // 要看 layer_id
    float language_model_model_layers_0_mlp_fc2_weight[HIDDEN_SIZE * INTERMEDIATE_SIZE];
    float language_model_model_layers_0_mlp_fc2_bias[HIDDEN_SIZE];
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
    float stddev = hls::sqrt(variance + eps);

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
    float residual[HIDDEN_SIZE];
    memcpy(residual, in_hidden_state, sizeof(float) * HIDDEN_SIZE);

    // flag: load_weight
    // 要看 layer_id
    float language_model_model_layers_0_input_layernorm_weight[HIDDEN_SIZE];
    float language_model_model_layers_0_input_layernorm_bias[HIDDEN_SIZE];
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

// void PhiRotaryEmbedding_forward(
//     float out_cos[SLEN][ROTARY_DIM],
//     float out_sin[SLEN][ROTARY_DIM],
//     int position_ids[SLEN]
// ) {
//     // rope type = "default"
//     // attention_scaling default is 1
//     // float attention_scaling = 1.0;

//     float inv_freq[ROTARY_DIM / 2] = {1, 0.562341, 0.316228, 0.177828, 0.1, 0.0562341, 0.0316228, 0.0177828, 0.01, 0.00562341, 0.00316228, 0.00177828, 0.001, 0.000562341, 0.000316228, 0.000177828};
//     float emb[SLEN][ROTARY_DIM];
//     for (int i = 0; i < SLEN; i++) {
//         for (int j = 0; j < ROTARY_DIM / 2; j++) {
//             emb[i][j] = i * inv_freq[j];
//             emb[i][j + ROTARY_DIM / 2] = i * inv_freq[j];
//         }
//     }
//     for (int i = 0; i < SLEN; i++) {
//         for (int j = 0; j < ROTARY_DIM; j++) {
//             // attention_scaling is 1
//             out_cos[i][j] = hls::cosf(emb[i][j]);
//             out_sin[i][j] = hls::sinf(emb[i][j]);
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

void PhiModel_forward(
    int* output_id,
    float input_embed[HIDDEN_SIZE],
    bool should_predict,
    int position_idx
) {

    // float input_embed[HIDDEN_SIZE];
    // float language_model_model_embed_tokens_weight[VOCAB_SIZE][HIDDEN_SIZE];
    // memcpy(input_embed, language_model_model_embed_tokens_weight[input_id], sizeof(float) * HIDDEN_SIZE);

    // flag: on board
    float hidden_state[HIDDEN_SIZE];
    for (int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
        memcpy(hidden_state, input_embed, sizeof(float) * HIDDEN_SIZE);
        PhiDecoderLayer_forward(input_embed, i, position_idx, hidden_state);
    }

    if (should_predict) {
        // flag: load_weight
        float language_model_model_final_layernorm_weight[HIDDEN_SIZE];
        float language_model_model_final_layernorm_bias[HIDDEN_SIZE];
        phi_layernorm(
            hidden_state,
            input_embed,
            language_model_model_final_layernorm_weight,
            language_model_model_final_layernorm_bias,
            LAYER_NORM_EPS
        );
        // flag: load_weight
        float language_model_model_lm_head_weight[VOCAB_SIZE * HIDDEN_SIZE];
        float language_model_model_lm_head_bias[VOCAB_SIZE];
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

    float cos[SLEN][ROTARY_DIM];
    float sin[SLEN][ROTARY_DIM];
    int position_ids[SLEN];
    for (int i = 0; i < SLEN; i++) {
        position_ids[i] = i;
    }
    // PhiRotaryEmbedding_forward(cos, sin, position_ids);

    bool should_predict;
    int output_id;
    int output_len = 0;
    float input_embed[HIDDEN_SIZE];
    for (int i = 0; i < SLEN; i++) {
        should_predict = (i >= (input_len - 1));
        if (i >= input_len) {
            memcpy(input_embed, input_embeds + i * HIDDEN_SIZE, sizeof(float) * HIDDEN_SIZE);
        } else {
            float language_model_model_embed_tokens_weight[VOCAB_SIZE][HIDDEN_SIZE];
            memcpy(input_embed, language_model_model_embed_tokens_weight[output_ids[output_len - 1]], sizeof(float) * HIDDEN_SIZE);
        }
        PhiModel_forward(&output_id, input_embed, should_predict, i);
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
//         float power = hls::powf(ROPE_THETA, exponent); // base^(2i/dim)
//         out_inv_freq[i] = 1.0f / power;
//     }
// }