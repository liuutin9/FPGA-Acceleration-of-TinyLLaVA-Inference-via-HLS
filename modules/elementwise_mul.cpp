#include "transformer.hpp"

template <int M, int N, class T>
void elementwise_mul(T out[M][N], T in[M][N], double in_scaling) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out[i][j] = in[i][j] * in_scaling;
        }
    }
}