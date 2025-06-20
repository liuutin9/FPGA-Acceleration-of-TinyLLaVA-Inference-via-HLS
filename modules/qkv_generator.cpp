#include "matmul.cpp"

template <int M, int K, int N>
void qkv_generator(
    int out_q[M][N],
    int out_k[M][N],
    int out_v[M][N],
    int in_x[M][K],
    int in_wq[K][N],
    int in_wk[K][N],
    int in_wv[K][N]
    ) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out_q mode=bram
    #pragma HLS INTERFACE port=out_k mode=bram
    #pragma HLS INTERFACE port=out_v mode=bram
    #pragma HLS INTERFACE port=in_x mode=bram
    #pragma HLS INTERFACE port=in_wq mode=bram
    #pragma HLS INTERFACE port=in_wk mode=bram
    #pragma HLS INTERFACE port=in_wv mode=bram
    
    matmul<M, K, N>(out_q, in_x, in_wq);
    matmul<M, K, N>(out_k, in_x, in_wk);
    matmul<M, K, N>(out_v, in_x, in_wv);

}