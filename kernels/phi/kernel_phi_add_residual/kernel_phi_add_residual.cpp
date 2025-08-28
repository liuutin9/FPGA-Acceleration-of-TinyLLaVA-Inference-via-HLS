#include <ap_fixed.h>
#include <hls_math.h>

#define HIDDEN_SIZE 2560
#define NUM_BLOCKS 10
#define BLOCK_SIZE 256

typedef ap_fixed<32,14> fixed32_14;

extern "C" {
    void kernel_phi_add_residual(
        fixed32_14 out[HIDDEN_SIZE],
        fixed32_14 before_layernorm[HIDDEN_SIZE],
        fixed32_14 before_mlp[HIDDEN_SIZE],
        fixed32_14 after_mlp[HIDDEN_SIZE]
    ) {

        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=before_layernorm offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=before_mlp offset=slave bundle=gmem2 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=after_mlp offset=slave bundle=gmem3 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=before_layernorm bundle=control
        #pragma HLS INTERFACE s_axilite port=before_mlp bundle=control
        #pragma HLS INTERFACE s_axilite port=after_mlp bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        fixed32_14 local_q_per_head[BLOCK_SIZE];
        fixed32_14 local_k_per_head[BLOCK_SIZE];
        fixed32_14 local_v_per_head[BLOCK_SIZE];

        #pragma HLS bind_storage variable=before_layernorm type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=before_mlp type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=after_mlp type=RAM_T2P impl=bram

        #pragma HLS ARRAY_PARTITION variable=before_layernorm cyclic factor=4 dim=1
        #pragma HLS ARRAY_PARTITION variable=before_mlp cyclic factor=4 dim=1
        #pragma HLS ARRAY_PARTITION variable=after_mlp cyclic factor=4 dim=1

        for (int i = 0; i < NUM_BLOCKS; i++) {
            for (int j = 0; j < BLOCK_SIZE; j++) {
                #pragma HLS PIPELINE II=1
                #pragma HLS UNROLL factor=4
                local_q_per_head[j] = before_layernorm[i * BLOCK_SIZE + j];
                local_k_per_head[j] = before_mlp[i * BLOCK_SIZE + j];
                local_v_per_head[j] = after_mlp[i * BLOCK_SIZE + j];
            }
            for (int j = 0; j < BLOCK_SIZE; j++) {
                #pragma HLS PIPELINE II=1
                #pragma HLS UNROLL factor=4
                out[i * BLOCK_SIZE + j] = local_q_per_head[j] + local_k_per_head[j] + local_v_per_head[j];
            }
        }
    }
}