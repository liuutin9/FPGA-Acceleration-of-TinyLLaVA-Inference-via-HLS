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
typedef ap_fixed<40,16> fixed40_16;
// typedef float fixed32_14;
typedef ap_uint<16>  uint16;

const float kGeluBeta = M_SQRT2 * M_2_SQRTPI * 0.5;
const float kGeluKappa = 0.044715;

void new_gelu(fixed40_16* out, float x) {
    float x_cube = x * x * x;
    float inner = kGeluBeta * (x + kGeluKappa * x_cube);
    float tanh_inner = hls::tanh(inner);
    *out = fixed40_16(0.5f * x * (1.0f + tanh_inner));
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
        float local_in_buf[HIDDEN_SIZE];
        float local_out_buf[HIDDEN_SIZE];
        fixed40_16 local_linear_1_in[HIDDEN_SIZE];
        fixed40_16 local_linear_1_out[INTERMEDIATE_SIZE];
        fixed40_16 local_linear_2_out[HIDDEN_SIZE];
        half local_bias[INTERMEDIATE_SIZE];
        half local_w_0[HIDDEN_SIZE];
        half local_w_1[HIDDEN_SIZE];
        half local_w_2[HIDDEN_SIZE];
        half local_w_3[HIDDEN_SIZE];
        half local_w_4[HIDDEN_SIZE];
        half local_w_5[HIDDEN_SIZE];
        half local_w_6[HIDDEN_SIZE];
        half local_w_7[HIDDEN_SIZE];
        fixed40_16 gelu_buf[8];
        fixed40_16 fc2_in_buf[8];

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
			local_linear_1_in[i] = fixed40_16(local_in_buf[i]);
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
			local_linear_1_out[i] = fixed40_16(local_bias[i]);
		}

		mlp_load_fc2_bias_0:
		for (int b = 0; b < HIDDEN_SIZE / 2 / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((uint16*)&local_bias[b * BURST_LEN + 0 * HIDDEN_SIZE / 2], (uint16*)&bias_fc2_0[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
			memcpy((uint16*)&local_bias[b * BURST_LEN + 1 * HIDDEN_SIZE / 2], (uint16*)&bias_fc2_1[b * BURST_LEN], sizeof(uint16) * BURST_LEN);
		}

		mlp_fc2_half_to_float:
		for (int i = 0; i < HIDDEN_SIZE; i++) {
			#pragma HLS PIPELINE II=1
			#pragma HLS UNROLL factor=2
			local_linear_2_out[i] = fixed40_16(local_bias[i]);
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
				gelu_buf[0] += local_linear_1_in[j] * fixed40_16(local_w_0[j]);
				gelu_buf[1] += local_linear_1_in[j] * fixed40_16(local_w_1[j]);
				gelu_buf[2] += local_linear_1_in[j] * fixed40_16(local_w_2[j]);
				gelu_buf[3] += local_linear_1_in[j] * fixed40_16(local_w_3[j]);
                gelu_buf[4] += local_linear_1_in[j] * fixed40_16(local_w_4[j]);
                gelu_buf[5] += local_linear_1_in[j] * fixed40_16(local_w_5[j]);
                gelu_buf[6] += local_linear_1_in[j] * fixed40_16(local_w_6[j]);
                gelu_buf[7] += local_linear_1_in[j] * fixed40_16(local_w_7[j]);
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
				local_linear_2_out[j] += ((fc2_in_buf[0] * fixed40_16(local_w_0[j]) + fc2_in_buf[1] * fixed40_16(local_w_1[j]))
									   + (fc2_in_buf[2] * fixed40_16(local_w_2[j]) + fc2_in_buf[3] * fixed40_16(local_w_3[j])))
                                       + ((fc2_in_buf[4] * fixed40_16(local_w_4[j]) + fc2_in_buf[5] * fixed40_16(local_w_5[j]))
									   + (fc2_in_buf[6] * fixed40_16(local_w_6[j]) + fc2_in_buf[7] * fixed40_16(local_w_7[j])));
			}
		}

        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            local_out_buf[i] = float(local_linear_2_out[i]);
        }

        mlp_store_output:
		for (int b = 0; b < HIDDEN_SIZE / BURST_LEN; b++) {
			#pragma HLS DATAFLOW
			memcpy((float*)&out[b * BURST_LEN], (float*)&local_out_buf[b * BURST_LEN], sizeof(float) * BURST_LEN);
		}
    }
}


Elapsed time: 801.273780 seconds
Elapsed time: 3.986437 seconds/token
HOST-Info: Output:
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr
```

### Exercise 2: Implement a function to sort a list of tuples based on the second element of each tuple using bubble sort.

Hint: You can access the second element of a tuple using indexing `[1]`.

```python
def bubble_sort_tuples(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j][1] > arr[j+1][1]:
                
HOST-Info: Finish generation!