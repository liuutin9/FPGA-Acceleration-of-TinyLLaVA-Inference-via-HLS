#include <cmath>

template <int M, int N>
void softmax(int out[M][N], int in[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in mode=bram

    for (int i = 0; i < M; i++) {
        int max_val = in[i][0];
        maxval_1D(&max_val, in[i]);
        int sum_exp = 0;
        for (int j = 0; j < N; j++) {
            out[i][j] = exp(in[i][j] - max_val);
            sum_exp += out[i][j];
        }
        for (int j = 0; j < N; j++) {
            out[i][j] /= sum_exp;
        }
    }
}