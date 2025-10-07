#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_half.h>
#include <ap_int.h>
#include <string.h>
#define BURST_LEN 256

#define HIDDEN_SIZE 2560
#define INTERMEDIATE_SIZE 10240
#define M_SQRT2 1.41421356237309504880
#define M_2_SQRTPI 1.12837916709551257390
#define BURST_SIZE 64

//typedef ap_fixed<32,14> fixed32_14;
typedef float fixed32_14;
typedef ap_uint<16>  uint16;

const float kGeluBeta = M_SQRT2 * M_2_SQRTPI * 0.5;
const float kGeluKappa = 0.044715;

void new_gelu(fixed32_14* out, float x) {
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
        half bias_fc2_0[HIDDEN_SIZE / 8],
        half bias_fc2_1[HIDDEN_SIZE / 8],
        half bias_fc2_2[HIDDEN_SIZE / 8],
        half bias_fc2_3[HIDDEN_SIZE / 8],
        half bias_fc2_4[HIDDEN_SIZE / 8],
        half bias_fc2_5[HIDDEN_SIZE / 8],
        half bias_fc2_6[HIDDEN_SIZE / 8],
        half bias_fc2_7[HIDDEN_SIZE / 8]
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
        #pragma HLS INTERFACE m_axi port=bias_fc2_0 offset=slave bundle=gmem0 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_1 offset=slave bundle=gmem1 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_1 offset=slave bundle=gmem1 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_2 offset=slave bundle=gmem2 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_2 offset=slave bundle=gmem2 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_3 offset=slave bundle=gmem3 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_3 offset=slave bundle=gmem3 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_4 offset=slave bundle=gmem0 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_4 offset=slave bundle=gmem0 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_5 offset=slave bundle=gmem1 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_5 offset=slave bundle=gmem1 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_6 offset=slave bundle=gmem2 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_6 offset=slave bundle=gmem2 depth=320 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight_fc2_7 offset=slave bundle=gmem3 depth=3276800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias_fc2_7 offset=slave bundle=gmem3 depth=320 max_read_burst_length=256

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
        half local_bias[INTERMEDIATE_SIZE];
        half local_w_0[HIDDEN_SIZE];
        half local_w_1[HIDDEN_SIZE];
        half local_w_2[HIDDEN_SIZE];
        half local_w_3[HIDDEN_SIZE];
        fixed32_14 gelu_buf[4];
        fixed32_14 fc2_in_buf[4];

		#pragma HLS bind_storage variable=local_linear_1_in type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_1_out type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_2_out type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_bias type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_0 type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_w_1 type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_w_2 type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=local_w_3 type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=gelu_buf type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=fc2_in_buf type=RAM_T2P impl=bram

        mlp_load_fc1_input:
        for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
            #pragma HLS DATAFLOW
        	memcpy((fixed32_14*)&local_linear_1_in[b * BURST_LEN], (fixed32_14*)&in[b * BURST_LEN], sizeof(fixed32_14) * BURST_LEN);
        }

        mlp_load_fc1_bias_0:
		for (int b = 0; b < INTERMEDIATE_SIZE / 8 / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((uint16*)&local_bias[b * BURST_LEN + 0 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_0[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 1 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_1[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 2 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_2[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 3 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_3[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
		}

		mlp_load_fc1_bias_1:
		for (int b = 0; b < INTERMEDIATE_SIZE / 8 / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((uint16*)&local_bias[b * BURST_LEN + 4 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_4[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 5 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_5[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 6 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_6[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 7 * INTERMEDIATE_SIZE / 8], (uint16*)&bias_fc1_7[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
		}

        mlp_fc1_half_to_float:
		for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
			#pragma HLS UNROLL factor=2
			local_linear_1_out[i] = fixed32_14(local_bias[i]);
		}

		mlp_load_fc2_bias_0:
		for (int b = 0; b < HIDDEN_SIZE / 8 / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((uint16*)&local_bias[b * BURST_LEN + 0 * HIDDEN_SIZE / 8], (uint16*)&bias_fc2_0[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 1 * HIDDEN_SIZE / 8], (uint16*)&bias_fc2_1[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 2 * HIDDEN_SIZE / 8], (uint16*)&bias_fc2_2[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 3 * HIDDEN_SIZE / 8], (uint16*)&bias_fc2_3[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
		}

		mlp_load_fc2_bias_1:
		for (int b = 0; b < HIDDEN_SIZE / 8 / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((uint16*)&local_bias[b * BURST_LEN + 4 * HIDDEN_SIZE / 8], (uint16*)&bias_fc2_4[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 5 * HIDDEN_SIZE / 8], (uint16*)&bias_fc2_5[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 6 * HIDDEN_SIZE / 8], (uint16*)&bias_fc2_6[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 7 * HIDDEN_SIZE / 8], (uint16*)&bias_fc2_7[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
		}

		mlp_fc2_half_to_float:
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
			local_linear_2_out[i] = fixed32_14(local_bias[i]);
		}

		mlp_compute_0:
		for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
			mlp_load_weight_fc1_0:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_0[b * BURST_LEN], (uint16*)&weight_fc1_0[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_1[b * BURST_LEN], (uint16*)&weight_fc1_1[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_2[b * BURST_LEN], (uint16*)&weight_fc1_2[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_3[b * BURST_LEN], (uint16*)&weight_fc1_3[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
			init_gelu_buf_0:
			for (int j = 0; j < 4; j++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS UNROLL factor=2
				gelu_buf[j] = local_linear_1_out[j * INTERMEDIATE_SIZE / 8 + i];
			}
			fc1_compute_0:
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				gelu_buf[0] += local_linear_1_in[j] * fixed32_14(local_w_0[j]);
				gelu_buf[1] += local_linear_1_in[j] * fixed32_14(local_w_1[j]);
				gelu_buf[2] += local_linear_1_in[j] * fixed32_14(local_w_2[j]);
				gelu_buf[3] += local_linear_1_in[j] * fixed32_14(local_w_3[j]);
			}
			gelu_0:
			for (int j = 0; j < 4; j++) {
				#pragma HLS UNROLL factor=2
				new_gelu(&fc2_in_buf[j], float(gelu_buf[j]));
			}
			mlp_load_weight_fc2_0:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_0[b * BURST_LEN], (uint16*)&weight_fc2_0[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_1[b * BURST_LEN], (uint16*)&weight_fc2_1[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_2[b * BURST_LEN], (uint16*)&weight_fc2_2[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_3[b * BURST_LEN], (uint16*)&weight_fc2_3[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
			fc2_compute_0:
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_2_out[j] += ((fc2_in_buf[0] * fixed32_14(local_w_0[j]) + fc2_in_buf[1] * fixed32_14(local_w_1[j]))
									   + (fc2_in_buf[2] * fixed32_14(local_w_2[j]) + fc2_in_buf[3] * fixed32_14(local_w_3[j])));
			}
		}

		mlp_compute_1:
		for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
			mlp_load_weight_fc1_1:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_0[b * BURST_LEN], (uint16*)&weight_fc1_4[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_1[b * BURST_LEN], (uint16*)&weight_fc1_5[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_2[b * BURST_LEN], (uint16*)&weight_fc1_6[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_3[b * BURST_LEN], (uint16*)&weight_fc1_7[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
			init_gelu_buf_1:
			for (int j = 0; j < 4; j++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS UNROLL factor=2
				gelu_buf[j] = local_linear_1_out[(j + 4) * INTERMEDIATE_SIZE / 8 + i];
			}
			fc1_compute_1:
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				gelu_buf[0] += local_linear_1_in[j] * fixed32_14(local_w_0[j]);
				gelu_buf[1] += local_linear_1_in[j] * fixed32_14(local_w_1[j]);
				gelu_buf[2] += local_linear_1_in[j] * fixed32_14(local_w_2[j]);
				gelu_buf[3] += local_linear_1_in[j] * fixed32_14(local_w_3[j]);
			}
			gelu_1:
			for (int j = 0; j < 4; j++) {
				#pragma HLS UNROLL factor=2
				new_gelu(&fc2_in_buf[j], float(gelu_buf[j]));
			}
			mlp_load_weight_fc2_1:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_0[b * BURST_LEN], (uint16*)&weight_fc2_4[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_1[b * BURST_LEN], (uint16*)&weight_fc2_5[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_2[b * BURST_LEN], (uint16*)&weight_fc2_6[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_3[b * BURST_LEN], (uint16*)&weight_fc2_7[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
			fc2_compute_1:
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_2_out[j] += ((fc2_in_buf[0] * fixed32_14(local_w_0[j]) + fc2_in_buf[1] * fixed32_14(local_w_1[j]))
									   + (fc2_in_buf[2] * fixed32_14(local_w_2[j]) + fc2_in_buf[3] * fixed32_14(local_w_3[j])));
			}
		}

        mlp_store_output:
		for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((fixed32_14*)&out[b * BURST_LEN], (fixed32_14*)&local_linear_2_out[b * BURST_LEN], sizeof(fixed32_14) * BURST_LEN);
		}
    }
}

// 1. transpose fc2 weight
// 2. burst read/write
// 3. compute 4 row in a loop

HOST-Info: -------------------------------------------------------------------------------
HOST-Info: Name           | type          | start        | end          | Duration(ms)
HOST-Info: -------------------------------------------------------------------------------
HOST-Info: kernel_phi_mlp | kernel        |   1483493909 |   1647006147 |      163.512
HOST-Info: Transfer_1     | mem (H<->G)   |   1469094044 |   1469136956 |     0.042912
HOST-Info: Transfer_2     | mem (H<->G)   |   1469776841 |   1471374776 |      1.59793
HOST-Info: Transfer_3     | mem (H<->G)   |   1469785951 |   1469924053 |     0.138102
HOST-Info: Transfer_4     | mem (H<->G)   |   1469929112 |   1471491500 |      1.56239
HOST-Info: Transfer_5     | mem (H<->G)   |   1471390447 |   1471413210 |     0.022763
HOST-Info: Transfer_6     | mem (H<->G)   |   1471415969 |   1473131168 |       1.7152
HOST-Info: Transfer_7     | mem (H<->G)   |   1471492414 |   1471501937 |     0.009523
HOST-Info: Transfer_8     | mem (H<->G)   |   1471502794 |   1473158083 |      1.65529
HOST-Info: Transfer_9     | mem (H<->G)   |   1473136463 |   1473161947 |     0.025484
HOST-Info: Transfer_10    | mem (H<->G)   |   1473171696 |   1474886573 |      1.71488
HOST-Info: Transfer_11    | mem (H<->G)   |   1473174850 |   1473184459 |     0.009609
HOST-Info: Transfer_12    | mem (H<->G)   |   1473185387 |   1474896087 |       1.7107
HOST-Info: Transfer_13    | mem (H<->G)   |   1474891564 |   1474906099 |     0.014535
HOST-Info: Transfer_14    | mem (H<->G)   |   1474903252 |   1476598501 |      1.69525
HOST-Info: Transfer_15    | mem (H<->G)   |   1474909290 |   1474921843 |     0.012553
HOST-Info: Transfer_16    | mem (H<->G)   |   1474924461 |   1476614818 |      1.69036
HOST-Info: Transfer_17    | mem (H<->G)   |   1476602971 |   1476616790 |     0.013819
HOST-Info: Transfer_18    | mem (H<->G)   |   1476619180 |   1478317364 |      1.69818
HOST-Info: Transfer_19    | mem (H<->G)   |   1476620086 |   1476633988 |     0.013902
HOST-Info: Transfer_20    | mem (H<->G)   |   1476636599 |   1478332710 |      1.69611
HOST-Info: Transfer_21    | mem (H<->G)   |   1478321213 |   1478335449 |     0.014236
HOST-Info: Transfer_22    | mem (H<->G)   |   1478337028 |   1480030888 |      1.69386
HOST-Info: Transfer_23    | mem (H<->G)   |   1478338384 |   1478354990 |     0.016606
HOST-Info: Transfer_24    | mem (H<->G)   |   1478357423 |   1480047658 |      1.69023
HOST-Info: Transfer_25    | mem (H<->G)   |   1480035193 |   1480048382 |     0.013189
HOST-Info: Transfer_26    | mem (H<->G)   |   1480052182 |   1481749525 |      1.69734
HOST-Info: Transfer_27    | mem (H<->G)   |   1480054645 |   1480068013 |     0.013368
HOST-Info: Transfer_28    | mem (H<->G)   |   1480070527 |   1481765357 |      1.69483
HOST-Info: Transfer_29    | mem (H<->G)   |   1481754065 |   1481767813 |     0.013748
HOST-Info: Transfer_30    | mem (H<->G)   |   1481769904 |   1483469970 |      1.70007
HOST-Info: Transfer_31    | mem (H<->G)   |   1481770936 |   1481783724 |     0.012788
HOST-Info: Transfer_32    | mem (H<->G)   |   1481786294 |   1483483044 |      1.69675
HOST-Info: Transfer_33    | mem (H<->G)   |   1483474096 |   1483487289 |     0.013193
HOST-Info: Transfer_34    | mem (H<->G)   |   1647138997 |   1647179973 |     0.040976
HOST-Info: -------------------------------------------------------------------------------
HOST-Info:     Kernels Execution Time (ms) :  163.512  (kernel_phi_mlp'end - kernel_phi_mlp'begin)
HOST-Info: Application Execution Time (ms) :  178.086  (Transfer_34'end - Transfer_1'begin)
HOST-Info: -------------------------------------------------------------------------------


HOST-Info: DONE