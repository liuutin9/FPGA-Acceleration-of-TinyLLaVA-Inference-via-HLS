#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_half.h>
#include <ap_int.h>
//#include <iostream>

#define HIDDEN_SIZE 2560
#define DIVIDE_SIZE 512
#define DIVIDE_BLOCK (HIDDEN_SIZE / DIVIDE_SIZE)
#define LAYER_NORM_EPS 0.00001

typedef ap_fixed<32,14> fixed32_14;
typedef ap_uint<16> uint16;

inline fixed32_14 uint16ToFixed32_14(uint16 in) {
    half h;
    *((uint16*)&h) = in;
    float f = (float)h;
    return fixed32_14(f);
}

inline void loadToLocal(fixed32_14* local, fixed32_14* global) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	local[i] = global[i];
    }
}

inline void loadUint16ToLocal(fixed32_14* local, uint16* global) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	local[i] = uint16ToFixed32_14(global[i]);
    }
}

inline void initLocal(
    fixed32_14 local_in[HIDDEN_SIZE],
    fixed32_14 local_out[HIDDEN_SIZE],
    fixed32_14 local_weight[HIDDEN_SIZE],
    fixed32_14 in[HIDDEN_SIZE],
    uint16 bias[HIDDEN_SIZE],
    uint16 weight[HIDDEN_SIZE]
) {
    loadToLocal(local_in, in);
    loadUint16ToLocal(local_out, bias);
    loadUint16ToLocal(local_weight, weight);
}

extern "C" {
    void kernel_phi_layernorm(
        fixed32_14 out[HIDDEN_SIZE],
        fixed32_14 in[HIDDEN_SIZE],
        uint16 weight[HIDDEN_SIZE],
        uint16 bias[HIDDEN_SIZE]
    ) {

        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight offset=slave bundle=gmem2 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias offset=slave bundle=gmem3 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=weight bundle=control
        #pragma HLS INTERFACE s_axilite port=bias bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

    	fixed32_14 local_out[HIDDEN_SIZE];
    	fixed32_14 local_in[HIDDEN_SIZE];
    	fixed32_14 local_weight[HIDDEN_SIZE];

        #pragma HLS bind_storage variable=local_out type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=local_in type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_weight type=RAM_T2P impl=bram

        fixed32_14 mean = fixed32_14(0.0f);
        fixed32_14 variance = fixed32_14(0.0f);
        fixed32_14 eps = fixed32_14(LAYER_NORM_EPS);

        initLocal(local_in, local_out, local_weight, in, bias, weight);

//        for (int i = 0; i < 5; i++) {
//        	printf("%f ", float(local_weight[i]));
//        }
//        printf("\n");

        mean_loop:
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
			mean += local_in[i];
		}
		mean /= HIDDEN_SIZE;
//        printf("mean: %f\n", float(mean));
//        for (int i = 0; i < HIDDEN_SIZE; i++) {
//        	printf("%f ", float(local_in[i]));
//        }
//        printf("\n");

        variance_loop:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
        	variance += (local_in[i] - mean) * (local_in[i] - mean);
		}
        variance /= HIDDEN_SIZE;
//        printf("variance: %f\n", float(variance));

        // 計算標準差
        fixed32_14 inv_stddev = 1 / hls::sqrt(variance + eps);

        normalization_loop:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            local_out[i] += local_weight[i] * (local_in[i] - mean) * inv_stddev;
        }

        store_out:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            out[i] = fixed32_14(local_out[i]);
        }
    }
}
