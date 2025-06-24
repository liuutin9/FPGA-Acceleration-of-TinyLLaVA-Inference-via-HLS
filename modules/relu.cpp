#include "transformer.hpp"
#include <cmath>

template <int M, int N, class T>
void relu(T out[M][N], T in[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in mode=bram

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[i][j] = in[i][j] > 0 ? in[i][j] : 0;
        }
    }
}