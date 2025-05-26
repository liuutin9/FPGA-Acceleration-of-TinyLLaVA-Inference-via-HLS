template <int M, int N>
void matadd(int out[M][N], int in1[M][N], int in2[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in1 mode=bram
    #pragma HLS INTERFACE port=in2 mode=bram

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[i][j] = in1[i][j] + in2[i][j];
        }
    }
}