#include <ap_fixed.h>

#define HIDDEN_SIZE 2560
#define NUM_KEY_VALUE_HEADS 32
#define HEAD_DIM 80
#define ROTARY_DIM 32
#define HALF_ROTARY_DIM 16

typedef ap_fixed<16,10> fixed16_10;

extern "C" {
    void kernel_phi_rotary_embed(
        fixed16_10 out[HIDDEN_SIZE],
        fixed16_10 in[HIDDEN_SIZE],
        fixed16_10 cosine[ROTARY_DIM],
        fixed16_10 sine[ROTARY_DIM]
    ) {

        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=cosine offset=slave bundle=gmem2 depth=32 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=sine offset=slave bundle=gmem3 depth=32 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=cosine bundle=control
        #pragma HLS INTERFACE s_axilite port=sine bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        fixed16_10 local_out[HIDDEN_SIZE];
        fixed16_10 local_in[HIDDEN_SIZE];
        fixed16_10 local_cosine[ROTARY_DIM];
        fixed16_10 local_sine[ROTARY_DIM];

        #pragma HLS bind_storage variable=local_out type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=local_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_cosine type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_sine type=RAM_T2P impl=bram

        #pragma HLS ARRAY_PARTITION variable=local_out cyclic factor=4 dim=1
        #pragma HLS ARRAY_PARTITION variable=local_in cyclic factor=4 dim=1
        #pragma HLS ARRAY_PARTITION variable=local_cosine cyclic factor=4 dim=1
        #pragma HLS ARRAY_PARTITION variable=local_sine cyclic factor=4 dim=1

        load_in:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=4
            local_in[i] = in[i];
        }

        load_cosine_sine:
        for (int i = 0; i < ROTARY_DIM; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=4
            local_cosine[i] = cosine[i];
            local_sine[i] = sine[i];
        }

        rotary_embed_loop:
        for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
            for (int j = 0; j < HALF_ROTARY_DIM; j++) {
                #pragma HLS PIPELINE II=1
                #pragma HLS UNROLL factor=4
                int idx1 = i * ROTARY_DIM + j;
                int idx2 = idx1 + HALF_ROTARY_DIM;
                fixed16_10 r1 = local_in[idx2];
                fixed16_10 r2 = local_in[idx1];
                local_out[idx1] = local_in[idx1] * local_cosine[j] - r1 * local_sine[j];
                local_out[idx2] = local_in[idx2] * local_cosine[j+HALF_ROTARY_DIM] - r2 * local_sine[j+HALF_ROTARY_DIM];
            }
        }


        load_out:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=4
            out[i] = local_out[i];
        }
    }
}