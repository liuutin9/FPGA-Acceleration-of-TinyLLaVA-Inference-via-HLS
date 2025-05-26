#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;

using Matrix = vector<vector<float>>;
using Vector = vector<float>;

// 簡單矩陣乘法 A(m*n) * B(n*p) = C(m*p)
Matrix matmul(const Matrix& A, const Matrix& B) {
    int m = (int)A.size();
    int n = (int)A[0].size();
    int p = (int)B[0].size();
    assert(n == (int)B.size());
    Matrix C(m, vector<float>(p, 0.0f));
    for(int i=0; i<m; i++) {
        for(int j=0; j<p; j++) {
            for(int k=0; k<n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// 矩陣加法 A+B
Matrix matadd(const Matrix& A, const Matrix& B) {
    int m = (int)A.size();
    int n = (int)A[0].size();
    assert(m == (int)B.size() && n == (int)B[0].size());
    Matrix C(m, vector<float>(n));
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// LayerNorm (按行做) gamma, beta 都是向量，大小 = n (特徵維度)
Matrix layernorm(const Matrix& X, const Vector& gamma, const Vector& beta, float eps=1e-5) {
    int m = (int)X.size();
    int n = (int)X[0].size();
    Matrix Y(m, vector<float>(n));
    for(int i=0; i<m; i++) {
        // mean
        float mean = accumulate(X[i].begin(), X[i].end(), 0.0f) / n;
        // var
        float var = 0;
        for(auto v : X[i]) var += (v - mean) * (v - mean);
        var /= n;
        // norm
        for(int j=0; j<n; j++) {
            Y[i][j] = gamma[j] * (X[i][j] - mean) / sqrt(var + eps) + beta[j];
        }
    }
    return Y;
}

// softmax 每行獨立做
Matrix softmax(const Matrix& X) {
    int m = (int)X.size();
    int n = (int)X[0].size();
    Matrix Y(m, vector<float>(n));
    for(int i=0; i<m; i++) {
        float max_val = *max_element(X[i].begin(), X[i].end());
        float sum_exp = 0;
        for(int j=0; j<n; j++) {
            Y[i][j] = exp(X[i][j] - max_val);
            sum_exp += Y[i][j];
        }
        for(int j=0; j<n; j++) {
            Y[i][j] /= sum_exp;
        }
    }
    return Y;
}

// ReLU
Matrix relu(const Matrix& X) {
    int m = (int)X.size();
    int n = (int)X[0].size();
    Matrix Y(m, vector<float>(n));
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            Y[i][j] = X[i][j] > 0 ? X[i][j] : 0;
        }
    }
    return Y;
}

// Attention(Q,K,V) = softmax(QK^T / sqrt(dk)) * V
Matrix attention(const Matrix& Q, const Matrix& K, const Matrix& V) {
    int seq_len = (int)Q.size();
    int dim = (int)Q[0].size();
    // QK^T
    Matrix scores(seq_len, vector<float>(seq_len, 0));
    for(int i=0; i<seq_len; i++) {
        for(int j=0; j<seq_len; j++) {
            for(int k=0; k<dim; k++) {
                scores[i][j] += Q[i][k] * K[j][k];
            }
        }
    }
    // scale
    float scale = 1.0f / sqrt((float)dim);
    for(int i=0; i<seq_len; i++) {
        for(int j=0; j<seq_len; j++) {
            scores[i][j] *= scale;
        }
    }
    // softmax
    Matrix weights = softmax(scores);
    // weights * V
    Matrix out(seq_len, vector<float>(dim, 0));
    for(int i=0; i<seq_len; i++) {
        for(int j=0; j<dim; j++) {
            for(int k=0; k<seq_len; k++) {
                out[i][j] += weights[i][k] * V[k][j];
            }
        }
    }
    return out;
}

// Feed Forward Network: FFN(x) = ReLU(xW1 + b1)W2 + b2
Matrix ffn(const Matrix& X, const Matrix& W1, const Vector& b1, const Matrix& W2, const Vector& b2) {
    int m = (int)X.size();
    int hidden_dim = (int)W1[0].size();
    int output_dim = (int)W2[0].size();

    // XW1 + b1
    Matrix hidden = matmul(X, W1);
    for(int i=0; i<m; i++) {
        for(int j=0; j<hidden_dim; j++) {
            hidden[i][j] += b1[j];
        }
    }
    hidden = relu(hidden);

    // hidden W2 + b2
    Matrix output = matmul(hidden, W2);
    for(int i=0; i<m; i++) {
        for(int j=0; j<output_dim; j++) {
            output[i][j] += b2[j];
        }
    }
    return output;
}

// Transformer Block Forward
Matrix transformer_block_forward(
    const Matrix& X,
    // LayerNorm params
    const Vector& ln1_gamma, const Vector& ln1_beta,
    const Vector& ln2_gamma, const Vector& ln2_beta,
    // Attention weights: Wq, Wk, Wv, Wo
    const Matrix& Wq, const Matrix& Wk, const Matrix& Wv, const Matrix& Wo,
    // FFN weights: W1, b1, W2, b2
    const Matrix& W1, const Vector& b1, const Matrix& W2, const Vector& b2
) {
    // LN1
    Matrix LN1 = layernorm(X, ln1_gamma, ln1_beta);

    // Q, K, V
    Matrix Q = matmul(LN1, Wq);
    Matrix K = matmul(LN1, Wk);
    Matrix V = matmul(LN1, Wv);

    // Attention
    Matrix attn_out = attention(Q, K, V);
    Matrix attn_proj = matmul(attn_out, Wo);

    // Residual 1
    Matrix X1 = matadd(X, attn_proj);

    // LN2
    Matrix LN2 = layernorm(X1, ln2_gamma, ln2_beta);

    // FFN
    Matrix ffn_out = ffn(LN2, W1, b1, W2, b2);

    // Residual 2
    Matrix out = matadd(X1, ffn_out);

    return out;
}

int main() {
    // 測試用：假設 batch=2, seq_len=3, dim=4
    Matrix X = {
        {0.1f, 0.2f, 0.3f, 0.4f},
        {0.5f, 0.6f, 0.7f, 0.8f},
        {0.9f, 1.0f, 1.1f, 1.2f}
    };

    // 隨便用 1.0 初始化權重 (實際要用模型權重)
    Vector gamma(4, 1.0f), beta(4, 0.0f);

    Matrix Wq(4, Vector(4, 1.0f));
    Matrix Wk(4, Vector(4, 1.0f));
    Matrix Wv(4, Vector(4, 1.0f));
    Matrix Wo(4, Vector(4, 1.0f));

    Matrix W1(4, Vector(8, 1.0f)); // FFN hidden=8
    Vector b1(8, 0.0f);
    Matrix W2(8, Vector(4, 1.0f));
    Vector b2(4, 0.0f);

    Matrix output = transformer_block_forward(
        X,
        gamma, beta,
        gamma, beta,
        Wq, Wk, Wv, Wo,
        W1, b1, W2, b2
    );

    // 印出結果
    for (auto& row : output) {
        for (auto& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}
