#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_half.h>
#include <ap_int.h>

#define HIDDEN_SIZE 2560
#define INTERMEDIATE_SIZE 10240
#define FIRST_NUM_BLOCKS 32
#define FIRST_BLOCK_SIZE (INTERMEDIATE_SIZE / FIRST_NUM_BLOCKS)
#define SECOND_NUM_BLOCKS 8
#define SECOND_BLOCK_SIZE (HIDDEN_SIZE / SECOND_NUM_BLOCKS)

typedef ap_fixed<32,14> fixed32_14;
typedef ap_uint<16> uint16;

fixed32_14 uint16ToFixed32_14(uint16 in) {
    hls::half h;
    *((uint16*)&h) = in;
    float f = (float)h;
    return fixed32_14(f);
}

void load_fc1_bias(fixed32_14* out, uint16* bias) {
    for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
        #pragma HLS PIPELINE II=1
    	out[i] = uint16ToFixed32_14(bias[i]);
    }
}

inline void init_fc1_out(
    fixed32_14 out[HIDDEN_SIZE],
    uint16 bias_0[INTERMEDIATE_SIZE / 8],
    uint16 bias_1[INTERMEDIATE_SIZE / 8],
    uint16 bias_2[INTERMEDIATE_SIZE / 8],
    uint16 bias_3[INTERMEDIATE_SIZE / 8],
    uint16 bias_4[INTERMEDIATE_SIZE / 8],
    uint16 bias_5[INTERMEDIATE_SIZE / 8],
    uint16 bias_6[INTERMEDIATE_SIZE / 8],
    uint16 bias_7[INTERMEDIATE_SIZE / 8]
) {
    #pragma HLS DATAFLOW
    load_fc1_bias(&out[0 * INTERMEDIATE_SIZE / 8], bias_0);
    load_fc1_bias(&out[1 * INTERMEDIATE_SIZE / 8], bias_1);
    load_fc1_bias(&out[2 * INTERMEDIATE_SIZE / 8], bias_2);
    load_fc1_bias(&out[3 * INTERMEDIATE_SIZE / 8], bias_3);
    load_fc1_bias(&out[4 * INTERMEDIATE_SIZE / 8], bias_4);
    load_fc1_bias(&out[5 * INTERMEDIATE_SIZE / 8], bias_5);
    load_fc1_bias(&out[6 * INTERMEDIATE_SIZE / 8], bias_6);
    load_fc1_bias(&out[7 * INTERMEDIATE_SIZE / 8], bias_7);
}

void load_fc2_bias(fixed32_14* out, uint16* bias) {
    for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
        #pragma HLS PIPELINE II=1
    	out[i] = uint16ToFixed32_14(bias[i]);
    }
}

inline void init_fc2_out(
    fixed32_14 out[INTERMEDIATE_SIZE],
    uint16 bias_0[HIDDEN_SIZE / 8],
    uint16 bias_1[HIDDEN_SIZE / 8],
    uint16 bias_2[HIDDEN_SIZE / 8],
    uint16 bias_3[HIDDEN_SIZE / 8],
    uint16 bias_4[HIDDEN_SIZE / 8],
    uint16 bias_5[HIDDEN_SIZE / 8],
    uint16 bias_6[HIDDEN_SIZE / 8],
    uint16 bias_7[HIDDEN_SIZE / 8]
) {
    #pragma HLS DATAFLOW
    load_fc2_bias(&out[0 * HIDDEN_SIZE / 8], bias_0);
    load_fc2_bias(&out[1 * HIDDEN_SIZE / 8], bias_1);
    load_fc2_bias(&out[2 * HIDDEN_SIZE / 8], bias_2);
    load_fc2_bias(&out[3 * HIDDEN_SIZE / 8], bias_3);
    load_fc2_bias(&out[4 * HIDDEN_SIZE / 8], bias_4);
    load_fc2_bias(&out[5 * HIDDEN_SIZE / 8], bias_5);
    load_fc2_bias(&out[6 * HIDDEN_SIZE / 8], bias_6);
    load_fc2_bias(&out[7 * HIDDEN_SIZE / 8], bias_7);
}

inline void loadToLocal(fixed32_14 local[HIDDEN_SIZE], fixed32_14 global[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	local[i] = global[i];
    }
}

void compute_gelu(fixed32_14 out[INTERMEDIATE_SIZE], fixed32_14 in[INTERMEDIATE_SIZE]) {
    for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        out[i] = fixed32_14(new_gelu((float)in[i]));
    }
}

float new_gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f; // √(2/π)
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = hls::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}

extern "C" {
    void kernel_phi_mlp(
        fixed32_14 out[HIDDEN_SIZE],
        fixed32_14 in[HIDDEN_SIZE],
        uint16 weight_fc1_0[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        uint16 weight_fc1_1[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        uint16 weight_fc1_2[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        uint16 weight_fc1_3[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        uint16 weight_fc1_4[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        uint16 weight_fc1_5[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        uint16 weight_fc1_6[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        uint16 weight_fc1_7[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        uint16 bias_fc1_0[INTERMEDIATE_SIZE / 8],
        uint16 bias_fc1_1[INTERMEDIATE_SIZE / 8],
        uint16 bias_fc1_2[INTERMEDIATE_SIZE / 8],
        uint16 bias_fc1_3[INTERMEDIATE_SIZE / 8],
        uint16 bias_fc1_4[INTERMEDIATE_SIZE / 8],
        uint16 bias_fc1_5[INTERMEDIATE_SIZE / 8],
        uint16 bias_fc1_6[INTERMEDIATE_SIZE / 8],
        uint16 bias_fc1_7[INTERMEDIATE_SIZE / 8],
        uint16 weight_fc2_0[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        uint16 weight_fc2_1[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        uint16 weight_fc2_2[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        uint16 weight_fc2_3[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        uint16 weight_fc2_4[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        uint16 weight_fc2_5[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        uint16 weight_fc2_6[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        uint16 weight_fc2_7[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        uint16 bias_fc2_0[HIDDEN_SIZE / 8],
        uint16 bias_fc2_1[HIDDEN_SIZE / 8],
        uint16 bias_fc2_2[HIDDEN_SIZE / 8],
        uint16 bias_fc2_3[HIDDEN_SIZE / 8],
        uint16 bias_fc2_4[HIDDEN_SIZE / 8],
        uint16 bias_fc2_5[HIDDEN_SIZE / 8],
        uint16 bias_fc2_6[HIDDEN_SIZE / 8],
        uint16 bias_fc2_7[HIDDEN_SIZE / 8]
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
        fixed32_14 local_linear_1_out[INTERMEDIATE_SIZE];
        fixed32_14 local_linear_1_in[HIDDEN_SIZE];
        fixed32_14 local_linear_2_out[HIDDEN_SIZE];
        fixed32_14 local_linear_2_in[INTERMEDIATE_SIZE];
        fixed32_14 local_w[INTERMEDIATE_SIZE];

		#pragma HLS bind_storage variable=local_linear_1_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_linear_1_out type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_linear_2_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_linear_2_out type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=local_w type=RAM_T2P impl=uram

        init_fc1_out(
            local_linear_1_out,
            bias_fc1_0,
            bias_fc1_1,
            bias_fc1_2,
            bias_fc1_3,
            bias_fc1_4,
            bias_fc1_5,
            bias_fc1_6,
            bias_fc1_7
        );

        init_fc2_out(
            local_linear_2_out,
            bias_fc2_0,
            bias_fc2_1,
            bias_fc2_2,
            bias_fc2_3,
            bias_fc2_4,
            bias_fc2_5,
            bias_fc2_6,
            bias_fc2_7
        );

        loadToLocal(local_linear_1_in, in);

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
            local_linear_2_in[i] = fixed32_14(new_gelu(float(local_linear_1_out[i]))) + bias_2[i];
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
