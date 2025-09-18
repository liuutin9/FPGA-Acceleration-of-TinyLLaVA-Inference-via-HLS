#include <ap_fixed.h>
#include <hls_math.h>

#define HIDDEN_SIZE 2560
#define NUM_BLOCKS 10
#define BLOCK_SIZE 256

typedef ap_fixed<32,14> fixed32_14;

inline void loadToLocal(fixed32_14 local[HIDDEN_SIZE], fixed32_14 global[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=8
    	local[i] = global[i];
    }
}

inline void initLocal(
    fixed32_14 local_in[HIDDEN_SIZE],
    fixed32_14 in[HIDDEN_SIZE]
) {
    #pragma HLS DATAFLOW
    loadToLocal(local_in, in);
}

inline void storeOutput(fixed32_14 out[HIDDEN_SIZE], fixed32_14 local_out[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=8
    	out[i] = local_out[i];
    }
}

extern "C" {
    void kernel_phi_copy_k(
        fixed32_14 out[HIDDEN_SIZE],
        fixed32_14 in[HIDDEN_SIZE]
    ) {

        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        fixed32_14 local_out[HIDDEN_SIZE];
        fixed32_14 local_in[HIDDEN_SIZE];

        #pragma HLS BIND_STORAGE variable=local_out type=RAM_1P impl=BRAM
        #pragma HLS BIND_STORAGE variable=local_in type=RAM_1P impl=BRAM

        #pragma HLS ARRAY_PARTITION variable=local_out cyclic factor=8 dim=1
        #pragma HLS ARRAY_PARTITION variable=local_in cyclic factor=8 dim=1

        initLocal(local_in, in);

        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=8
            local_out[i] = local_in[i];
        }

        storeOutput(out, local_out);
    }
}