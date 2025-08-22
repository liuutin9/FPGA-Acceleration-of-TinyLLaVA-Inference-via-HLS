#include <hls_math.h>
#include <ap_fixed.h>

typedef ap_fixed<16,10> fixed16_10;
typedef ap_fixed<32,14> fixed32_14;

#define HIDDEN_SIZE 1152
#define INPUT_DIM 729
#define LAYER_NORM_EPS 0.00001

extern "C" {
void Siglip_layernorm(
		fixed16_10 *out,
		fixed16_10 *in,
		fixed16_10 *weight,
		fixed16_10 *bias
) {
	#pragma HLS INTERFACE m_axi port=out  offset=slave bundle=gmem depth=INPUT_DIM*HIDDEN_SIZE max_read_burst_length=64
    #pragma HLS INTERFACE m_axi port=in  offset=slave bundle=gmem depth=INPUT_DIM*HIDDEN_SIZE max_read_burst_length=64
	#pragma HLS INTERFACE m_axi port=weight  offset=slave bundle=gmem depth=HIDDEN_SIZE max_read_burst_length=64
	#pragma HLS INTERFACE m_axi port=bias  offset=slave bundle=gmem depth=HIDDEN_SIZE max_read_burst_length=64

	#pragma HLS INTERFACE s_axilite port=out bundle=control
	#pragma HLS INTERFACE s_axilite port=in bundle=control
	#pragma HLS INTERFACE s_axilite port=weight bundle=control
	#pragma HLS INTERFACE s_axilite port=bias bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	fixed32_14 mean, variance;
	fixed32_14 stddev_inv;
	fixed32_14 eps = fixed32_14(LAYER_NORM_EPS);

	for (int i = 0; i < INPUT_DIM; i++) {
		mean = fixed32_14(0.0f);
		variance = fixed32_14(0.0f);

		// Step 1: Compute mean
		for (int j = 0; j < HIDDEN_SIZE; j++) {
			mean += in[i*HIDDEN_SIZE+j];
		}
		mean /= HIDDEN_SIZE;

		// Step 2: Compute variance
		for (int j = 0; j < HIDDEN_SIZE; j++) {
			variance += (in[i*HIDDEN_SIZE+j] - mean) * (in[i*HIDDEN_SIZE+j] - mean);
		}
		variance /= HIDDEN_SIZE;

		// Step 3: Normalize
		stddev_inv = fixed32_14(1.0f / (float)hls::sqrt(variance + eps));
		for (int j = 0; j < HIDDEN_SIZE; j++) {
			out[i*HIDDEN_SIZE+j] = (in[i*HIDDEN_SIZE+j] - mean) * stddev_inv * weight[j] + bias[j];
		}
	}
}
}
