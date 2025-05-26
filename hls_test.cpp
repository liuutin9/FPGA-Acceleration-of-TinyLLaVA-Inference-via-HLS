#include <iostream>

template <int M, int N>
void transpose(int in[M][N], int out[N][M]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[j][i] = in[i][j];
        }
    }
}

template <int M, int K, int N>
void matmul(int in1[M][K], int in2[K][N], int out[M][N]) {
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

template <int M, int N>
void matadd(int in1[M][N], int in2[M][N], int out[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[i][j] = in1[i][j] + in2[i][j];
        }
    }
}

template <int N>
void maxval_1D(int* max_val, int in[N]) {
    *max_val = in[0];
    for (int i = 1; i < N; i++) {
        if (in[i] > *max_val) {
            *max_val = in[i];
        }
    }
}

template <int M, int N>
void softmax(int in[M][N], int out[M][N]) {
    for (int i = 0; i < M; i++) {
        int max_val = in[i][0];
        maxval_1D(&max_val, in[i]);
        int sum_exp = 0;
        for (int j = 0; j < N; j++) {
            out[i][j] = std::exp(in[i][j] - max_val);
            sum_exp += out[i][j];
        }
        for (int j = 0; j < N; j++) {
            out[i][j] /= sum_exp;
        }
    }
}

int main() {
    const int N = 4;
    int in1[N][N] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    int in2[N][N] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    int out[N][N];

    matmul<N, N, N>(in1, in2, out);

    // Print output matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << out[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}