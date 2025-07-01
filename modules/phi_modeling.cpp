#include <string.h>
#include <hls_math.h>
#include <ap_fixed.h>
#include "transformer.hpp"
#include "phi_config.hpp"

template<class T>
void rotate_half(
    T out[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    T hidden_states[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM]
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

template<class T>
void apply_rotary_pos_emb(
    T out_q_embed[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    T out_k_embed[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    T in_q[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    T in_k[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    T in_cos[SLEN][ROTARY_DIM],
    T in_sin[SLEN][ROTARY_DIM]
) {
    T rotate_half_q[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    T rotate_half_k[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    rotate_half<NUM_KEY_VALUE_HEADS, SLEN, ROTARY_DIM, T>(rotate_half_q, in_q);
    rotate_half<NUM_KEY_VALUE_HEADS, SLEN, ROTARY_DIM, T>(rotate_half_k, in_k);
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

template<class T>
void repeat_kv(
    T out[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][HEAD_DIM],
    T hidden_states[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM]
) {
    if (NUM_KEY_VALUE_GROUPS == 1) {
        memcpy(out, hidden_states, sizeof(T) * NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM);
        return;
    }
    int area_per_square = SLEN * HEAD_DIM;
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int rep = 0; rep < NUM_KEY_VALUE_GROUPS; rep++) {
            memcpy(out[i * NUM_KEY_VALUE_GROUPS + rep], hidden_states[i], sizeof(T) * area_per_square);
        }
    }
}

// TODO: Have not implemented causal mask
template<class T>
void eager_attention_forward(
    T out_attn_output[SLEN][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][HEAD_DIM],
    T out_attn_weights[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][SLEN],
    T in_q[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM],
    T in_k[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM],
    T in_v[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM],
    float in_scaling
) {
    T repeated_k[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][HEAD_DIM];
    T repeated_v[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][HEAD_DIM];
    repeat_kv<NUM_KEY_VALUE_HEADS, SLEN, HEAD_DIM, NUM_KEY_VALUE_GROUPS>(repeated_k, in_k);
    repeat_kv<NUM_KEY_VALUE_HEADS, SLEN, HEAD_DIM, NUM_KEY_VALUE_GROUPS>(repeated_v, in_v);
    T attn_output[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][HEAD_DIM];
    T attn_weights[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][SLEN];
    for (int i = 0; i < HEAD_DIM; i++) {
        for (int j = 0; j < NUM_KEY_VALUE_HEADS; j++) {
            for (int k = 0; k < NUM_KEY_VALUE_GROUPS; k++) {
                T tmp_hs[HEAD_DIM][SLEN];
                T tmp_ss[SLEN][SLEN];
                transpose<SLEN, HEAD_DIM, T>(tmp_hs, repeated_k[i][j * NUM_KEY_VALUE_GROUPS + k]);
                matmul<SLEN, HEAD_DIM, SLEN>(tmp_ss, in_q[i][j], tmp_hs);
                elementwise_mul<SLEN, SLEN>(attn_weights[i][j * NUM_KEY_VALUE_GROUPS + k], tmp_ss, in_scaling);
            }
        }
    }

    // if attention_mask is not none, do mask

    // softmax
    for (int i = 0; i < NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS; i++) {
        softmax<SLEN, SLEN>(out_attn_weights[i], attn_weights[i]);
    }

    // Do not need drop out during inferrence

    for (int i = 0; i < NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS; i++) {
        matmul<SLEN, SLEN, HEAD_DIM>(attn_output[i], out_attn_weights[i], repeated_v[i]);
    }

    // shape 0, 1 transpose for attn_output
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS; j++) {
            for (int k = 0; k < HEAD_DIM; k++) {
                out_attn_output[i][j][k] = attn_output[j][i][k];
            }
        }
    }
    
}

template<class T>
void PhiAttention_forward(
    T out_attn_output[SLEN][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM],
    T out_attn_weights[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][SLEN],
    T in_hidden_states[SLEN][HIDDEN_SIZE],
    T in_cos[SLEN][ROTARY_DIM],
    T in_sin[SLEN][ROTARY_DIM]
) {
    T linear_q[SLEN][NUM_KEY_VALUE_HEADS * HEAD_DIM];
    T linear_k[SLEN][NUM_KEY_VALUE_HEADS * HEAD_DIM];
    T linear_v[SLEN][NUM_KEY_VALUE_HEADS * HEAD_DIM];

    T wq[NUM_KEY_VALUE_HEADS * HEAD_DIM][HIDDEN_SIZE];
    T wk[NUM_KEY_VALUE_HEADS * HEAD_DIM][HIDDEN_SIZE];
    T wv[NUM_KEY_VALUE_HEADS * HEAD_DIM][HIDDEN_SIZE];
    T b[NUM_KEY_VALUE_HEADS * HEAD_DIM];

    linear<HIDDEN_SIZE, NUM_KEY_VALUE_HEADS * HEAD_DIM, SLEN>(linear_q, in_hidden_states, wq, b);
    linear<HIDDEN_SIZE, NUM_KEY_VALUE_HEADS * HEAD_DIM, SLEN>(linear_k, in_hidden_states, wk, b);
    linear<HIDDEN_SIZE, NUM_KEY_VALUE_HEADS * HEAD_DIM, SLEN>(linear_v, in_hidden_states, wv, b);

    T reshaped_linear_q[SLEN][NUM_KEY_VALUE_HEADS][HEAD_DIM];
    T reshaped_linear_k[SLEN][NUM_KEY_VALUE_HEADS][HEAD_DIM];
    T reshaped_linear_v[SLEN][NUM_KEY_VALUE_HEADS][HEAD_DIM];

    memcpy(reshaped_linear_q, linear_q, sizeof(T) * NUM_KEY_VALUE_HEADS * HEAD_DIM);
    memcpy(reshaped_linear_k, linear_k, sizeof(T) * NUM_KEY_VALUE_HEADS * HEAD_DIM);
    memcpy(reshaped_linear_v, linear_v, sizeof(T) * NUM_KEY_VALUE_HEADS * HEAD_DIM);

    T query_states[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM];
    T key_states[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM];
    T value_states[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM];

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

    T rotary_q[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    T rotary_k[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    T embed_q[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];
    T embed_k[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM];

    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < ROTARY_DIM; k++) {
                rotary_q[i][j][k] = query_states[i][j][k];
                rotary_k[i][j][k] = key_states[i][j][k];
            }
        }
    }

    apply_rotary_pos_emb<NUM_KEY_VALUE_HEADS, SLEN, ROTARY_DIM, T>(embed_q, embed_k, rotary_q, rotary_k, in_cos, in_sin);

    // 接回去
    for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
        for (int j = 0; j < SLEN; j++) {
            for (int k = 0; k < ROTARY_DIM; k++) {
                query_states[i][j][k] = embed_q[i][j][k];
                key_states[i][j][k] = embed_k[i][j][k];
            }
        }
    }

    // TODO kv_cache
    bool past_key_value;

    // attention 實作選擇：eager_attention_forward, flash_attention_2, sdpa

    // 進 attention，拿出 attn_output, attn_weights
    // int n_rep_k, n_rep_v;
    float scaling = 1.0;
    T attn_output[SLEN][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][HEAD_DIM];
    // T attn_weights[num_key_value_heads * n_rep][SLEN][SLEN];
    eager_attention_forward<NUM_KEY_VALUE_HEADS, SLEN, HEAD_DIM, NUM_KEY_VALUE_GROUPS, NUM_KEY_VALUE_GROUPS, T>(attn_output, out_attn_weights, query_states, key_states, value_states, scaling);

    // attn_output 進 Linear
    T reshaped_attn_output[SLEN][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM];
    T wo[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM][SLEN] = {0};
    T bo[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM] = {0};
    memcpy(reshaped_attn_output, attn_output, sizeof(T) * SLEN * NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM);
    linear<NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM, NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM, SLEN, T>(out_attn_output, reshaped_attn_output, wo, bo);

    // 回傳 attn_output, attn_weights

}

// TODO intermediate_size 是多少？
// class PhiMLP(nn.Module):
//     def __init__(self, config):
//         super().__init__()
//         self.config = config
//         self.activation_fn = ACT2FN[config.hidden_act]
//         self.fc1 = nn.Linear(config.hidden_size, config.intermediate_size)
//         self.fc2 = nn.Linear(config.intermediate_size, config.hidden_size)

//     def forward(self, hidden_states: torch.Tensor) -> torch.Tensor:
//         hidden_states = self.fc1(hidden_states)
//         hidden_states = self.activation_fn(hidden_states)
//         hidden_states = self.fc2(hidden_states)
//         return hidden_states

float gelu_linear(float x) {
    if (x < -1.0f) return 0.0f;
    else if (x > 1.0f) return x;
    else return 0.5f * x * (1.0f + x); // 粗略近似
}

template<class T>
void PhiMLP_forward(
    T out[SLEN][HIDDEN_SIZE],
    T in[SLEN][HIDDEN_SIZE]
) {
    T w1[INTERMEDIATE_SIZE][HIDDEN_SIZE];
    T b1[INTERMEDIATE_SIZE];
    T w2[INTERMEDIATE_SIZE][HIDDEN_SIZE];
    T b2[INTERMEDIATE_SIZE];
    T linear_out[SLEN][INTERMEDIATE_SIZE];
    T gelu_out[SLEN][INTERMEDIATE_SIZE];
    linear<HIDDEN_SIZE, INTERMEDIATE_SIZE, SLEN, T>(linear_out, in, w1, b1);
    // TODO GeLU Function 之後再做
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
            gelu_out[i][j] = (T) gelu_linear(linear_out[i][j]);
        }
    }
    linear<HIDDEN_SIZE, INTERMEDIATE_SIZE, SLEN, T>(out, gelu_out, w2, b2);
}

template<class T>
void PhiDecoderLayer_forward(
    T out[SLEN][HIDDEN_SIZE],
    T in_hidden_states[SLEN][HIDDEN_SIZE],
    T in_cos[SLEN][ROTARY_DIM],
    T in_sin[SLEN][ROTARY_DIM]
) {
    T residual[SLEN][HIDDEN_SIZE];
    memcpy(residual, in_hidden_states, sizeof(T) * SLEN * HIDDEN_SIZE);

    layer_norm<SLEN, HIDDEN_SIZE>(in_hidden_states, residual);

    T attn_output[SLEN][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM];
    T attn_weights[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][SLEN];
    PhiAttention_forward<T>(attn_output, attn_weights, in_hidden_states, in_cos, in_sin);

    T feed_forward_hidden_states[SLEN][HIDDEN_SIZE];
    PhiMLP_forward<T>(feed_forward_hidden_states, attn_output);

    // hidden_states = attn_outputs + feed_forward_hidden_states + residual
    //     outputs = (hidden_states,)

    //     if output_attentions: // 這目前是 false
    //         outputs += (self_attn_weights,)

    //     return outputs

    T tmp[SLEN][HIDDEN_SIZE];
    matadd<SLEN, HIDDEN_SIZE>(tmp, attn_output, feed_forward_hidden_states);
    matadd<SLEN, HIDDEN_SIZE>(out, tmp, residual);
}

// 算完之後的值應該就固定了，可能可以寫死
void compute_default_rope_parameters(
    float out_inv_freq[ROTARY_DIM / 2]
) {
    int dim = ROTARY_DIM;
    for (int i = 0; i < dim / 2; i++) {
        float exponent = (2.0f * i) / (float)dim;
        float power = hls::powf(ROPE_THETA, exponent);      // base^(2i/dim)
        out_inv_freq[i] = 1.0f / power;
    }
}

void PhiRotaryEmbedding_forward(
    float out_cos[SLEN][ROTARY_DIM],
    float out_sin[SLEN][ROTARY_DIM],
    float position_ids[SLEN]
) {
    // rope type = "default"
    // attention_scaling default is 1

    // float attention_scaling = 1.0;

    float inv_freq[ROTARY_DIM / 2];
    compute_default_rope_parameters(inv_freq);
    float inv_freq_expanded[ROTARY_DIM / 2][1];
    memcpy(inv_freq_expanded, inv_freq, sizeof(float) * ROTARY_DIM / 2);
    float position_ids_expanded[1][SLEN];
    memcpy(position_ids_expanded, position_ids, sizeof(float) * SLEN);
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

void PhiPreTrainedModel_init_weights() {
    // 用來定義 linear, embedding, layernorm 訓練初始參數
    // 推論用不到
}

template<class T>
void PhiModel_forward(
    T out_last_hidden_state[SLEN][HIDDEN_SIZE],
    T out_past_key_values[NUM_HIDDEN_LAYERS][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][HEAD_DIM],
    int input_ids[],
    T attention_mask[],
    float position_ids[SLEN], // 應該要是 int
    T past_key_values[], // cache
    T inputs_embeds[SLEN][HIDDEN_SIZE]
) {

    // create mask

    float cos[SLEN][ROTARY_DIM];
    float sin[SLEN][ROTARY_DIM];
    PhiRotaryEmbedding_forward(cos, sin, position_ids);

    T hidden_states[SLEN][HIDDEN_SIZE];

    for (int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
        memcpy(hidden_states, inputs_embeds, sizeof(T) * SLEN * HIDDEN_SIZE);
        PhiDecoderLayer_forward<T>(inputs_embeds, hidden_states, cos, sin);
    }

    layer_norm<SLEN, HIDDEN_SIZE>(hidden_states, inputs_embeds);

}

template<class T>
void PhiForCausalLM_forward(
    T out_loss,
    T out_logits,
    T out_past_key_values[NUM_HIDDEN_LAYERS][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][SLEN][HEAD_DIM],
    int input_ids[],
    T attention_mask[],
    float position_ids[SLEN], // 應該要是 int
    T past_key_values[], // cache
    T inputs_embeds[SLEN][HIDDEN_SIZE],
    int logits_to_keep
) {
    T last_hidden_state[SLEN][HIDDEN_SIZE];
    PhiModel_forward<T>(last_hidden_state, past_key_values, input_ids, attention_mask, position_ids, past_key_values, inputs_embeds);
    
}