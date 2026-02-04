#include <ap_fixed.h>
#include <hls_math.h>
#include <ap_int.h>
#include <hls_half.h>

#define HIDDEN_SIZE 2560

//typedef ap_fixed<32,14> fixed32_14;
typedef float fixed32_14;

extern "C" {
    void kernel_phi_q_proj(
        fixed32_14* out,
        fixed32_14* in,
        half* weight_1,
        half* weight_2,
        half* bias_1,
        half* bias_2
    ) {
        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_1 offset=slave bundle=gmem0 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_2 offset=slave bundle=gmem1 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_1 offset=slave bundle=gmem0 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_2 offset=slave bundle=gmem1 depth=1280 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        fixed32_14 local_in[HIDDEN_SIZE];
        fixed32_14 local_out[HIDDEN_SIZE];

		#pragma HLS bind_storage variable=local_in type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_out type=RAM_T2P impl=uram

        load_bias:
        for (int i = 0; i < HIDDEN_SIZE / 2; i++) {
			#pragma HLS PIPELINE II=1
        	local_out[i] = float(bias_1[i]);
        	local_out[i + HIDDEN_SIZE / 2] = float(bias_2[i]);
        }

        load_in:
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
			local_in[i] = in[i];
		}

		compute:
		for (int i = 0; i < HIDDEN_SIZE / 2; i++) {
			for (int j = 0; j < HIDDEN_SIZE / 2; j++) {
				#pragma HLS PIPELINE II=1
				local_out[i] += float(weight_1[i * HIDDEN_SIZE + j]) * local_in[j] + float(weight_1[i * HIDDEN_SIZE + j + HIDDEN_SIZE / 2]) * local_in[j + HIDDEN_SIZE / 2];
				local_out[i + HIDDEN_SIZE / 2] += float(weight_2[i * HIDDEN_SIZE + j]) * local_in[j] + float(weight_2[i * HIDDEN_SIZE + j + HIDDEN_SIZE / 2]) * local_in[j + HIDDEN_SIZE / 2];
			}
		}

		store_output:
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
			out[i] = local_out[i];
		}
    }
}
