// #include <iostream>
// #include <cmath>

// const int M = 2, N = 3;

// void attention(int out[M][N], int q[M][N], int k[M][N], int v[M][N], int d_k = 3);

// int main() {
//     int q[M][N], k[M][N], v[M][N], out[M][N] = {0};
//     int expectedOut[M][N] = {0};
//     int errors = 0;
//     int d_k = 3; // Dimension of key vectors, default to 3
//     // Initialize input matrices
//     for (int i = 0; i < M; i++) {
//         for (int j = 0; j < N; j++) {
//             q[i][j] = i + j;
//             k[i][j] = i * j;
//             v[i][j] = i - j;
//         }
//     }
//     // Calculate expected output(attention result)
//     int k_t[N][M]; // Transpose of k
//     for (int i = 0; i < M; i++) {
//         for (int j = 0; j < N; j++) {
//             k_t[j][i] = k[i][j]; // Transpose k
//         }
//     }
//     int qk[M][M] = {0}; // q * k^T
//     for (int i = 0; i < M; i++) {
//         for (int j = 0; j < M; j++) {
//             for (int k_idx = 0; k_idx < N; k_idx++) {
//                 qk[i][j] += q[i][k_idx] * k_t[j][k_idx];
//             }
//             qk[i][j] /= d_k; // Scale by d_k
//         }
//     }
//     int qk_scaled_exp[M][M]; // Apply softmax
//     for (int i = 0; i < M; i++) {
//         int max_val = qk[i][0];
//         for (int j = 1; j < M; j++) {
//             if (qk[i][j] > max_val) {
//                 max_val = qk[i][j];
//             }
//         }
//         int sum_exp = 0;
//         for (int j = 0; j < M; j++) {
//             qk_scaled_exp[i][j] = exp(qk[i][j] - max_val);
//             sum_exp += qk_scaled_exp[i][j];
//         }
//         for (int j = 0; j < M; j++) {
//             qk_scaled_exp[i][j] /= sum_exp; // Normalize
//         }
//     }
//     // Calculate expected output
//     for (int i = 0; i < M; i++) {
//         for (int j = 0; j < N; j++) {
//             expectedOut[i][j] = 0;
//             for (int k_idx = 0; k_idx < M; k_idx++) {
//                 expectedOut[i][j] += qk_scaled_exp[i][k_idx] * v[k_idx][j];
//             }
//         }
//     }
    
//     // Call the attention function
//     attention(out, q, k, v, d_k);
//     // Check results
//     for (int i = 0; i < M; i++) {
//         for (int j = 0; j < N; j++) {
//             if (out[i][j] != expectedOut[i][j]) {
//                 std::cout << "Error at out[" << i << "][" << j << "]: Expected "
//                           << expectedOut[i][j] << ", Got " << out[i][j] << std::endl;
//                 errors++;
//             }
//         }
//     }
//     if (errors == 0) {
//         std::cout << "Test passed!" << std::endl;
//     } else {
//         std::cout << "Test failed with " << errors << " errors." << std::endl;
//     }
//     return 0;
// }