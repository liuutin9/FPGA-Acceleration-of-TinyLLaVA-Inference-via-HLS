// Public interface of the CPU modules, for code that uses more than one of them
// (e.g. TinyLlava.cpp). It has no #defines, so it does not clash with the per-module
// config headers (Siglip_config.hpp / connector_config.hpp / phi-2_config.hpp each define
// their own HIDDEN_SIZE, SLEN, ...). Only a module's own .cpp should include its config.
#pragma once

#include <string>

namespace tinyllava {
// SigLIP (siglip-so400m-patch14-384)
constexpr int kNumChannels     = 3;
constexpr int kImageSize       = 384;
constexpr int kVisionHidden    = 1152;
constexpr int kSiglipTokens    = 729;                 // (384 / 14)^2
constexpr int kImageTokens     = kSiglipTokens - 1;   // 728, "patch" strategy drops token 0
// Phi-2
constexpr int kPhiHidden       = 2560;
constexpr int kPhiVocab        = 51200;
constexpr int kEosTokenId      = 50256;
constexpr int kImageTokenIndex = -200;
}  // namespace tinyllava

// ---- SigLIP (modules/Siglip/Siglip_modeling.cpp) ----
void set_siglip_weight_dir(const std::string& dir);
bool load_siglip_embedding_weight();
// input : 3*384*384 preprocessed pixels; output: 729*1152 (26 encoder layers, no post-LN)
void Siglip_Transformer_forward(float* output, float* input);

// ---- Connector (modules/connector/connector.cpp) ----
void set_connector_weight_dir(const std::string& dir);
bool load_connector_weight();
// mlp2x_gelu: Linear(1152, 2560) -> GELU -> Linear(2560, 2560), row by row.
// in: n_tokens*1152, out: n_tokens*2560
void Connector_forward(float* out, const float* in, int n_tokens);

// ---- Phi-2 (modules/phi-2/phi-2_modeling.cpp) ----
void set_phi_weight_dir(const std::string& dir);
bool load_phi_weight();
// Word embedding of one token: out = embed_tokens[token_id], 2560 floats.
void phi_embed_token(int token_id, float* out);
// Greedy decoding from prompt embeddings (input_len * 2560).
// Writes up to max_new_tokens ids (EOS not included) and returns how many were written.
int PhiForCausalLM_generate(const float* input_embeds, int input_len, int max_new_tokens, int* output_ids);
