#include <iostream>

const int M = 3, N = 2, K = 4;
void matmul(int out[M][K], int in1[M][N], int in2[N][K]);

// template <int M, int N, int K>
// void matmul(int out[M][K], int in1[M][N], int in2[N][K]);

int main() {
    int in1[M][N], in2[N][K], out[M][K];
    int expectedOut[M][K] = {0};
    int errors = 0;

    // Initialize input matrices
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            in1[i][j] = i + j;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            in2[i][j] = i * j;
        }
    }

    // Calculate expected output
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < N; k++) {
                expectedOut[i][j] += in1[i][k] * in2[k][j];
            }
        }
    }

    // Call the matmul function
    // matmul<M, N, K>(out, in1, in2);
    matmul(out, in1, in2);

    // Check results
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            if (out[i][j] != expectedOut[i][j]) {
                std::cout << "Error at out[" << i << "][" << j << "]: Expected "
                          << expectedOut[i][j] << ", Got " << out[i][j] << std::endl;
                errors++;
            }
        }
    }

    if (errors == 0) {
        std::cout << "Test passed!" << std::endl;
    } else {
        std::cout << "Test failed with " << errors << " errors." << std::endl;
    }

    return errors;
}