// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
# 1 "C:/Users/liuut/Desktop/Project/test/hls_test/mat_mul.cpp"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 420 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/liuut/Desktop/Project/test/hls_test/mat_mul.cpp" 2


void mat_mul(int in1[4][4], int in2[4][4], int out[4][4]) {
#pragma HLS INTERFACE port=return mode=s_axilite
#pragma HLS INTERFACE port=in1 mode=bram
#pragma HLS INTERFACE port=in2 mode=bram
#pragma HLS INTERFACE port=out mode=bram

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int sum = 0;
            for (int k = 0; k < 4; k++) {
#pragma HLS UNROLL factor=2
                sum += in1[i][k] * in2[k][j];
            }
            out[i][j] = sum;
        }
    }

}
#ifndef HLS_FASTSIM
#ifdef __cplusplus
extern "C"
#endif
void apatb_mat_mul_ir(int (*)[4], int (*)[4], int (*)[4]);
#ifdef __cplusplus
extern "C"
#endif
void mat_mul_hw_stub(int (*in1)[4], int (*in2)[4], int (*out)[4]){
mat_mul(in1, in2, out);
return ;
}
#ifdef __cplusplus
extern "C"
#endif
void refine_signal_handler();
#ifdef __cplusplus
extern "C"
#endif
void apatb_mat_mul_sw(int (*in1)[4], int (*in2)[4], int (*out)[4]){
refine_signal_handler();
apatb_mat_mul_ir(in1, in2, out);
return ;
}
#endif
# 20 "C:/Users/liuut/Desktop/Project/test/hls_test/mat_mul.cpp"

