#include <stdio.h>
#define N 4

void mat_mul(int in1[N][N], int in2[N][N], int out[N][N]);

int main() {
    int in1[N][N], in2[N][N], out[N][N];
    int expectedOut[N][N] = {0};
    int errors = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            in1[i][j] = in2[i][j] = i * j + j;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                expectedOut[i][j] += in1[i][k] * in2[k][j];
            }
        }
    }

    mat_mul(in1, in2, out);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (out[i][j] != expectedOut[i][j]){
                printf("Error at c[%d][%d]: Expected %d, Got %d\n", i, j, expectedOut[i][j], out[i][j]);
                errors++;
            }
        }
    }

    if (errors == 0) {
        printf("Test passed!\n");
    } else {
        printf("Test failed with %d errors.\n", errors);
    }

    return errors;

}