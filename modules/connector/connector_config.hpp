// #include "../utils/transformer.hpp"

// connector config
#define VISION_HIDDEN_SIZE 1152
#define HIDDEN_SIZE 2560
#define SLEN 729 // INPUT_DIM in Siglip_config.hpp

// weights
float connector_connector_0_weight[HIDDEN_SIZE*VISION_HIDDEN_SIZE];
float connector_connector_0_bias[HIDDEN_SIZE];
float connector_connector_2_weight[HIDDEN_SIZE*HIDDEN_SIZE];
float connector_connector_2_bias[HIDDEN_SIZE];

float linear_out[SLEN*HIDDEN_SIZE];   
float gelu_out[SLEN*HIDDEN_SIZE];

//linear for connector
float weight_transpose4[VISION_HIDDEN_SIZE*HIDDEN_SIZE];
float weight_transpose5[HIDDEN_SIZE*HIDDEN_SIZE];

void Connector_forward(
    float out[SLEN*HIDDEN_SIZE],
    float in[SLEN*VISION_HIDDEN_SIZE]
    // int layer_id
);

float gelu(float x);

template <int in_features, int out_features, int n_samples>
void linear4(float out[n_samples*out_features], float in[n_samples*in_features], float weight[out_features*in_features], float bias[out_features]);

template <int in_features, int out_features, int n_samples>
void linear5(float out[n_samples*out_features], float in[n_samples*in_features], float weight[out_features*in_features], float bias[out_features]);