// Phi-2 (PhiForCausalLM) on the CPU, one token per step with a KV cache, greedy decoding.
//
// Fixes compared with the previous version:
//   * no weight was ever loaded: every layer used uninitialised local arrays named
//     language_model_model_layers_0_* (and they were 26 MB-105 MB stack arrays)
//   * decoder layer: Phi-2 feeds the *layernorm output* to both attention and MLP
//     (parallel block); the MLP was fed the attention output
//   * partial rotary embedding: the first ROTARY_DIM dims of *each head* are rotated;
//     the old code rotated the first 32*32 contiguous values instead
//   * per-head attention slices used offset i*NUM_KEY_VALUE_HEADS instead of i*HEAD_DIM
//     (q) / per-head cache rows (k, v)
//   * scores were divided by 0.1118 (= 1/sqrt(80)) instead of multiplied
//   * phi_vocab_linear_argmax never wrote *output_id
//   * PhiForCausalLM_forward used the prompt embeddings for i >= input_len and the
//     embedding table for the prompt (swapped), and read output_ids[-1] on the first step
//   * 2 GB static KV cache defined in the header (one copy per including .cpp)

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "./phi-2_config.hpp"
#include "../utils/weight_io.hpp"

namespace {

std::string weight_dir = "../../../Weight/model_bins1/";

struct LayerWeights {   // fp16, PyTorch Linear layout [out][in]
    std::vector<uint16_t> ln_w, ln_b;
    std::vector<uint16_t> q_w, q_b, k_w, k_b, v_w, v_b, dense_w, dense_b;
    std::vector<uint16_t> fc1_w, fc1_b, fc2_w, fc2_b;
};
std::vector<LayerWeights> layers;
std::vector<uint16_t> embed_tokens, final_ln_w, final_ln_b, lm_head_w, lm_head_b;
bool loaded = false;

// KV cache: [layer][position][HIDDEN_SIZE] (heads are contiguous HEAD_DIM slices)
std::vector<float> k_cache, v_cache;
int cache_len = 0;

inline float* cache_row(std::vector<float>& cache, int layer, int pos) {
    return cache.data() + (static_cast<size_t>(layer) * cache_len + pos) * HIDDEN_SIZE;
}

// out[o] = b[o] + sum_i in[i] * w[o][i]
void matvec(float* out, const float* in, const uint16_t* w, const uint16_t* b, int out_dim, int in_dim) {
    const float* lut = weight_io::fp16_table();
    #pragma omp parallel for
    for (int o = 0; o < out_dim; ++o) {
        const uint16_t* wr = w + static_cast<size_t>(o) * in_dim;
        float acc = b ? lut[b[o]] : 0.0f;
        for (int i = 0; i < in_dim; ++i) acc += in[i] * lut[wr[i]];
        out[o] = acc;
    }
}

void layernorm(float* out, const float* in, const std::vector<uint16_t>& w, const std::vector<uint16_t>& b) {
    const float* lut = weight_io::fp16_table();
    float mean = 0.0f;
    for (int i = 0; i < HIDDEN_SIZE; ++i) mean += in[i];
    mean /= HIDDEN_SIZE;
    float var = 0.0f;
    for (int i = 0; i < HIDDEN_SIZE; ++i) var += (in[i] - mean) * (in[i] - mean);
    var /= HIDDEN_SIZE;
    const float inv_std = 1.0f / std::sqrt(var + static_cast<float>(LAYER_NORM_EPS));
    for (int i = 0; i < HIDDEN_SIZE; ++i) out[i] = (in[i] - mean) * inv_std * lut[w[i]] + lut[b[i]];
}

// gelu_new (tanh approximation), Phi-2's hidden_act
inline float gelu_new(float x) {
    const float k = 0.7978845608028654f;  // sqrt(2/pi)
    return 0.5f * x * (1.0f + std::tanh(k * (x + 0.044715f * x * x * x)));
}

// Partial rotary embedding on the first ROTARY_DIM dims of every head:
// x_rot = x * cos + rotate_half(x) * sin, rotate_half([x1, x2]) = [-x2, x1]
void apply_rotary(float* x, int pos) {
    constexpr int half = ROTARY_DIM / 2;
    float c[half], s[half];
    for (int i = 0; i < half; ++i) {
        const float inv_freq = 1.0f / std::pow(static_cast<float>(ROPE_THETA), (2.0f * i) / ROTARY_DIM);
        const float angle = static_cast<float>(pos) * inv_freq;
        c[i] = std::cos(angle);
        s[i] = std::sin(angle);
    }
    for (int h = 0; h < NUM_ATTENTION_HEADS; ++h) {
        float* v = x + h * HEAD_DIM;
        for (int i = 0; i < half; ++i) {
            const float x1 = v[i], x2 = v[i + half];
            v[i]        = x1 * c[i] - x2 * s[i];
            v[i + half] = x2 * c[i] + x1 * s[i];
        }
    }
}

// One decoder layer for the token at `pos`; hidden is updated in place.
void decoder_layer(float* hidden, int layer_id, int pos) {
    const LayerWeights& L = layers[layer_id];
    std::vector<float> x(HIDDEN_SIZE), q(HIDDEN_SIZE), attn(HIDDEN_SIZE), attn_out(HIDDEN_SIZE);
    std::vector<float> fc1(INTERMEDIATE_SIZE), mlp_out(HIDDEN_SIZE);

    layernorm(x.data(), hidden, L.ln_w, L.ln_b);

    // ---- self attention ----
    float* k_row = cache_row(k_cache, layer_id, pos);
    float* v_row = cache_row(v_cache, layer_id, pos);
    matvec(q.data(), x.data(), L.q_w.data(), L.q_b.data(), HIDDEN_SIZE, HIDDEN_SIZE);
    matvec(k_row,    x.data(), L.k_w.data(), L.k_b.data(), HIDDEN_SIZE, HIDDEN_SIZE);
    matvec(v_row,    x.data(), L.v_w.data(), L.v_b.data(), HIDDEN_SIZE, HIDDEN_SIZE);
    apply_rotary(q.data(), pos);
    apply_rotary(k_row, pos);

    const float scaling = 1.0f / std::sqrt(static_cast<float>(HEAD_DIM));
    #pragma omp parallel for
    for (int h = 0; h < NUM_ATTENTION_HEADS; ++h) {
        const float* qh = q.data() + h * HEAD_DIM;
        std::vector<float> scores(pos + 1);
        float max_score = -INFINITY;
        for (int t = 0; t <= pos; ++t) {
            const float* kh = cache_row(k_cache, layer_id, t) + h * HEAD_DIM;
            float dot = 0.0f;
            for (int d = 0; d < HEAD_DIM; ++d) dot += qh[d] * kh[d];
            scores[t] = dot * scaling;
            max_score = std::max(max_score, scores[t]);
        }
        float sum = 0.0f;
        for (int t = 0; t <= pos; ++t) {
            scores[t] = std::exp(scores[t] - max_score);
            sum += scores[t];
        }
        float* oh = attn.data() + h * HEAD_DIM;
        std::fill(oh, oh + HEAD_DIM, 0.0f);
        for (int t = 0; t <= pos; ++t) {
            const float p = scores[t] / sum;
            const float* vh = cache_row(v_cache, layer_id, t) + h * HEAD_DIM;
            for (int d = 0; d < HEAD_DIM; ++d) oh[d] += p * vh[d];
        }
    }
    matvec(attn_out.data(), attn.data(), L.dense_w.data(), L.dense_b.data(), HIDDEN_SIZE, HIDDEN_SIZE);

    // ---- MLP (same layernorm output as attention: Phi-2 parallel block) ----
    matvec(fc1.data(), x.data(), L.fc1_w.data(), L.fc1_b.data(), INTERMEDIATE_SIZE, HIDDEN_SIZE);
    for (float& v : fc1) v = gelu_new(v);
    matvec(mlp_out.data(), fc1.data(), L.fc2_w.data(), L.fc2_b.data(), HIDDEN_SIZE, INTERMEDIATE_SIZE);

    for (int i = 0; i < HIDDEN_SIZE; ++i) hidden[i] += attn_out[i] + mlp_out[i];
}

int predict_next(const float* hidden) {
    std::vector<float> x(HIDDEN_SIZE), logits(VOCAB_SIZE);
    layernorm(x.data(), hidden, final_ln_w, final_ln_b);
    matvec(logits.data(), x.data(), lm_head_w.data(), lm_head_b.data(), VOCAB_SIZE, HIDDEN_SIZE);
    return static_cast<int>(std::max_element(logits.begin(), logits.end()) - logits.begin());
}

bool load(const std::string& name, std::vector<uint16_t>& out, size_t count) {
    return weight_io::read_fp16(weight_io::join(weight_dir, name + ".bin"), out, count);
}

}  // namespace

void set_phi_weight_dir(const std::string& dir) {
    weight_dir = dir;
    loaded = false;
}

bool load_phi_weight() {
    if (loaded) return true;
    constexpr size_t H = HIDDEN_SIZE, I = INTERMEDIATE_SIZE, V = VOCAB_SIZE;
    layers.assign(NUM_HIDDEN_LAYERS, LayerWeights());
    for (int l = 0; l < NUM_HIDDEN_LAYERS; ++l) {
        const std::string p = "language_model.model.layers." + std::to_string(l) + ".";
        LayerWeights& L = layers[l];
        const bool ok =
            load(p + "input_layernorm.weight", L.ln_w, H) && load(p + "input_layernorm.bias", L.ln_b, H) &&
            load(p + "self_attn.q_proj.weight", L.q_w, H * H) && load(p + "self_attn.q_proj.bias", L.q_b, H) &&
            load(p + "self_attn.k_proj.weight", L.k_w, H * H) && load(p + "self_attn.k_proj.bias", L.k_b, H) &&
            load(p + "self_attn.v_proj.weight", L.v_w, H * H) && load(p + "self_attn.v_proj.bias", L.v_b, H) &&
            load(p + "self_attn.dense.weight", L.dense_w, H * H) && load(p + "self_attn.dense.bias", L.dense_b, H) &&
            load(p + "mlp.fc1.weight", L.fc1_w, I * H) && load(p + "mlp.fc1.bias", L.fc1_b, I) &&
            load(p + "mlp.fc2.weight", L.fc2_w, H * I) && load(p + "mlp.fc2.bias", L.fc2_b, H);
        if (!ok) return false;
        std::cout << "phi-2: loaded layer " << l << std::endl;
    }
    loaded = load("language_model.model.embed_tokens.weight", embed_tokens, V * H) &&
             load("language_model.model.final_layernorm.weight", final_ln_w, H) &&
             load("language_model.model.final_layernorm.bias", final_ln_b, H) &&
             load("language_model.lm_head.weight", lm_head_w, V * H) &&
             load("language_model.lm_head.bias", lm_head_b, V);
    return loaded;
}

void phi_embed_token(int token_id, float* out) {
    if (!load_phi_weight() || token_id < 0 || token_id >= VOCAB_SIZE) {
        std::cerr << "phi_embed_token: invalid token id " << token_id << " or weights missing" << std::endl;
        std::fill(out, out + HIDDEN_SIZE, 0.0f);
        return;
    }
    const float* lut = weight_io::fp16_table();
    const uint16_t* row = embed_tokens.data() + static_cast<size_t>(token_id) * HIDDEN_SIZE;
    for (int i = 0; i < HIDDEN_SIZE; ++i) out[i] = lut[row[i]];
}

int PhiForCausalLM_generate(const float* input_embeds, int input_len, int max_new_tokens, int* output_ids) {
    if (!load_phi_weight() || input_len <= 0 || max_new_tokens <= 0) return 0;

    int total = input_len + max_new_tokens;
    if (total > MAX_POSITION_EMBEDDINGS) {
        std::cerr << "phi-2: sequence capped at MAX_POSITION_EMBEDDINGS=" << MAX_POSITION_EMBEDDINGS << std::endl;
        total = MAX_POSITION_EMBEDDINGS;
    }
    cache_len = total;
    k_cache.assign(static_cast<size_t>(NUM_HIDDEN_LAYERS) * cache_len * HIDDEN_SIZE, 0.0f);
    v_cache.assign(static_cast<size_t>(NUM_HIDDEN_LAYERS) * cache_len * HIDDEN_SIZE, 0.0f);

    std::vector<float> hidden(HIDDEN_SIZE);
    int n_out = 0;
    for (int pos = 0; pos < total; ++pos) {
        if (pos < input_len) {
            std::memcpy(hidden.data(), input_embeds + static_cast<size_t>(pos) * HIDDEN_SIZE, sizeof(float) * HIDDEN_SIZE);
        } else {
            phi_embed_token(output_ids[n_out - 1], hidden.data());
        }
        for (int l = 0; l < NUM_HIDDEN_LAYERS; ++l) decoder_layer(hidden.data(), l, pos);

        if (pos < input_len - 1) continue;   // prefill: only the KV cache is needed
        const int next = predict_next(hidden.data());
        if (next == EOS_TOKEN_ID) break;
        output_ids[n_out++] = next;
        if (n_out == max_new_tokens) break;
    }
    return n_out;
}

void PhiForCausalLM_forward(int output_ids[SLEN], float input_embeds[SLEN * HIDDEN_SIZE], int input_len) {
    std::fill(output_ids, output_ids + SLEN, END_OF_TEXT_ID);
    PhiForCausalLM_generate(input_embeds, input_len, SLEN - input_len, output_ids);
}
