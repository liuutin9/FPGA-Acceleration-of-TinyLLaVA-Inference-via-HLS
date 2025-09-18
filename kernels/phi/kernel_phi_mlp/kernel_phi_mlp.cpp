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

inline fixed32_14 uint16ToFixed32_14(uint16 in) {
    half h;
    *((uint16*)&h) = in;
    float f = (float)h;
    return fixed32_14(f);
}

inline void load_fc1_bias(fixed32_14* out, uint16* bias) {
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

inline void load_fc2_bias(fixed32_14* out, uint16* bias) {
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

inline void load_fc1_weight(fixed32_14* out, uint16* weight) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	out[i] = uint16ToFixed32_14(weight[i]);
    }
}

inline void load_fc2_weight(fixed32_14* out, uint16* weight) {
    for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	out[i] = uint16ToFixed32_14(weight[i]);
    }
}

inline void loadToLocal(fixed32_14 local[HIDDEN_SIZE], fixed32_14 global[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	local[i] = global[i];
    }
}

inline void compute_fc1(fixed32_14* out, fixed32_14 in[HIDDEN_SIZE], fixed32_14 weight[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        *out += in[i] * weight[i];
    }
}

inline void compute_fc2(fixed32_14* out, fixed32_14 in[INTERMEDIATE_SIZE], fixed32_14 weight[INTERMEDIATE_SIZE]) {
    for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        *out += in[i] * weight[i];
    }
}

inline float new_gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f; // √(2/π)
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = hls::tanh(inner);
    return 0.5f * x * (1.0f + tanh_inner);
}

inline void compute_gelu(fixed32_14 out[INTERMEDIATE_SIZE], fixed32_14 in[INTERMEDIATE_SIZE]) {
    for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        out[i] = fixed32_14(new_gelu((float)in[i]));
    }
}

inline void storeOutput(fixed32_14 out[HIDDEN_SIZE], fixed32_14 local_out[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
    	out[i] = local_out[i];
    }
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
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_0 offset=slave bundle=gmem1 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_0 offset=slave bundle=gmem1 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_1 offset=slave bundle=gmem2 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_1 offset=slave bundle=gmem2 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_2 offset=slave bundle=gmem3 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_2 offset=slave bundle=gmem3 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_3 offset=slave bundle=gmem4 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_3 offset=slave bundle=gmem4 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_4 offset=slave bundle=gmem5 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_4 offset=slave bundle=gmem5 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_5 offset=slave bundle=gmem6 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_5 offset=slave bundle=gmem6 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_6 offset=slave bundle=gmem7 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_6 offset=slave bundle=gmem7 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_7 offset=slave bundle=gmem8 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_7 offset=slave bundle=gmem8 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_0 offset=slave bundle=gmem9 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_0 offset=slave bundle=gmem9 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_1 offset=slave bundle=gmem10 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_1 offset=slave bundle=gmem10 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_2 offset=slave bundle=gmem11 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_2 offset=slave bundle=gmem11 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_3 offset=slave bundle=gmem12 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_3 offset=slave bundle=gmem12 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_4 offset=slave bundle=gmem13 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_4 offset=slave bundle=gmem13 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_5 offset=slave bundle=gmem14 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_5 offset=slave bundle=gmem14 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_6 offset=slave bundle=gmem15 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_6 offset=slave bundle=gmem15 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_7 offset=slave bundle=gmem16 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_7 offset=slave bundle=gmem16 depth=320 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc1_0 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc1_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc1_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc1_3 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc1_4 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc1_5 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc1_6 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc1_7 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc1_0 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc1_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc1_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc1_3 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc1_4 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc1_5 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc1_6 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc1_7 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc2_0 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc2_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc2_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc2_3 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc2_4 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc2_5 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc2_6 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_fc2_7 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc2_0 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc2_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc2_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc2_3 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc2_4 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc2_5 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc2_6 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_fc2_7 bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        // 壓縮並存放到 local buffer
        fixed32_14 local_linear_1_out[INTERMEDIATE_SIZE];
        fixed32_14 local_linear_1_in[HIDDEN_SIZE];
        fixed32_14 local_linear_2_out[HIDDEN_SIZE];
        fixed32_14 local_linear_2_in[INTERMEDIATE_SIZE];
        fixed32_14 local_weight_1[HIDDEN_SIZE];
        fixed32_14 local_weight_2[INTERMEDIATE_SIZE];

		#pragma HLS bind_storage variable=local_linear_1_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_linear_1_out type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_linear_2_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_linear_2_out type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=local_weight_1 type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_weight_2 type=RAM_T2P impl=uram

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

        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
            load_fc1_weight(local_weight_1, &weight_fc1_0[i * HIDDEN_SIZE]);
            compute_fc1(&local_linear_1_out[i], local_linear_1_in, local_weight_1);
        }
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
            load_fc1_weight(local_weight_1, &weight_fc1_1[i * HIDDEN_SIZE]);
            compute_fc1(&local_linear_1_out[i + INTERMEDIATE_SIZE / 8], local_linear_1_in, local_weight_1);
        }
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
            load_fc1_weight(local_weight_1, &weight_fc1_2[i * HIDDEN_SIZE]);
            compute_fc1(&local_linear_1_out[i + 2 * INTERMEDIATE_SIZE / 8], local_linear_1_in, local_weight_1);
        }
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
            load_fc1_weight(local_weight_1, &weight_fc1_3[i * HIDDEN_SIZE]);
            compute_fc1(&local_linear_1_out[i + 3 * INTERMEDIATE_SIZE / 8], local_linear_1_in, local_weight_1);
        }
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
            load_fc1_weight(local_weight_1, &weight_fc1_4[i * HIDDEN_SIZE]);
            compute_fc1(&local_linear_1_out[i + 4 * INTERMEDIATE_SIZE / 8], local_linear_1_in, local_weight_1);
        }
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
            load_fc1_weight(local_weight_1, &weight_fc1_5[i * HIDDEN_SIZE]);
            compute_fc1(&local_linear_1_out[i + 5 * INTERMEDIATE_SIZE / 8], local_linear_1_in, local_weight_1);
        }
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
            load_fc1_weight(local_weight_1, &weight_fc1_6[i * HIDDEN_SIZE]);
            compute_fc1(&local_linear_1_out[i + 6 * INTERMEDIATE_SIZE / 8], local_linear_1_in, local_weight_1);
        }
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
            load_fc1_weight(local_weight_1, &weight_fc1_7[i * HIDDEN_SIZE]);
            compute_fc1(&local_linear_1_out[i + 7 * INTERMEDIATE_SIZE / 8], local_linear_1_in, local_weight_1);
        }

        compute_gelu(local_linear_2_in, local_linear_1_out);

        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
            load_fc2_weight(local_weight_2, &weight_fc2_0[i * INTERMEDIATE_SIZE]);
            compute_fc2(&local_linear_2_out[i], local_linear_2_in, local_weight_2);
        }
        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
            load_fc2_weight(local_weight_2, &weight_fc2_1[i * INTERMEDIATE_SIZE]);
            compute_fc2(&local_linear_2_out[i + HIDDEN_SIZE / 8], local_linear_2_in, local_weight_2);
        }
        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
            load_fc2_weight(local_weight_2, &weight_fc2_2[i * INTERMEDIATE_SIZE]);
            compute_fc2(&local_linear_2_out[i + 2 * HIDDEN_SIZE / 8], local_linear_2_in, local_weight_2);
        }
        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
            load_fc2_weight(local_weight_2, &weight_fc2_3[i * INTERMEDIATE_SIZE]);
            compute_fc2(&local_linear_2_out[i + 3 * HIDDEN_SIZE / 8], local_linear_2_in, local_weight_2);
        }
        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
            load_fc2_weight(local_weight_2, &weight_fc2_4[i * INTERMEDIATE_SIZE]);
            compute_fc2(&local_linear_2_out[i + 4 * HIDDEN_SIZE / 8], local_linear_2_in, local_weight_2);
        }
        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
            load_fc2_weight(local_weight_2, &weight_fc2_5[i * INTERMEDIATE_SIZE]);
            compute_fc2(&local_linear_2_out[i + 5 * HIDDEN_SIZE / 8], local_linear_2_in, local_weight_2);
        }
        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
            load_fc2_weight(local_weight_2, &weight_fc2_6[i * INTERMEDIATE_SIZE]);
            compute_fc2(&local_linear_2_out[i + 6 * HIDDEN_SIZE / 8], local_linear_2_in, local_weight_2);
        }
        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
            load_fc2_weight(local_weight_2, &weight_fc2_7[i * INTERMEDIATE_SIZE]);
            compute_fc2(&local_linear_2_out[i + 7 * HIDDEN_SIZE / 8], local_linear_2_in, local_weight_2);
        }

        storeOutput(out, local_linear_2_out);
    }
}
