template <int N>
void maxval_1D(int* max_val, int in[N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite bundle=CTRL
    #pragma HLS INTERFACE port=max_val mode=s_axilite bundle=CTRL
    #pragma HLS INTERFACE port=in mode=bram
    
    *max_val = in[0];
    for (int i = 1; i < N; i++) {
        if (in[i] > *max_val) {
            *max_val = in[i];
        }
    }
}