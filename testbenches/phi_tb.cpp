#include <iostream>
// #include "../modules/phi-2/phi-2_config.hpp"

#define HEAD_DIM 80 // HIDDEN_SIZE / NUM_ATTENTION_HEADS
#define NUM_ATTENTION_HEADS 32
#define NUM_HIDDEN_LAYERS 32
#define SLEN 2048 // 最大序列長度
#define VOCAB_SIZE 51200

void PhiForCausalLM_forward(
    float out_logits[SLEN][VOCAB_SIZE],
    float out_past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM],
    int input_ids[SLEN],
    float past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM] // cache
);

float out_logits[SLEN][VOCAB_SIZE];
float out_past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM];
int input_ids[SLEN];
float past_key_values[NUM_HIDDEN_LAYERS][NUM_ATTENTION_HEADS][SLEN][HEAD_DIM];

int main() {
    for (int i = 0; i < SLEN; ++i) {
        input_ids[i] = i % VOCAB_SIZE; // Example input IDs
    }
    for (int i = 0; i < 5; ++i) {
        std::cout << input_ids[i] << " ";
    }
    std::cout << std::endl;

    PhiForCausalLM_forward(
        out_logits,
        out_past_key_values,
        input_ids,
        past_key_values
    );

    for (int i = 0; i < 5; ++i) {
        std::cout << out_logits[i][0] << " ";
    }
    std::cout << std::endl;

    return 0;
}