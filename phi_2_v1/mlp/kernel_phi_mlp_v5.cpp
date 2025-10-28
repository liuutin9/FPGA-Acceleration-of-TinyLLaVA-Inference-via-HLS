#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_half.h>
#include <ap_int.h>

#define HIDDEN_SIZE 2560
#define INTERMEDIATE_SIZE 10240
#define M_SQRT2 1.41421356237309504880
#define M_2_SQRTPI 1.12837916709551257390

//typedef ap_fixed<32,14> fixed32_14;
typedef float fixed32_14;

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
        fixed32_14 local_linear_2_in[INTERMEDIATE_SIZE];

		#pragma HLS bind_storage variable=local_linear_1_in type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_1_out type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_2_in type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_2_out type=RAM_T2P impl=uram

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
        half local_w_10[INTERMEDIATE_SIZE];
		half local_w_11[INTERMEDIATE_SIZE];
		half local_w_12[INTERMEDIATE_SIZE];
		half local_w_13[INTERMEDIATE_SIZE];
		half local_w_14[INTERMEDIATE_SIZE];
		half local_w_15[INTERMEDIATE_SIZE];
		half local_w_16[INTERMEDIATE_SIZE];
		half local_w_17[INTERMEDIATE_SIZE];

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

        mlp_fc1_half_to_float:
		for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			local_linear_1_out[i] = fixed32_14(local_bias_0[i]);
		}

		mlp_fc2_half_to_float:
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			local_linear_2_out[i] = fixed32_14(local_bias_1[i]);
		}

        fc1:
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
            fc1_compute:
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_1_out[0 * INTERMEDIATE_SIZE / 8 + i] += local_linear_1_in[j] * fixed32_14(local_w_00[j]);
				local_linear_1_out[1 * INTERMEDIATE_SIZE / 8 + i] += local_linear_1_in[j] * fixed32_14(local_w_01[j]);
				local_linear_1_out[2 * INTERMEDIATE_SIZE / 8 + i] += local_linear_1_in[j] * fixed32_14(local_w_02[j]);
				local_linear_1_out[3 * INTERMEDIATE_SIZE / 8 + i] += local_linear_1_in[j] * fixed32_14(local_w_03[j]);
                local_linear_1_out[4 * INTERMEDIATE_SIZE / 8 + i] += local_linear_1_in[j] * fixed32_14(local_w_04[j]);
                local_linear_1_out[5 * INTERMEDIATE_SIZE / 8 + i] += local_linear_1_in[j] * fixed32_14(local_w_05[j]);
                local_linear_1_out[6 * INTERMEDIATE_SIZE / 8 + i] += local_linear_1_in[j] * fixed32_14(local_w_06[j]);
                local_linear_1_out[7 * INTERMEDIATE_SIZE / 8 + i] += local_linear_1_in[j] * fixed32_14(local_w_07[j]);
			}
        }

        gelu:
        for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
            new_gelu(&local_linear_2_in[j], float(local_linear_1_out[j]));
        }

        fc2:
		for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
			mlp_load_weight_fc2_0:
			for (int b = 0; b < INTERMEDIATE_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_10[b * BURST_LEN], (uint16*)&weight_fc2_0[i * INTERMEDIATE_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_11[b * BURST_LEN], (uint16*)&weight_fc2_1[i * INTERMEDIATE_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_12[b * BURST_LEN], (uint16*)&weight_fc2_2[i * INTERMEDIATE_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_13[b * BURST_LEN], (uint16*)&weight_fc2_3[i * INTERMEDIATE_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
            mlp_load_weight_fc2_1:
			for (int b = 0; b < INTERMEDIATE_SIZE / BURST_LEN; b++) {
				#pragma HLS DATAFLOW
				memcpy((uint16*)&local_w_14[b * BURST_LEN], (uint16*)&weight_fc2_4[i * INTERMEDIATE_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_15[b * BURST_LEN], (uint16*)&weight_fc2_5[i * INTERMEDIATE_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_16[b * BURST_LEN], (uint16*)&weight_fc2_6[i * INTERMEDIATE_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
				memcpy((uint16*)&local_w_17[b * BURST_LEN], (uint16*)&weight_fc2_7[i * INTERMEDIATE_SIZE + b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			}
            fc2_compute:
			for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_2_out[0 * HIDDEN_SIZE / 8 + i] += local_linear_2_in[j] * fixed32_14(local_w_00[j]);
				local_linear_2_out[1 * HIDDEN_SIZE / 8 + i] += local_linear_2_in[j] * fixed32_14(local_w_01[j]);
				local_linear_2_out[2 * HIDDEN_SIZE / 8 + i] += local_linear_2_in[j] * fixed32_14(local_w_02[j]);
				local_linear_2_out[3 * HIDDEN_SIZE / 8 + i] += local_linear_2_in[j] * fixed32_14(local_w_03[j]);
                local_linear_2_out[4 * HIDDEN_SIZE / 8 + i] += local_linear_2_in[j] * fixed32_14(local_w_04[j]);
                local_linear_2_out[5 * HIDDEN_SIZE / 8 + i] += local_linear_2_in[j] * fixed32_14(local_w_05[j]);
                local_linear_2_out[6 * HIDDEN_SIZE / 8 + i] += local_linear_2_in[j] * fixed32_14(local_w_06[j]);
                local_linear_2_out[7 * HIDDEN_SIZE / 8 + i] += local_linear_2_in[j] * fixed32_14(local_w_07[j]);
			}
        }

        mlp_store_output:
		for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((fixed32_14*)&out[b * BURST_LEN], (fixed32_14*)&local_linear_2_out[b * BURST_LEN], sizeof(fixed32_14) * BURST_LEN);
		}
    }
}


HOST-Info: -------------------------------------------------------------------------------
HOST-Info: Name           | type          | start        | end          | Duration(ms)
HOST-Info: -------------------------------------------------------------------------------
HOST-Info: kernel_phi_mlp | kernel        |   7917729679 |   8096324852 |      178.595
HOST-Info: Transfer_1     | mem (H<->G)   |   7902676840 |   7902814043 |     0.137203
HOST-Info: Transfer_2     | mem (H<->G)   |   7903884834 |   7905682986 |      1.79815
HOST-Info: Transfer_3     | mem (H<->G)   |   7903891316 |   7904021360 |     0.130044
HOST-Info: Transfer_4     | mem (H<->G)   |   7904026942 |   7905729649 |      1.70271
HOST-Info: Transfer_5     | mem (H<->G)   |   7905688385 |   7905783716 |     0.095331
HOST-Info: Transfer_6     | mem (H<->G)   |   7905737234 |   7907521777 |      1.78454
HOST-Info: Transfer_7     | mem (H<->G)   |   7905789438 |   7905917347 |     0.127909
HOST-Info: Transfer_8     | mem (H<->G)   |   7905922480 |   7907494111 |      1.57163
HOST-Info: Transfer_9     | mem (H<->G)   |   7907499426 |   7907589321 |     0.089895
HOST-Info: Transfer_10    | mem (H<->G)   |   7907527437 |   7909133863 |      1.60643
HOST-Info: Transfer_11    | mem (H<->G)   |   7907594818 |   7907697407 |     0.102589
HOST-Info: Transfer_12    | mem (H<->G)   |   7907702617 |   7909236071 |      1.53345
HOST-Info: Transfer_13    | mem (H<->G)   |   7909139352 |   7909157956 |     0.018604
HOST-Info: Transfer_14    | mem (H<->G)   |   7909161978 |   7910761054 |      1.59908
HOST-Info: Transfer_15    | mem (H<->G)   |   7909241478 |   7909312818 |      0.07134
HOST-Info: Transfer_16    | mem (H<->G)   |   7909313954 |   7910888184 |      1.57423
HOST-Info: Transfer_17    | mem (H<->G)   |   7910766889 |   7910783208 |     0.016319
HOST-Info: Transfer_18    | mem (H<->G)   |   7910787029 |   7912445163 |      1.65813
HOST-Info: Transfer_19    | mem (H<->G)   |   7910889322 |   7910902123 |     0.012801
HOST-Info: Transfer_20    | mem (H<->G)   |   7910904881 |   7912449641 |      1.54476
HOST-Info: Transfer_21    | mem (H<->G)   |   7912450974 |   7912463389 |     0.012415
HOST-Info: Transfer_22    | mem (H<->G)   |   7912452058 |   7914176305 |      1.72425
HOST-Info: Transfer_23    | mem (H<->G)   |   7912464841 |   7912475066 |     0.010225
HOST-Info: Transfer_24    | mem (H<->G)   |   7912475945 |   7914186436 |      1.71049
HOST-Info: Transfer_25    | mem (H<->G)   |   7914186482 |   7914238909 |     0.052427
HOST-Info: Transfer_26    | mem (H<->G)   |   7914202322 |   7916001143 |      1.79882
HOST-Info: Transfer_27    | mem (H<->G)   |   7914248412 |   7914276707 |     0.028295
HOST-Info: Transfer_28    | mem (H<->G)   |   7914281816 |   7916005528 |      1.72371
HOST-Info: Transfer_29    | mem (H<->G)   |   7916004594 |   7916013274 |      0.00868
HOST-Info: Transfer_30    | mem (H<->G)   |   7916007016 |   7917711545 |      1.70453
HOST-Info: Transfer_31    | mem (H<->G)   |   7916014876 |   7916023436 |      0.00856
HOST-Info: Transfer_32    | mem (H<->G)   |   7916024153 |   7917725595 |      1.70144
HOST-Info: Transfer_33    | mem (H<->G)   |   7917713560 |   7917722085 |     0.008525
HOST-Info: Transfer_34    | mem (H<->G)   |   8096456238 |   8096650553 |     0.194315
HOST-Info: -------------------------------------------------------------------------------
HOST-Info:     Kernels Execution Time (ms) :  178.595  (kernel_phi_mlp'end - kernel_phi_mlp'begin)
HOST-Info: Application Execution Time (ms) :  193.974  (Transfer_34'end - Transfer_1'begin)
HOST-Info: -------------------------------------------------------------------------------