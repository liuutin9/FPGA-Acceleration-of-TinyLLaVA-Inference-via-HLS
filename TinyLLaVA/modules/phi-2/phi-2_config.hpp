// phi-2 config (only phi-2_modeling.cpp should include this; other code uses ../tinyllava_modules.hpp)
#pragma once
#include <string>

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
// #define SLEN 2048 // 最大序列長度
#define SLEN 3072
#define TIE_WORD_EMBEDDINGS false
#define TORCH_DTYPE_FLOAT16 // 使用特殊處理
#define TRANSFORMERS_VERSION_4_37_0 // 使用特殊處理
#define USE_CACHE true
#define VOCAB_SIZE 51200

#define END_OF_TEXT_ID 50256

// The KV cache used to be `static float k_cache[32][32][SLEN][80]` in this header: 1 GB each,
// duplicated in every .cpp that included it. It now lives in phi-2_modeling.cpp and is sized
// to the actual sequence length.

// ---- weights ----
// Folder with the fp16 .bin exports named after the HF tensors, e.g.
//   language_model.model.layers.0.self_attn.q_proj.weight.bin
//   language_model.model.embed_tokens.weight.bin, language_model.lm_head.weight.bin
void set_phi_weight_dir(const std::string& dir);
bool load_phi_weight();   // ~5.6 GB (kept as fp16 in memory)

// ---- inference ----
void phi_embed_token(int token_id, float* out);   // out[HIDDEN_SIZE]

// Greedy decoding from prompt embeddings (input_len * HIDDEN_SIZE).
// Writes up to max_new_tokens ids (EOS not included) and returns how many were written.
int PhiForCausalLM_generate(const float* input_embeds, int input_len, int max_new_tokens, int* output_ids);

// Old interface kept for existing callers: output_ids[SLEN] is filled with the generated ids
// followed by END_OF_TEXT_ID.
void PhiForCausalLM_forward(
    int output_ids[SLEN],
    float input_embeds[SLEN * HIDDEN_SIZE],
    int input_len
);
