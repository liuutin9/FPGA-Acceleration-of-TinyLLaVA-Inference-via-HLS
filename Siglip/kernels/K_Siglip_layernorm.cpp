#include <hls_math.h>
#include <ap_fixed.h>
#include <hls_half.h>
#include <iostream>

typedef ap_fixed<32,14> fixed32_14;
typedef ap_fixed<48,32> fixed48_32;

#define HIDDEN_SIZE 1152
#define INPUT_DIM 729
#define LAYER_NORM_EPS 0.00001

extern "C" {
void Siglip_layernorm(
	fixed32_14 out[INPUT_DIM*HIDDEN_SIZE],
	fixed32_14 in[INPUT_DIM*HIDDEN_SIZE],
	half weight[HIDDEN_SIZE],
	half bias[HIDDEN_SIZE]
) {
	#pragma HLS INTERFACE m_axi port=out    offset=slave bundle=gmem0 depth=INPUT_DIM*HIDDEN_SIZE max_read_burst_length=128
    #pragma HLS INTERFACE m_axi port=in     offset=slave bundle=gmem1 depth=INPUT_DIM*HIDDEN_SIZE max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=weight offset=slave bundle=gmem1 depth=HIDDEN_SIZE           max_read_burst_length=128
	#pragma HLS INTERFACE m_axi port=bias   offset=slave bundle=gmem0 depth=HIDDEN_SIZE           max_read_burst_length=128

	#pragma HLS INTERFACE s_axilite port=out    bundle=control
	#pragma HLS INTERFACE s_axilite port=in     bundle=control
	#pragma HLS INTERFACE s_axilite port=weight bundle=control
	#pragma HLS INTERFACE s_axilite port=bias   bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	fixed32_14 mean = fixed32_14(0.0f);
	fixed32_14 variance = fixed32_14(0.0f);
	fixed48_32 sum = fixed48_32(0.0f);
	fixed32_14 eps = fixed32_14(LAYER_NORM_EPS);

	fixed32_14 in_buffer[HIDDEN_SIZE];
	fixed32_14 weight_buffer[HIDDEN_SIZE];
	fixed32_14 bias_buffer[HIDDEN_SIZE];
	#pragma HLS bind_storage variable=in_buffer     type=RAM_T2P impl=bram
	#pragma HLS bind_storage variable=weight_buffer type=RAM_T2P impl=bram
	#pragma HLS bind_storage variable=bias_buffer    type=RAM_T2P impl=bram

	#pragma HLS ARRAY_PARTITION variable=in_buffer cyclic factor=8 dim=1
	#pragma HLS ARRAY_PARTITION variable=weight_buffer cyclic factor=8 dim=1
	#pragma HLS ARRAY_PARTITION variable=bias_buffer cyclic factor=8 dim=1

	// Pre-convert weight and bias from half to fixed32_14
	for (int j = 0; j < HIDDEN_SIZE; j++) {
		#pragma HLS PIPELINE II=1
		//#pragma HLS UNROLL factor=2
		weight_buffer[j] = fixed32_14(weight[j]);
		bias_buffer[j] = fixed32_14(bias[j]);
	}

	for (int i = 0; i < INPUT_DIM; i++) {
		mean = fixed32_14(0.0f);
		variance = fixed32_14(0.0f);
		sum = fixed48_32(0.0f);

		for (int j = 0; j < HIDDEN_SIZE; j++) {
			#pragma HLS PIPELINE II=1
            //#pragma HLS UNROLL factor=2
			in_buffer[j] = in[i*HIDDEN_SIZE+j];
		}

		// Step 1: Compute mean
		for (int j = 0; j < HIDDEN_SIZE; j++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=4
    		#pragma HLS reduction variable=mean operator=+
			mean += in_buffer[j];
		}
		mean /= HIDDEN_SIZE;

		for (int j = 0; j < HIDDEN_SIZE; j++) {
			#pragma HLS PIPELINE II=1
            //#pragma HLS UNROLL factor=2
			in_buffer[j] -= mean;
		}

		// Step 2: Compute variance
		for (int j = 0; j < HIDDEN_SIZE; j++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=4
    		#pragma HLS reduction variable=sum operator=+
			sum += in_buffer[j] * in_buffer[j];
		}
		variance = sum / HIDDEN_SIZE;

		// Step 3: Normalize
		fixed32_14 stddev_inv = fixed32_14(1.0f / (float)hls::sqrt(variance + eps));
		for (int j = 0; j < HIDDEN_SIZE; j++) {
			#pragma HLS PIPELINE II=1
            //#pragma HLS UNROLL factor=2
			out[i*HIDDEN_SIZE+j] = in_buffer[j] * stddev_inv * weight_buffer[j] + bias_buffer[j];
		}
	}
}
}
