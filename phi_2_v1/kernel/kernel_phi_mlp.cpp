#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_half.h>
#include <ap_int.h>

#define HIDDEN_SIZE 2560
#define INTERMEDIATE_SIZE 10240
#define M_SQRT2 1.41421356237309504880
#define M_2_SQRTPI 1.12837916709551257390

typedef ap_fixed<32,14> fixed32_14;

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
        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem4 depth=2560 max_read_burst_length=256
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
        fixed32_14 local_linear_2_in[INTERMEDIATE_SIZE];

		#pragma HLS bind_storage variable=local_linear_1_in type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_1_out type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_2_in type=RAM_T2P impl=uram
		#pragma HLS bind_storage variable=local_linear_2_out type=RAM_T2P impl=uram

        mlp_load_fc1_input:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
        	local_linear_1_in[i] = in[i];
        }

        mlp_load_fc1_bias_1:
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
			#pragma HLS PIPELINE II=1
        	local_linear_1_out[i + 0 * INTERMEDIATE_SIZE / 8] = fixed32_14(bias_fc1_0[i]);
        	local_linear_1_out[i + 1 * INTERMEDIATE_SIZE / 8] = fixed32_14(bias_fc1_1[i]);
        	local_linear_1_out[i + 2 * INTERMEDIATE_SIZE / 8] = fixed32_14(bias_fc1_2[i]);
        	local_linear_1_out[i + 3 * INTERMEDIATE_SIZE / 8] = fixed32_14(bias_fc1_3[i]);
        }

        mlp_load_fc1_bias_2:
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
			#pragma HLS PIPELINE II=1
			local_linear_1_out[i + 4 * INTERMEDIATE_SIZE / 8] = fixed32_14(bias_fc1_4[i]);
			local_linear_1_out[i + 5 * INTERMEDIATE_SIZE / 8] = fixed32_14(bias_fc1_5[i]);
			local_linear_1_out[i + 6 * INTERMEDIATE_SIZE / 8] = fixed32_14(bias_fc1_6[i]);
			local_linear_1_out[i + 7 * INTERMEDIATE_SIZE / 8] = fixed32_14(bias_fc1_7[i]);
		}

        mlp_compute_fc1_1:
        for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_1_out[i + 0 * INTERMEDIATE_SIZE / 8] += local_linear_1_in[j] * fixed32_14(weight_fc1_0[i]);
				local_linear_1_out[i + 1 * INTERMEDIATE_SIZE / 8] += local_linear_1_in[j] * fixed32_14(weight_fc1_1[i]);
				local_linear_1_out[i + 2 * INTERMEDIATE_SIZE / 8] += local_linear_1_in[j] * fixed32_14(weight_fc1_2[i]);
				local_linear_1_out[i + 3 * INTERMEDIATE_SIZE / 8] += local_linear_1_in[j] * fixed32_14(weight_fc1_3[i]);
			}
        }

        mlp_compute_fc1_2:
		for (int i = 0; i < INTERMEDIATE_SIZE / 8; i++) {
			for (int j = 0; j < HIDDEN_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_1_out[i + 4 * INTERMEDIATE_SIZE / 8] += local_linear_1_in[j] * fixed32_14(weight_fc1_4[i]);
				local_linear_1_out[i + 5 * INTERMEDIATE_SIZE / 8] += local_linear_1_in[j] * fixed32_14(weight_fc1_5[i]);
				local_linear_1_out[i + 6 * INTERMEDIATE_SIZE / 8] += local_linear_1_in[j] * fixed32_14(weight_fc1_6[i]);
				local_linear_1_out[i + 7 * INTERMEDIATE_SIZE / 8] += local_linear_1_in[j] * fixed32_14(weight_fc1_7[i]);
			}
		}

        mlp_compute_new_gelu:
        for (int i = 0; i < INTERMEDIATE_SIZE; i++) {
			#pragma HLS PIPELINE II=1
        	new_gelu(&local_linear_2_in[i], (float)local_linear_1_out[i]);
        }

        mlp_load_fc2_bias_1:
        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
			#pragma HLS PIPELINE II=1
			local_linear_2_out[i + 0 * HIDDEN_SIZE / 8] = fixed32_14(bias_fc2_0[i]);
			local_linear_2_out[i + 1 * HIDDEN_SIZE / 8] = fixed32_14(bias_fc2_1[i]);
			local_linear_2_out[i + 2 * HIDDEN_SIZE / 8] = fixed32_14(bias_fc2_2[i]);
			local_linear_2_out[i + 3 * HIDDEN_SIZE / 8] = fixed32_14(bias_fc2_3[i]);
		}

        mlp_load_fc2_bias_2:
		for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
			#pragma HLS PIPELINE II=1
			local_linear_2_out[i + 4 * HIDDEN_SIZE / 8] = fixed32_14(bias_fc2_4[i]);
			local_linear_2_out[i + 5 * HIDDEN_SIZE / 8] = fixed32_14(bias_fc2_5[i]);
			local_linear_2_out[i + 6 * HIDDEN_SIZE / 8] = fixed32_14(bias_fc2_6[i]);
			local_linear_2_out[i + 7 * HIDDEN_SIZE / 8] = fixed32_14(bias_fc2_7[i]);
		}

        mlp_compute_fc2_1:
        for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
			for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_2_out[i + 0 * HIDDEN_SIZE / 8] += local_linear_2_in[j] * fixed32_14(weight_fc2_0[i]);
				local_linear_2_out[i + 1 * HIDDEN_SIZE / 8] += local_linear_2_in[j] * fixed32_14(weight_fc2_1[i]);
				local_linear_2_out[i + 2 * HIDDEN_SIZE / 8] += local_linear_2_in[j] * fixed32_14(weight_fc2_2[i]);
				local_linear_2_out[i + 3 * HIDDEN_SIZE / 8] += local_linear_2_in[j] * fixed32_14(weight_fc2_3[i]);
			}
		}

        mlp_compute_fc2_2:
		for (int i = 0; i < HIDDEN_SIZE / 8; i++) {
			for (int j = 0; j < INTERMEDIATE_SIZE; j++) {
				#pragma HLS PIPELINE II=1
				local_linear_2_out[i + 4 * HIDDEN_SIZE / 8] += local_linear_2_in[j] * fixed32_14(weight_fc2_4[i]);
				local_linear_2_out[i + 5 * HIDDEN_SIZE / 8] += local_linear_2_in[j] * fixed32_14(weight_fc2_5[i]);
				local_linear_2_out[i + 6 * HIDDEN_SIZE / 8] += local_linear_2_in[j] * fixed32_14(weight_fc2_6[i]);
				local_linear_2_out[i + 7 * HIDDEN_SIZE / 8] += local_linear_2_in[j] * fixed32_14(weight_fc2_7[i]);
			}
		}

        mlp_store_output:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
        	out[i] = local_linear_2_out[i];
        }
    }
}
