#include <hls_math.h>
#include "transformer.hpp"

template<int M, int N>
void layer_norm(
    float out[M][N],
    float in[M][N],
    float eps,
    float weight[M][N],
    float bias[N]
) {

    // 對每一個 feature（row）做 LayerNorm
    for (int i = 0; i < M; i++) {
        #pragma HLS PIPELINE II=1

        float mean = 0.0;
        float variance = 0.0;

        // Step 1: 計算均值
        for (int j = 0; j < N; j++) {
            #pragma HLS UNROLL
            mean += in[i][j];
        }
        mean /= N;

        // Step 2: 計算變異數
        for (int j = 0; j < N; j++) {
            #pragma HLS UNROLL
            float diff = in[i][j] - mean;
            variance += diff * diff;
        }
        variance /= N;

        float stddev_inv = 1.0 / hls::sqrt(variance + eps);

        // Step 3: 標準化
        for (int j = 0; j < N; j++) {
            #pragma HLS UNROLL
            out[i][j] = (in[i][j] - mean) * stddev_inv * weight[i][j] + bias[j];
        }
    }
}

template<int M, int N>
void rms_norm(float out[N][M], float in[N][M], float gamma[M]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=in mode=bram
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=gamma mode=bram

    const float epsilon = 1e-5;

    for (int n = 0; n < N; n++) {
        #pragma HLS PIPELINE II=1

        float sq_sum = 0.0;
        for (int i = 0; i < M; i++) {
            #pragma HLS UNROLL
            sq_sum += in[n][i] * in[n][i];
        }

        float rms = hls::sqrt(sq_sum / M + epsilon);

        for (int i = 0; i < M; i++) {
            #pragma HLS UNROLL
            out[n][i] = (in[n][i] / rms) * gamma[i];
        }
    }
}