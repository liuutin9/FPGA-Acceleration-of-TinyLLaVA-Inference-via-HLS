
#include <hls_math.h>
#include <ap_fixed.h>
#include <hls_half.h>
typedef ap_fixed<16,10> fixed16_10;
typedef ap_fixed<32,14> fixed32_14;
typedef ap_fixed<40,16> fixed40_16;
//#include <cmath>

#define VISION_HIDDEN_SIZE 1152
#define HIDDEN_SIZE 2560
#define INPUT_DIM 728                     // 729 SigLIP tokens minus token 0 ("patch" strategy: image_features[:, 1:])
#define SIGLIP_TOKENS (INPUT_DIM + 1)     // `in` holds the full 729-token SigLIP output
#define BLOCK_SIZE 8
#define IN_BLOCK_NUM 91                   // INPUT_DIM / BLOCK_SIZE = 728 / 8
#define W_BLOCK_NUM 320

//#define BLOCK_SIZE 32
//#define IN_BLOCK_NUM 2//INPUT_DIM/BLOCK_SIZE
//#define W_BLOCK_NUM 80

//fixed32_14 gelu_fixed(fixed32_14 x) {
//    const fixed32_14 sqrt_2_over_pi = 0.7978845608;
//    fixed32_14 x3 = x * x * x;
//    fixed32_14 inner = sqrt_2_over_pi * (x + (fixed32_14)0.044715 * x3);
//    fixed32_14 t = hls::tanh(inner);
//    return (fixed32_14)0.5 * x * ((fixed32_14)1.0 + t);
//}

float gelu(float x) {
    const float sqrt_2_over_pi = 0.7978845608f;
    float x3 = x * x * x;
    float inner = sqrt_2_over_pi * (x + 0.044715f * x3);
    float tanh_inner = hls::tanh(inner);
    //float tanh_inner = std::tanh(inner); // 使用標準 C++ tanh
    return 0.5f * x * (1.0f + tanh_inner);
}

extern "C" {
void Connector(
		fixed32_14 *out,
		fixed32_14 *in,
		half *_0_weight,
		half *_0_bias,
		half *_2_weight,
		half *_2_bias
	) {
		#pragma HLS INTERFACE m_axi port=out       offset=slave bundle=gmem3 depth=INPUT_DIM*HIDDEN_SIZE 			max_read_burst_length=128
		#pragma HLS INTERFACE m_axi port=in        offset=slave bundle=gmem0 depth=SIGLIP_TOKENS*VISION_HIDDEN_SIZE 	max_read_burst_length=128
		#pragma HLS INTERFACE m_axi port=_0_weight offset=slave bundle=gmem1 depth=HIDDEN_SIZE*VISION_HIDDEN_SIZE 	max_read_burst_length=128
		#pragma HLS INTERFACE m_axi port=_0_bias   offset=slave bundle=gmem1 depth=HIDDEN_SIZE 						max_read_burst_length=128
		#pragma HLS INTERFACE m_axi port=_2_weight offset=slave bundle=gmem2 depth=HIDDEN_SIZE*HIDDEN_SIZE			max_read_burst_length=128
		#pragma HLS INTERFACE m_axi port=_2_bias   offset=slave bundle=gmem2 depth=HIDDEN_SIZE 						max_read_burst_length=128

		#pragma HLS INTERFACE s_axilite port=out bundle=control
		#pragma HLS INTERFACE s_axilite port=in bundle=control
		#pragma HLS INTERFACE s_axilite port=_0_weight bundle=control
		#pragma HLS INTERFACE s_axilite port=_0_bias bundle=control
		#pragma HLS INTERFACE s_axilite port=_2_weight bundle=control
		#pragma HLS INTERFACE s_axilite port=_2_bias bundle=control
		#pragma HLS INTERFACE s_axilite port=return bundle=control


		#pragma HLS STREAM variable=_0_weight depth=1024

		fixed40_16 temp_out_1[BLOCK_SIZE*HIDDEN_SIZE];
		//fixed32_14 temp_out_2[BLOCK_SIZE*HIDDEN_SIZE];
		fixed32_14 temp_in_1[BLOCK_SIZE*VISION_HIDDEN_SIZE];
		//fixed32_14 temp_in_2[BLOCK_SIZE*VISION_HIDDEN_SIZE];
		fixed32_14 temp_0_bias[HIDDEN_SIZE];
		fixed32_14 temp_2_bias[HIDDEN_SIZE];
		fixed32_14 block_0_weight[BLOCK_SIZE*VISION_HIDDEN_SIZE];
		fixed32_14 block_2_weight[BLOCK_SIZE*HIDDEN_SIZE];
		fixed40_16 block_0_bias[BLOCK_SIZE*HIDDEN_SIZE];
		fixed40_16 block_2_bias[BLOCK_SIZE*HIDDEN_SIZE];


		#pragma HLS bind_storage variable=temp_out_1 type=RAM_T2P impl=uram
		#pragma HLS ARRAY_PARTITION variable=temp_out_1 cyclic factor=8 dim=1
		//#pragma HLS bind_storage variable=temp_out_2 type=RAM_T2P impl=uram

		#pragma HLS bind_storage variable=temp_in_1 type=RAM_T2P impl=uram
		#pragma HLS ARRAY_PARTITION variable=temp_in_1 cyclic factor=8 dim=1
		//#pragma HLS bind_storage variable=temp_in_2 type=RAM_T2P impl=uram

		#pragma HLS bind_storage variable=temp_0_bias type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=temp_2_bias type=RAM_T2P impl=uram

		#pragma HLS bind_storage variable=block_0_weight type=RAM_T2P impl=uram
		#pragma HLS ARRAY_PARTITION variable=block_0_weight cyclic factor=8 dim=1

		#pragma HLS bind_storage variable=block_2_weight type=RAM_T2P impl=uram
		#pragma HLS ARRAY_PARTITION variable=block_2_weight cyclic factor=8 dim=1

		#pragma HLS bind_storage variable=block_0_bias type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=block_2_bias type=RAM_T2P impl=uram

//		fixed32_14 temp_in_1[BLOCK_SIZE * VISION_HIDDEN_SIZE];
//		#pragma HLS bind_storage variable=temp_in_1 type=RAM_T2P impl=uram
//		#pragma HLS ARRAY_PARTITION variable=temp_in_1 cyclic factor=4 dim=1

		fixed32_14 sum1, sum2, sum;
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			temp_0_bias[i] = fixed32_14(_0_bias[i]);
			temp_2_bias[i] = fixed32_14(_2_bias[i]);
		}

		for (int b = 0; b < IN_BLOCK_NUM; b += 1) {
			// cache input blocks
			copy_in:
			for (int i = 0; i < BLOCK_SIZE*VISION_HIDDEN_SIZE; i++) {
				#pragma HLS PIPELINE II=1
				// skip token 0: block b covers SigLIP tokens [b*BLOCK_SIZE + 1, b*BLOCK_SIZE + BLOCK_SIZE]
				temp_in_1[i] = in[(b*BLOCK_SIZE + 1)*VISION_HIDDEN_SIZE + i];
			}

			for (int i = 0; i < BLOCK_SIZE; i++) {
				for (int j = 0; j < HIDDEN_SIZE; j++) {
					#pragma HLS PIPELINE II=1
					block_0_bias[i*HIDDEN_SIZE + j] = temp_0_bias[j];
					block_2_bias[i*HIDDEN_SIZE + j] = temp_2_bias[j];
				}
			}

			compute_block_1:
			for (int w = 0; w < W_BLOCK_NUM; w++) {
				// cache weights
				copy_w0:
				for (int idx = 0; idx < BLOCK_SIZE*VISION_HIDDEN_SIZE; idx++) {
					#pragma HLS PIPELINE II=1
					block_0_weight[idx] = fixed32_14(_0_weight[w*BLOCK_SIZE*VISION_HIDDEN_SIZE + idx]);
				}
				in_block_1:
				for (int i = 0; i < BLOCK_SIZE; i++) {
					weight_block_1:
					for (int j = 0; j < BLOCK_SIZE; j++) {
						fixed40_16 sum1 = fixed40_16(0.0f);
						partial_sum:
						for (int k=0; k<VISION_HIDDEN_SIZE; k++){
							#pragma HLS PIPELINE II=1
							#pragma HLS reduction variable=sum operator=+
							#pragma HLS UNROLL factor=4
							sum1 += temp_in_1[i*VISION_HIDDEN_SIZE + k] * block_0_weight[j*VISION_HIDDEN_SIZE + k];
						}
						// if (k < VISION_HIDDEN_SIZE) {
						// 	sum_0 += temp_in_1[row_i * VISION_HIDDEN_SIZE + k] * block_0_weight[global_j * VISION_HIDDEN_SIZE + k];
						// }
						block_0_bias[i*HIDDEN_SIZE+w*BLOCK_SIZE+j] += sum1;
						//sum1 = sum1_0 + sum1_1;
						// temp_out_1[i*HIDDEN_SIZE+w*BLOCK_SIZE+j] = fixed32_14(gelu(float(sum1 + _0_bias[w*BLOCK_SIZE+j])));
						// temp_out_2[i*HIDDEN_SIZE+w*BLOCK_SIZE+j] = fixed32_14(gelu(float(sum2 + _0_bias[w*BLOCK_SIZE+j])));
					}
				}
			}
			gelu:
			for (int i = 0; i < BLOCK_SIZE*HIDDEN_SIZE; i++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS UNROLL factor=4
				temp_out_1[i] = fixed40_16(gelu(block_0_bias[i]));
			}

			// 第二層
			compute_block_2:
			for (int w = 0; w < W_BLOCK_NUM; w++) {
				copy_w2:
				for (int idx = 0; idx < BLOCK_SIZE*HIDDEN_SIZE; idx++) {
					#pragma HLS PIPELINE II=1
					block_2_weight[idx] = fixed32_14(_2_weight[w*BLOCK_SIZE*HIDDEN_SIZE + idx]);
				}
				// out1
				in_block_2:
				for (int i = 0; i < BLOCK_SIZE; i++) {
					weight_block_2:
					for (int j = 0; j < BLOCK_SIZE; j++) {
						//#pragma HLS PIPELINE II=2
						fixed40_16 sum2 = fixed40_16(0.0f);
						inner2:
						for (int k=0; k<HIDDEN_SIZE; k++){
							#pragma HLS PIPELINE II=1
							#pragma HLS reduction variable=sum operator=+
							#pragma HLS UNROLL factor=4
							sum2 += temp_out_1[i*HIDDEN_SIZE + k] * block_2_weight[j*HIDDEN_SIZE + k];
						}
						block_2_bias[i*HIDDEN_SIZE + w*BLOCK_SIZE+j] += sum2;
					}
				}
			}
			// write back once, after all W_BLOCK_NUM weight blocks have been accumulated
			out:
			for (int i = 0; i < BLOCK_SIZE*HIDDEN_SIZE; i++) {
				#pragma HLS PIPELINE II=1
				out[b*BLOCK_SIZE*HIDDEN_SIZE + i] = fixed32_14(block_2_bias[i]);
			}
		}
	}
}
