#include <hls_math.h>

template<int M, int N>
void layer_norm(double out[M][N], double in[M][N], double eps) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in mode=bram

    // 對每一個 feature（row）做 LayerNorm
    for (int i = 0; i < M; i++) {
        #pragma HLS PIPELINE II=1

        double mean = 0.0;
        double variance = 0.0;

        // Step 1: 計算均值
        for (int j = 0; j < N; j++) {
            #pragma HLS UNROLL
            mean += in[i][j];
        }
        mean /= N;

        // Step 2: 計算變異數
        for (int j = 0; j < N; j++) {
            #pragma HLS UNROLL
            double diff = in[i][j] - mean;
            variance += diff * diff;
        }
        variance /= N;

        double stddev_inv = 1.0 / hls::sqrt(variance + eps);

        // Step 3: 標準化
        for (int j = 0; j < N; j++) {
            #pragma HLS UNROLL
            out[i][j] = (in[i][j] - mean) * stddev_inv;
        }
    }
}

template<int M, int N>
void rms_norm(double out[N][M], double in[N][M], double gamma[M]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=in mode=bram
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=gamma mode=bram

    const double epsilon = 1e-5;

    for (int n = 0; n < N; n++) {
        #pragma HLS PIPELINE II=1

        double sq_sum = 0.0;
        for (int i = 0; i < M; i++) {
            #pragma HLS UNROLL
            sq_sum += in[n][i] * in[n][i];
        }

        double rms = hls::sqrt(sq_sum / M + epsilon);

        for (int i = 0; i < M; i++) {
            #pragma HLS UNROLL
            out[n][i] = (in[n][i] / rms) * gamma[i];
        }
    }
}