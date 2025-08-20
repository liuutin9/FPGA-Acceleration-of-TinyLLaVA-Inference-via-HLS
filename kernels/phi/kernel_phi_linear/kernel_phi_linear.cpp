#include <ap_fixed.h>
#include <hls_math.h>

#define HIDDEN_SIZE 2560
#define NUM_BLOCKS 8
#define BLOCK_SIZE (HIDDEN_SIZE / NUM_BLOCKS)

typedef ap_fixed<16,10> fixed16_10;

extern "C" {
    void kernel_phi_linear(
        // float out[HIDDEN_SIZE],
        // float in[HIDDEN_SIZE],
        // float weight[HIDDEN_SIZE * HIDDEN_SIZE],
        // float bias[HIDDEN_SIZE]
        fixed16_10* out,
        fixed16_10* in,
        fixed16_10* weight,
        fixed16_10* bias
    ) {
        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight offset=slave bundle=gmem2 depth=6553600 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias offset=slave bundle=gmem3 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=weight bundle=control
        #pragma HLS INTERFACE s_axilite port=bias bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        // 壓縮並存放到 local buffer
        // Local buffers for input slice and weight block
        fixed16_10 local_in[HIDDEN_SIZE];
        fixed16_10 local_w[BLOCK_SIZE * HIDDEN_SIZE];
        fixed16_10 local_out[HIDDEN_SIZE];

		#pragma HLS bind_storage variable=local_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_w type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_out type=RAM_T2P impl=bram

        // 初始化 output = bias
        init_out:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
        	local_out[i] = bias[i];
        }

        load_in:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            local_in[i] = in[i];
        }

        // 分批次計算
        block_loop:
        for (int block = 0; block < NUM_BLOCKS; block++) {

            // Load weight block
            load_w:
            for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=4
                    local_w[i * HIDDEN_SIZE + j] = weight[(block * BLOCK_SIZE + i) * HIDDEN_SIZE + j];
                }
            }

            // 計算並累加結果
            compute:
            for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=4
                	local_out[block * BLOCK_SIZE + i] += local_in[j] * local_w[i * HIDDEN_SIZE + j];
                }
            }
        }

        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=4
        	out[i] = local_out[i];
        }

    }
}
