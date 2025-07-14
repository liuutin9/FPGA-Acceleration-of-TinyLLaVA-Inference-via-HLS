#include<stdio.h>
#include<string.h>
#include"../utils/transformer.hpp"
#include"Siglip_config.hpp"
#include "Siglip.hpp"

#define INPUT_SIZE
#define OUTPUT_SIZE 
#define num_patch_x 27
#define num_patch_y 27

void Siglip_Transformer_forward(
    float output[INPUT_DIM][OUTPUT_DIM],
    float input[IN_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
) {
    // Step 1: Patch + Position Embedding
    float embedded_vector[INPUT_DIM][OUTPUT_DIM] = {0};
    Embedding(
        embedded_vector,
        input
    );

    // Step 2: Encoder
    float encoder_output[INPUT_DIM][OUTPUT_DIM] = {0};
    Siglip_Encoder(
        encoder_output,
        embedded_vector
    );
    memcpy(output, encoder_output, sizeof(float) * INPUT_DIM * OUTPUT_DIM);
    /*
    // Step 3: Layer Norm
    float norm_output[INPUT_DIM][OUTPUT_DIM] = {0};
    T vision_tower_vision_tower_vision_model_post_layernorm_weight[OUTPUT_DIM] = {0};
    T vision_tower_vision_tower_vision_model_post_layernorm_bias[OUTPUT_DIM] = {0};
    layer_norm<INPUT_DIM, OUTPUT_DIM>(
        norm_output, encoder_output, LAYER_NORM_EPS,
        vision_tower_vision_tower_vision_model_post_layernorm_weight,
        vision_tower_vision_tower_vision_model_post_layernorm_bias
    );

    // Step 4: Attention Pooling → 輸出特徵
    SiglipMultiheadAttentionPooling_forward(output, norm_output);
    */
}

//in : [3][384][384], out : [1152]
void Embedding(
    float embedded_vector[INPUT_DIM][OUTPUT_DIM],
    float pixel_values[IN_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
){
    float patched_pixel_values[HIDDEN_SIZE][num_patch_x][num_patch_y] = {0};
    Patch_Embedding(
        patched_pixel_values, 
        pixel_values
    );
    float flatten_patched_pixel_values[num_patch_x * num_patch_y][OUTPUT_DIM];
    flatten(
        flatten_patched_pixel_values,
        patched_pixel_values
    );
    Pos_Embedding(
        embedded_vector, 
        flatten_patched_pixel_values
    );
}

void Siglip_Encoder(
    float encoder_output[INPUT_DIM][OUTPUT_DIM],
    float embedded_vector[INPUT_DIM][OUTPUT_DIM]
) {
    // copy input to working buffer
    float hidden_state[INPUT_DIM][OUTPUT_DIM];
    for (int layer = 0; layer < NUM_HIDDEN_LAYERS - 1; layer++) {
        memcpy(hidden_state, embedded_vector, sizeof(float) * INPUT_DIM * HIDDEN_SIZE);
        SiglipEncoderLayer(embedded_vector, hidden_state, layer);
    }

    // write final output
    memcpy(encoder_output, embedded_vector, sizeof(float) * INPUT_DIM * HIDDEN_SIZE);
    // for (int i = 0; i < INPUT_DIM; i++) {
    //     for (int j = 0; j < OUTPUT_DIM; j++) {
    //         encoder_output[i][j] = embedded_vector[i][j];
    //     }
    // }
}

void SiglipEncoderLayer(
    float output[INPUT_DIM][HIDDEN_SIZE], 
    float hidden_state[INPUT_DIM][HIDDEN_SIZE],
    int layer_id
) {
    // TODO: load weights by layer_id
    float vision_tower_vision_tower_vision_model_encoder_layers_0_layer_norm1_weight[HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_layer_norm1_bias[HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_layer_norm2_weight[HIDDEN_SIZE];
    float vision_tower_vision_tower_vision_model_encoder_layers_0_layer_norm2_bias[HIDDEN_SIZE];

    float residual[INPUT_DIM][HIDDEN_SIZE];
    float layer_norm_out[INPUT_DIM][HIDDEN_SIZE];
    float attn_out[INPUT_DIM][HIDDEN_SIZE];
    float mlp_out[INPUT_DIM][HIDDEN_SIZE];

    // // First LayerNorm
    // for (int i = 0; i < INPUT_DIM; i++) {
    //     for (int j = 0; j < HIDDEN_SIZE; j++) {
    //         residual1[i][j] = hidden_state[i][j];  // Save residual
    //     }
    // }

    memcpy(residual, hidden_state, sizeof(float) * INPUT_DIM * HIDDEN_SIZE);

    layer_norm<INPUT_DIM, HIDDEN_SIZE>(
        layer_norm_out, hidden_state, LAYER_NORM_EPS,
        vision_tower_vision_tower_vision_model_encoder_layers_0_layer_norm1_weight,
        vision_tower_vision_tower_vision_model_encoder_layers_0_layer_norm1_bias
    );

    SiglipAttention(
        attn_out, 
        layer_norm_out, 
        layer_id
    );

    for (int i = 0; i < INPUT_DIM; i++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            hidden_state[i][j] = residual[i][j] + attn_out[i][j];
        }
    }

    memcpy(residual, hidden_state, sizeof(float) * INPUT_DIM * HIDDEN_SIZE);

    layer_norm<INPUT_DIM, HIDDEN_SIZE>(
        layer_norm_out, hidden_state, LAYER_NORM_EPS,
        vision_tower_vision_tower_vision_model_encoder_layers_0_layer_norm2_weight,
        vision_tower_vision_tower_vision_model_encoder_layers_0_layer_norm2_bias
    );

    SiglipMLP(mlp_out, layer_norm_out, layer_id);

    for (int i = 0; i < INPUT_DIM; i++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            output[i][j] = residual[i][j] + mlp_out[i][j];
        }
    }
}