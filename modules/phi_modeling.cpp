#include <string.h>
#include "transformer.hpp"
#include "phi_config.hpp"

template<int batch, int num_key_value_heads, int slen, int rotary_dim, class T>
void rotate_half(
    T out[batch][num_key_value_heads][slen][rotary_dim],
    T hidden_states[batch][num_key_value_heads][slen][rotary_dim]
) {
    int half_dim = rotary_dim / 2;
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < half_dim; l++) {
                    out[i][j][k][l] = (-1) * hidden_states[i][j][k][l + half_dim];
                    out[i][j][k][l + half_dim] = hidden_states[i][j][k][l];
                }
            }
        }
    }
}

template<int batch, int num_key_value_heads, int slen, int rotary_dim, class T>
void apply_rotary_pos_emb(
    T out_q_embed[batch][num_key_value_heads][slen][rotary_dim],
    T out_k_embed[batch][num_key_value_heads][slen][rotary_dim],
    T in_q[batch][num_key_value_heads][slen][rotary_dim],
    T in_k[batch][num_key_value_heads][slen][rotary_dim],
    T in_cos[batch][slen][rotary_dim],
    T in_sin[batch][slen][rotary_dim]
) {
    T rotate_half_q[batch][num_key_value_heads][slen][rotary_dim];
    T rotate_half_k[batch][num_key_value_heads][slen][rotary_dim];
    rotate_half<batch, num_key_value_heads, slen, rotary_dim, T>(rotate_half_q, in_q);
    rotate_half<batch, num_key_value_heads, slen, rotary_dim, T>(rotate_half_k, in_k);
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < rotary_dim; l++) {
                    out_q_embed[i][j][k][j] = in_q[i][j][k][l] * in_cos[i][k][l];
                    out_k_embed[i][j][k][j] = in_k[i][j][k][l] * in_cos[i][k][l];
                    out_q_embed[i][j][k][j] += rotate_half_q[i][j][k][l] * in_sin[i][k][l];
                    out_k_embed[i][j][k][j] += rotate_half_k[i][j][k][l] * in_sin[i][k][l];
                }
            }
        }
    }

}

template<int batch, int num_key_value_heads, int slen, int head_dim, int n_rep, class T>
void repeat_kv(
    T out[batch][num_key_value_heads * n_rep][slen][head_dim],
    T hidden_states[batch][num_key_value_heads][slen][head_dim]
) {
    if (n_rep == 1) {
        memcpy(out, hidden_states, sizeof(T) * batch * num_key_value_heads * slen * head_dim);
        return;
    }
    int area_per_square = slen * head_dim;
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int rep = 0; rep < n_rep; rep++) {
                memcpy(out[i][j * n_rep + rep], hidden_states[i][j], sizeof(T) * area_per_square);
            }
        }
    }
    return;
}

// TODO: Have not implemented causal mask
template<int batch, int num_key_value_heads, int slen, int head_dim, class T>
void eager_attention_forward(
    T out_attn_output[batch][slen][num_key_value_heads * NUM_KEY_VALUE_GROUPS][head_dim],
    T out_attn_weights[batch][num_key_value_heads * NUM_KEY_VALUE_GROUPS][slen][slen],
    T in_q[batch][num_key_value_heads][slen][head_dim],
    T in_k[batch][num_key_value_heads][slen][head_dim],
    T in_v[batch][num_key_value_heads][slen][head_dim],
    double in_scaling
) {
    T repeated_k[batch][num_key_value_heads * NUM_KEY_VALUE_GROUPS][slen][head_dim];
    T repeated_v[batch][num_key_value_heads * NUM_KEY_VALUE_GROUPS][slen][head_dim];
    repeat_kv<batch, num_key_value_heads, slen, head_dim, NUM_KEY_VALUE_GROUPS>(repeated_k, in_k);
    repeat_kv<batch, num_key_value_heads, slen, head_dim, NUM_KEY_VALUE_GROUPS>(repeated_v, in_v);
    T attn_output[batch][num_key_value_heads * NUM_KEY_VALUE_GROUPS][slen][head_dim];
    T attn_weights[batch][num_key_value_heads * NUM_KEY_VALUE_GROUPS][slen][slen];
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int k = 0; k < NUM_KEY_VALUE_GROUPS; k++) {
                T tmp_hs[head_dim][slen];
                T tmp_ss[slen][slen];
                transpose<slen, head_dim, T>(tmp_hs, repeated_k[i][j * NUM_KEY_VALUE_GROUPS + k]);
                matmul<slen, head_dim, slen>(tmp_ss, in_q[i][j], tmp_hs);
                elementwise_mul<slen, slen>(attn_weights[i][j * NUM_KEY_VALUE_GROUPS + k], tmp_ss, in_scaling);
            }
        }
    }

    // softmax
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads * NUM_KEY_VALUE_GROUPS; j++) {
            softmax<slen, slen>(out_attn_weights[i][j], attn_weights[i][j]);
        }
    }

    // Do not need drop out during inferrence

    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads * NUM_KEY_VALUE_GROUPS; j++) {
            matmul<slen, slen, head_dim>(attn_output[i][j], out_attn_weights[i][j], repeated_v[i][j]);
        }
    }

    // shape 1, 2 transpose for attn_output
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < slen; j++) {
            for (int k = 0; k < num_key_value_heads * NUM_KEY_VALUE_GROUPS; k++) {
                for (int l = 0; l < head_dim; l++) {
                    out_attn_output[i][j][k][l] = attn_output[i][k][j][l];
                }
            }
        }
    }
    
}

template<int batch, int slen, class T>
void PhiAttention_forward(
    T out_attn_output[batch][slen][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM],
    T out_attn_weights[batch][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][slen][slen],
    T in_hidden_states[batch][slen][HIDDEN_SIZE]
) {
    T linear_q[batch][slen][NUM_KEY_VALUE_HEADS * HEAD_DIM];
    T linear_k[batch][slen][NUM_KEY_VALUE_HEADS * HEAD_DIM];
    T linear_v[batch][slen][NUM_KEY_VALUE_HEADS * HEAD_DIM];

    T wq[NUM_KEY_VALUE_HEADS * HEAD_DIM][HIDDEN_SIZE] = {0};
    T wk[NUM_KEY_VALUE_HEADS * HEAD_DIM][HIDDEN_SIZE] = {0};
    T wv[NUM_KEY_VALUE_HEADS * HEAD_DIM][HIDDEN_SIZE] = {0};
    T b[NUM_KEY_VALUE_HEADS * HEAD_DIM] = {0};

    for (int i = 0; i < batch; i++) {
        linear<HIDDEN_SIZE, NUM_KEY_VALUE_HEADS * HEAD_DIM, slen>(linear_q, in_hidden_states, wq, b);
        linear<HIDDEN_SIZE, NUM_KEY_VALUE_HEADS * HEAD_DIM, slen>(linear_k, in_hidden_states, wk, b);
        linear<HIDDEN_SIZE, NUM_KEY_VALUE_HEADS * HEAD_DIM, slen>(linear_v, in_hidden_states, wv, b);
    }

    T query_states[batch][NUM_KEY_VALUE_HEADS][slen][HEAD_DIM];
    T key_states[batch][NUM_KEY_VALUE_HEADS][slen][HEAD_DIM];
    T value_states[batch][NUM_KEY_VALUE_HEADS][slen][HEAD_DIM];

    // transpose 1, 2
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < NUM_KEY_VALUE_HEADS; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < HEAD_DIM; l++) {
                    query_states[i][j][k][l] = linear_q[i][k][j * HEAD_DIM + l];
                    key_states[i][j][k][l] = linear_k[i][k][j * HEAD_DIM + l];
                    value_states[i][j][k][l] = linear_v[i][k][j * HEAD_DIM + l];
                }
            }
        }
    }

    // QK_LAYERNORM is false
    // if (QK_LAYERNORM) {
    //     T tmp_q[batch][num_key_value_heads][slen][head_dim];
    //     T tmp_k[batch][num_key_value_heads][slen][head_dim];
    //     memcpy(tmp_q, query_states, sizeof(T) * batch * num_key_value_heads * slen * head_dim);
    //     memcpy(tmp_k, key_states, sizeof(T) * batch * num_key_value_heads * slen * head_dim);
    //     for (int i = 0; i < batch; i++) {
    //         for (int j = 0; j < num_key_value_heads; j++) {
    //             layer_norm<slen, head_dim>(query_states, tmp_q);
    //             layer_norm<slen, head_dim>(key_states, tmp_k);
    //         }
    //     }
    // }

    T cos[batch][slen][ROTARY_DIM] = {0};
    T sin[batch][slen][ROTARY_DIM] = {0};
    T rotary_q[batch][NUM_KEY_VALUE_HEADS][slen][ROTARY_DIM];
    T rotary_k[batch][NUM_KEY_VALUE_HEADS][slen][ROTARY_DIM];
    T embed_q[batch][NUM_KEY_VALUE_HEADS][slen][ROTARY_DIM];
    T embed_k[batch][NUM_KEY_VALUE_HEADS][slen][ROTARY_DIM];

    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < NUM_KEY_VALUE_HEADS; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < ROTARY_DIM; l++) {
                    rotary_q[i][j][k][l] = query_states[i][j][k][l];
                    rotary_k[i][j][k][l] = key_states[i][j][k][l];
                }
            }
        }
    }

    apply_rotary_pos_emb<batch, NUM_KEY_VALUE_HEADS, slen, ROTARY_DIM, T>(embed_q, embed_k, rotary_q, rotary_k, cos, sin);

    // 接回去
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < NUM_KEY_VALUE_HEADS; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < ROTARY_DIM; l++) {
                    query_states[i][j][k][l] = embed_q[i][j][k][l];
                    key_states[i][j][k][l] = embed_k[i][j][k][l];
                }
            }
        }
    }

    // TODO kv_cache
    bool past_key_value;

    // attention 實作選擇：eager_attention_forward, flash_attention_2, sdpa

    // 進 attention，拿出 attn_output, attn_weights
    // int n_rep_k, n_rep_v;
    double scaling = 1.0;
    T attn_output[batch][slen][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][HEAD_DIM];
    // T attn_weights[batch][num_key_value_heads * n_rep][slen][slen];
    eager_attention_forward<batch, NUM_KEY_VALUE_HEADS, slen, HEAD_DIM, NUM_KEY_VALUE_GROUPS, NUM_KEY_VALUE_GROUPS, T>(attn_output, out_attn_weights, query_states, key_states, value_states, scaling);

    // attn_output 進 Linear
    T reshaped_attn_output[batch][slen][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM];
    T wo[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM][slen] = {0};
    T bo[NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM] = {0};
    memcpy(reshaped_attn_output, attn_output, sizeof(T) * batch * slen * NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM);
    for (int i = 0; i < batch; i++) {
        linear<NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM, NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM, slen, T>(out_attn_output, reshaped_attn_output, wo, bo);
    }
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

template<int batch, int slen, class T>
void PhiMLP_forward(
    T out[batch][slen][HIDDEN_SIZE],
    T in[batch][slen][HIDDEN_SIZE]
) {
    T w1[INTERMEDIATE_SIZE][HIDDEN_SIZE];
    T b1[INTERMEDIATE_SIZE];
    T w2[INTERMEDIATE_SIZE][HIDDEN_SIZE];
    T b2[INTERMEDIATE_SIZE];
    T linear_out[batch][slen][INTERMEDIATE_SIZE];
    T gelu_out[batch][slen][INTERMEDIATE_SIZE];
    for (int i = 0; i < batch; i++) {
        linear<HIDDEN_SIZE, INTERMEDIATE_SIZE, slen, T>(linear_out[i], in[i], w1, b1);
        // TODO GeLU Function 之後再做
        for (int j = 0; j < slen; j++) {
            for (int k = 0; k < INTERMEDIATE_SIZE; k++) {
                gelu_out[i][j][k] = (T) gelu_linear(linear_out[i][j][k]);
            }
        }
        linear<HIDDEN_SIZE, INTERMEDIATE_SIZE, slen, T>(out[i], gelu_out[i], w2, b2);
    }
}

template<int batch, int slen, class T>
void PhiDecoderLayer_forward(
    T out[batch][slen][HIDDEN_SIZE],
    T in_hidden_states[batch][slen][HIDDEN_SIZE]
) {
    T residual[batch][slen][HIDDEN_SIZE];
    memcpy(residual, in_hidden_states, sizeof(T) * batch * slen * HIDDEN_SIZE);

    for (int i = 0; i < batch; i++) {
        layer_norm<slen, HIDDEN_SIZE>(in_hidden_states[i], residual[i]);
    }

    T attn_output[batch][slen][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS * HEAD_DIM];
    T attn_weights[batch][NUM_KEY_VALUE_HEADS * NUM_KEY_VALUE_GROUPS][slen][slen];
    PhiAttention_forward<batch, slen, T>(attn_output, attn_weights, in_hidden_states);

    T feed_forward_hidden_states[batch][slen][HIDDEN_SIZE];
    PhiMLP_forward<batch, slen, T>(feed_forward_hidden_states, attn_output);

    // hidden_states = attn_outputs + feed_forward_hidden_states + residual
    //     outputs = (hidden_states,)

    //     if output_attentions: // 這目前是 false
    //         outputs += (self_attn_weights,)

    //     return outputs

    T tmp[batch][slen][HIDDEN_SIZE];
    for (int i = 0; i < batch; i++) {
        matadd<slen, HIDDEN_SIZE>(tmp[i], attn_output[i], feed_forward_hidden_states[i]);
        matadd<slen, HIDDEN_SIZE>(out[i], tmp[i], residual[i]);
    }
}

void PhiRotaryEmbedding_forward() {

}

void PhiPreTrainedModel() {

}

void PhiModel_forward() {

}

void PhiForCausalLM_forward() {

}