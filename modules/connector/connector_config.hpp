#include "../utils/transformer.hpp"

// connector config
#define VISION_HIDDEN_SIZE 1152
#define HIDDEN_SIZE 2560
#define SLEN 2048 // TODO: 最大序列長度

void Connector_forward(
    float out[SLEN][HIDDEN_SIZE],
    float in[SLEN][VISION_HIDDEN_SIZE]
    // int layer_id
);

float gelu(float x);