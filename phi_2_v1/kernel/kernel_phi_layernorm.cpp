#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_half.h>
#include <ap_int.h>

#define HIDDEN_SIZE 2560
#define LAYER_NORM_EPS 0.00001

//typedef ap_fixed<32,14> fixed32_14;
typedef float fixed32_14;
//typedef ap_fixed<40,22> fixed40_22;
typedef float fixed40_22;

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
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=weight bundle=control
        #pragma HLS INTERFACE s_axilite port=bias bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

    	fixed40_22 local_out[HIDDEN_SIZE];
    	fixed40_22 local_in[HIDDEN_SIZE];
    	fixed40_22 local_weight[HIDDEN_SIZE];

        #pragma HLS bind_storage variable=local_out type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_in type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_weight type=RAM_T2P impl=uram

    	fixed40_22 mean = fixed40_22(0.0f);
    	fixed40_22 variance = fixed40_22(0.0f);
    	fixed40_22 eps = fixed40_22(LAYER_NORM_EPS);

        initLocal(local_in, local_out, local_weight, in, bias, weight);

        mean_loop:
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
			mean += local_in[i];
		}
		mean /= HIDDEN_SIZE;

        variance_loop:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
        	variance += (local_in[i] - mean) * (local_in[i] - mean);
		}
        variance /= HIDDEN_SIZE;

        // 計算標準差
        fixed40_22 inv_stddev = 1 / hls::sqrt(variance + eps);

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
