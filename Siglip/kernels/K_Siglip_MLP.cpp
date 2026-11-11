#include <hls_math.h>
#include <ap_fixed.h>
#include <hls_half.h>
#include <iostream>

#define INPUT_DIM 729
#define HIDDEN_SIZE 1152
#define INTERMEDIATE_SIZE 4304
#define BLOCK_SIZE 16 //27
#define IN_BLOCK_NUM 45//...9 //27
#define IN_REST_NUM 9
#define W1_BLOCK_NUM 269//159...11
#define W2_BLOCK_NUM 72 //42...18

typedef ap_fixed<40,16> fixed40_16;
typedef ap_fixed<32,14> fixed32_14;

float gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f;
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = hls::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}

extern "C" {
void Siglip_MLP(
	fixed32_14 *out,      // INPUT_DIM*HIDDEN_SIZE
    fixed32_14 *in,       // INPUT_DIM*HIDDEN_SIZE
	half *weight1,  // INTERMEDIATE_SIZE*HIDDEN_SIZE
	half *bias1,    // INTERMEDIATE_SIZE
	half *weight2,  // HIDDEN_SIZE*INTERMEDIATE_SIZE
	half *bias2     // HIDDEN_SIZE
) {
	#pragma HLS INTERFACE m_axi port=out     offset=slave bundle=gmem1 depth=INPUT_DIM*HIDDEN_SIZE         max_read_burst_length=128
    #pragma HLS INTERFACE m_axi port=in      offset=slave bundle=gmem0 depth=INPUT_DIM*HIDDEN_SIZE         max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=weight1 offset=slave bundle=gmem2 depth=INTERMEDIATE_SIZE*HIDDEN_SIZE max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=bias1   offset=slave bundle=gmem1 depth=INTERMEDIATE_SIZE             max_read_burst_length=128
    #pragma HLS INTERFACE m_axi port=weight2 offset=slave bundle=gmem3 depth=HIDDEN_SIZE*INTERMEDIATE_SIZE max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=bias2   offset=slave bundle=gmem0 depth=HIDDEN_SIZE                   max_read_burst_length=128

	#pragma HLS INTERFACE s_axilite port=out     bundle=control
	#pragma HLS INTERFACE s_axilite port=in      bundle=control
	#pragma HLS INTERFACE s_axilite port=weight1 bundle=control
	#pragma HLS INTERFACE s_axilite port=bias1   bundle=control
    #pragma HLS INTERFACE s_axilite port=weight2 bundle=control
	#pragma HLS INTERFACE s_axilite port=bias2   bundle=control
	#pragma HLS INTERFACE s_axilite port=return  bundle=control

	fixed40_16 temp_out_1[BLOCK_SIZE*INTERMEDIATE_SIZE];
	fixed32_14 temp_in_1[BLOCK_SIZE*HIDDEN_SIZE];
	fixed32_14 temp_bias1[INTERMEDIATE_SIZE];
	fixed32_14 temp_bias2[HIDDEN_SIZE];
	fixed32_14 block_weight1[BLOCK_SIZE*HIDDEN_SIZE];
	fixed32_14 block_weight2[BLOCK_SIZE*INTERMEDIATE_SIZE];
	fixed40_16 block_bias1[BLOCK_SIZE*INTERMEDIATE_SIZE];
	fixed40_16 block_bias2[BLOCK_SIZE*HIDDEN_SIZE];

	#pragma HLS bind_storage    variable=temp_out_1    type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=temp_out_1    cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=temp_in_1     type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=temp_in_1     cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=temp_bias1    type=RAM_T2P impl=uram
	#pragma HLS bind_storage    variable=temp_bias2    type=RAM_T2P impl=uram
	#pragma HLS bind_storage    variable=block_weight1 type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=block_weight1 cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=block_weight2 type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=block_weight2 cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=block_bias1   type=RAM_T2P impl=uram
	#pragma HLS bind_storage    variable=block_bias2   type=RAM_T2P impl=uram

	cache_bias_1:
	for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
		#pragma HLS PIPELINE II=1
		temp_bias1[i] = fixed32_14(bias1[i]);
	}

	cache_bias_2:
	for (int i = 0; i < HIDDEN_SIZE; i++) {
		#pragma HLS PIPELINE II=1
		temp_bias2[i] = fixed32_14(bias2[i]);
	}

	iter_block:
	for (int b = 0; b < IN_BLOCK_NUM; b += 1) {
		copy_in:
		for (int i = 0; i < BLOCK_SIZE*HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			temp_in_1[i] = in[b*BLOCK_SIZE*HIDDEN_SIZE + i];
		}

		copy_bias_1:
		for (int i = 0; i < BLOCK_SIZE; i++) {
			for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				block_bias1[i*INTERMEDIATE_SIZE + j] = temp_bias1[j];
			}
		}
		copy_bias_2:
		for (int i = 0; i < BLOCK_SIZE; i++) {
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				block_bias2[i*HIDDEN_SIZE + j] = temp_bias2[j];
			}
		}

		compute_block_1:
		for (int w = 0; w < W1_BLOCK_NUM; w++) {
			copy_w0:
			for (int idx = 0; idx < BLOCK_SIZE*HIDDEN_SIZE; idx++) {
				#pragma HLS PIPELINE II=1
				block_weight1[idx] = fixed32_14(weight1[w*BLOCK_SIZE*HIDDEN_SIZE + idx]);
			}
			in_block_1:
			for (int i = 0; i < BLOCK_SIZE; i++) {
				weight_block_1:
				for (int j = 0; j < BLOCK_SIZE; j++) {
					fixed40_16 sum1 = fixed40_16(0.0f);
					partial_sum_1:
					for (int k=0; k<HIDDEN_SIZE; k++){
						#pragma HLS PIPELINE II=1
						#pragma HLS reduction variable=sum operator=+
						#pragma HLS UNROLL factor=4
//    				#pragma HLS reduction variable=sum operator=+
						sum1 += temp_in_1[i*HIDDEN_SIZE + k] * block_weight1[j*HIDDEN_SIZE + k];
					}
					block_bias1[i*INTERMEDIATE_SIZE+w*BLOCK_SIZE+j] += sum1;
				}
			}
		}

		gelu:
		for (int i = 0; i < BLOCK_SIZE*INTERMEDIATE_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=4
			temp_out_1[i] = fixed40_16(gelu(block_bias1[i]));
		}

		compute_block_2:
		for (int w = 0; w < W2_BLOCK_NUM; w++) {
			copy_w2:
			for (int idx = 0; idx < BLOCK_SIZE*INTERMEDIATE_SIZE; idx++) {
				#pragma HLS PIPELINE II=1
				block_weight2[idx] = fixed32_14(weight2[w*BLOCK_SIZE*INTERMEDIATE_SIZE + idx]);
			}
			in_block_2:
			for (int i = 0; i < BLOCK_SIZE; i++) {

				weight_block_2:
				for (int j = 0; j < BLOCK_SIZE; j++) {
					fixed40_16 sum2 = fixed40_16(0.0f);
					partial_sum_2:
					for (int k=0; k<INTERMEDIATE_SIZE; k++){
						#pragma HLS PIPELINE II=1
						#pragma HLS reduction variable=sum operator=+
						#pragma HLS UNROLL factor=4
//    				#pragma HLS reduction variable=sum operator=+
						sum2 += temp_out_1[i*INTERMEDIATE_SIZE + k] * block_weight2[j*INTERMEDIATE_SIZE + k];
					}
					block_bias2[i*HIDDEN_SIZE + w*BLOCK_SIZE+j] += sum2;
					// fixed40_16 sum2_0 = 0;
					// fixed40_16 sum2_1 = 0;
					// partial_sum_2:
					// for (int k=0; k<INTERMEDIATE_SIZE; k+=2){
					// 	#pragma HLS PIPELINE II=1
					// 	sum2_0 += temp_out_1[i*INTERMEDIATE_SIZE + k] * block_weight2[j*INTERMEDIATE_SIZE + k];
					// 	sum2_1 += temp_out_1[i*INTERMEDIATE_SIZE + k+1] * block_weight2[j*INTERMEDIATE_SIZE + k+1];
					// }
					// block_bias2[i*HIDDEN_SIZE + w*BLOCK_SIZE+j] += (sum2_0 + sum2_1);
				}
			}
			out:
			for (int i = 0; i < BLOCK_SIZE*HIDDEN_SIZE; i++) {
				#pragma HLS PIPELINE II=1
				out[b*BLOCK_SIZE*HIDDEN_SIZE + i] = fixed32_14(block_bias2[i]);
			}
		}
	}

	// rest input
	// cache input blocks
	copy_in_r:
	for (int i = 0; i < IN_REST_NUM*HIDDEN_SIZE; i++) {
		#pragma HLS PIPELINE II=1
		temp_in_1[i] = in[IN_BLOCK_NUM*BLOCK_SIZE*HIDDEN_SIZE + i];
	}

	copy_bias_1_r:
	for (int i = 0; i < IN_REST_NUM; i++) {
		for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
			#pragma HLS PIPELINE II=1
			block_bias1[i*INTERMEDIATE_SIZE + j] = temp_bias1[j];
		}
	}

	copy_bias_2_r:
	for (int i = 0; i < IN_REST_NUM; i++) {
		for (int j = 0; j < HIDDEN_SIZE; j++) {
			#pragma HLS PIPELINE II=1
			block_bias2[i*HIDDEN_SIZE + j] = temp_bias2[j];
		}
	}

	compute_block_1_r:
	for (int w = 0; w < W1_BLOCK_NUM; w++) {
		copy_w0_r:
		for (int idx = 0; idx < BLOCK_SIZE*HIDDEN_SIZE; idx++) {
			#pragma HLS PIPELINE II=1
			block_weight1[idx] = fixed32_14(weight1[w*BLOCK_SIZE*HIDDEN_SIZE + idx]);
		}
		#pragma HLS DEPENDENCE variable=block_weight1 inter false
		in_block_1_r:
		for (int i = 0; i < IN_REST_NUM; i++) {
			weight_block_1_r:
			for (int j = 0; j < BLOCK_SIZE; j++) {
				fixed40_16 sum1 = fixed40_16(0.0f);
				partial_sum_1_r:
				for (int k=0; k<HIDDEN_SIZE; k++){
					#pragma HLS PIPELINE II=1
					#pragma HLS reduction variable=sum operator=+
					#pragma HLS UNROLL factor=4
//    				#pragma HLS reduction variable=sum operator=++
					sum1 += temp_in_1[i*HIDDEN_SIZE + k] * block_weight1[j*HIDDEN_SIZE + k];
				}
				block_bias1[i*INTERMEDIATE_SIZE+w*BLOCK_SIZE+j] += sum1;
				// fixed40_16 sum1_0 = fixed40_16(0.0f);
				// fixed40_16 sum1_1 = fixed40_16(0.0f);
				// partial_sum_1_r:
				// for (int k=0; k<HIDDEN_SIZE; k+=2){
				// 	#pragma HLS PIPELINE II=1
				// 	sum1_0 += temp_in_1[i*HIDDEN_SIZE + k] * block_weight1[j*HIDDEN_SIZE + k];
				// 	sum1_1 += temp_in_1[i*HIDDEN_SIZE + k+1] * block_weight1[j*HIDDEN_SIZE + k+1];
				// }
				// block_bias1[i*INTERMEDIATE_SIZE+w*BLOCK_SIZE+j] += (sum1_0 + sum1_1);
			}
		}
	}

	gelu_r:
	for (int i = 0; i < IN_REST_NUM*INTERMEDIATE_SIZE; i++) {
		#pragma HLS PIPELINE II=1
		temp_out_1[i] = fixed40_16(gelu(block_bias1[i]));
	}

	compute_block_2_r:
	for (int w = 0; w < W2_BLOCK_NUM; w++) {
		copy_w2_r:
		for (int idx = 0; idx < BLOCK_SIZE*INTERMEDIATE_SIZE; idx++) {
			#pragma HLS PIPELINE II=1
			block_weight2[idx] = fixed32_14(weight2[w*BLOCK_SIZE*INTERMEDIATE_SIZE + idx]);
		}
		in_block_2_r:
		for (int i = 0; i < IN_REST_NUM; i++) {
			weight_block_2_r:
			for (int j = 0; j < BLOCK_SIZE; j++) {
				fixed40_16 sum2 = fixed40_16(0.0f);
				partial_sum_2_r:
				for (int k=0; k<INTERMEDIATE_SIZE; k++){
					#pragma HLS PIPELINE II=1
					#pragma HLS reduction variable=sum operator=+
					#pragma HLS UNROLL factor=4
//    				#pragma HLS reduction variable=sum operator=+
					sum2 += temp_out_1[i*INTERMEDIATE_SIZE + k] * block_weight2[j*INTERMEDIATE_SIZE + k];
				}
				block_bias2[i*HIDDEN_SIZE + w*BLOCK_SIZE+j] += sum2;
//				fixed40_16 sum2_0 = 0;
//				fixed40_16 sum2_1 = 0;
//				partial_sum_2_r:
//				for (int k=0; k<INTERMEDIATE_SIZE; k+=2){
//					#pragma HLS PIPELINE II=1
//					sum2_0 += temp_out_1[i*INTERMEDIATE_SIZE + k] * block_weight2[j*INTERMEDIATE_SIZE + k];
//					sum2_1 += temp_out_1[i*INTERMEDIATE_SIZE + k+1] * block_weight2[j*INTERMEDIATE_SIZE + k+1];
//				}
//				block_bias2[i*HIDDEN_SIZE + w*BLOCK_SIZE+j] += (sum2_0 + sum2_1);
			}
		}
		out_r:
		for (int i = 0; i < IN_REST_NUM*HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=4
			out[IN_BLOCK_NUM * BLOCK_SIZE * HIDDEN_SIZE + i] = fixed32_14(block_bias2[i]);
		}
	}
	
}
}
