#include <ap_fixed.h>
#include <hls_math.h>
#include <ap_int.h>
#include <hls_half.h>

#define HIDDEN_SIZE 2560

typedef ap_fixed<32,14> fixed32_14;
typedef ap_uint<16> uint16;

inline fixed32_14 uint16ToFixed32_14(uint16 in) {
    half h;
    *((uint16*)&h) = in;
    float f = (float)h;
    return fixed32_14(f);
}

inline void load_bias(fixed32_14* out, uint16* bias) {
    for (int i = 0; i < HIDDEN_SIZE / 2; i++) {
        #pragma HLS PIPELINE II=1
    	out[i] = uint16ToFixed32_14(bias[i]);
    }
}

inline void init_out(fixed32_14 out[HIDDEN_SIZE], uint16 bias_1[HIDDEN_SIZE / 2], uint16 bias_2[HIDDEN_SIZE / 2]) {
    #pragma HLS DATAFLOW
    load_bias(out, bias_1);
    load_bias(&out[HIDDEN_SIZE / 2], bias_2);
}

inline void load_in(fixed32_14 in[HIDDEN_SIZE], fixed32_14 local_in[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	local_in[i] = in[i];
    }
}

inline void load_w(fixed32_14 local_w[HIDDEN_SIZE], uint16 weight[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        local_w[i] = uint16ToFixed32_14(weight[i]);
    }
}

inline void load_weight(fixed32_14 local_w_1[HIDDEN_SIZE], fixed32_14 local_w_2[HIDDEN_SIZE], uint16 weight_1[HIDDEN_SIZE], uint16 weight_2[HIDDEN_SIZE]) {
    #pragma HLS DATAFLOW
    load_w(local_w_1, weight_1);
    load_w(local_w_2, weight_2);
}

inline void multiply_accumulate(fixed32_14* local_out, fixed32_14 local_in[HIDDEN_SIZE], fixed32_14 local_w[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=2
        *local_out += local_in[i] * local_w[i];
    }
}

inline void compute(fixed32_14* local_out_1, fixed32_14* local_out_2, fixed32_14 local_in[HIDDEN_SIZE], fixed32_14 local_w_1[HIDDEN_SIZE], fixed32_14 local_w_2[HIDDEN_SIZE]) {
    #pragma HLS DATAFLOW
    multiply_accumulate(local_out_1, local_in, local_w_1);
    multiply_accumulate(local_out_2, local_in, local_w_2);
}

inline void storeOutput(fixed32_14 out[HIDDEN_SIZE], fixed32_14 local_out[HIDDEN_SIZE]) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
    	out[i] = local_out[i];
    }
}

extern "C" {
    void kernel_phi_dense(
        fixed32_14* out,
        fixed32_14* in,
        uint16* weight_1,
        uint16* weight_2,
        uint16* bias_1,
        uint16* bias_2
    ) {
        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_1 offset=slave bundle=gmem2 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_2 offset=slave bundle=gmem3 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_1 offset=slave bundle=gmem4 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_2 offset=slave bundle=gmem5 depth=1280 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=weight_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=bias_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        // 壓縮並存放到 local buffer
        // Local buffers for input slice and weight block
        fixed32_14 local_in[HIDDEN_SIZE];
        fixed32_14 local_w_1[HIDDEN_SIZE];
        fixed32_14 local_w_2[HIDDEN_SIZE];
        fixed32_14 local_out[HIDDEN_SIZE];

		#pragma HLS bind_storage variable=local_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_w_1 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_2 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_out type=RAM_T2P impl=bram

        // 初始化 output = bias
        init_out(local_out, bias_1, bias_2);
        // 載入 input 到 local buffer
        load_in(in, local_in);

        // 計算
        for (int i = 0; i < HIDDEN_SIZE / 2; i++) {
            load_weight(local_w_1, local_w_2, &weight_1[i * HIDDEN_SIZE], &weight_2[i * HIDDEN_SIZE]);
            compute(&local_out[i], &local_out[i + HIDDEN_SIZE / 2], local_in, local_w_1, local_w_2);
        }

        // 存儲輸出
        storeOutput(out, local_out);
    }
}