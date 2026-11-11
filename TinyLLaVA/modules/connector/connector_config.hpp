// connector config (only connector.cpp should include this; other code uses ../tinyllava_modules.hpp)
#pragma once
#include <string>

#define VISION_HIDDEN_SIZE 1152
#define HIDDEN_SIZE 2560
#define SLEN 729 // INPUT_DIM in Siglip_config.hpp (TinyLLaVA feeds 728 rows: token 0 is dropped)

// Weights live in connector.cpp (they used to be defined in this header, which broke
// linking as soon as two .cpp files included it).
void set_connector_weight_dir(const std::string& dir);
bool load_connector_weight();

// Linear(VISION_HIDDEN_SIZE -> HIDDEN_SIZE) -> GELU -> Linear(HIDDEN_SIZE -> HIDDEN_SIZE), row by row.
// in: n_tokens*VISION_HIDDEN_SIZE, out: n_tokens*HIDDEN_SIZE, n_tokens <= SLEN
void Connector_forward(float* out, const float* in, int n_tokens);
