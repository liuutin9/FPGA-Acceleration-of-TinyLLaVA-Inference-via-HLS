#include "matadd.cpp"
#include "matmul.cpp"
#include "transpose.cpp"
#include <cmath>

void attention(
    int out[2][3], 
    int q[2][3], 
    int k[2][3], 
    int v[2][3],
    int d_k = 3 // Dimension of key vectors, default to 3
) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=q mode=bram
    #pragma HLS INTERFACE port=k mode=bram
    #pragma HLS INTERFACE port=v mode=bram

    // Perform matrix addition and multiplication
    int k_t[3][2];
    transpose<2, 3>(k_t, k);
    int qk[2][2];
    matmul<2, 3, 2>(qk, q, k_t);
    int qk_scaled[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            qk_scaled[i][j] = qk[i][j] / d_k;
        }
    }
    int qk_scaled_exp[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            qk_scaled_exp[i][j] = exp(qk_scaled[i][j]); // Apply softmax
        }
    }
    matmul<2, 2, 3>(out, qk_scaled_exp, v);
}