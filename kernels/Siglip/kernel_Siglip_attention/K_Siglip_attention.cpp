#include <hls_math.h>
#include <ap_fixed.h>
#include <stdio.h>
typedef ap_fixed<16,10> fixed16_10;
typedef ap_fixed<32,14> fixed32_14;

#define HIDDEN_SIZE 1152
#define INPUT_DIM 729
#define NUM_ATTENTION_HEADS 16
#define HEAD_DIM 72

extern "C" {
void Siglip_attention(
	fixed16_10 *out,         // NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
	fixed16_10 *query,       // NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
	fixed16_10 *key,         // NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
	fixed16_10 *value        // NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
) {
	#pragma HLS INTERFACE m_axi port=out    offset=slave bundle=gmem depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=64
    #pragma HLS INTERFACE m_axi port=query  offset=slave bundle=gmem depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=64
	#pragma HLS INTERFACE m_axi port=key    offset=slave bundle=gmem depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=64
	#pragma HLS INTERFACE m_axi port=value  offset=slave bundle=gmem depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=64

	#pragma HLS INTERFACE s_axilite port=out bundle=control
	#pragma HLS INTERFACE s_axilite port=query bundle=control
	#pragma HLS INTERFACE s_axilite port=key bundle=control
	#pragma HLS INTERFACE s_axilite port=value bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	fixed16_10 scaled_attn_weights_row[INPUT_DIM];
	fixed32_14 softmax_attn_weights_row[INPUT_DIM];
    #pragma HLS bind_storage variable=scaled_attn_weights_row type=RAM_T2P impl=bram
    #pragma HLS bind_storage variable=softmax_attn_weights_row type=RAM_T2P impl=bram

    fixed32_14 scaling = fixed32_14(1.0f / (float)hls::sqrt(HEAD_DIM));
    fixed32_14 sum, sum_exp, score;
	fixed16_10 max_val;

	for (int h = 0; h < NUM_ATTENTION_HEADS; h++) {
		for (int i = 0; i < INPUT_DIM; i++) {
			for (int j = 0; j < INPUT_DIM; j++) {
				sum = fixed32_14(0.0f);
				for (int k = 0; k < HEAD_DIM; k++) {
					sum += query[h*INPUT_DIM*HEAD_DIM + i*HEAD_DIM + k] * key[h*INPUT_DIM*HEAD_DIM + j*HEAD_DIM + k];
				}
				scaled_attn_weights_row[j] = sum * scaling;
			}

			max_val = scaled_attn_weights_row[0];
			for (int j = 1; j < INPUT_DIM; j++) {
				max_val = hls::max(max_val, scaled_attn_weights_row[j]);
			}
			sum_exp = fixed32_14(0.0f);
			for (int j = 0; j < INPUT_DIM; j++) {
				softmax_attn_weights_row[j] = hls::exp(scaled_attn_weights_row[j] - max_val);
				sum_exp += softmax_attn_weights_row[j];
			}
			for (int j = 0; j < INPUT_DIM; j++) {
				softmax_attn_weights_row[j] /= sum_exp;
			}

			for (int j = 0; j < HEAD_DIM; j++) {
				score = fixed32_14(0.0f);
				for (int k = 0; k < INPUT_DIM; k++) {
					score += softmax_attn_weights_row[k] * value[h*INPUT_DIM*HEAD_DIM + k*HEAD_DIM + j];
				}
				out[h*INPUT_DIM*HEAD_DIM + i*HEAD_DIM + j] = score;
			}
		}
	}
}
}
