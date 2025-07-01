#include <hls_math.h>
#include "transformer.hpp"

// TODO: 要優化
float new_gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f; // √(2/π)
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = hls::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}
