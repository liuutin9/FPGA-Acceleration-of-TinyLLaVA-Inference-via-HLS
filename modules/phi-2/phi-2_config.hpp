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
#define MAX_POSITION_EMBEDDINGS 2048
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
#define SLEN 2048 // 最大序列長度
#define TIE_WORD_EMBEDDINGS false
#define TORCH_DTYPE_FLOAT16 // 使用特殊處理
#define TRANSFORMERS_VERSION_4_37_0 // 使用特殊處理
#define USE_CACHE true
#define VOCAB_SIZE 51200

void rotate_half(
    float out[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float hidden_states[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM]
);

void apply_rotary_pos_emb(
    float out_q_embed[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float out_k_embed[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float in_q[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float in_k[NUM_KEY_VALUE_HEADS][SLEN][ROTARY_DIM],
    float in_cos[SLEN][ROTARY_DIM],
    float in_sin[SLEN][ROTARY_DIM]
);

void repeat_kv(
    float out[NUM_ATTENTION_HEADS][SLEN][HEAD_DIM],
    float hidden_states[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM]
);

void eager_attention_forward(
    float out_attn_output[SLEN][NUM_ATTENTION_HEADS][HEAD_DIM],
    float out_attn_weights[NUM_ATTENTION_HEADS][SLEN][SLEN],
    float in_q[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM],
    float in_k[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM],
    float in_v[NUM_KEY_VALUE_HEADS][SLEN][HEAD_DIM],
    float in_attention_mask[NUM_ATTENTION_HEADS][SLEN][SLEN],
    float in_scaling
);

void PhiAttention_forward(
    float out_attn_output[SLEN][NUM_ATTENTION_HEADS * HEAD_DIM],
    float out_attn_weights[NUM_ATTENTION_HEADS][SLEN][SLEN],
    int layer_id,
    float in_hidden_states[SLEN][HIDDEN_SIZE],
    float in_cos[SLEN][ROTARY_DIM],
    float in_sin[SLEN][ROTARY_DIM],
    float in_attention_mask[NUM_ATTENTION_HEADS][SLEN][SLEN]
);

void PhiMLP_forward(
    float out[SLEN][HIDDEN_SIZE],
    float in[SLEN][HIDDEN_SIZE],
    int layer_id
);

void PhiDecoderLayer_forward(
    float out[SLEN][HIDDEN_SIZE],
    int layer_id,
    float in_hidden_states[SLEN][HIDDEN_SIZE],
    float in_cos[SLEN][ROTARY_DIM],
    float in_sin[SLEN][ROTARY_DIM],
    float in_attention_mask[NUM_ATTENTION_HEADS][SLEN][SLEN]
);

void PhiRotaryEmbedding_forward(
    float out_cos[SLEN][ROTARY_DIM],
    float out_sin[SLEN][ROTARY_DIM],
    int position_ids[SLEN]
);

void Embedding_forward(
    float out[SLEN][HIDDEN_SIZE],
    int input_ids[SLEN]
);

void PhiModel_forward(
    float out_last_hidden_state[SLEN][HIDDEN_SIZE],
    float out_past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM],
    int in_input_ids[SLEN],
    float in_past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM] // cache
);

void PhiForCausalLM_forward(
    float out_logits[SLEN][VOCAB_SIZE],
    float out_past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM],
    int input_ids[SLEN],
    float past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM] // cache
);

void compute_default_rope_parameters(
    float out_inv_freq[ROTARY_DIM / 2]
);

void create_causal_mask(
    float out_causal_mask[NUM_ATTENTION_HEADS][SLEN][SLEN]
);