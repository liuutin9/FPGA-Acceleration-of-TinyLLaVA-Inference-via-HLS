#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_half.h>

#define HIDDEN_SIZE 2560
#define NUM_KEY_VALUE_HEADS 32
#define HEAD_DIM 80
#define ROTARY_DIM 32
#define HALF_ROTARY_DIM 16

//typedef ap_fixed<32,14> fixed32_14;
typedef float fixed32_14;

extern "C" {
    void kernel_phi_rotary_embed(
        fixed32_14 out_q[HIDDEN_SIZE],
        fixed32_14 out_k_cache_1[800 * HIDDEN_SIZE],
        fixed32_14 out_k_cache_2[32 * HIDDEN_SIZE],
        fixed32_14 in_q[HIDDEN_SIZE],
        fixed32_14 in_k[HIDDEN_SIZE],
		half* cosine,
		half* sine,
        int* position_idx
    ) {

        #pragma HLS INTERFACE m_axi port=out_q offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=out_k_cache_1 offset=slave bundle=gmem1 depth=2048000 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=out_k_cache_2 offset=slave bundle=gmem1 depth=81920 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_q offset=slave bundle=gmem2 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_k offset=slave bundle=gmem2 depth=2560 max_read_burst_length=256
		#pragma HLS INTERFACE m_axi port=cosine offset=slave bundle=gmem2 depth=13312 max_read_burst_length=256
		#pragma HLS INTERFACE m_axi port=sine offset=slave bundle=gmem2 depth=13312 max_read_burst_length=256
		#pragma HLS INTERFACE m_axi port=position_idx offset=slave bundle=gmem0 depth=1 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out_q bundle=control
        #pragma HLS INTERFACE s_axilite port=out_k_cache_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=out_k_cache_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=in_q bundle=control
        #pragma HLS INTERFACE s_axilite port=in_k bundle=control
		#pragma HLS INTERFACE s_axilite port=cosine bundle=control
		#pragma HLS INTERFACE s_axilite port=sine bundle=control
        #pragma HLS INTERFACE s_axilite port=position_idx bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        fixed32_14 local_out_q[HIDDEN_SIZE];
        fixed32_14 local_out_k[HIDDEN_SIZE];
        fixed32_14 local_in_q[HIDDEN_SIZE];
        fixed32_14 local_in_k[HIDDEN_SIZE];
        fixed32_14 local_cosine[HALF_ROTARY_DIM];
        fixed32_14 local_sine[HALF_ROTARY_DIM];

        #pragma HLS bind_storage variable=local_out_q type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_out_k type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_in_q type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_in_k type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_cosine type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_sine type=RAM_T2P impl=bram

        load_in:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS UNROLL factor=2
            local_in_q[i] = in_q[i];
            local_in_k[i] = in_k[i];
            local_out_q[i] = in_q[i];
            local_out_k[i] = in_k[i];
        }

        load_cosine_sine:
        for (int i = 0; i < HALF_ROTARY_DIM; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            local_cosine[i] = fixed32_14(cosine[position_idx[0] * 16 + i]);
            local_sine[i] = fixed32_14(sine[position_idx[0] * 16 + i]);
        }

        rotary_embed_loop:
        for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
            for (int j = 0; j < HALF_ROTARY_DIM; j++) {
                #pragma HLS PIPELINE II=1
            	local_out_q[i * HEAD_DIM + j] = local_in_q[i * HEAD_DIM + j] * local_cosine[j] - local_in_q[i * HEAD_DIM + j + HALF_ROTARY_DIM] * local_sine[j];
            	local_out_q[i * HEAD_DIM + j + HALF_ROTARY_DIM] = local_in_q[i * HEAD_DIM + j + HALF_ROTARY_DIM] * local_cosine[j] + local_in_q[i * HEAD_DIM + j] * local_sine[j];
            	local_out_k[i * HEAD_DIM + j] = local_in_k[i * HEAD_DIM + j] * local_cosine[j] - local_in_k[i * HEAD_DIM + j + HALF_ROTARY_DIM] * local_sine[j];
            	local_out_k[i * HEAD_DIM + j + HALF_ROTARY_DIM] = local_in_k[i * HEAD_DIM + j + HALF_ROTARY_DIM] * local_cosine[j] + local_in_k[i * HEAD_DIM + j] * local_sine[j];
            }
        }


        load_out:
        int idx = position_idx[0] < 800 ? position_idx[0] : position_idx[0] - 800;
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            out_q[i] = local_out_q[i];
            if (position_idx[0] < 800) {
                out_k_cache_1[idx * HIDDEN_SIZE + i] = local_out_k[i];
            } else {
                out_k_cache_2[idx * HIDDEN_SIZE + i] = local_out_k[i];
            }
        }
    }
}
