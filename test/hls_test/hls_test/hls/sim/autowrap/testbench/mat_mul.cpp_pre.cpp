# 1 "C:/Users/liuut/Desktop/Project/test/hls_test/mat_mul.cpp"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 420 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/liuut/Desktop/Project/test/hls_test/mat_mul.cpp" 2


void mat_mul(int in1[4][4], int in2[4][4], int out[4][4]) {
#pragma HLS INTERFACE port=return mode=s_axilite
#pragma HLS INTERFACE port=in1 mode=bram
#pragma HLS INTERFACE port=in2 mode=bram
#pragma HLS INTERFACE port=out mode=bram

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int sum = 0;
            for (int k = 0; k < 4; k++) {
#pragma HLS UNROLL factor=2
                sum += in1[i][k] * in2[k][j];
            }
            out[i][j] = sum;
        }
    }

}
