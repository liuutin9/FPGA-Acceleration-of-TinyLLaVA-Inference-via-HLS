#include<stdio.h>
#include"../utils/transformer.hpp"
#include"Siglip_config.hpp"

//in : [3][384][384], out : [1152][27][27]
void Patch_Embedding(
    float patched_pixel_values[HIDDEN_SIZE][NUM_PATCH][NUM_PATCH],
    float pixel_values[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
){
    Conv2D(patched_pixel_values, pixel_values);
}

//in : [1152][27][27], out : [729][1152]
void flatten(
    float output[NUM_PATCH * NUM_PATCH][HIDDEN_SIZE],
    float input[HIDDEN_SIZE][NUM_PATCH][NUM_PATCH]
) {
    for (int i = 0; i < NUM_PATCH; i++) {
        for (int j = 0; j < NUM_PATCH; j++) {
            int patch_idx = i * NUM_PATCH + j;
            for (int c = 0; c < HIDDEN_SIZE; c++) {
                output[patch_idx][c] = input[c][i][j];
            }
        }
    }
}


// 假設 patched_pixel_values 是 flatten 過後的 [n_patches][embed_dim]
// output: embedded_vector[INPUT_DIM][HIDDEN_SIZE] ← 如果 INPUT_DIM = n_patches，output_dim = embed_dim
void Pos_Embedding(
    float embedded_vector[INPUT_DIM][HIDDEN_SIZE],
    float flatten_patched_pixel_values[INPUT_DIM][HIDDEN_SIZE]
) {
    float vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight[INPUT_DIM][HIDDEN_SIZE];

    for (int i = 0; i < NUM_PATCH; i++) {
        for (int j = 0; j < NUM_PATCH; j++) {
            int patch_id = i * NUM_PATCH + j;
            for (int c = 0; c < HIDDEN_SIZE; c++) {
                embedded_vector[patch_id][c] = (float)flatten_patched_pixel_values[c][patch_id]
                                             + vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight[patch_id][c];
            }
        }
    }
}

void Conv2D(
    float output[HIDDEN_SIZE][NUM_PATCH][NUM_PATCH],
    float pixel_values[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE]
){
    float kernels[HIDDEN_SIZE][NUM_CHANNELS][PATHC_SIZE][PATHC_SIZE];
    float bias[HIDDEN_SIZE];
    for(int k = 0; k < HIDDEN_SIZE; k++){
        for(int i = 0; i < NUM_PATCH; i++){
            for(int j = 0; j < NUM_PATCH; j++){
                output[k][i][j] = mult_with_kernel(pixel_values, kernels[k], i * PATHC_SIZE, j * PATHC_SIZE) + bias[k];
            }
        }
    }

}

float mult_with_kernel(
    float input[NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE], 
    float kernel[NUM_CHANNELS][PATHC_SIZE][PATHC_SIZE], 
    int kernel_x, 
    int kernel_y
){
    float result = 0;
    for(int c = 0; c < NUM_CHANNELS; c++){
        for(int i = 0; i < PATHC_SIZE; i++){
            for(int j = 0; j < PATHC_SIZE; j++){
                result += input[c][kernel_x + i][kernel_y + j] * kernel[c][i][j];
            }
        }
    }
    return result;
}

