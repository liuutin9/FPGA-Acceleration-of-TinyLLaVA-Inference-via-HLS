#include "../utils/transformer.hpp"

// phi-2 config

#define ATTENTION_DROPOUT 0.0
#define BOS_TOKEN_ID 50256
#define EMBD_DROPOUT 0.0
#define EOS_TOKEN_ID 50256
#define HEAD_DIM 80 // HIDDEN_SIZE / NUM_ATTENTION_HEADS
#define HIDDEN_ACT_GELU_NEW // 使用特殊處理
#define HIDDEN_SIZE 2560
#define INITIALIZER_RANGE 0.02
#define INTERMEDIATE_SIZE 10240
#define LAYER_NORM_EPS 1e-05
// #define MAX_POSITION_EMBEDDINGS 2048
#define MAX_POSITION_EMBEDDINGS 3072
#define MODEL_TYPE_PHI // 使用特殊處理
#define NUM_ATTENTION_HEADS 32
#define NUM_HIDDEN_LAYERS 32
#define NUM_KEY_VALUE_GROUPS 1 // NUM_ATTENTION_HEADS / NUM_KEY_VALUE_HEADS
#define NUM_KEY_VALUE_HEADS 32
#define PARTIAL_ROTARY_FACTOR 0.4
#define QK_LAYERNORM false
#define RESID_DROPOUT 0.1
#define ROPE_SCALING null
#define ROPE_THETA 10000.0
#define ROTARY_DIM 32 // HEAD_DIM * PARTIAL_ROTARY_FACTOR
#define HALF_ROTARY_DIM 16
// #define SLEN 2048 // 最大序列長度
#define SLEN 3072
#define TIE_WORD_EMBEDDINGS false
#define TORCH_DTYPE_FLOAT16 // 使用特殊處理
#define TRANSFORMERS_VERSION_4_37_0 // 使用特殊處理
#define USE_CACHE true
#define VOCAB_SIZE 51200

#define END_OF_TEXT_ID 50256

static float k_cache[32][NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM];
static float v_cache[32][NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM];

void rotate_half(
    float out[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    float in[NUM_KEY_VALUE_HEADS * ROTARY_DIM]
);

void apply_rotary_pos_emb(
    float out_q_embed[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    float out_k_embed[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    float in_q[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    float in_k[NUM_KEY_VALUE_HEADS * ROTARY_DIM],
    int position_idx
);

void qkv_with_cache(
    float out_attention[HEAD_DIM], // 1-dimension
    float in_q[HEAD_DIM], // 1-dimension
    float in_k[SLEN * HEAD_DIM], // 2-dimension
    float in_v[SLEN * HEAD_DIM], // 2-dimension
    float scale,
    int curr_len
);

void eager_attention_forward_with_kv_cache(
    float out_attention[NUM_ATTENTION_HEADS * HEAD_DIM],
    float in_q[NUM_KEY_VALUE_HEADS * HEAD_DIM],
    float in_k[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM],
    float in_v[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM],
    float in_scaling,
    int position_idx
);

void phi_linear(
    float out[HIDDEN_SIZE],
    float in[HIDDEN_SIZE],
    float weight[HIDDEN_SIZE * HIDDEN_SIZE],
    float bias[HIDDEN_SIZE]
);

void phi_mlp_linear_1(
    float out[INTERMEDIATE_SIZE],
    float in[HIDDEN_SIZE],
    float weight[INTERMEDIATE_SIZE * HIDDEN_SIZE],
    float bias[INTERMEDIATE_SIZE]
);

void phi_mlp_linear_2(
    float out[HIDDEN_SIZE],
    float in[INTERMEDIATE_SIZE],
    float weight[HIDDEN_SIZE * INTERMEDIATE_SIZE],
    float bias[HIDDEN_SIZE]
);

void phi_vocab_linear_argmax(
    int* output_id,
    float in[HIDDEN_SIZE],
    float weight[VOCAB_SIZE * HIDDEN_SIZE],
    float bias[VOCAB_SIZE]
);

void PhiAttention_forward(
    float out_attn_output[NUM_ATTENTION_HEADS * HEAD_DIM],
    int layer_id,
    int position_idx,
    float in_hidden_state[HIDDEN_SIZE],
    int position_idx
);

void PhiMLP_forward(
    float out[HIDDEN_SIZE],
    float in[HIDDEN_SIZE],
    int layer_id
);

void phi_layernorm(
    float out[HIDDEN_SIZE],
    float in[HIDDEN_SIZE],
    float weight[HIDDEN_SIZE],
    float bias[HIDDEN_SIZE],
    float eps
);

void PhiDecoderLayer_forward(
    float out[HIDDEN_SIZE],
    int layer_id,
    int position_idx,
    float in_hidden_state[HIDDEN_SIZE],
    int position_idx
);

// void PhiRotaryEmbedding_forward(
//     float out_cos[SLEN][ROTARY_DIM],
//     float out_sin[SLEN][ROTARY_DIM],
//     int position_ids[SLEN]
// );

void PhiModel_forward(
    int* output_id,
    float input_embed[HIDDEN_SIZE],
    bool should_predict,
    int position_idx
);

void PhiForCausalLM_forward(
    int output_ids[SLEN],
    float input_embeds[SLEN * HIDDEN_SIZE],
    int input_len
);

// void compute_default_rope_parameters(
//     float out_inv_freq[ROTARY_DIM / 2]
// );