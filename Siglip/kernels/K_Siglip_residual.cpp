#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_half.h>
#include <ap_int.h>
#include <string.h>

typedef ap_fixed<32,14> fixed32_14;

#define HIDDEN_SIZE 1152
#define INPUT_DIM 729
#define BURST_LEN 8
#define BURST_TIME 144

extern "C" {
void Siglip_residual(
	fixed32_14 out[INPUT_DIM*HIDDEN_SIZE],
	fixed32_14 in1[INPUT_DIM*HIDDEN_SIZE],
	fixed32_14 in2[INPUT_DIM*HIDDEN_SIZE]
) {
	#pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=INPUT_DIM*HIDDEN_SIZE max_read_burst_length=256
    #pragma HLS INTERFACE m_axi port=in1 offset=slave bundle=gmem1 depth=INPUT_DIM*HIDDEN_SIZE max_read_burst_length=256
	#pragma HLS INTERFACE m_axi port=in2 offset=slave bundle=gmem2 depth=INPUT_DIM*HIDDEN_SIZE max_read_burst_length=256

	#pragma HLS INTERFACE s_axilite port=out    bundle=control
	#pragma HLS INTERFACE s_axilite port=in1    bundle=control
	#pragma HLS INTERFACE s_axilite port=in2    bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	fixed32_14 buffer1[HIDDEN_SIZE];
	fixed32_14 buffer2[HIDDEN_SIZE];
	fixed32_14 buffer3[HIDDEN_SIZE];

	#pragma HLS bind_storage variable=buffer1 type=RAM_T2P impl=bram
	#pragma HLS ARRAY_PARTITION variable=buffer1 cyclic factor=8 dim=1
	#pragma HLS bind_storage variable=buffer2 type=RAM_T2P impl=bram
	#pragma HLS ARRAY_PARTITION variable=buffer2 cyclic factor=8 dim=1
	#pragma HLS bind_storage variable=buffer3 type=RAM_T2P impl=bram
	#pragma HLS ARRAY_PARTITION variable=buffer3 cyclic factor=8 dim=1

	for(int i = 0; i < INPUT_DIM; i++){
		//#pragma HLS DATAFLOW
		loop_1:
		for(int j = 0; j < BURST_TIME; j++){
			//#pragma HLS PIPELINE II=1
			memcpy(&buffer1[j * BURST_LEN], &in1[i * HIDDEN_SIZE + j * BURST_LEN], sizeof(fixed32_14) * BURST_LEN);
			memcpy(&buffer2[j * BURST_LEN], &in2[i * HIDDEN_SIZE + j * BURST_LEN], sizeof(fixed32_14) * BURST_LEN);
		}
		for(int j = 0; j < HIDDEN_SIZE; j++){
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=4
			buffer3[j] = buffer2[j] + buffer1[j];
		}
		for(int j = 0; j < BURST_TIME; j++){
			//#pragma HLS PIPELINE II=1
			memcpy(&out[i * HIDDEN_SIZE + j * BURST_LEN], &buffer3[j * BURST_LEN], sizeof(fixed32_14) * BURST_LEN);
		}
	}

//	 for (int i = 0; i < INPUT_DIM*HIDDEN_SIZE; i++) {
//         //#pragma HLS PIPELINE II=1
//	 	out[i] = in1[i] + in2[i];
//	 }
}
}
