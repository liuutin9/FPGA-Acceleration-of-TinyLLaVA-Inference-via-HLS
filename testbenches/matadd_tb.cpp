#include <iostream>

const int M = 5, N = 3;
void matadd(int out[M][N], int in1[M][N], int in2[M][N]);

// template <int M, int N>
// void matadd(int out[M][N], int in1[M][N], int in2[M][N]);

int main() {
    int in1[M][N], in2[M][N], out[M][N];
    int expectedOut[M][N] = {0};
    int errors = 0;

    // Initialize input matrices
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            in1[i][j] = i + j;
            in2[i][j] = i * j;
        }
    }

    // Calculate expected output
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            expectedOut[i][j] = in1[i][j] + in2[i][j];
        }
    }

    // Call the matadd function
    // matadd<M, N>(out, in1, in2);
    matadd(out, in1, in2);

    // Check results
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
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