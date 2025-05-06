#define N 4

void mat_mul(int in1[N][N], int in2[N][N], int out[N][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=in1 mode=bram
    #pragma HLS INTERFACE port=in2 mode=bram
    #pragma HLS INTERFACE port=out mode=bram

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                #pragma HLS UNROLL factor=2
                sum += in1[i][k] * in2[k][j];
            }
            out[i][j] = sum;
        }
    }

}