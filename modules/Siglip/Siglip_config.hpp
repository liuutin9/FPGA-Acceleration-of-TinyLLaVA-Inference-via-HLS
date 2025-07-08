#include "__/utils/transformer_hpp"

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
#define SLEN 2048 // TODO: 最大序列長度

//SIGLIP
#define INITIALIZER_FACTOR 1_0

/*
    vocab_size=32000,
    hidden_size=768,
    intermediate_size=3072,
    num_hidden_layers=12,
    num_attention_heads=12,
    max_position_embeddings=64,
    hidden_act="gelu_pytorch_tanh",
    layer_norm_eps=1e-6,
    attention_dropout=0.0,
    # This differs from `CLIPTokenizer`'s default and from openai/siglip
    # See https://github.com/huggingface/transformers/pull/24773#issuecomment-1632287538
    pad_token_id=1,
    bos_token_id=49406,
    eos_token_id=49407,
    projection_size=None,
*/

// "vision_tower__vision_tower_vision_model_embeddings_patch_embedding_bias": "model-00002-of-00002.safetensors",
// "vision_tower__vision_tower_vision_model_embeddings_patch_embedding_weight": "model-00002-of-00002.safetensors",
// "vision_tower__vision_tower_vision_model_embeddings_position_embedding_weight": "model-00002-of-00002.safetensors",