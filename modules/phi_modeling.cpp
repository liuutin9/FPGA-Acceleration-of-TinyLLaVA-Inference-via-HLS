#include <string.h>

template<int batch, int num_key_value_heads, int slen, int head_dim, int n_rep>
void repeat_kv(int out[batch][num_key_value_heads * n_rep][slen][head_dim], int hidden_states[batch][num_key_value_heads][slen][head_dim]) {
    if (n_rep == 1) {
        memcpy(out, hidden_states, sizeof(int) * batch * num_key_value_heads * slen * head_dim);
        return;
    }
    int area_per_square = slen * head_dim;
    for (int i = 0; i < batch; i++) {
        for (int j = 0; j < num_key_value_heads; j++) {
            for (int rep = 0; rep < n_rep; rep++) {
                memcpy(out[i][j * n_rep + rep], hidden_states[i][j], sizeof(int) * area_per_square);
            }
        }
    }
    return;
}