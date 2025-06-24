#include <string.h>

template<int batch, int num_key_value_heads, int slen, int head_dim, class T>
void rotate_half(T out[batch][num_key_value_heads][slen][head_dim], T hidden_states[batch][num_key_value_heads][slen][head_dim]) {
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

template<int batch, int num_key_value_heads, int slen, int head_dim, int n_rep, class T>
void repeat_kv(T out[batch][num_key_value_heads * n_rep][slen][head_dim], T hidden_states[batch][num_key_value_heads][slen][head_dim]) {
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