#include "transformer.hpp"

template <int M, int N, class T>
void transpose(T out[N][M], T in[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in mode=bram
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[j][i] = in[i][j];
        }
    }
}