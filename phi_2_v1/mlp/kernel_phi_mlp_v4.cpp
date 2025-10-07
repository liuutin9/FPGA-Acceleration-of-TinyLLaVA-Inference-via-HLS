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

typedef ap_fixed<32,14> fixed32_14;
typedef ap_fixed<40,22> fixed40_22;
// typedef float fixed32_14;
typedef ap_uint<16>  uint16;

const float kGeluBeta = M_SQRT2 * M_2_SQRTPI * 0.5;
const float kGeluKappa = 0.044715;

void new_gelu(fixed40_22* out, float x) {
    float x_cube = x * x * x;
    float inner = kGeluBeta * (x + kGeluKappa * x_cube);
    float tanh_inner = hls::tanh(inner);
    *out = fixed40_22(0.5f * x * (1.0f + tanh_inner));
}

extern "C" {
    void kernel_phi_mlp(
        float out[HIDDEN_SIZE],
        float in[HIDDEN_SIZE],
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
        float local_in_buf[HIDDEN_SIZE];
        float local_out_buf[HIDDEN_SIZE];
        fixed40_22 local_linear_1_in[HIDDEN_SIZE];
        fixed40_22 local_linear_1_out[INTERMEDIATE_SIZE];
        fixed40_22 local_linear_2_out[HIDDEN_SIZE];
        half local_bias[INTERMEDIATE_SIZE];
        half local_w_0[HIDDEN_SIZE];
        half local_w_1[HIDDEN_SIZE];
        half local_w_2[HIDDEN_SIZE];
        half local_w_3[HIDDEN_SIZE];
        half local_w_4[HIDDEN_SIZE];
        half local_w_5[HIDDEN_SIZE];
        half local_w_6[HIDDEN_SIZE];
        half local_w_7[HIDDEN_SIZE];
        fixed40_22 gelu_buf[8];
        fixed40_22 fc2_in_buf[8];

        #pragma HLS bind_storage variable=local_in_buf type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_out_buf type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_1_in type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_1_out type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_2_out type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_bias type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_0 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_1 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_2 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_3 type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_w_4 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_5 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_6 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_w_7 type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=gelu_buf type=RAM_T2P impl=bram
		#pragma HLS bind_storage variable=fc2_in_buf type=RAM_T2P impl=bram

        mlp_load_fc1_input:
        for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
            #pragma HLS DATAFLOW
        	memcpy(&local_in_buf[b * BURST_LEN], &in[b * BURST_LEN], sizeof(float) * BURST_LEN);
        }

        mlp_fc1_in_half_to_float:
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
			local_linear_1_in[i] = fixed40_22(local_in_buf[i]);
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
            #pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
			local_linear_1_out[i] = fixed40_22(local_bias[i]);
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
			local_linear_2_out[i] = fixed40_22(local_bias[i]);
		}

		mlp_compute:
		for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
			mlp_load_weight_fc1_0:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_0[b * BURST_LEN], (uint16*)&weight_fc1_0[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_1[b * BURST_LEN], (uint16*)&weight_fc1_1[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_2[b * BURST_LEN], (uint16*)&weight_fc1_2[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_3[b * BURST_LEN], (uint16*)&weight_fc1_3[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
            mlp_load_weight_fc1_1:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_4[b * BURST_LEN], (uint16*)&weight_fc1_4[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_5[b * BURST_LEN], (uint16*)&weight_fc1_5[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_6[b * BURST_LEN], (uint16*)&weight_fc1_6[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_7[b * BURST_LEN], (uint16*)&weight_fc1_7[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
			init_gelu_buf:
			for (int j = 0; j < 8; j++) {
				#pragma HLS PIPELINE II=1
				#pragma HLS UNROLL factor=2
				gelu_buf[j] = local_linear_1_out[j * INTERMEDIATE_SIZE / 8 + i];
			}
			fc1_compute:
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				gelu_buf[0] += local_linear_1_in[j] * fixed40_22(local_w_0[j]);
				gelu_buf[1] += local_linear_1_in[j] * fixed40_22(local_w_1[j]);
				gelu_buf[2] += local_linear_1_in[j] * fixed40_22(local_w_2[j]);
				gelu_buf[3] += local_linear_1_in[j] * fixed40_22(local_w_3[j]);
                gelu_buf[4] += local_linear_1_in[j] * fixed40_22(local_w_4[j]);
                gelu_buf[5] += local_linear_1_in[j] * fixed40_22(local_w_5[j]);
                gelu_buf[6] += local_linear_1_in[j] * fixed40_22(local_w_6[j]);
                gelu_buf[7] += local_linear_1_in[j] * fixed40_22(local_w_7[j]);
			}
			gelu:
			for (int j = 0; j < 8; j++) {
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
            mlp_load_weight_fc2_1:
			for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_4[b * BURST_LEN], (uint16*)&weight_fc2_4[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_5[b * BURST_LEN], (uint16*)&weight_fc2_5[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_6[b * BURST_LEN], (uint16*)&weight_fc2_6[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_7[b * BURST_LEN], (uint16*)&weight_fc2_7[i * HIDDEN_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
			fc2_compute:
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_2_out[j] += ((fc2_in_buf[0] * fixed40_22(local_w_0[j]) + fc2_in_buf[1] * fixed40_22(local_w_1[j]))
									   + (fc2_in_buf[2] * fixed40_22(local_w_2[j]) + fc2_in_buf[3] * fixed40_22(local_w_3[j])))
                                       + ((fc2_in_buf[4] * fixed40_22(local_w_4[j]) + fc2_in_buf[5] * fixed40_22(local_w_5[j]))
									   + (fc2_in_buf[6] * fixed40_22(local_w_6[j]) + fc2_in_buf[7] * fixed40_22(local_w_7[j])));
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
// 3. compute 8 row in a loop
// 4. use ap_fixed<32,14>

HOST-Info: -------------------------------------------------------------------------------
HOST-Info: Name           | type          | start        | end          | Duration(ms)
HOST-Info: -------------------------------------------------------------------------------
HOST-Info: kernel_phi_mlp | kernel        |   7711885335 |   7770585297 |         58.7
HOST-Info: Transfer_1     | mem (H<->G)   |   7695909904 |   7696065089 |     0.155185
HOST-Info: Transfer_2     | mem (H<->G)   |   7697144488 |   7698976461 |      1.83197
HOST-Info: Transfer_3     | mem (H<->G)   |   7697147067 |   7697293652 |     0.146585
HOST-Info: Transfer_4     | mem (H<->G)   |   7697300803 |   7698966398 |      1.66559
HOST-Info: Transfer_5     | mem (H<->G)   |   7699002698 |   7699145534 |     0.142836
HOST-Info: Transfer_6     | mem (H<->G)   |   7699010422 |   7700601629 |      1.59121
HOST-Info: Transfer_7     | mem (H<->G)   |   7699150781 |   7699250504 |     0.099723
HOST-Info: Transfer_8     | mem (H<->G)   |   7699255768 |   7700772671 |       1.5169
HOST-Info: Transfer_9     | mem (H<->G)   |   7700608765 |   7700734969 |     0.126204
HOST-Info: Transfer_10    | mem (H<->G)   |   7700739829 |   7702411236 |      1.67141
HOST-Info: Transfer_11    | mem (H<->G)   |   7700777873 |   7700852853 |      0.07498
HOST-Info: Transfer_12    | mem (H<->G)   |   7700854304 |   7702470641 |      1.61634
HOST-Info: Transfer_13    | mem (H<->G)   |   7702416349 |   7702429561 |     0.013212
HOST-Info: Transfer_14    | mem (H<->G)   |   7702432016 |   7704333049 |      1.90103
HOST-Info: Transfer_15    | mem (H<->G)   |   7702472433 |   7702496856 |     0.024423
HOST-Info: Transfer_16    | mem (H<->G)   |   7702497677 |   7704412611 |      1.91493
HOST-Info: Transfer_17    | mem (H<->G)   |   7704367936 |   7704403877 |     0.035941
HOST-Info: Transfer_18    | mem (H<->G)   |   7704406333 |   7706197625 |      1.79129
HOST-Info: Transfer_19    | mem (H<->G)   |   7704414025 |   7704436880 |     0.022855
HOST-Info: Transfer_20    | mem (H<->G)   |   7704439330 |   7706186574 |      1.74724
HOST-Info: Transfer_21    | mem (H<->G)   |   7706187404 |   7706200518 |     0.013114
HOST-Info: Transfer_22    | mem (H<->G)   |   7706201914 |   7708017508 |      1.81559
HOST-Info: Transfer_23    | mem (H<->G)   |   7706203709 |   7706218021 |     0.014312
HOST-Info: Transfer_24    | mem (H<->G)   |   7706220843 |   7708025094 |      1.80425
HOST-Info: Transfer_25    | mem (H<->G)   |   7708022838 |   7708037359 |     0.014521
HOST-Info: Transfer_26    | mem (H<->G)   |   7708041078 |   7709892360 |      1.85128
HOST-Info: Transfer_27    | mem (H<->G)   |   7708043637 |   7708055558 |     0.011921
HOST-Info: Transfer_28    | mem (H<->G)   |   7708056851 |   7710014528 |      1.95768
HOST-Info: Transfer_29    | mem (H<->G)   |   7709928292 |   7709968474 |     0.040182
HOST-Info: Transfer_30    | mem (H<->G)   |   7709971110 |   7711723145 |      1.75204
HOST-Info: Transfer_31    | mem (H<->G)   |   7710024230 |   7710041281 |     0.017051
HOST-Info: Transfer_32    | mem (H<->G)   |   7710044932 |   7711878744 |      1.83381
HOST-Info: Transfer_33    | mem (H<->G)   |   7711757911 |   7711800896 |     0.042985
HOST-Info: Transfer_34    | mem (H<->G)   |   7770783796 |   7770985594 |     0.201798
HOST-Info: -------------------------------------------------------------------------------
HOST-Info:     Kernels Execution Time (ms) :  58.7  (kernel_phi_mlp'end - kernel_phi_mlp'begin)
HOST-Info: Application Execution Time (ms) :  75.0757  (Transfer_34'end - Transfer_1'begin)
HOST-Info: -------------------------------------------------------------------------------


HOST-Info: DONE