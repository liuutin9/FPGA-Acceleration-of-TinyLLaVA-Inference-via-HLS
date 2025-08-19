#include <ap_fixed.h>
#include <hls_math.h>
#include <stdio.h>

#define HIDDEN_SIZE 2560
#define DIVIDE_SIZE 512
#define DIVIDE_BLOCK (HIDDEN_SIZE / DIVIDE_SIZE)
#define LAYER_NORM_EPS 0.00001

typedef ap_fixed<24,10> fixed16_10;
//typedef float fixed16_10;
typedef ap_fixed<32,14> fixed32_14;

extern "C" {
    void kernel_phi_layernorm(
        fixed16_10 out[HIDDEN_SIZE],
        fixed16_10 in[HIDDEN_SIZE],
        fixed16_10 weight[HIDDEN_SIZE],
        fixed16_10 bias[HIDDEN_SIZE]
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

        fixed32_14 mean = fixed16_10(0.0f);
        fixed32_14 variance = fixed16_10(0.0f);
        fixed32_14 eps = fixed16_10(LAYER_NORM_EPS);

        init:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            local_out[i] = fixed32_14(bias[i]);
            local_in[i] = fixed32_14(in[i]);
            local_weight[i] = fixed32_14(weight[i]);
        }

        mean_loop:
//		for (int i = 0; i < DIVIDE_BLOCK; i++) {
//			fixed16_10 sum = fixed16_10(0.0f);
//			for (int j = 0; j < DIVIDE_SIZE; j++) {
//				#pragma HLS PIPELINE II=1
//            	#pragma HLS UNROLL factor=2
//				sum += local_in[i * DIVIDE_SIZE + j];
//			}
////			mean += (sum >> 4);
//			mean += sum;
//		}
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
			mean += local_in[i];
		}
//		mean = mean >> 4;
//		mean = mean / 10;
		mean /= HIDDEN_SIZE;
        printf("mean: %f\n", float(mean));

        variance_loop:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
//			variance += ((local_in[i] - mean) >> 2) * ((local_in[i] - mean) >> 2);
        	variance += (local_in[i] - mean) * (local_in[i] - mean);
		}
//        variance = variance >> 4;
//        variance = variance / 10;
        variance /= HIDDEN_SIZE;
        printf("variance: %f\n", float(variance));

        // 計算標準差
//        float tmp = variance + eps;
        fixed32_14 inv_stddev = 1 / hls::sqrt(variance + eps);

        normalization_loop:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            local_out[i] += local_weight[i] * (local_in[i] - mean) * inv_stddev;
        }

        load_out:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            out[i] = fixed16_10(local_out[i]);
        }
    }
}
