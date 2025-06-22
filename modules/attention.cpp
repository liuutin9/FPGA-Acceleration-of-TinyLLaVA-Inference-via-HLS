#include "transformer.hpp"
#include <cmath>

template<int M, int N>
void attention(
    // int out[2][3],
    // int q[2][3],
    // int k[2][3],
    // int v[2][3],
    int out[M][N],
    int q[M][N],
    int k[M][N],
    int v[M][N]
) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=q mode=bram
    #pragma HLS INTERFACE port=k mode=bram
    #pragma HLS INTERFACE port=v mode=bram

    int d_k = 3; // Dimension of key vectors, default to 3, should be feature size / # of heads

    // Perform matrix addition and multiplication
    int k_t[N][M];
    transpose<M, N>(k_t, k);
    int qk[M][M];
    matmul<M, N, M>(qk, q, k_t);
    int qk_scaled[M][M];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            qk_scaled[i][j] = qk[i][j] / d_k;
        }
    }
    int qk_scaled_exp[M][M];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            qk_scaled_exp[i][j] = exp(qk_scaled[i][j]); // Apply softmax
        }
    }
    matmul<M, M, N>(out, qk_scaled_exp, v);
}