#define HIDDEN_SIZE 2560
#define NUM_BLOCKS 8
#define BLOCK_SIZE (HIDDEN_SIZE / NUM_BLOCKS)

extern "C" {
    void kernel_phi_linear(
        // float out[HIDDEN_SIZE],
        // float in[HIDDEN_SIZE],
        // float weight[HIDDEN_SIZE * HIDDEN_SIZE],
        // float bias[HIDDEN_SIZE]
        float* out,
        float* in,
        float* weight,
        float* bias
    ) {
        #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem1 depth=2560 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=weight offset=slave bundle=gmem2 depth=6553600 max_read_burst_length=256
        #pragma HLS INTERFACE m_axi port=bias offset=slave bundle=gmem3 depth=2560 max_read_burst_length=256

        #pragma HLS INTERFACE s_axilite port=out bundle=control
        #pragma HLS INTERFACE s_axilite port=in bundle=control
        #pragma HLS INTERFACE s_axilite port=weight bundle=control
        #pragma HLS INTERFACE s_axilite port=bias bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control

        // 壓縮並存放到 local buffer
        // Local buffers for input slice and weight block
        float local_in[HIDDEN_SIZE];
        float local_w[BLOCK_SIZE * HIDDEN_SIZE];

        // 初始化 output = bias
        init_out:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            out[i] = bias[i];
        }

        load_in:
        for (int i = 0; i < HIDDEN_SIZE; i++) {
            #pragma HLS PIPELINE II=1
            local_in[i] = in[i];
        }

        // 分批次計算
        block_loop:
        for (int block = 0; block < NUM_BLOCKS; block++) {

            // Load weight block
            load_w:
            for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    #pragma HLS PIPELINE II=1
                    local_w[i * HIDDEN_SIZE + j] = weight[(block * BLOCK_SIZE + i) * HIDDEN_SIZE + j];
                }
            }

            // 計算並累加結果
            compute:
            for (int i = 0; i < BLOCK_SIZE; i++) {
                #pragma HLS PIPELINE II=1
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    out[block * BLOCK_SIZE + i] += local_in[j] * local_w[i * HIDDEN_SIZE + j];
                }
            }
        }
    }
}