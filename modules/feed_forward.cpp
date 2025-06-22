#include "transformer.hpp"

template <int M, int N>
void feed_forward(int out[M][N], int in_x[M][N], int in_w1[N][4 * N], int in_w2[4 * N][N], int in_b1[M][4 * N], int in_b2[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in_x mode=bram
    #pragma HLS INTERFACE port=in_w1 mode=bram
    #pragma HLS INTERFACE port=in_w2 mode=bram
    #pragma HLS INTERFACE port=in_b1 mode=bram
    #pragma HLS INTERFACE port=in_b2 mode=bram
    
    int w1_out[M][4 * N], b1_out[M][4 * N], relu_out[M][4 * N], w2_out[M][N];
    matmul<M, N, 4 * N>(w1_out, in_x, in_w1);
    matadd<M, 4 * N>(b1_out, w1_out, in_b1);
    relu<M, 4 * N>(relu_out, b1_out);
    matmul<M, 4 * N, N>(w2_out, relu_out, in_w2);
    matadd<M, N>(out, w2_out, in_b2);
}