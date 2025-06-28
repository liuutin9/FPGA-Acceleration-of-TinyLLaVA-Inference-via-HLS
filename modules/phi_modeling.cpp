#include <string.h>
#include "transformer.hpp"

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
template<int batch, int num_key_value_heads, int slen, int head_dim, int n_rep_k, int n_rep_v, class T>
void eager_attention_forward(
    T out_attn_output[batch][slen][num_key_value_heads * n_rep_k][head_dim],
    T out_attn_weights[batch][num_key_value_heads * n_rep_k][slen][slen],
    T in_q[batch][num_key_value_heads][slen][head_dim],
    T in_k[batch][num_key_value_heads][slen][head_dim],
    T in_v[batch][num_key_value_heads][slen][head_dim],
    double in_scaling
) {
    T repeated_k[batch][num_key_value_heads * n_rep_k][slen][head_dim];
    T repeated_v[batch][num_key_value_heads * n_rep_v][slen][head_dim];
    repeat_kv<batch, num_key_value_heads, slen, head_dim, n_rep_k>(repeated_k, in_k);
    repeat_kv<batch, num_key_value_heads, slen, head_dim, n_rep_v>(repeated_v, in_v);
    T attn_output[batch][num_key_value_heads * n_rep_k][slen][head_dim];
    T attn_weights[batch][num_key_value_heads * n_rep_k][slen][slen];
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int k = 0; k < n_rep_k; k++) {
                T tmp_hs[head_dim][slen];
                T tmp_ss[slen][slen];
                transpose<slen, head_dim, T>(tmp_hs, repeated_k[i][j * n_rep_k + k]);
                matmul<slen, head_dim, slen>(tmp_ss, in_q[i][j], tmp_hs);
                elementwise_mul<slen, slen>(attn_weights[i][j * n_rep_k + k], tmp_ss, in_scaling);
            }
        }
    }

    // softmax
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads * n_rep_k; j++) {
            softmax<slen, slen>(out_attn_weights[i][j], attn_weights[i][j]);
        }
    }

    // Do not need drop out during inferrence

    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads * n_rep_k; j++) {
            matmul<slen, slen, head_dim>(attn_output[i][j], out_attn_weights[i][j], repeated_v[i][j]);
        }
    }

    // shape 1, 2 transpose for attn_output
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < slen; j++) {
            for (int k = 0; k < num_key_value_heads * n_rep_k; k++) {
                for (int l = 0; l < head_dim; l++) {
                    out_attn_output[i][j][k][l] = attn_output[i][k][j][l];
                }
            }
        }
    }
    
}

template<int batch, int num_key_value_heads, int slen, int head_dim, int hidden_size, int n_rep, class T>
void PhiAttention_forward(
    bool qk_layernorm,
    T hidden_states[batch][slen][hidden_size],
    T out_attn_output[batch][slen][num_key_value_heads * n_rep * head_dim],
    T out_attn_weights[batch][num_key_value_heads * n_rep][slen][slen]
) {
    T linear_q[batch][slen][num_key_value_heads * head_dim];
    T linear_k[batch][slen][num_key_value_heads * head_dim];
    T linear_v[batch][slen][num_key_value_heads * head_dim];

    T wq[num_key_value_heads * head_dim][hidden_size] = {0};
    T wk[num_key_value_heads * head_dim][hidden_size] = {0};
    T wv[num_key_value_heads * head_dim][hidden_size] = {0};
    T b[num_key_value_heads * head_dim] = {0};

    for (int i = 0; i < batch; i++) {
        linear<hidden_size, num_key_value_heads * head_dim, slen>(linear_q, hidden_states, wq, b);
        linear<hidden_size, num_key_value_heads * head_dim, slen>(linear_k, hidden_states, wk, b);
        linear<hidden_size, num_key_value_heads * head_dim, slen>(linear_v, hidden_states, wv, b);
    }

    // T reshaped_q[batch][slen][num_key_value_heads][head_dim];
    // T reshaped_k[batch][slen][num_key_value_heads][head_dim];
    // T reshaped_v[batch][slen][num_key_value_heads][head_dim];

    // memcpy(reshaped_q, linear_q, sizeof(T) * batch * slen * num_key_value_heads * head_dim);
    // memcpy(reshaped_k, linear_k, sizeof(T) * batch * slen * num_key_value_heads * head_dim);
    // memcpy(reshaped_v, linear_v, sizeof(T) * batch * slen * num_key_value_heads * head_dim);

    T query_states[batch][num_key_value_heads][slen][head_dim];
    T key_states[batch][num_key_value_heads][slen][head_dim];
    T value_states[batch][num_key_value_heads][slen][head_dim];

    // transpose 1, 2
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < head_dim; l++) {
                    query_states[i][j][k][l] = linear_q[i][k][j * head_dim + l];
                    key_states[i][j][k][l] = linear_k[i][k][j * head_dim + l];
                    value_states[i][j][k][l] = linear_v[i][k][j * head_dim + l];
                }
            }
        }
    }

    if (qk_layernorm) {
        T tmp_q[batch][num_key_value_heads][slen][head_dim];
        T tmp_k[batch][num_key_value_heads][slen][head_dim];
        memcpy(tmp_q, query_states, sizeof(T) * batch * num_key_value_heads * slen * head_dim);
        memcpy(tmp_k, key_states, sizeof(T) * batch * num_key_value_heads * slen * head_dim);
        for (int i = 0; i < batch; i++) {
            for (int j = 0; j < num_key_value_heads; j++) {
                layer_norm<slen, head_dim>(query_states, tmp_q);
                layer_norm<slen, head_dim>(key_states, tmp_k);
            }
        }
    }

    int rotary_dim = head_dim / 2; // < -> rotate, > -> do nothing = (int(self.head_dim * config.partial_rotary_factor))
    T cos[batch][slen][rotary_dim] = {0};
    T sin[batch][slen][rotary_dim] = {0};
    T rotary_q[batch][num_key_value_heads][slen][rotary_dim];
    T rotary_k[batch][num_key_value_heads][slen][rotary_dim];
    T embed_q[batch][num_key_value_heads][slen][rotary_dim];
    T embed_k[batch][num_key_value_heads][slen][rotary_dim];

    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < rotary_dim; l++) {
                    rotary_q[i][j][k][l] = query_states[i][j][k][l];
                    rotary_k[i][j][k][l] = key_states[i][j][k][l];
                }
            }
        }
    }

    apply_rotary_pos_emb<batch, num_key_value_heads, slen, rotary_dim, T>(embed_q, embed_k, rotary_q, rotary_k, cos, sin);

    // 接回去
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < rotary_dim; l++) {
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
    T attn_output[batch][slen][num_key_value_heads * n_rep][head_dim];
    // T attn_weights[batch][num_key_value_heads * n_rep][slen][slen];
    eager_attention_forward<batch, num_key_value_heads, slen, head_dim, n_rep, n_rep, T>(attn_output, out_attn_weights, query_states, key_states, value_states, scaling);

    // attn_output 進 Linear
    T reshaped_attn_output[batch][slen][num_key_value_heads * n_rep * head_dim];
    T wo[num_key_value_heads * n_rep * head_dim][slen] = {0};
    T bo[num_key_value_heads * n_rep * head_dim] = {0};
    memcpy(reshaped_attn_output, attn_output, sizeof(T) * batch * slen * num_key_value_heads * n_rep * head_dim);
    for (int i = 0; i < batch; i++) {
        linear<slen, num_key_value_heads * n_rep * head_dim>(out_attn_output, reshaped_attn_output, wo, bo);
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