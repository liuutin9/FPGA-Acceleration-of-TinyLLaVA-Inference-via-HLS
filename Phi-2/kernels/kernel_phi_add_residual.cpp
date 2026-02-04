#include <ap_fixed.h>
#include <hls_math.h>

#define HIDDEN_SIZE 2560

//typedef ap_fixed<32,14> fixed32_14;
typedef float fixed32_14;

extern "C" {
    void kernel_phi_add_residual(
        fixed32_14 out[HIDDEN_SIZE],
        fixed32_14 before_layernorm[HIDDEN_SIZE],
        fixed32_14 after_attention[HIDDEN_SIZE],
        fixed32_14 after_mlp[HIDDEN_SIZE]
    ) {

        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=before_layernorm offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=after_attention offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=after_mlp offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=before_layernorm bundle=control
        #pragma HLS INTERFACE s_axilite port=after_attention bundle=control
        #pragma HLS INTERFACE s_axilite port=after_mlp bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
        	out[i] = before_layernorm[i] + after_attention[i] + after_mlp[i];
        }
    }
}
