// #include <hls_math.h>
// #include <ap_fixed.h>
// #include <ap_int.h>
//vision config
#define VOCAB_SIZE 32000
#define HIDDEN_SIZE 1152
#define INTERMEDIATE_SIZE 4304
#define NUM_HIDDEN_LAYERS 27
#define NUM_ATTENTION_HEADS 16
#define HEAD_DIM 72 // 1152 / 16 = 72
#define NUM_CHANNELS 3
#define IMAGE_SIZE 384
#define PATCH_SIZE 14
#define HIDDEN_ACT "gelu_pytorch_tanh"
#define LAYER_NORM_EPS 1e-6
#define ATTENTION_DROPOUT 0.0
#define SLEN 729

//SIGLIP
#define INITIALIZER_FACTOR 1_0

#define NUM_PATCH ((IMAGE_SIZE - PATCH_SIZE + 1) / PATCH_SIZE + 1)
#define INPUT_DIM 729
#define num_patch_x 27
#define num_patch_y 27

// float vision_tower_vision_tower_vision_model_embeddings_position_embedding_weight[INPUT_DIM*HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_embeddings_patch_embedding_weight[HIDDEN_SIZE*NUM_CHANNELS*PATCH_SIZE*PATCH_SIZE];
// float vision_tower_vision_tower_vision_model_embeddings_patch_embedding_bias[HIDDEN_SIZE];

// float vision_tower_vision_tower_vision_model_encoder_layers_layer_norm1_weight[HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_layer_norm1_bias[HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_layer_norm2_weight[HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_layer_norm2_bias[HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_q_proj_weight[HIDDEN_SIZE*HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_q_proj_bias[HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_k_proj_weight[HIDDEN_SIZE*HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_k_proj_bias[HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_v_proj_weight[HIDDEN_SIZE*HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_v_proj_bias[HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_out_proj_weight[HIDDEN_SIZE*HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_encoder_layers_self_attn_out_proj_bias[HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_head_mlp_fc1_weight[INTERMEDIATE_SIZE*HIDDEN_SIZE];
// float vision_tower_vision_tower_vision_model_head_mlp_fc1_bias[INTERMEDIATE_SIZE];
// float vision_tower_vision_tower_vision_model_head_mlp_fc2_weight[HIDDEN_SIZE*INTERMEDIATE_SIZE];
// float vision_tower_vision_tower_vision_model_head_mlp_fc2_bias[HIDDEN_SIZE];

// float output[INPUT_DIM*HIDDEN_SIZE];
// float input[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE];

// float embedded_vector[INPUT_DIM*HIDDEN_SIZE];
// float patched_pixel_values[HIDDEN_SIZE*num_patch_x*num_patch_y];
// float flatten_patched_pixel_values[(num_patch_x * num_patch_y)*HIDDEN_SIZE];

// float hidden_state[INPUT_DIM*HIDDEN_SIZE];
// float q_proj[SLEN*(NUM_ATTENTION_HEADS*HEAD_DIM)];
// float k_proj[SLEN*(NUM_ATTENTION_HEADS*HEAD_DIM)];
// float v_proj[SLEN*(NUM_ATTENTION_HEADS*HEAD_DIM)];
// float reshaped_q_proj[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
// float reshaped_k_proj[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
// float reshaped_v_proj[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
// float query[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
// float key[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
// float value[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
// float attn_scores[NUM_ATTENTION_HEADS*SLEN*HEAD_DIM];
// // float attn_out[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];
// float reshaped_attn_out[SLEN*NUM_ATTENTION_HEADS*HEAD_DIM];

// //linear
// float weight_transpose1[HIDDEN_SIZE*INTERMEDIATE_SIZE];
// float weight_transpose2[HIDDEN_SIZE*NUM_ATTENTION_HEADS * HEAD_DIM];
// float weight_transpose3[HIDDEN_SIZE*HIDDEN_SIZE];

// //eager
// float scaled_attn_weights[SLEN*SLEN];
// float softmax_attn_weights[SLEN*SLEN];
// float eager_attn_scores[SLEN*HEAD_DIM];

// //MLP
// float linear_out[SLEN*INTERMEDIATE_SIZE];
// float gelu_out[SLEN*INTERMEDIATE_SIZE];

// float residual[INPUT_DIM*HIDDEN_SIZE];
// float layer_norm_out[INPUT_DIM*HIDDEN_SIZE];
// float attn_out[INPUT_DIM*HIDDEN_SIZE];
// float mlp_out[INPUT_DIM*HIDDEN_SIZE];

void Siglip_Transformer_forward(
    float output[INPUT_DIM*HIDDEN_SIZE],
    float input[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE]
);

void Embedding(
    float embedded_vector[INPUT_DIM*HIDDEN_SIZE],
    float pixel_values[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE]
);

void Patch_Embedding(
    float patch_embeds[HIDDEN_SIZE*NUM_PATCH*NUM_PATCH],
    float pixel_values[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE]
);

void flatten_and_transpose(
    float output[(NUM_PATCH*NUM_PATCH)*HIDDEN_SIZE],
    float input[HIDDEN_SIZE*NUM_PATCH*NUM_PATCH]
);

void Pos_Embedding(
    float embedded_vector[INPUT_DIM*HIDDEN_SIZE],
    float flatten_patched_pixel_values[INPUT_DIM*HIDDEN_SIZE]
);

void Conv2D(
    float output[HIDDEN_SIZE*NUM_PATCH*NUM_PATCH],
    float pixel_values[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE]
);

float mult_with_kernel(
    float input[NUM_CHANNELS*IMAGE_SIZE*IMAGE_SIZE], 
    float kernel[NUM_CHANNELS*PATCH_SIZE*PATCH_SIZE], 
    int kernel_x, 
    int kernel_y
);

void Siglip_Encoder(
    float encoder_output[INPUT_DIM*HIDDEN_SIZE],
    float embedded_vector[INPUT_DIM*HIDDEN_SIZE]
);

void SiglipEncoderLayer(
    float output[INPUT_DIM*HIDDEN_SIZE], 
    float hidden_state[INPUT_DIM*HIDDEN_SIZE],
    int layer_id
);

void SiglipAttention(
    float attn_out[SLEN*HIDDEN_SIZE],
    float hidden_states[SLEN*HIDDEN_SIZE],
    int layer_id
);

void eager_attention_per_head(
    float out[SLEN*HEAD_DIM],
    float query[SLEN*HEAD_DIM],
    float key[SLEN*HEAD_DIM],
    float value[SLEN*HEAD_DIM],
    float scaling
);

void matmul_with_scale_no_transpose(
    float out[SLEN*SLEN], 
    float in1[SLEN*HEAD_DIM], 
    float in2[SLEN*HEAD_DIM], 
    float scaling
);

void SiglipMLP(
    float out[SLEN*HIDDEN_SIZE], 
    float hidden_state[SLEN*HIDDEN_SIZE],
    int layer_id
);

// Utils
float gelu(float x);
template <int M, int N> 
void softmax(float out[M*N], float in[M*N]);
template <int M, int K, int N> 
void matmul(float out[M*N], float in1[M*K], float in2[K*N]);
template <int in_features, int out_features, int n_samples>
void linear(
    float out[n_samples*out_features], 
    float in[n_samples*in_features], 
    float weight[out_features*in_features], 
    float bias[out_features]
);
void Siglip_layer_norm(
    float out[INPUT_DIM*HIDDEN_SIZE],
    float in[INPUT_DIM*HIDDEN_SIZE],
    float eps,
    float weight[HIDDEN_SIZE],
    float bias[HIDDEN_SIZE]
);