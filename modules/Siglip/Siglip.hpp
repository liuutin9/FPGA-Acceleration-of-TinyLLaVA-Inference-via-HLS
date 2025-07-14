#include "Siglip_config.hpp"
#include "../utils/transformer.hpp"

#define IN_CHANNELS NUM_CHANNELS
#define OUT_CHANNELS HIDDEN_SIZE
#define KERNEL_SIZE PATHC_SIZE
#define STRIDE PATHC_SIZE
#define PADDING PATHC_SIZE
#define OUTPUT_DIM HIDDEN_SIZE
#define IMAGE_SIZE 384
#define NUM_PATCH ((IMAGE_SIZE - KERNEL_SIZE + 1) / KERNEL_SIZE + 1)
#define INPUT_DIM NUM_PATCH * NUM_PATCH

void Siglip_Transformer_forward(
    float output[INPUT_DIM][OUTPUT_DIM],
    float input[IN_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
);

void Embedding(
    float embedded_vector[INPUT_DIM][OUTPUT_DIM],
    float pixel_values[IN_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
);

void Patch_Embedding(
    float patched_pixel_values[HIDDEN_SIZE][NUM_PATCH][NUM_PATCH],
    float pixel_values[IN_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
);

void flatten(
    float output[NUM_PATCH * NUM_PATCH][HIDDEN_SIZE],
    float input[HIDDEN_SIZE][NUM_PATCH][NUM_PATCH]
);

void Pos_Embedding(
    float embedded_vector[INPUT_DIM][OUTPUT_DIM],
    float flatten_patched_pixel_values[INPUT_DIM][HIDDEN_SIZE]
);

void Conv2D(
    float output[HIDDEN_SIZE][NUM_PATCH][NUM_PATCH],
    float pixel_values[IN_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
);

float mult_with_kernel(
    float input[IN_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], 
    float kernel[IN_CHANNELS][KERNEL_SIZE][KERNEL_SIZE], 
    int kernel_x, 
    int kernel_y
);

void Siglip_Encoder(
    float encoder_output[INPUT_DIM][OUTPUT_DIM],
    float embedded_vector[INPUT_DIM][OUTPUT_DIM]
);

void SiglipEncoderLayer(
    float output[INPUT_DIM][HIDDEN_SIZE], 
    float hidden_state[INPUT_DIM][HIDDEN_SIZE],
    int layer_id
);

// Activation
float gelu(float x);

// MLP
void SiglipMLP(
    float out[SLEN][HIDDEN_SIZE], 
    float hidden_state[SLEN][HIDDEN_SIZE],
    int layer_id
);

void matmul_with_scale(
    float out[SLEN][SLEN], 
    float in1[SLEN][HEAD_DIM], float in2[HEAD_DIM][SLEN], 
    float scaling
);

void eager_attention_per_head(
    float out[SLEN][HEAD_DIM],
    float query[SLEN][HEAD_DIM],
    float key[SLEN][HEAD_DIM],
    float value[SLEN][HEAD_DIM],
    float scaling
);

// Transformer Layer Attention
void SiglipAttention(
    float attn_out[SLEN][HIDDEN_SIZE],
    float hidden_states[SLEN][HIDDEN_SIZE],
    int layer_id
);
//add other func?