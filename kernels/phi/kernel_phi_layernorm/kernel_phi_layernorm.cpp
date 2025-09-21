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
typedef ap_fixed<40,22> fixed40_22;

inline void loadToLocal(fixed40_22* local, fixed32_14* global) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	local[i] = fixed40_22(global[i]);
    }
}

inline void loadhalfToLocal(fixed40_22* local, half* global) {
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        #pragma HLS PIPELINE II=1
    	local[i] = fixed40_22(global[i]);
    }
}

inline void initLocal(
	fixed40_22 local_in[HIDDEN_SIZE],
	fixed40_22 local_out[HIDDEN_SIZE],
	fixed40_22 local_weight[HIDDEN_SIZE],
    fixed32_14 in[HIDDEN_SIZE],
    half bias[HIDDEN_SIZE],
    half weight[HIDDEN_SIZE]
) {
    loadToLocal(local_in, in);
    loadhalfToLocal(local_out, bias);
    loadhalfToLocal(local_weight, weight);
}

extern "C" {
    void kernel_phi_layernorm(
        fixed32_14 out[HIDDEN_SIZE],
        fixed32_14 in[HIDDEN_SIZE],
        half weight[HIDDEN_SIZE],
        half bias[HIDDEN_SIZE]
    ) {

        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=weight bundle=control
        #pragma HLS INTERFACE s_axilite port=bias bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

    	fixed40_22 local_out[HIDDEN_SIZE];
    	fixed40_22 local_in[HIDDEN_SIZE];
    	fixed40_22 local_weight[HIDDEN_SIZE];

        #pragma HLS bind_storage variable=local_out type=RAM_2P impl=uram
        #pragma HLS bind_storage variable=local_in type=RAM_2P impl=uram
		#pragma HLS bind_storage variable=local_weight type=RAM_2P impl=uram

    	fixed40_22 mean = fixed40_22(0.0f);
    	fixed40_22 variance = fixed40_22(0.0f);
    	fixed40_22 eps = fixed40_22(LAYER_NORM_EPS);

        initLocal(local_in, local_out, local_weight, in, bias, weight);

//        for (int i = 0; i < 5; i++) {
//        	printf("%f ", fixed32_14(local_weight[i]));
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
//        for (int i = 0; i < 10; i++) {
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
        fixed40_22 inv_stddev = 1 / hls::sqrt(variance + eps);

//        printf("1 / Std Dev: %f\n", float(inv_stddev));

//        printf("Weights:");
//        for (int i = 0; i < 10; i++) {
//        	printf(" %f", float(local_weight[i]));
//        }
//        printf("\n");

        normalization_loop:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            local_out[i] += local_weight[i] * (local_in[i] - mean) * inv_stddev;
        }

//        printf("Local out:");
//        for (int i = 0; i < 10; i++) {
//        	printf(" %f", float(local_out[i]));
//        	local_out[i] == 0 ? printf("F") : printf("T");
//        }
//        printf("\n");

        store_out:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            out[i] = fixed32_14(local_out[i]);
        }
    }
}
