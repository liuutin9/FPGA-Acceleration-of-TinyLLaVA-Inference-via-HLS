#include <ap_fixed.h>
#include <hls_math.h>

#define HIDDEN_SIZE 2560
#define NUM_KEY_VALUE_HEADS 32
#define HEAD_DIM 80
#define ROTARY_DIM 32
#define HALF_ROTARY_DIM 16

typedef ap_fixed<32,14> fixed32_14;

extern "C" {
    void kernel_phi_rotary_embed(
        fixed32_14 out_q[HIDDEN_SIZE],
        fixed32_14 out_k_cache_1[800 * HIDDEN_SIZE],
        fixed32_14 out_k_cache_2[32 * HIDDEN_SIZE],
        fixed32_14 in_q[HIDDEN_SIZE],
        fixed32_14 in_k[HIDDEN_SIZE],
        int position_idx
    ) {

        #pragma HLS INTERFACE m_axi port=out_q offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=out_k_cache_1 offset=slave bundle=gmem1 depth=2048000 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=out_k_cache_2 offset=slave bundle=gmem1 depth=81920 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_q offset=slave bundle=gmem2 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_k offset=slave bundle=gmem2 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out_q bundle=control
        #pragma HLS INTERFACE s_axilite port=out_k_cache_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=out_k_cache_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=in_q bundle=control
        #pragma HLS INTERFACE s_axilite port=in_k bundle=control
        #pragma HLS INTERFACE s_axilite port=position_idx bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        fixed32_14 local_out_q[HIDDEN_SIZE];
        fixed32_14 local_out_k[HIDDEN_SIZE];
        fixed32_14 local_in_q[HIDDEN_SIZE];
        fixed32_14 local_in_k[HIDDEN_SIZE];
        fixed32_14 local_base[HALF_ROTARY_DIM] = {1, 0.562341, 0.316228, 0.177828, 0.1, 0.0562341, 0.0316228, 0.0177828, 0.01, 0.00562341, 0.00316228, 0.00177828, 0.001, 0.000562341, 0.000316228, 0.000177828};
        fixed32_14 local_cosine[HALF_ROTARY_DIM];
        fixed32_14 local_sine[HALF_ROTARY_DIM];

        #pragma HLS bind_storage variable=local_out_q type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_out_k type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_in_q type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_in_k type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_base type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_cosine type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_sine type=RAM_T2P impl=uram

        load_in:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS UNROLL factor=2
            local_in_q[i] = in_q[i];
            local_in_k[i] = in_k[i];
        }

        load_cosine_sine:
        for (int i = 0; i < HALF_ROTARY_DIM; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            local_cosine[i] = hls::cosf(position_idx * local_base[i]);
            local_sine[i] = hls::sinf(position_idx * local_base[i]);
        }

        rotary_embed_loop:
        for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
            for (int j = 0; j < HALF_ROTARY_DIM; j++) {
                #pragma HLS UNROLL factor=2
                int idx1 = i * ROTARY_DIM + j;
                int idx2 = idx1 + HALF_ROTARY_DIM;

                fixed32_14 r1 = local_in_q[idx2];
                fixed32_14 r2 = local_in_q[idx1];
                local_out_q[idx1] = local_in_q[idx1] * local_cosine[j] - r1 * local_sine[j];
                local_out_q[idx2] = local_in_q[idx2] * local_cosine[j] - r2 * local_sine[j];

                fixed32_14 r3 = local_in_k[idx2];
                fixed32_14 r4 = local_in_k[idx1];
                local_out_k[idx1] = local_in_k[idx1] * local_cosine[j] - r3 * local_sine[j];
                local_out_k[idx2] = local_in_k[idx2] * local_cosine[j] - r4 * local_sine[j];
            }
        }


        load_out:
        int idx = position_idx < 800 ? position_idx : position_idx - 800;
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            out_q[i] = local_out_q[i];
            if (position_idx < 800) {
                out_k_cache_1[idx * HIDDEN_SIZE + i] = local_out_k[i];
            } else {
                out_k_cache_2[idx * HIDDEN_SIZE + i] = local_out_k[i];
            }
        }
    }
}
