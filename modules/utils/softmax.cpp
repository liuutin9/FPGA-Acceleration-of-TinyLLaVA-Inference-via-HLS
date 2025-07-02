#include <hls_math.h>
#include "transformer.hpp"

// TODO: exp 要優化
template <int M, int N>
void softmax(float out[M][N], float in[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in mode=bram

    for (int i = 0; i < M; i++) {
        float max_val = in[i][0];
        maxval_1D<N, float>(&max_val, in[i]);
        float sum_exp = 0;
        for (int j = 0; j < N; j++) {
            out[i][j] = hls::exp(in[i][j] - max_val);
            sum_exp += out[i][j];
        }
        for (int j = 0; j < N; j++) {
            out[i][j] /= sum_exp;
        }
    }
}