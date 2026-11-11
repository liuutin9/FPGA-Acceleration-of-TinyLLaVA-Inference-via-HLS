#include <ap_fixed.h>
#include <hls_half.h>
#include <iostream>

typedef ap_fixed<32,14> fixed32_14;

#define INPUT_DIM 729
#define HIDDEN_SIZE 1152
#define NUM_ATTENTION_HEADS 16
#define HEAD_DIM 72
#define BLOCK_SIZE 36
#define IN_BLOCK_NUM 20
#define IN_REST_NUM 9
#define W_BLOCK_NUM 32

extern "C" {
void Siglip_linear(
	fixed32_14 *query,    // NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM
	fixed32_14 *key,      // NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM
	fixed32_14 *value,    // NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM
	fixed32_14 *in,       // INPUT_DIM*HIDDEN_SIZE
	half *q_weight,       // HIDDEN_SIZE*HIDDEN_SIZE
	half *q_bias,         // HIDDEN_SIZE
	half *k_weight,       // HIDDEN_SIZE*HIDDEN_SIZE
	half *k_bias,         // HIDDEN_SIZE
	half *v_weight,       // HIDDEN_SIZE*HIDDEN_SIZE
	half *v_bias          // HIDDEN_SIZE
) {
	#pragma HLS INTERFACE m_axi port=query    offset=slave bundle=gmem0 depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=key      offset=slave bundle=gmem1 depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=value    offset=slave bundle=gmem2 depth=NUM_ATTENTION_HEADS*INPUT_DIM*HEAD_DIM max_read_burst_length=128
    #pragma HLS INTERFACE m_axi port=in       offset=slave bundle=gmem3 depth=INPUT_DIM*HIDDEN_SIZE                  max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=q_weight offset=slave bundle=gmem4 depth=HIDDEN_SIZE*HIDDEN_SIZE                max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=k_weight offset=slave bundle=gmem3 depth=HIDDEN_SIZE*HIDDEN_SIZE                max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=v_weight offset=slave bundle=gmem5 depth=HIDDEN_SIZE*HIDDEN_SIZE                max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=q_bias   offset=slave bundle=gmem4 depth=HIDDEN_SIZE                            max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=k_bias   offset=slave bundle=gmem3 depth=HIDDEN_SIZE                            max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=v_bias   offset=slave bundle=gmem5 depth=HIDDEN_SIZE                            max_read_burst_length=128

	#pragma HLS INTERFACE s_axilite port=query    bundle=control
	#pragma HLS INTERFACE s_axilite port=key      bundle=control
	#pragma HLS INTERFACE s_axilite port=value    bundle=control
	#pragma HLS INTERFACE s_axilite port=in       bundle=control
	#pragma HLS INTERFACE s_axilite port=q_weight bundle=control
	#pragma HLS INTERFACE s_axilite port=k_weight bundle=control
	#pragma HLS INTERFACE s_axilite port=v_weight bundle=control
	#pragma HLS INTERFACE s_axilite port=q_bias   bundle=control
	#pragma HLS INTERFACE s_axilite port=k_bias   bundle=control
	#pragma HLS INTERFACE s_axilite port=v_bias   bundle=control
	#pragma HLS INTERFACE s_axilite port=return   bundle=control

	fixed32_14 temp_in[BLOCK_SIZE * HIDDEN_SIZE];
	fixed32_14 temp_q_bias[HIDDEN_SIZE];
	fixed32_14 temp_k_bias[HIDDEN_SIZE];
	fixed32_14 temp_v_bias[HIDDEN_SIZE];
	fixed32_14 block_q_weight[BLOCK_SIZE * HIDDEN_SIZE];
	fixed32_14 block_k_weight[BLOCK_SIZE * HIDDEN_SIZE];
	fixed32_14 block_v_weight[BLOCK_SIZE * HIDDEN_SIZE];
	fixed32_14 block_q_bias[BLOCK_SIZE * HIDDEN_SIZE];
	fixed32_14 block_k_bias[BLOCK_SIZE * HIDDEN_SIZE];
	fixed32_14 block_v_bias[BLOCK_SIZE * HIDDEN_SIZE];

	#pragma HLS bind_storage    variable=temp_in        type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=temp_in        cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=temp_q_bias    type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=temp_q_bias    cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=temp_k_bias    type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=temp_k_bias    cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=temp_v_bias    type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=temp_v_bias    cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=block_q_weight type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=block_q_weight cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=block_k_weight type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=block_k_weight cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=block_v_weight type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=block_v_weight cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=block_q_bias   type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=block_q_bias   cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=block_k_bias   type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=block_k_bias   cyclic factor=8 dim=1
	#pragma HLS bind_storage    variable=block_v_bias   type=RAM_T2P impl=uram
	#pragma HLS ARRAY_PARTITION variable=block_v_bias   cyclic factor=8 dim=1

	fixed32_14 sum;
	int d, k;

	copy_bias:
	for(int i = 0; i < HIDDEN_SIZE; i++){
		#pragma HLS PIPELINE II=1
		temp_q_bias[i] =  fixed32_14(q_bias[i]);
		temp_k_bias[i] =  fixed32_14(k_bias[i]);
		temp_v_bias[i] =  fixed32_14(v_bias[i]);
	}

	main:
	for(int b = 0; b < IN_BLOCK_NUM; b++){
		d = 0;
		k = 0;
		copy_in:
		for(int idx = 0; idx < BLOCK_SIZE * HIDDEN_SIZE; idx++){
			#pragma HLS PIPELINE II=1
			temp_in[idx] = in[b * BLOCK_SIZE * HIDDEN_SIZE + idx];
		}
		copy_block_bias:
		for (int i = 0; i < BLOCK_SIZE; i++) {
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				block_q_bias[i*HIDDEN_SIZE + j] = temp_q_bias[j];
				block_k_bias[i*HIDDEN_SIZE + j] = temp_k_bias[j];
				block_v_bias[i*HIDDEN_SIZE + j] = temp_v_bias[j];
			}
		}
		compute_block:
		for(int w = 0; w < W_BLOCK_NUM; w++){
			copy_weight:
			for (int idx = 0; idx < BLOCK_SIZE*HIDDEN_SIZE; idx++) {
				#pragma HLS PIPELINE II=1
				block_q_weight[idx] = fixed32_14(q_weight[w*BLOCK_SIZE*HIDDEN_SIZE + idx]);
				block_k_weight[idx] = fixed32_14(k_weight[w*BLOCK_SIZE*HIDDEN_SIZE + idx]);
				block_v_weight[idx] = fixed32_14(v_weight[w*BLOCK_SIZE*HIDDEN_SIZE + idx]);
			}
			in_block:
			for(int i = 0; i < BLOCK_SIZE; i++){
				weight_block:
				for(int j = 0; j < BLOCK_SIZE; j++){
					fixed32_14 acc_q = 0, acc_k = 0, acc_v = 0;
					// Step 1: linear
					compute_qkv:
					for (int k = 0; k < HIDDEN_SIZE; k++) {
						#pragma HLS PIPELINE II=1
						#pragma HLS reduction variable=sum operator=+
						#pragma HLS UNROLL factor=4
						acc_q += temp_in[i*HIDDEN_SIZE + k] * block_q_weight[j*HIDDEN_SIZE + k];
						acc_k += temp_in[i*HIDDEN_SIZE + k] * block_k_weight[j*HIDDEN_SIZE + k];
						acc_v += temp_in[i*HIDDEN_SIZE + k] * block_v_weight[j*HIDDEN_SIZE + k];
					}
					block_q_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j] += acc_q;
					block_k_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j] += acc_k;
					block_v_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j] += acc_v;
				}
			}
			out:
			for(int i = 0; i < BLOCK_SIZE; i++){
				out_in:
				for(int j = 0; j < BLOCK_SIZE; j++){
					#pragma HLS PIPELINE II=1
					int out_index = k * INPUT_DIM * HEAD_DIM + (b * BLOCK_SIZE + i) * HEAD_DIM + d*BLOCK_SIZE+j;
					query[out_index] = block_q_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j];
					key[out_index]   = block_k_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j];
					value[out_index] = block_v_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j];
				}
			}
			d = d ^ 1;
        	if(d == 0) k = k + 1;
		}
	}

	//rest block
	copy_in_r:
	for (int i = 0; i < IN_REST_NUM*HIDDEN_SIZE; i++) {
		#pragma HLS PIPELINE II=1
		temp_in[i] = in[IN_BLOCK_NUM*BLOCK_SIZE*HIDDEN_SIZE + i];
	}

	for (int i = 0; i < IN_REST_NUM; i++) {
		for (int j = 0; j < HIDDEN_SIZE; j++) {
			#pragma HLS PIPELINE II=1
			block_q_bias[i*HIDDEN_SIZE + j] = temp_q_bias[j];
			block_k_bias[i*HIDDEN_SIZE + j] = temp_k_bias[j];
			block_v_bias[i*HIDDEN_SIZE + j] = temp_v_bias[j];
		}
	}

	d = 0;
	k = 0;
	compute_block_r:
	for (int w = 0; w < W_BLOCK_NUM; w++) {
		// cache weights
		copy_w_r:
		for (int idx = 0; idx < BLOCK_SIZE*HIDDEN_SIZE; idx++) {
			#pragma HLS PIPELINE II=1
			block_q_weight[idx] = fixed32_14(q_weight[w*BLOCK_SIZE*HIDDEN_SIZE + idx]);
			block_k_weight[idx] = fixed32_14(k_weight[w*BLOCK_SIZE*HIDDEN_SIZE + idx]);
			block_v_weight[idx] = fixed32_14(v_weight[w*BLOCK_SIZE*HIDDEN_SIZE + idx]);
		}
		in_block_r:
		for (int i = 0; i < IN_REST_NUM; i++) {
			weight_block_r:
			for(int j = 0; j < BLOCK_SIZE; j++){
				fixed32_14 acc_q = 0, acc_k = 0, acc_v = 0;
				// Step 1: linear
				compute_qkv_r:
				for (int k = 0; k < HIDDEN_SIZE; k++) {
					#pragma HLS PIPELINE II=1
					#pragma HLS reduction variable=sum operator=+
					#pragma HLS UNROLL factor=4
					acc_q += temp_in[i*HIDDEN_SIZE + k] * block_q_weight[j*HIDDEN_SIZE + k];
					acc_k += temp_in[i*HIDDEN_SIZE + k] * block_k_weight[j*HIDDEN_SIZE + k];
					acc_v += temp_in[i*HIDDEN_SIZE + k] * block_v_weight[j*HIDDEN_SIZE + k];
				}
				block_q_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j] += acc_q;
				block_k_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j] += acc_k;
				block_v_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j] += acc_v;
			}
		}
		out_r:
		for(int i = 0; i < IN_REST_NUM; i++){
			out_in_r:
			for(int j = 0; j < BLOCK_SIZE; j++){
				#pragma HLS PIPELINE II=1
				int out_index = k * INPUT_DIM * HEAD_DIM + (IN_BLOCK_NUM * BLOCK_SIZE + i) * HEAD_DIM + d*BLOCK_SIZE+j;
				query[out_index] = block_q_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j];
				key[out_index]   = block_k_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j];
				value[out_index] = block_v_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE + j];
			}
		}
		d = d ^ 1;
		if(d == 0) k = k + 1;
	}
}
}

