#include <ap_fixed.h>
#include <hls_math.h>

#define HIDDEN_SIZE 2560
#define NUM_BLOCKS 10
#define BLOCK_SIZE 256

typedef ap_fixed<32,14> fixed32_14;

inline void loadToLocal(fixed32_14 local[HIDDEN_SIZE], fixed32_14 global[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	local[i] = global[i];
    }
}

inline void initLocal(
    fixed32_14 local_before_layernorm[HIDDEN_SIZE],
    fixed32_14 local_after_attention[HIDDEN_SIZE],
    fixed32_14 local_after_mlp[HIDDEN_SIZE],
    fixed32_14 before_layernorm[HIDDEN_SIZE],
    fixed32_14 after_attention[HIDDEN_SIZE],
    fixed32_14 after_mlp[HIDDEN_SIZE]
) {
//    #pragma HLS DATAFLOW
    loadToLocal(local_before_layernorm, before_layernorm);
    loadToLocal(local_after_attention, after_attention);
    loadToLocal(local_after_mlp, after_mlp);
}

inline void storeOutput(fixed32_14 out[HIDDEN_SIZE], fixed32_14 local_out[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
    	out[i] = local_out[i];
    }
}

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

        fixed32_14 local_out[HIDDEN_SIZE];
        fixed32_14 local_before_layernorm[HIDDEN_SIZE];
        fixed32_14 local_after_attention[HIDDEN_SIZE];
        fixed32_14 local_after_mlp[HIDDEN_SIZE];

        #pragma HLS BIND_STORAGE variable=local_out type=RAM_1P impl=uram
        #pragma HLS BIND_STORAGE variable=local_before_layernorm type=RAM_1P impl=uram
        #pragma HLS BIND_STORAGE variable=local_after_attention type=RAM_1P impl=uram
        #pragma HLS BIND_STORAGE variable=local_after_mlp type=RAM_1P impl=uram

        initLocal(
            local_before_layernorm,
            local_after_attention,
            local_after_mlp,
            before_layernorm,
            after_attention,
            after_mlp
        );

        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            local_out[i] = local_before_layernorm[i] + local_after_attention[i] + local_after_mlp[i];
        }

        storeOutput(out, local_out);
    }
}
