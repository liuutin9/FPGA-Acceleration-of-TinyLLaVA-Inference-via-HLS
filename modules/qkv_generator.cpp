#include "transformer.hpp"

template <int M, int K, int N, class T>
void qkv_generator(
    T out_q[M][N],
    T out_k[M][N],
    T out_v[M][N],
    T in_x[M][K],
    T in_wq[K][N],
    T in_wk[K][N],
    T in_wv[K][N]
    ) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out_q mode=bram
    #pragma HLS INTERFACE port=out_k mode=bram
    #pragma HLS INTERFACE port=out_v mode=bram
    #pragma HLS INTERFACE port=in_x mode=bram
    #pragma HLS INTERFACE port=in_wq mode=bram
    #pragma HLS INTERFACE port=in_wk mode=bram
    #pragma HLS INTERFACE port=in_wv mode=bram
    
    matmul<M, K, N, T>(out_q, in_x, in_wq);
    matmul<M, K, N, T>(out_k, in_x, in_wk);
    matmul<M, K, N, T>(out_v, in_x, in_wv);

}