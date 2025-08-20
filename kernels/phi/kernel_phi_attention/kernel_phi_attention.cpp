#include <ap_fixed.h>
#include <hls_math.h>

#define HIDDEN_SIZE 2560
#define NUM_KEY_VALUE_HEADS 32
#define HEAD_DIM 80
#define SLEN 128

typedef ap_fixed<16,10> fixed16_10;

extern "C" {
    void kernel_phi_attention(
        float out_attention[NUM_ATTENTION_HEADS * HEAD_DIM],
        float in_q[NUM_KEY_VALUE_HEADS * HEAD_DIM],
        float in_k[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM],
        float in_v[NUM_KEY_VALUE_HEADS * SLEN * HEAD_DIM],
        int position_idx
    ) {

        #pragma HLS INTERFACE m_axi port=out_attention offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_q offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_k offset=slave bundle=gmem2 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in_v offset=slave bundle=gmem3 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=position_idx offset=slave bundle=gmem4 depth=1 max_read_burst_length=1

        #pragma HLS INTERFACE s_axilite port=out_attention bundle=control
        #pragma HLS INTERFACE s_axilite port=in_q bundle=control
        #pragma HLS INTERFACE s_axilite port=in_k bundle=control
        #pragma HLS INTERFACE s_axilite port=in_v bundle=control
        #pragma HLS INTERFACE s_axilite port=position_idx bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        fixed16_10 local_q_per_head[HEAD_DIM];
        fixed16_10 local_k_per_head[SLEN * HEAD_DIM];
        fixed16_10 local_v_per_head[SLEN * HEAD_DIM];
        fixed16_10 qkt[SLEN];
        int curr_len = position_idx + 1;

        #pragma HLS bind_storage variable=local_q_per_head type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=local_k_per_head type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=local_v_per_head type=RAM_T2P impl=bram
        #pragma HLS bind_storage variable=qkt type=RAM_T2P impl=bram

        #pragma HLS ARRAY_PARTITION variable=local_q_per_head cyclic factor=4 dim=1
        #pragma HLS ARRAY_PARTITION variable=local_k_per_head cyclic factor=4 dim=1
        #pragma HLS ARRAY_PARTITION variable=local_v_per_head cyclic factor=4 dim=1
        #pragma HLS ARRAY_PARTITION variable=qkt cyclic factor=4 dim=1

        float scaling = 0.1118033989f; // 1 / sqrt(HEAD_DIM)

        head_loop:
        for (int i = 0; i < NUM_KEY_VALUE_HEADS; i++) {
            load_q:
            for (int j = 0; j < HEAD_DIM; j++) {
                #pragma HLS PIPELINE II=1
                #pragma HLS UNROLL factor=4
                local_q_per_head[j] = in_q[i * HEAD_DIM + j];
            }
            load_kv:
            for (int j = 0; j < curr_len * HEAD_DIM; j++) {
                #pragma HLS PIPELINE II=1
                #pragma HLS UNROLL factor=4
                local_k_per_head[j] = in_k[i * SLEN * HEAD_DIM + j];
                local_v_per_head[j] = in_v[i * SLEN * HEAD_DIM + j];
            }
            compute_qkt:
            for (int j = 0; j < curr_len; j++) {
                fixed16_10 sum = 0;
                for (int k = 0; k < HEAD_DIM; k++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=4
                    sum += local_q_per_head[k] * local_k_per_head[j * HEAD_DIM + k];
                }
                qkt[j] = sum * scaling;
            }
            compute_softmax:
            fixed16_10 max_qkt = qkt[0];
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
                qkt[j] = fixed16_10(exp_qkt[j] / sum_exp);
            }
            compute_attention_output:
            for (int j = 0; j < curr_len; j++) {
                for (int k = 0; k < HEAD_DIM; k++) {
                    #pragma HLS PIPELINE II=1
                    #pragma HLS UNROLL factor=4
                    out_attention[i * HEAD_DIM + k] += qkt[j] * local_v_per_head[j * HEAD_DIM + k];
                }
            }
        }
    }
}