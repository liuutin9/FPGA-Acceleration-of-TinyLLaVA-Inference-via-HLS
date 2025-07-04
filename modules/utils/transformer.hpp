#include <hls_math.h>

template <int M, int N, class T>
void matadd(T out[M][N], T in1[M][N], T in2[M][N]) {
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

template <int M, int K, int N, class T>
void matmul(T out[M][N], T in1[M][K], T in2[K][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in1 mode=bram
    #pragma HLS INTERFACE port=in2 mode=bram

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            T sum = 0;
            for (int k = 0; k < K; k++) {
                #pragma HLS UNROLL factor=2
                sum += in1[i][k] * in2[k][j];
            }
            out[i][j] = sum;
        }
    }
}

template <int N, class T>
void maxval_1D(T* max_val, T in[N]) {
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

// TODO: exp 要優化
template <int M, int N>
void softmax(float out[M][N], float in[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in mode=bram

    for (int i = 0; i < M; i++) {
        float max_val = in[i][0];
        maxval_1D<N, float>(&max_val, in[i]);
        float sum_exp = 0;
        for (int j = 0; j < N; j++) {
            out[i][j] = hls::exp(in[i][j] - max_val);
            sum_exp += out[i][j];
        }
        for (int j = 0; j < N; j++) {
            out[i][j] /= sum_exp;
        }
    }
}

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

template<int M, int N>
void layer_norm(
    float out[M][N],
    float in[M][N],
    float eps,
    float weight[N],
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
            out[i][j] = (in[i][j] - mean) * stddev_inv * weight[j] + bias[j];
        }
    }
}

template <int M, int N, class T>
void relu(T out[M][N], T in[M][N]) {
    #pragma HLS INTERFACE port=return mode=s_axilite
    #pragma HLS INTERFACE port=out mode=bram
    #pragma HLS INTERFACE port=in mode=bram

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[i][j] = in[i][j] > 0 ? in[i][j] : 0;
        }
    }
}

template <int M, int N, class T>
void elementwise_mul(T out[M][N], T in[M][N], T in_scaling) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[i][j] = in[i][j] * in_scaling;
        }
    }
}

template <int in_features, int out_features, int n_samples, class T>
void linear(T out[n_samples][out_features], T in[n_samples][in_features], T weight[out_features][in_features], T bias[out_features]) {
    T weight_transpose[in_features][out_features];
    transpose<out_features, in_features>(weight_transpose, weight);
    matmul<n_samples, in_features, out_features>(out, in, weight_transpose);
    for (int i = 0; i < n_samples; i++) {
        for (int j = 0; j < out_features; j++) {
            out[i][j] += bias[j];
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

template<int N, class T>
void argmax(
    int* out,
    T arr[N]
) {
    *out = 0;
    T max = arr[0];
    for (int i = 1; i < N; i++) {
        if (arr[i] > max) {
            max = arr[i];
            *out = i;
        }
    }
}