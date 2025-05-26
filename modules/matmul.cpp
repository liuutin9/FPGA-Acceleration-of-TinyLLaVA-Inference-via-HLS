template <int M, int K, int N>
void matmul(int out[M][N], int in1[M][N], int in2[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in1 mode=bram
    #pragma HLS INTERFACE port=in2 mode=bram

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < K; k++) {
                #pragma HLS UNROLL factor=2
                sum += in1[i][k] * in2[k][j];
            }
            out[i][j] = sum;
        }
    }
}