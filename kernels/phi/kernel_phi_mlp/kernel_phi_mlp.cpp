#include <ap_fixed.h>
#include <hls_math.h>

#define HIDDEN_SIZE 2560
#define INTERMEDIATE_SIZE 10240
#define FIRST_NUM_BLOCKS 32
#define FIRST_BLOCK_SIZE (INTERMEDIATE_SIZE / FIRST_NUM_BLOCKS)
#define SECOND_NUM_BLOCKS 8
#define SECOND_BLOCK_SIZE (HIDDEN_SIZE / SECOND_NUM_BLOCKS)

typedef ap_fixed<16,10> fixed16_10;

float new_gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f; // √(2/π)
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = hls::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}

extern "C" {
    void kernel_phi_mlp(
        fixed16_10 out[HIDDEN_SIZE],
        fixed16_10 in[HIDDEN_SIZE],
        fixed16_10 weight_1[INTERMEDIATE_SIZE * HIDDEN_SIZE],
        fixed16_10 bias_1[INTERMEDIATE_SIZE],
        fixed16_10 weight_2[HIDDEN_SIZE * INTERMEDIATE_SIZE],
        fixed16_10 bias_2[HIDDEN_SIZE]
    ) {
        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_1 offset=slave bundle=gmem2 depth=26214400 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_1 offset=slave bundle=gmem3 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_2 offset=slave bundle=gmem4 depth=26214400 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_2 offset=slave bundle=gmem5 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        // 壓縮並存放到 local buffer
        fixed16_10 local_linear_1_out[INTERMEDIATE_SIZE];
        fixed16_10 local_linear_1_in[HIDDEN_SIZE];
        fixed16_10 local_linear_2_out[HIDDEN_SIZE];
        fixed16_10 local_linear_2_in[INTERMEDIATE_SIZE];
        fixed16_10 local_w[FIRST_BLOCK_SIZE * HIDDEN_SIZE];

		#pragma HLS bind_storage variable=local_linear_1_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_linear_1_out type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_linear_2_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_linear_2_out type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=local_w type=RAM_T2P impl=uram

        // 初始化 output = bias
        init_linear_1_out:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
        	local_linear_1_out[i] = bias_1[i];
        }

        load_in:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            local_linear_1_in[i] = in[i];
        }

        // 分批次計算
        block_loop_1:
        for (int block = 0; block < FIRST_NUM_BLOCKS; block++) {

            // Load weight block
            load_w:
            for (int i = 0; i < FIRST_BLOCK_SIZE; i++) {
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=4
                    local_w[i * HIDDEN_SIZE + j] = weight_1[(block * FIRST_BLOCK_SIZE + i) * HIDDEN_SIZE + j];
                }
            }

            // 計算並累加結果
            compute:
            for (int i = 0; i < FIRST_BLOCK_SIZE; i++) {
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=4
                	local_linear_1_out[block * FIRST_BLOCK_SIZE + i] += local_linear_1_in[j] * local_w[i * HIDDEN_SIZE + j];
                }
            }
        }

        gelu_loop:
        for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
            local_linear_2_in[i] = fixed16_10(new_gelu(float(local_linear_1_out[i]))) + bias_2[i];
        }

        // 分批次計算
        block_loop_2:
        for (int block = 0; block < SECOND_NUM_BLOCKS; block++) {

            // Load weight block
            load_w:
            for (int i = 0; i < SECOND_BLOCK_SIZE; i++) {
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=4
                    local_w[i * HIDDEN_SIZE + j] = weight_2[(block * SECOND_BLOCK_SIZE + i) * HIDDEN_SIZE + j];
                }
            }

            // 計算並累加結果
            compute:
            for (int i = 0; i < SECOND_BLOCK_SIZE; i++) {
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=4
                	local_linear_2_out[block * SECOND_BLOCK_SIZE + i] += local_linear_2_in[j] * local_w[i * HIDDEN_SIZE + j];
                }
            }
        }

        // output
        load_out:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            out[i] = local_linear_2_out[i];
        }

    }
}
