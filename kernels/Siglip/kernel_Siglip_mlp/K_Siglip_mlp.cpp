#include <hls_math.h>
#include <ap_fixed.h>
typedef ap_fixed<16,10> fixed16_10;
typedef ap_fixed<32,14> fixed32_14;

#define HIDDEN_SIZE 1152
#define INPUT_DIM 729
#define NUM_ATTENTION_HEADS 16
#define HEAD_DIM (HIDDEN_SIZE / NUM_ATTENTION_HEADS)

extern "C" {
void Siglip_linear(
		fixed16_10 *out,
		fixed16_10 *in,
		fixed16_10 *weight,
		fixed16_10 *bias
) {
	#pragma HLS INTERFACE m_axi port=out  offset=slave bundle=gmem depth=INPUT_DIM*(NUM_ATTENTION_HEADS * HEAD_DIM) max_read_burst_length=64
    #pragma HLS INTERFACE m_axi port=in  offset=slave bundle=gmem depth=INPUT_DIM*HIDDEN_SIZE max_read_burst_length=64
	#pragma HLS INTERFACE m_axi port=weight  offset=slave bundle=gmem depth=(NUM_ATTENTION_HEADS*HEAD_DIM)*HIDDEN_SIZE max_read_burst_length=64
	#pragma HLS INTERFACE m_axi port=bias  offset=slave bundle=gmem depth=NUM_ATTENTION_HEADS * HEAD_DIM max_read_burst_length=64

	#pragma HLS INTERFACE s_axilite port=out bundle=control
	#pragma HLS INTERFACE s_axilite port=in bundle=control
	#pragma HLS INTERFACE s_axilite port=weight bundle=control
	#pragma HLS INTERFACE s_axilite port=bias bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	fixed32_14 sum;

	for (int i = 0; i < INPUT_DIM; i++) {
		for (int j = 0; j < (NUM_ATTENTION_HEADS * HEAD_DIM); j++) {
			sum = fixed32_14(0.0f);
			for (int k = 0; k < HIDDEN_SIZE; k++) {
				sum += in[i*HIDDEN_SIZE + k] * weight[j*HIDDEN_SIZE + k];
			}
			out[i*(NUM_ATTENTION_HEADS * HEAD_DIM) + j] = fixed16_10(sum + bias[j]);
		}
	}
}
}
