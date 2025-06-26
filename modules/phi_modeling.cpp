#include <string.h>
#include "transformer.hpp"

template<int batch, int num_key_value_heads, int slen, int head_dim, class T>
void rotate_half(
    T out[batch][num_key_value_heads][slen][head_dim],
    T hidden_states[batch][num_key_value_heads][slen][head_dim]
) {
    int half_dim = head_dim / 2;
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

template<int batch, int num_key_value_heads, int slen, int head_dim, class T>
void apply_rotary_pos_emb(
    T out_q_embed[batch][num_key_value_heads][slen][head_dim],
    T out_k_embed[batch][num_key_value_heads][slen][head_dim],
    T in_q[batch][num_key_value_heads][slen][head_dim],
    T in_k[batch][num_key_value_heads][slen][head_dim],
    T in_cos[batch][slen][head_dim],
    T in_sin[batch][slen][head_dim]
) {
    T rotate_half_q[batch][num_key_value_heads][slen][head_dim];
    T rotate_half_k[batch][num_key_value_heads][slen][head_dim];
    rotate_half<batch, num_key_value_heads, slen, head_dim, T>(rotate_half_q, in_q);
    rotate_half<batch, num_key_value_heads, slen, head_dim, T>(rotate_half_k, in_k);
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < head_dim; l++) {
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
    T out_attn_output[batch][num_key_value_heads * n_rep_k][slen][slen],
    T out_attn_weights[batch][num_key_value_heads * n_rep_k][slen][head_dim],
    T in_q[batch][num_key_value_heads][slen][head_dim],
    T in_k[batch][num_key_value_heads][slen][head_dim],
    T in_v[batch][num_key_value_heads][slen][head_dim],
    double in_scaling
) {
    T repeated_k[batch][num_key_value_heads * n_rep_k][slen][head_dim];
    T repeated_v[batch][num_key_value_heads * n_rep_v][slen][head_dim];
    repeat_kv<batch, num_key_value_heads, slen, head_dim, n_rep_k>(repeated_k, in_k);
    repeat_kv<batch, num_key_value_heads, slen, head_dim, n_rep_v>(repeated_v, in_v);
    T attn_weights[batch][num_key_value_heads * n_rep_k][slen][slen];
    T attn_output[batch][num_key_value_heads * n_rep_k][slen][slen];
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

    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads * n_rep_k; j++) {
            for (int k = 0; k < slen; k++) {
                for (int l = 0; l < head_dim; l++) {
                    out_attn_output[i][j][k][l] = attn_output[i][k][j][l];
                }
            }
        }
    }
    
}