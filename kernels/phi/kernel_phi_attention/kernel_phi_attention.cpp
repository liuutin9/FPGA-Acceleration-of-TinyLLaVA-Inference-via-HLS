#include <ap_fixed.h>
#include <hls_math.h>

#define HIDDEN_SIZE 2560
#define NUM_KEY_VALUE_HEADS 32
#define HEAD_DIM 80
#define SLEN 832

typedef ap_fixed<32,14> fixed32_14;

extern "C" {
    void kernel_phi_attention(
        fixed32_14 out_attention[NUM_KEY_VALUE_HEADS * HEAD_DIM],
        fixed32_14 in_q[NUM_KEY_VALUE_HEADS * HEAD_DIM],
        fixed32_14 in_k_1[800 * NUM_KEY_VALUE_HEADS * HEAD_DIM],
        fixed32_14 in_v_1[800 * NUM_KEY_VALUE_HEADS * HEAD_DIM],
        fixed32_14 in_k_2[32 * NUM_KEY_VALUE_HEADS * HEAD_DIM],
        fixed32_14 in_v_2[32 * NUM_KEY_VALUE_HEADS * HEAD_DIM],
        int position_idx
    ) {

        #pragma HLS INTERFACE m_axi port=out_attention offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_q offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_k_1 offset=slave bundle=gmem2 depth=204800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_v_1 offset=slave bundle=gmem3 depth=204800 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_k_2 offset=slave bundle=gmem4 depth=81920 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_v_2 offset=slave bundle=gmem5 depth=81920 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=position_idx offset=slave bundle=gmem6 depth=1 max_read_burst_length=1

        #pragma HLS INTERFACE s_axilite port=out_attention bundle=control
        #pragma HLS INTERFACE s_axilite port=in_q bundle=control
        #pragma HLS INTERFACE s_axilite port=in_k_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=in_v_1 bundle=control
        #pragma HLS INTERFACE s_axilite port=in_k_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=in_v_2 bundle=control
        #pragma HLS INTERFACE s_axilite port=position_idx bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        fixed32_14 local_out_attention[NUM_KEY_VALUE_HEADS * HEAD_DIM];
        fixed32_14 local_q_per_head[HEAD_DIM];
        fixed32_14 local_k_per_head[SLEN * HEAD_DIM];
        fixed32_14 local_v_per_head[SLEN * HEAD_DIM];
        fixed32_14 qkt[SLEN];
        int curr_len = position_idx + 1;

        #pragma HLS bind_storage variable=local_out_attention type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=local_q_per_head type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=local_k_per_head type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=local_v_per_head type=RAM_T2P impl=uram
        #pragma HLS bind_storage variable=qkt type=RAM_T2P impl=bram

        fixed32_14 scaling = fixed32_14(0.1118033989f); // 1 / sqrt(HEAD_DIM)

        head_loop:
        for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
            load_q:
            for (int j = 0; j < HEAD_DIM; j++) {
                #pragma HLS PIPELINE II=1
                #pragma HLS UNROLL factor=2
                local_q_per_head[j] = in_q[i * HEAD_DIM + j];
            }
            load_kv:
            for (int j = 0; j < curr_len; j++) {
                for (int k = 0; k < HEAD_DIM; k++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=2
                    local_k_per_head[j * HEAD_DIM + k] = in_k_1[j * HIDDEN_SIZE + i * HEAD_DIM + k];
                    local_v_per_head[j * HEAD_DIM + k] = in_v_1[j * HIDDEN_SIZE + i * HEAD_DIM + k];
                }
            }
            if (curr_len > 800) {
                for (int j = 0; j < curr_len - 800; j++) {
                    for (int k = 0; k < HEAD_DIM; k++) {
                        #pragma HLS PIPELINE II=1
                        #pragma HLS UNROLL factor=2
                        local_k_per_head[(j + 800) * HEAD_DIM + k] = in_k_2[j * HIDDEN_SIZE + i * HEAD_DIM + k];
                        local_v_per_head[(j + 800) * HEAD_DIM + k] = in_v_2[j * HIDDEN_SIZE + i * HEAD_DIM + k];
                    }
                }
            }
            compute_qkt:
            for (int j = 0; j < curr_len; j++) {
                fixed32_14 sum = 0;
                for (int k = 0; k < HEAD_DIM; k++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=2
                    sum += local_q_per_head[k] * local_k_per_head[j * HEAD_DIM + k];
                }
                qkt[j] = sum * scaling;
            }
            compute_softmax:
            fixed32_14 max_qkt = qkt[0];
            for (int j = 1; j < curr_len; j++) {
                max_qkt = hls::max(max_qkt, qkt[j]);
            }
            float sum_exp = 0.0f;
            float exp_qkt[curr_len];
            for (int j = 0; j < curr_len; j++) {
                exp_qkt[j] = hls::exp(qkt[j] - max_qkt);
                sum_exp += exp_qkt[j];
            }
            for (int j = 0; j < curr_len; j++) {
                qkt[j] = fixed32_14(exp_qkt[j] / sum_exp);
            }
            compute_attention_output:
            for (int k = 0; k < HEAD_DIM; k++) {
                local_out_attention[i * HEAD_DIM + k] = fixed32_14(0.0f);
                for (int j = 0; j < curr_len; j++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=2
                    local_out_attention[i * HEAD_DIM + k] += qkt[j] * local_v_per_head[j * HEAD_DIM + k];
                }
            }
            for (int j = 0; j < curr_len; j++) {
                for (int k = 0; k < HEAD_DIM; k++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=2
                    local_out_attention[i * HEAD_DIM + k] = fixed32_14(0.0f);
                }
            }
            for (int j = 0; j < curr_len; j++) {
                for (int k = 0; k < HEAD_DIM; k++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=2
                    out_attention[i * HEAD_DIM + k] += qkt[j] * local_v_per_head[j * HEAD_DIM + k];
                }
            }
        }
        store_out:
        for (int i = 0; i < NUM_KEY_VALUE_HEADS * HEAD_DIM; i++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=2
            local_out_attention[i] = out_attention[i];
        }
    }
}