#include <hls_math.h>
#include <ap_fixed.h>
#include <hls_half.h>
#include <iostream>

typedef ap_fixed<32,14> fixed32_14;

#define HIDDEN_SIZE 1152
#define INPUT_DIM 729
#define NUM_ATTENTION_HEADS 16
#define HEAD_DIM 72

extern "C" {
void Siglip_attention(
	fixed32_14 *out,         // INPUT_DIM * HIDDEN_SIZE
	fixed32_14 *query,       // NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
	fixed32_14 *key,         // NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
	fixed32_14 *value,       // NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
	half *weight,            // HIDDEN_SIZE * HIDDEN_SIZE
	half *bias               // HIDDEN_SIZE
) {
	#pragma HLS INTERFACE m_axi port=out    offset=slave bundle=gmem0 depth=INPUT_DIM * HIDDEN_SIZE                max_read_burst_length=64
    #pragma HLS INTERFACE m_axi port=query  offset=slave bundle=gmem1 depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=64
	#pragma HLS INTERFACE m_axi port=key    offset=slave bundle=gmem2 depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=64
	#pragma HLS INTERFACE m_axi port=value  offset=slave bundle=gmem3 depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=weight offset=slave bundle=gmem4 depth=HIDDEN_SIZE*HIDDEN_SIZE                max_read_burst_length=64
	#pragma HLS INTERFACE m_axi port=bias   offset=slave bundle=gmem5 depth=HIDDEN_SIZE                            max_read_burst_length=64

	#pragma HLS INTERFACE s_axilite port=out    bundle=control
	#pragma HLS INTERFACE s_axilite port=query  bundle=control
	#pragma HLS INTERFACE s_axilite port=key    bundle=control
	#pragma HLS INTERFACE s_axilite port=value  bundle=control
	#pragma HLS INTERFACE s_axilite port=weight bundle=control
	#pragma HLS INTERFACE s_axilite port=bias   bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	fixed32_14 query_buf[HEAD_DIM];
	fixed32_14 value_buf[INPUT_DIM];
	fixed32_14 scaled_attn_weights_row[INPUT_DIM];
	fixed32_14 softmax_attn_weights_row[INPUT_DIM];
	fixed32_14 out_proj_buf[HIDDEN_SIZE];
	#pragma HLS bind_storage variable=query_buf                type=RAM_T2P impl=uram
	#pragma HLS bind_storage variable=value_buf                type=RAM_T2P impl=uram

    #pragma HLS bind_storage variable=scaled_attn_weights_row  type=RAM_T2P impl=bram
	#pragma HLS ARRAY_PARTITION variable=scaled_attn_weights_row cyclic factor=4 dim=1
	#pragma HLS bind_storage variable=softmax_attn_weights_row type=RAM_T2P impl=bram
	#pragma HLS bind_storage variable=out_proj_buf             type=RAM_T2P impl=bram

    fixed32_14 scaling = fixed32_14(1.0f / (float)hls::sqrt(HEAD_DIM));
    fixed32_14 sum, sum_exp, score, sum_out_proj;
	fixed32_14 max_val;
	int new_index;

	head_loop:
	for (int h = 0; h < NUM_ATTENTION_HEADS; h++) {
		for (int i = 0; i < INPUT_DIM; i++) {
			load_query:
			for (int k = 0; k < HEAD_DIM; k++) {
				#pragma HLS PIPELINE II=1
//				#pragma HLS UNROLL factor=2
				query_buf[k] = query[h*INPUT_DIM*HEAD_DIM + i*HEAD_DIM + k];
			}
			compute_qkt:
			for (int j = 0; j < INPUT_DIM; j++) {
				sum = fixed32_14(0.0f);
				for (int k = 0; k < HEAD_DIM; k++) {
					#pragma HLS PIPELINE II=1
					#pragma HLS UNROLL factor=4
					#pragma HLS reduction variable=sum operator=+
					sum += query_buf[k] * key[h*INPUT_DIM*HEAD_DIM + j*HEAD_DIM + k];
				}
				scaled_attn_weights_row[j] = sum * scaling;
			}
			compute_softmax_1:
			max_val = scaled_attn_weights_row[0];
			for (int j = 1; j < INPUT_DIM; j++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS UNROLL factor=2
				max_val = hls::max(max_val, scaled_attn_weights_row[j]);
			}
			compute_softmax_2:
			sum_exp = fixed32_14(0.0f);
			for (int j = 0; j < INPUT_DIM; j++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS UNROLL factor=4
				#pragma HLS reduction variable=sum_exp operator=+
				softmax_attn_weights_row[j] = hls::exp(scaled_attn_weights_row[j] - max_val);
				sum_exp += softmax_attn_weights_row[j];
			}
			compute_softmax_3:
			for (int j = 0; j < INPUT_DIM; j++) {
				#pragma HLS PIPELINE II=1
				//#pragma HLS UNROLL factor=4
				softmax_attn_weights_row[j] /= sum_exp;
			}
			compute_attention:
			for (int j = 0; j < HEAD_DIM; j++) {
				load_value:
				for (int k = 0; k < INPUT_DIM; k++) {
					#pragma HLS PIPELINE II=1
					value_buf[k] = value[h*INPUT_DIM*HEAD_DIM + k*HEAD_DIM + j];
				}
				score = fixed32_14(0.0f);
				for (int k = 0; k < INPUT_DIM; k++) {
					#pragma HLS PIPELINE II=1
					#pragma HLS UNROLL factor=4
					#pragma HLS reduction variable=score operator=+
					score += softmax_attn_weights_row[k] * value_buf[k];
				}
				out[i*NUM_ATTENTION_HEADS*HEAD_DIM + h*HEAD_DIM + j] = score;
			}
		}
	}

	out_proj:
	for (int i = 0; i < INPUT_DIM; i++) {
		load_out:
		for (int t = 0; t < HIDDEN_SIZE; t++) {
			#pragma HLS PIPELINE II=1
//			#pragma HLS UNROLL factor=2
			out_proj_buf[t] = out[i*HIDDEN_SIZE + t];
		}
		compute_out:
		for (int t = 0; t < HIDDEN_SIZE; t++) {
			sum_out_proj = fixed32_14(bias[t]);
			for (int k = 0; k < HIDDEN_SIZE; k++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS UNROLL factor=4
				#pragma HLS reduction variable=sum_out_proj operator=+
				sum_out_proj += out_proj_buf[k] * fixed32_14(weight[t*HIDDEN_SIZE + k]);
			}
			out[i*HIDDEN_SIZE + t] = sum_out_proj;
		}
	}
}
}