#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_half.h>
#include <ap_int.h>
#include <string.h>
//#include <iostream>

#define BURST_LEN 256

#define HIDDEN_SIZE 2560
#define INTERMEDIATE_SIZE 10240
#define M_SQRT2 1.41421356237309504880
#define M_2_SQRTPI 1.12837916709551257390
#define BURST_SIZE 64

//typedef ap_fixed<32,14> fixed32_14;
typedef float fixed32_14;
//typedef ap_fixed<40,16> fixed32_14;
typedef ap_uint<16>  uint16;

const float kGeluBeta = M_SQRT2 * M_2_SQRTPI * 0.5;
const float kGeluKappa = 0.044715;

void new_gelu(fixed32_14* out, float x) {
#pragma HLS PIPELINE
    float x_cube = x * x * x;
    float inner = kGeluBeta * (x + kGeluKappa * x_cube);
    float tanh_inner = hls::tanh(inner);
    *out = fixed32_14(0.5f * x * (1.0f + tanh_inner));
}

extern "C" {
    void kernel_phi_mlp(
        fixed32_14 out[HIDDEN_SIZE],
        fixed32_14 in[HIDDEN_SIZE],
        half weight_fc1_0[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        half weight_fc1_1[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        half weight_fc1_2[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        half weight_fc1_3[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        half weight_fc1_4[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        half weight_fc1_5[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        half weight_fc1_6[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        half weight_fc1_7[INTERMEDIATE_SIZE / 8 * HIDDEN_SIZE],
        half bias_fc1_0[INTERMEDIATE_SIZE / 8],
        half bias_fc1_1[INTERMEDIATE_SIZE / 8],
        half bias_fc1_2[INTERMEDIATE_SIZE / 8],
        half bias_fc1_3[INTERMEDIATE_SIZE / 8],
        half bias_fc1_4[INTERMEDIATE_SIZE / 8],
        half bias_fc1_5[INTERMEDIATE_SIZE / 8],
        half bias_fc1_6[INTERMEDIATE_SIZE / 8],
        half bias_fc1_7[INTERMEDIATE_SIZE / 8],
        half weight_fc2_0[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        half weight_fc2_1[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        half weight_fc2_2[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        half weight_fc2_3[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        half weight_fc2_4[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        half weight_fc2_5[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        half weight_fc2_6[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        half weight_fc2_7[HIDDEN_SIZE / 8 * INTERMEDIATE_SIZE],
        half bias_fc2_0[HIDDEN_SIZE / 2],
        half bias_fc2_1[HIDDEN_SIZE / 2]
    ) {
        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem4 depth=2560 max_write_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem4 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_0 offset=slave bundle=gmem0 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_0 offset=slave bundle=gmem0 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_1 offset=slave bundle=gmem1 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_1 offset=slave bundle=gmem1 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_2 offset=slave bundle=gmem2 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_2 offset=slave bundle=gmem2 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_3 offset=slave bundle=gmem3 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_3 offset=slave bundle=gmem3 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_4 offset=slave bundle=gmem0 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_4 offset=slave bundle=gmem0 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_5 offset=slave bundle=gmem1 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_5 offset=slave bundle=gmem1 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_6 offset=slave bundle=gmem2 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_6 offset=slave bundle=gmem2 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc1_7 offset=slave bundle=gmem3 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc1_7 offset=slave bundle=gmem3 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_0 offset=slave bundle=gmem0 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_0 offset=slave bundle=gmem0 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_1 offset=slave bundle=gmem1 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_1 offset=slave bundle=gmem1 depth=1280 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_2 offset=slave bundle=gmem2 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_3 offset=slave bundle=gmem3 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_4 offset=slave bundle=gmem0 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_5 offset=slave bundle=gmem1 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_6 offset=slave bundle=gmem2 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_7 offset=slave bundle=gmem3 depth=3276800 max_read_burst_length=256

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
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        // 壓縮並存放到 local buffer
        fixed32_14 local_linear_1_out[INTERMEDIATE_SIZE];
        fixed32_14 local_linear_1_in[HIDDEN_SIZE];
        fixed32_14 local_linear_2_out[HIDDEN_SIZE];
        half local_bias_0[INTERMEDIATE_SIZE];
        half local_bias_1[HIDDEN_SIZE];
        half local_w_00[HIDDEN_SIZE];
        half local_w_01[HIDDEN_SIZE];
        half local_w_02[HIDDEN_SIZE];
        half local_w_03[HIDDEN_SIZE];
        half local_w_04[HIDDEN_SIZE];
        half local_w_05[HIDDEN_SIZE];
        half local_w_06[HIDDEN_SIZE];
        half local_w_07[HIDDEN_SIZE];
        half local_w_10[HIDDEN_SIZE];
		half local_w_11[HIDDEN_SIZE];
		half local_w_12[HIDDEN_SIZE];
		half local_w_13[HIDDEN_SIZE];
		half local_w_14[HIDDEN_SIZE];
		half local_w_15[HIDDEN_SIZE];
		half local_w_16[HIDDEN_SIZE];
		half local_w_17[HIDDEN_SIZE];
        fixed32_14 gelu_buf[8];
        fixed32_14 fc2_in_buf[8];

		#pragma HLS bind_storage variable=local_linear_1_in type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_1_out type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_2_out type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_bias_0 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_bias_1 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_00 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_01 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_02 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_03 type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_w_04 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_05 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_06 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_07 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_10 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_11 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_12 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_13 type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_w_14 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_15 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_16 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_17 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=gelu_buf type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=fc2_in_buf type=RAM_T2P impl=uram

        mlp_load_fc1_input:
        for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
            #pragma HLS DATAFLOW
        	memcpy((fixed32_14*)&local_linear_1_in[b * BURST_LEN], (fixed32_14*)&in[b * BURST_LEN], sizeof(fixed32_14) * BURST_LEN);
        }

        mlp_load_fc1_bias_0:
		for (int b = 0; b < INTERMEDIATE_SIZE / 8 / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((uint16*)&local_bias_0[b * BURST_LEN + 0 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_0[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias_0[b * BURST_LEN + 1 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_1[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias_0[b * BURST_LEN + 2 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_2[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias_0[b * BURST_LEN + 3 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_3[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
		}

		mlp_load_fc1_bias_1:
		for (int b = 0; b < INTERMEDIATE_SIZE / 8 / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((uint16*)&local_bias_0[b * BURST_LEN + 4 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_4[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias_0[b * BURST_LEN + 5 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_5[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias_0[b * BURST_LEN + 6 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_6[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias_0[b * BURST_LEN + 7 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_7[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
		}

		mlp_load_fc2_bias_0:
		for (int b = 0; b < HIDDEN_SIZE / 2 / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((uint16*)&local_bias_1[b * BURST_LEN + 0 * HIDDEN_SIZE / 2], (uint16*)&bias_fc2_0[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias_1[b * BURST_LEN + 1 * HIDDEN_SIZE / 2], (uint16*)&bias_fc2_1[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
		}

		mlp_fc2_half_to_float:
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			local_linear_2_out[i] = fixed32_14(local_bias_1[i]);
		}

		mlp_compute:
		for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
			mlp_load_weight_fc1_0:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_00[b * BURST_LEN], (uint16*)&weight_fc1_0[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_01[b * BURST_LEN], (uint16*)&weight_fc1_1[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_02[b * BURST_LEN], (uint16*)&weight_fc1_2[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_03[b * BURST_LEN], (uint16*)&weight_fc1_3[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
            mlp_load_weight_fc1_1:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_04[b * BURST_LEN], (uint16*)&weight_fc1_4[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_05[b * BURST_LEN], (uint16*)&weight_fc1_5[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_06[b * BURST_LEN], (uint16*)&weight_fc1_6[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_07[b * BURST_LEN], (uint16*)&weight_fc1_7[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
			mlp_load_weight_fc2_0:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_10[b * BURST_LEN], (uint16*)&weight_fc2_0[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_11[b * BURST_LEN], (uint16*)&weight_fc2_1[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_12[b * BURST_LEN], (uint16*)&weight_fc2_2[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_13[b * BURST_LEN], (uint16*)&weight_fc2_3[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
			mlp_load_weight_fc2_1:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_14[b * BURST_LEN], (uint16*)&weight_fc2_4[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_15[b * BURST_LEN], (uint16*)&weight_fc2_5[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_16[b * BURST_LEN], (uint16*)&weight_fc2_6[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_17[b * BURST_LEN], (uint16*)&weight_fc2_7[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
			init_gelu_buf:
			for (int j = 0; j < 8; j++) {
				#pragma HLS PIPELINE II=1
				gelu_buf[j] = fixed32_14(local_bias_0[j * INTERMEDIATE_SIZE / 8 + i]);
			}
			fc1_compute:
			for (int j = 0; j < HIDDEN_SIZE; j++) {
//				#pragma HLS PIPELINE II=1
				gelu_buf[0] += local_linear_1_in[j] * fixed32_14(local_w_00[j]);
				gelu_buf[1] += local_linear_1_in[j] * fixed32_14(local_w_01[j]);
				gelu_buf[2] += local_linear_1_in[j] * fixed32_14(local_w_02[j]);
				gelu_buf[3] += local_linear_1_in[j] * fixed32_14(local_w_03[j]);
                gelu_buf[4] += local_linear_1_in[j] * fixed32_14(local_w_04[j]);
                gelu_buf[5] += local_linear_1_in[j] * fixed32_14(local_w_05[j]);
                gelu_buf[6] += local_linear_1_in[j] * fixed32_14(local_w_06[j]);
                gelu_buf[7] += local_linear_1_in[j] * fixed32_14(local_w_07[j]);
			}
			gelu:
			for (int j = 0; j < 8; j++) {
				new_gelu(&fc2_in_buf[j], float(gelu_buf[j]));
			}
			fc2_compute:
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_2_out[j] += ((fc2_in_buf[0] * fixed32_14(local_w_10[j]) + fc2_in_buf[1] * fixed32_14(local_w_11[j]))
									   + (fc2_in_buf[2] * fixed32_14(local_w_12[j]) + fc2_in_buf[3] * fixed32_14(local_w_13[j])))
                                       + ((fc2_in_buf[4] * fixed32_14(local_w_14[j]) + fc2_in_buf[5] * fixed32_14(local_w_15[j]))
									   + (fc2_in_buf[6] * fixed32_14(local_w_16[j]) + fc2_in_buf[7] * fixed32_14(local_w_17[j])));
			}
		}

        mlp_store_output:
		for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((fixed32_14*)&out[b * BURST_LEN], (fixed32_14*)&local_linear_2_out[b * BURST_LEN], sizeof(fixed32_14) * BURST_LEN);
		}
    }
}
