#include <hls_math.h>
#include <ap_fixed.h>
#include "./connector_config.hpp"

// TODO: 用tanh近似的版本
float gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f; // √(2/π)
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = hls::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}

void Connector_forward(
    float out[SLEN][HIDDEN_SIZE],
    float in[SLEN][VISION_HIDDEN_SIZE]
    // int layer_id
) {    
    // weights
    float connector_connector_0_weight[HIDDEN_SIZE][VISION_HIDDEN_SIZE];
    float connector_connector_0_bias[HIDDEN_SIZE];
    float connector_connector_2_weight[HIDDEN_SIZE][HIDDEN_SIZE];
    float connector_connector_2_bias[HIDDEN_SIZE];

    float linear_out[SLEN][HIDDEN_SIZE];   
    float gelu_out[SLEN][HIDDEN_SIZE];

    linear<VISION_HIDDEN_SIZE, HIDDEN_SIZE, SLEN, float>(
        linear_out, in, 
        connector_connector_0_weight, connector_connector_0_bias
    );
    for (int i = 0; i < SLEN; i++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            gelu_out[i][j] = gelu(linear_out[i][j]);
        }
    }
    linear<HIDDEN_SIZE, HIDDEN_SIZE, SLEN, float>(
        out, gelu_out,
        connector_connector_2_weight, connector_connector_2_bias
    );
}