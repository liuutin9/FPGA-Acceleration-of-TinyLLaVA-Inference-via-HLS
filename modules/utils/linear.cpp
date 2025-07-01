#include "transformer.hpp"

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