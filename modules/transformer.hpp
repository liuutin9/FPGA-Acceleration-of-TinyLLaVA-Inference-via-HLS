template<int M, int N>
void attention(int out[M][N], int q[M][N], int k[M][N], int v[M][N]);

template <int M, int N>
void matadd(int out[M][N], int in1[M][N], int in2[M][N]);

template <int M, int K, int N>
void matmul(int out[M][N], int in1[M][K], int in2[K][N]);

template <int N>
void maxval_1D(int* max_val, int in[N]);

template <int M, int N>
void softmax(int out[M][N], int in[M][N]);

template <int M, int N>
void transpose(int out[N][M], int in[M][N]);

// template <int M, int N>
// void transformer_block(int out[M][N], int in[M][N]);

template <int M, int K, int N>
void qkv_generator(int out_q[M][N], int out_k[M][N], int out_v[M][N], int in_x[M][K], int in_wq[K][N], int in_wk[K][N], int in_wv[K][N]);

template<int M, int N>
void layer_norm(float out[M][N], float in[M][N]);

template <int M, int N>
void feed_forward(int out[M][N], int in[M][N]);

template <int M, int N>
void relu(int out[M][N], int in[M][N]);