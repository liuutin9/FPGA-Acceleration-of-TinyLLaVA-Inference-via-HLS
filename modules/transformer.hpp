template<int M, int N, class T>
void attention(T out[M][N], T q[M][N], T k[M][N], T v[M][N]);

template <int M, int N, class T>
void matadd(T out[M][N], T in1[M][N], T in2[M][N]);

template <int M, int K, int N, class T>
void matmul(T out[M][N], T in1[M][K], T in2[K][N]);

template <int N, class T>
void maxval_1D(T* max_val, T in[N]);

template <int M, int N>
void softmax(double out[M][N], double in[M][N]);

template <int M, int N, class T>
void transpose(T out[N][M], T in[M][N]);

// template <int M, int N>
// void transformer_block(int out[M][N], int in[M][N]);

template <int M, int K, int N, class T>
void qkv_generator(T out_q[M][N], T out_k[M][N], T out_v[M][N], T in_x[M][K], T in_wq[K][N], T in_wk[K][N], T in_wv[K][N]);

template<int M, int N>
void layer_norm(double out[M][N], double in[M][N]);

template <int M, int N, class T>
void feed_forward(T out[M][N], T in_x[M][N], T in_w1[N][4 * N], T in_w2[4 * N][N], T in_b1[M][4 * N], T in_b2[M][N]);

template <int M, int N, class T>
void relu(T out[M][N], T in[M][N]);

template <int M, int N, class T>
void elementwise_mul(T out[M][N], T in[M][N], double in_scaling);