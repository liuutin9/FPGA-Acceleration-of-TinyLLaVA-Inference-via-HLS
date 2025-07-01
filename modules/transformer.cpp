#include "transformer.hpp"
#include <cmath>

# define M 50 // 50 tokens
# define N 256 // vector length

void transformer_block(float out[M][N], float in[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in mode=bram

    float wq[N][N] = {0}, wk[N][N] = {0}, wv[N][N] = {0};
    float Q[M][N], K[M][N], V[M][N], attention_out[M][N], add_out[M][N], ffn_in[M][N], ffn_out[M][N];
    float layer_norm_in[M][N], layer_norm_out[M][N];
    qkv_generator<M, N, N, float>(Q, K, V, in, wq, wk, wv);
    attention<M, N, float>(attention_out, Q, K, V);
    matadd<M, N, float>(add_out, attention_out, in);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            layer_norm_in[i][j] = 0.0 + add_out[i][j];
        }
    }
    layer_norm<M, N>(layer_norm_out, layer_norm_in);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            ffn_in[i][j] = (int) std::floor(layer_norm_out[i][j]);
        }
    }
    float w1[N][4 * N] = {0}, w2[4 * N][N] = {0}, b1[M][4 * N] = {0}, b2[M][N] = {0};
    feed_forward<M, N, float>(ffn_out, ffn_in, w1, w2, b1, b2);
    matadd<M, N, float>(add_out, ffn_out, ffn_in);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            layer_norm_in[i][j] = 0.0 + add_out[i][j];
        }
    }
    layer_norm<M, N>(layer_norm_out, layer_norm_in);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[i][j] = std::floor(layer_norm_out[i][j]);
        }
    }
}