#include <string.h>
#include <hls_math.h>
#include <ap_fixed.h>
#include "../basic/transformer.hpp"
#include "./phi-2_config.hpp"

void rotate_half(
    float out[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float hidden_states[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM]
) {
    int half_dim = ROTARY_DIM / 2;
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < half_dim; k++) {
                out[i][j][k] = (-1) * hidden_states[i][j][k + half_dim];
                out[i][j][k + half_dim] = hidden_states[i][j][k];
            }
        }
    }
}

void apply_rotary_pos_emb(
    float out_q_embed[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float out_k_embed[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float in_q[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float in_k[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float in_cos[SLEN][ROTARY_DIM],
    float in_sin[SLEN][ROTARY_DIM]
) {
    float rotate_half_q[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    float rotate_half_k[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    rotate_half(rotate_half_q, in_q);
    rotate_half(rotate_half_k, in_k);
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < ROTARY_DIM; k++) {
                out_q_embed[i][j][k] = in_q[i][j][k] * in_cos[j][k];
                out_k_embed[i][j][k] = in_k[i][j][k] * in_cos[j][k];
                out_q_embed[i][j][k] += rotate_half_q[i][j][k] * in_sin[j][k];
                out_k_embed[i][j][k] += rotate_half_k[i][j][k] * in_sin[j][k];
            }
        }
    }
}

void repeat_kv(
    float out[NUM_ATTENTION_HEADS][SLEN][HEAD_DIM],
    float hidden_states[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM]
) {
    if (NUM_KEY_VALUE_GROUPS == 1) {
        memcpy(out, hidden_states, sizeof(float) * NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM);
        return;
    }
    int area_per_square = SLEN * HEAD_DIM;
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int rep = 0; rep < NUM_KEY_VALUE_GROUPS; rep++) {
            memcpy(out[i * NUM_KEY_VALUE_GROUPS + rep], hidden_states[i], sizeof(float) * area_per_square);
        }
    }
}

// TODO: Have not implemented causal mask
void eager_attention_forward(
    float out_attn_output[SLEN][NUM_ATTENTION_HEADS][HEAD_DIM],
    float out_attn_weights[NUM_ATTENTION_HEADS][SLEN][SLEN],
    float in_q[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM],
    float in_k[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM],
    float in_v[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM],
    float in_attention_mask[NUM_ATTENTION_HEADS][SLEN][SLEN],
    float in_scaling
) {
    // phi doesn't need to repeat k, v
    // float repeated_k[NUM_ATTENTION_HEADS][SLEN][HEAD_DIM];
    // float repeated_v[NUM_ATTENTION_HEADS][SLEN][HEAD_DIM];
    // repeat_kv(repeated_k, in_k);
    // repeat_kv(repeated_v, in_v);

    float transposed_k[NUM_ATTENTION_HEADS][HEAD_DIM][SLEN];
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        // phi doesn't need to repeat k, v
        // transpose<SLEN, HEAD_DIM, float>(transposed_k[i], repeated_k[i]);
        transpose<SLEN, HEAD_DIM, float>(transposed_k[i], in_k[i]);
    }

    float unscaled_attn_weights[NUM_ATTENTION_HEADS][SLEN][SLEN];
    for (int i = 0; i < NUM_ATTENTION_HEADS; i++) {
        matmul<SLEN, HEAD_DIM, SLEN, float>(unscaled_attn_weights[i], in_q[i], transposed_k[i]);
    }

    float unmasked_attn_weights[NUM_ATTENTION_HEADS][SLEN][SLEN];
    for (int i = 0; i < NUM_ATTENTION_HEADS; i++) {
        elementwise_mul<SLEN, SLEN, float>(unmasked_attn_weights[i], unscaled_attn_weights[i], in_scaling);
    }

    // causal mask
    float unsoftmax_attn_weights[NUM_ATTENTION_HEADS][SLEN][SLEN];
    for (int i = 0; i < NUM_ATTENTION_HEADS; i++) {
        matadd<SLEN, SLEN, float>(unsoftmax_attn_weights[i], unmasked_attn_weights[i], in_attention_mask[i]);
    }

    // softmax
    for (int i = 0; i < NUM_ATTENTION_HEADS; i++) {
        softmax<SLEN, SLEN>(out_attn_weights[i], unsoftmax_attn_weights[i]);
    }

    // Do not need drop out during inferrence

    float attn_output[NUM_ATTENTION_HEADS][SLEN][HEAD_DIM];
    for (int i = 0; i < NUM_ATTENTION_HEADS; i++) {
        // phi doesn't need to repeat k, v
        // matmul<SLEN, SLEN, HEAD_DIM>(attn_output[i], out_attn_weights[i], repeated_v[i]);
        matmul<SLEN, SLEN, HEAD_DIM, float>(attn_output[i], out_attn_weights[i], in_v[i]);
    }

    // shape 0, 1 transpose for attn_output
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < NUM_ATTENTION_HEADS; j++) {
            for (int k = 0; k < HEAD_DIM; k++) {
                out_attn_output[i][j][k] = attn_output[j][i][k];
            }
        }
    }
    
}

void PhiAttention_forward(
    float out_attn_output[SLEN][NUM_ATTENTION_HEADS * HEAD_DIM],
    float out_attn_weights[NUM_ATTENTION_HEADS][SLEN][SLEN],
    int layer_id,
    float in_hidden_states[SLEN][HIDDEN_SIZE],
    float in_cos[SLEN][ROTARY_DIM],
    float in_sin[SLEN][ROTARY_DIM],
    float in_attention_mask[NUM_ATTENTION_HEADS][SLEN][SLEN]
) {
    float linear_q[SLEN][NUM_KEY_VALUE_HEADS * HEAD_DIM];
    float linear_k[SLEN][NUM_KEY_VALUE_HEADS * HEAD_DIM];
    float linear_v[SLEN][NUM_KEY_VALUE_HEADS * HEAD_DIM];

    // flag: load_weight
    // 要看 layer_id
    // q_proj
    float language_model_model_layers_0_self_attn_q_proj_weight[NUM_KEY_VALUE_HEADS * HEAD_DIM][HIDDEN_SIZE];
    float language_model_model_layers_0_self_attn_q_proj_bias[NUM_KEY_VALUE_HEADS * HEAD_DIM];
    linear<HIDDEN_SIZE, NUM_KEY_VALUE_HEADS * HEAD_DIM, SLEN>(linear_q, in_hidden_states, language_model_model_layers_0_self_attn_q_proj_weight, language_model_model_layers_0_self_attn_q_proj_bias);
    // k_proj
    float language_model_model_layers_0_self_attn_k_proj_weight[NUM_KEY_VALUE_HEADS * HEAD_DIM][HIDDEN_SIZE];
    float language_model_model_layers_0_self_attn_k_proj_bias[NUM_KEY_VALUE_HEADS * HEAD_DIM];
    linear<HIDDEN_SIZE, NUM_KEY_VALUE_HEADS * HEAD_DIM, SLEN>(linear_k, in_hidden_states, language_model_model_layers_0_self_attn_k_proj_weight, language_model_model_layers_0_self_attn_k_proj_bias);
    // v_proj
    float language_model_model_layers_0_self_attn_v_proj_weight[NUM_KEY_VALUE_HEADS * HEAD_DIM][HIDDEN_SIZE];
    float language_model_model_layers_0_self_attn_v_proj_bias[NUM_KEY_VALUE_HEADS * HEAD_DIM];
    linear<HIDDEN_SIZE, NUM_KEY_VALUE_HEADS * HEAD_DIM, SLEN>(linear_v, in_hidden_states, language_model_model_layers_0_self_attn_v_proj_weight, language_model_model_layers_0_self_attn_v_proj_bias);

    float reshaped_linear_q[SLEN][NUM_KEY_VALUE_HEADS][HEAD_DIM];
    float reshaped_linear_k[SLEN][NUM_KEY_VALUE_HEADS][HEAD_DIM];
    float reshaped_linear_v[SLEN][NUM_KEY_VALUE_HEADS][HEAD_DIM];

    memcpy(reshaped_linear_q, linear_q, sizeof(float) * NUM_KEY_VALUE_HEADS * HEAD_DIM);
    memcpy(reshaped_linear_k, linear_k, sizeof(float) * NUM_KEY_VALUE_HEADS * HEAD_DIM);
    memcpy(reshaped_linear_v, linear_v, sizeof(float) * NUM_KEY_VALUE_HEADS * HEAD_DIM);

    float query_states[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM];
    float key_states[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM];
    float value_states[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM];

    // transpose 0, 1
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < HEAD_DIM; k++) {
                query_states[i][j][k] = reshaped_linear_q[j][i][k];
                key_states[i][j][k] = reshaped_linear_k[j][i][k];
                value_states[i][j][k] = reshaped_linear_v[j][i][k];
            }
        }
    }

    // QK_LAYERNORM is false
    // if (QK_LAYERNORM) {
    //     T tmp_q[num_key_value_heads][SLEN][head_dim];
    //     T tmp_k[num_key_value_heads][SLEN][head_dim];
    //     memcpy(tmp_q, query_states, sizeof(T) * batch * num_key_value_heads * SLEN * head_dim);
    //     memcpy(tmp_k, key_states, sizeof(T) * batch * num_key_value_heads * SLEN * head_dim);
    //     for (int i = 0; i < batch; i++) {
    //         for (int j = 0; j < num_key_value_heads; j++) {
    //             layer_norm<SLEN, head_dim>(query_states, tmp_q);
    //             layer_norm<SLEN, head_dim>(key_states, tmp_k);
    //         }
    //     }
    // }

    float rotary_q[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    float rotary_k[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    float embed_q[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    float embed_k[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];

    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < ROTARY_DIM; k++) {
                rotary_q[i][j][k] = query_states[i][j][k];
                rotary_k[i][j][k] = key_states[i][j][k];
            }
        }
    }

    apply_rotary_pos_emb(embed_q, embed_k, rotary_q, rotary_k, in_cos, in_sin);

    // 接回去
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < ROTARY_DIM; k++) {
                query_states[i][j][k] = embed_q[i][j][k];
                key_states[i][j][k] = embed_k[i][j][k];
            }
        }
    }

    // TODO: kv_cache
    bool past_key_value;

    // attention 實作可選擇：eager_attention_forward, flash_attention_2, sdpa

    // 進 attention，拿出 attn_output, attn_weights
    float scaling = 1.0;
    float attn_output[SLEN][NUM_ATTENTION_HEADS][HEAD_DIM];
    eager_attention_forward(attn_output, out_attn_weights, query_states, key_states, value_states, in_attention_mask, scaling);

    // attn_output 進 Linear
    float reshaped_attn_output[SLEN][NUM_ATTENTION_HEADS * HEAD_DIM];
    memcpy(reshaped_attn_output, attn_output, sizeof(float) * SLEN * NUM_ATTENTION_HEADS * HEAD_DIM);
    // flag: load_weight
    // 要看 layer_id
    float language_model_model_layers_0_self_attn_dense_weight[NUM_ATTENTION_HEADS * HEAD_DIM][NUM_ATTENTION_HEADS * HEAD_DIM];
    float language_model_model_layers_0_self_attn_dense_bias[NUM_ATTENTION_HEADS * HEAD_DIM];
    linear<NUM_ATTENTION_HEADS * HEAD_DIM, NUM_ATTENTION_HEADS * HEAD_DIM, SLEN, float>(out_attn_output, reshaped_attn_output, language_model_model_layers_0_self_attn_dense_weight, language_model_model_layers_0_self_attn_dense_bias);
}

void PhiMLP_forward(
    float out[SLEN][HIDDEN_SIZE],
    float in[SLEN][HIDDEN_SIZE],
    int layer_id
) {
    // flag: load_weight
    // 要看 layer_id
    float language_model_model_layers_0_mlp_fc1_weight[INTERMEDIATE_SIZE][HIDDEN_SIZE];
    float language_model_model_layers_0_mlp_fc1_bias[INTERMEDIATE_SIZE];
    float linear_out[SLEN][INTERMEDIATE_SIZE];
    linear<HIDDEN_SIZE, INTERMEDIATE_SIZE, SLEN, float>(linear_out, in, language_model_model_layers_0_mlp_fc1_weight, language_model_model_layers_0_mlp_fc1_bias);
    
    // TODO GeLU Function 先用 hls 的
    float gelu_out[SLEN][INTERMEDIATE_SIZE];
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
            gelu_out[i][j] = new_gelu(linear_out[i][j]);
        }
    }

    // flag: load_weight
    // 要看 layer_id
    float language_model_model_layers_0_mlp_fc2_weight[HIDDEN_SIZE][INTERMEDIATE_SIZE];
    float language_model_model_layers_0_mlp_fc2_bias[HIDDEN_SIZE];
    linear<INTERMEDIATE_SIZE, HIDDEN_SIZE, SLEN, float>(out, gelu_out, language_model_model_layers_0_mlp_fc2_weight, language_model_model_layers_0_mlp_fc2_bias);
}

void PhiDecoderLayer_forward(
    float out[SLEN][HIDDEN_SIZE],
    int layer_id,
    float in_hidden_states[SLEN][HIDDEN_SIZE],
    float in_cos[SLEN][ROTARY_DIM],
    float in_sin[SLEN][ROTARY_DIM],
    float in_attention_mask[NUM_ATTENTION_HEADS][SLEN][SLEN]
) {
    float residual[SLEN][HIDDEN_SIZE];
    memcpy(residual, in_hidden_states, sizeof(float) * SLEN * HIDDEN_SIZE);

    // flag: load_weight
    // 要看 layer_id
    float language_model_model_layers_0_input_layernorm_weight[SLEN][HIDDEN_SIZE];
    float language_model_model_layers_0_input_layernorm_bias[HIDDEN_SIZE];
    layer_norm<SLEN, HIDDEN_SIZE>(in_hidden_states, residual, LAYER_NORM_EPS, language_model_model_layers_0_input_layernorm_weight, language_model_model_layers_0_input_layernorm_bias);

    float attn_output[SLEN][NUM_ATTENTION_HEADS * HEAD_DIM];
    float attn_weights[NUM_ATTENTION_HEADS][SLEN][SLEN];
    PhiAttention_forward(attn_output, attn_weights, layer_id, in_hidden_states, in_cos, in_sin, in_attention_mask);

    float feed_forward_hidden_states[SLEN][HIDDEN_SIZE];
    PhiMLP_forward(feed_forward_hidden_states, attn_output, layer_id);

    float tmp[SLEN][HIDDEN_SIZE];
    matadd<SLEN, HIDDEN_SIZE, float>(tmp, attn_output, feed_forward_hidden_states);
    matadd<SLEN, HIDDEN_SIZE, float>(out, tmp, residual);
}

void PhiRotaryEmbedding_forward(
    float out_cos[SLEN][ROTARY_DIM],
    float out_sin[SLEN][ROTARY_DIM],
    int position_ids[SLEN]
) {
    // rope type = "default"
    // attention_scaling default is 1
    // float attention_scaling = 1.0;

    float inv_freq[ROTARY_DIM / 2];
    compute_default_rope_parameters(inv_freq);
    float inv_freq_expanded[ROTARY_DIM / 2][1];
    memcpy(inv_freq_expanded, inv_freq, sizeof(float) * ROTARY_DIM / 2);
    float position_ids_expanded[1][SLEN];
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < SLEN; j++) {
            position_ids_expanded[i][j] = (float) position_ids[j];
        }
    }
    float freqs_transposed[ROTARY_DIM / 2][SLEN];
    matmul<ROTARY_DIM / 2, 1, SLEN>(freqs_transposed, inv_freq_expanded, position_ids_expanded);
    float freqs[SLEN][ROTARY_DIM / 2];
    transpose<ROTARY_DIM / 2, SLEN>(freqs, freqs_transposed);
    float emb[SLEN][ROTARY_DIM];
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < ROTARY_DIM / 2; j++) {
            emb[i][j] = freqs[i][j];
            emb[i][j + ROTARY_DIM / 2] = freqs[i][j];
        }
    }
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < ROTARY_DIM; j++) {
            // cosf -> f means float not double
            // out_cos = cosf(emb[i][j]) * attention_scaling;
            // out_sin = sinf(emb[i][j]) * attention_scaling;

            // attention_scaling is 1
            out_cos[i][j] = hls::cosf(emb[i][j]);
            out_sin[i][j] = hls::sinf(emb[i][j]);
        }
    }
}

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
void Embedding_forward(
    float out[SLEN][HIDDEN_SIZE],
    int input_ids[SLEN]
) {
    // 從 language_model_model_embed_tokens_weight 拿
    float language_model_model_embed_tokens_weight[VOCAB_SIZE][HIDDEN_SIZE];
    for (int i = 0; i < SLEN; ++i) {
        int idx = input_ids[i];

        // 直接查表，不檢查越界
        for (int j = 0; j < HIDDEN_SIZE; ++j) {
            out[i][j] = language_model_model_embed_tokens_weight[idx][j];
        }
    }
}

void PhiModel_forward(
    float out_last_hidden_state[SLEN][HIDDEN_SIZE],
    float out_past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM],
    int in_input_ids[SLEN],
    float in_past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM] // cache
) {

    float inputs_embeds[SLEN][HIDDEN_SIZE];
    Embedding_forward(inputs_embeds, in_input_ids);

    // create mask
    float attention_mask[NUM_ATTENTION_HEADS][SLEN][SLEN];
    create_causal_mask(attention_mask);

    float cos[SLEN][ROTARY_DIM];
    float sin[SLEN][ROTARY_DIM];
    int position_ids[SLEN];
    for (int i = 0; i < SLEN; i++) {
        position_ids[i] = i;
    }
    PhiRotaryEmbedding_forward(cos, sin, position_ids);

    float hidden_states[SLEN][HIDDEN_SIZE];

    for (int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
        memcpy(hidden_states, inputs_embeds, sizeof(float) * SLEN * HIDDEN_SIZE);
        PhiDecoderLayer_forward(inputs_embeds, i, hidden_states, cos, sin, attention_mask);
    }

    // flag: load_weight
    float language_model_model_final_layernorm_weight[SLEN][HIDDEN_SIZE];
    float language_model_model_final_layernorm_bias[HIDDEN_SIZE];
    layer_norm<SLEN, HIDDEN_SIZE>(hidden_states, inputs_embeds, LAYER_NORM_EPS, language_model_model_final_layernorm_weight, language_model_model_final_layernorm_bias);
}

void PhiForCausalLM_forward(
    float out_logits[SLEN][VOCAB_SIZE],
    float out_past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM],
    int input_ids[SLEN],
    float past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM] // cache
) {
    float last_hidden_state[SLEN][HIDDEN_SIZE];
    PhiModel_forward(last_hidden_state, out_past_key_values, input_ids, past_key_values);

    // flag: load_weight
    float language_model_lm_head_weight[VOCAB_SIZE][HIDDEN_SIZE];
    float language_model_lm_head_bias[VOCAB_SIZE];
    linear<HIDDEN_SIZE, VOCAB_SIZE, SLEN, float>(out_logits, last_hidden_state, language_model_lm_head_weight, language_model_lm_head_bias);
}

// 算完之後的值應該就固定了，可能可以寫死
void compute_default_rope_parameters(
    float out_inv_freq[ROTARY_DIM / 2]
) {
    int dim = ROTARY_DIM;
    for (int i = 0; i < dim / 2; i++) {
        float exponent = (2.0f * i) / (float)dim;
        float power = hls::powf(ROPE_THETA, exponent); // base^(2i/dim)
        out_inv_freq[i] = 1.0f / power;
    }
}

void create_causal_mask(
    float out_causal_mask[NUM_ATTENTION_HEADS][SLEN][SLEN]
) {
    for (int i = 0; i < NUM_ATTENTION_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < SLEN; k++) {
                out_causal_mask[i][j][k] = k <= j ? 0.0 : -1e9;
            }
        }
    }
}