#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "./connector_config.hpp"
#include "../utils/weight_io.hpp"

// Fixes compared with the previous version:
//   * first Linear used linear4<HIDDEN_SIZE, ...>, i.e. 2560 input features instead of 1152
//     (read past the end of the input / weight arrays)
//   * weights were declared but never loaded
//   * weights and scratch buffers were defined in the header (multiple definition at link time)
//   * transpose/matmul came from utils/transformer.hpp, whose templates take 2-D arrays
//     plus a type parameter, so the 1-D calls here did not compile
namespace {

std::string weight_dir = "../../../Weight/model_bins1/";

std::vector<float> w0;  // [HIDDEN_SIZE][VISION_HIDDEN_SIZE]  connector._connector.0.weight
std::vector<float> b0;  // [HIDDEN_SIZE]
std::vector<float> w2;  // [HIDDEN_SIZE][HIDDEN_SIZE]         connector._connector.2.weight
std::vector<float> b2;  // [HIDDEN_SIZE]
bool loaded = false;

// TinyLLaVA's mlp2x_gelu connector uses torch.nn.GELU() (exact, erf form).
// The previous code used the tanh approximation; the difference is small but not zero.
inline float gelu_erf(float x) {
    return 0.5f * x * (1.0f + std::erf(x * 0.70710678118654752f));
}

// out[n][o] = b[o] + sum_i in[n][i] * w[o][i]   (PyTorch Linear layout, no transpose needed)
void linear(float* out, const float* in, const std::vector<float>& w, const std::vector<float>& b,
            int n_samples, int in_features, int out_features) {
    #pragma omp parallel for
    for (int n = 0; n < n_samples; ++n) {
        const float* x = in + static_cast<size_t>(n) * in_features;
        float* y = out + static_cast<size_t>(n) * out_features;
        for (int o = 0; o < out_features; ++o) {
            const float* wr = w.data() + static_cast<size_t>(o) * in_features;
            float acc = b[o];
            for (int i = 0; i < in_features; ++i) acc += x[i] * wr[i];
            y[o] = acc;
        }
    }
}

}  // namespace

void set_connector_weight_dir(const std::string& dir) {
    weight_dir = dir;
    loaded = false;
}

bool load_connector_weight() {
    if (loaded) return true;
    using weight_io::join;
    using weight_io::read_fp16_as_f32;
    loaded = read_fp16_as_f32(join(weight_dir, "connector._connector.0.weight.bin"), w0,
                              static_cast<size_t>(HIDDEN_SIZE) * VISION_HIDDEN_SIZE)
          && read_fp16_as_f32(join(weight_dir, "connector._connector.0.bias.bin"), b0, HIDDEN_SIZE)
          && read_fp16_as_f32(join(weight_dir, "connector._connector.2.weight.bin"), w2,
                              static_cast<size_t>(HIDDEN_SIZE) * HIDDEN_SIZE)
          && read_fp16_as_f32(join(weight_dir, "connector._connector.2.bias.bin"), b2, HIDDEN_SIZE);
    return loaded;
}

void Connector_forward(float* out, const float* in, int n_tokens) {
    if (!load_connector_weight()) {
        std::cerr << "Connector_forward: weights not available" << std::endl;
        return;
    }
    std::vector<float> hidden(static_cast<size_t>(n_tokens) * HIDDEN_SIZE);
    linear(hidden.data(), in, w0, b0, n_tokens, VISION_HIDDEN_SIZE, HIDDEN_SIZE);
    for (float& v : hidden) v = gelu_erf(v);
    linear(out, hidden.data(), w2, b2, n_tokens, HIDDEN_SIZE, HIDDEN_SIZE);
}
