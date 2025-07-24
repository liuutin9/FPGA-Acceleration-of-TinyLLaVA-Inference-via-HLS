#include "../utils/transformer.hpp"

//vision config
#define VOCAB_SIZE 32000
#define HIDDEN_SIZE 1152
#define INTERMEDIATE_SIZE 4304
#define NUM_HIDDEN_LAYERS 27
#define NUM_ATTENTION_HEADS 16
#define HEAD_DIM 72 // 1152 / 16 = 72
#define NUM_CHANNELS 3
#define IMAGE_SIZE 384
#define PATHC_SIZE 14
#define HIDDEN_ACT "gelu_pytorch_tanh"
#define LAYER_NORM_EPS 1e-6
#define ATTENTION_DROPOUT 0.0
#define SLEN INPUT_DIM

//SIGLIP
#define INITIALIZER_FACTOR 1_0

#define NUM_PATCH ((IMAGE_SIZE - PATHC_SIZE + 1) / PATHC_SIZE + 1)
#define INPUT_DIM NUM_PATCH * NUM_PATCH

void Siglip_Transformer_forward(
    float output[INPUT_DIM][HIDDEN_SIZE],
    float input[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
);

void Embedding(
    float embedded_vector[INPUT_DIM][HIDDEN_SIZE],
    float pixel_values[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
);

void Patch_Embedding(
    float patched_pixel_values[HIDDEN_SIZE][NUM_PATCH][NUM_PATCH],
    float pixel_values[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
);

void flatten(
    float output[NUM_PATCH * NUM_PATCH][HIDDEN_SIZE],
    float input[HIDDEN_SIZE][NUM_PATCH][NUM_PATCH]
);

void Pos_Embedding(
    float embedded_vector[INPUT_DIM][HIDDEN_SIZE],
    float flatten_patched_pixel_values[INPUT_DIM][HIDDEN_SIZE]
);

void Conv2D(
    float output[HIDDEN_SIZE][NUM_PATCH][NUM_PATCH],
    float pixel_values[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
);

float mult_with_kernel(
    float input[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], 
    float kernel[NUM_CHANNELS][PATHC_SIZE][PATHC_SIZE], 
    int kernel_x, 
    int kernel_y
);

void Siglip_Encoder(
    float encoder_output[INPUT_DIM][HIDDEN_SIZE],
    float embedded_vector[INPUT_DIM][HIDDEN_SIZE]
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