#include "transformer.hpp"
#include <cmath>

template<int M, int N, class T>
void attention(
    T out[M][N],
    T q[M][N],
    T k[M][N],
    T v[M][N]
) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=q mode=bram
    #pragma HLS INTERFACE port=k mode=bram
    #pragma HLS INTERFACE port=v mode=bram

    int d_k = 3; // Dimension of key vectors, default to 3, should be feature size / # of heads

    // Perform matrix addition and multiplication
    T k_t[N][M];
    transpose<M, N, T>(k_t, k);
    T qk[M][M];
    matmul<M, N, M, T>(qk, q, k_t);
    T qk_scaled[M][M];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            qk_scaled[i][j] = qk[i][j] / d_k;
        }
    }
    T qk_scaled_exp[M][M];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            qk_scaled_exp[i][j] = exp(qk_scaled[i][j]); // Apply softmax
        }
    }
    matmul<M, M, N, T>(out, qk_scaled_exp, v);
}