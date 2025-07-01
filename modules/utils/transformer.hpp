template <int M, int N, class T>
void matadd(T out[M][N], T in1[M][N], T in2[M][N]);

template <int M, int K, int N, class T>
void matmul(T out[M][N], T in1[M][K], T in2[K][N]);

template <int N, class T>
void maxval_1D(T* max_val, T in[N]);

template <int M, int N>
void softmax(float out[M][N], float in[M][N]);

template <int M, int N, class T>
void transpose(T out[N][M], T in[M][N]);

template<int M, int N>
void layer_norm(float out[M][N], float in[M][N], float eps, float weight[M][N], float bias[N]);

template <int M, int N, class T>
void relu(T out[M][N], T in[M][N]);

template <int M, int N, class T>
void elementwise_mul(T out[M][N], T in[M][N], float in_scaling);

template <int in_features, int out_features, int n_samples, class T>
void linear(T out[n_samples][out_features], T in[n_samples][in_features], T weight[out_features][in_features], T bias[out_features]);

float new_gelu(float x);