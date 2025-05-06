// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xmat_mul.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMat_mul_CfgInitialize(XMat_mul *InstancePtr, XMat_mul_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMat_mul_Start(XMat_mul *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMat_mul_ReadReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_AP_CTRL) & 0x80;
    XMat_mul_WriteReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMat_mul_IsDone(XMat_mul *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMat_mul_ReadReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMat_mul_IsIdle(XMat_mul *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMat_mul_ReadReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMat_mul_IsReady(XMat_mul *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMat_mul_ReadReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMat_mul_Continue(XMat_mul *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMat_mul_ReadReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_AP_CTRL) & 0x80;
    XMat_mul_WriteReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XMat_mul_EnableAutoRestart(XMat_mul *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMat_mul_WriteReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XMat_mul_DisableAutoRestart(XMat_mul *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMat_mul_WriteReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_AP_CTRL, 0);
}

void XMat_mul_InterruptGlobalEnable(XMat_mul *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMat_mul_WriteReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_GIE, 1);
}

void XMat_mul_InterruptGlobalDisable(XMat_mul *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMat_mul_WriteReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_GIE, 0);
}

void XMat_mul_InterruptEnable(XMat_mul *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMat_mul_ReadReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_IER);
    XMat_mul_WriteReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_IER, Register | Mask);
}

void XMat_mul_InterruptDisable(XMat_mul *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMat_mul_ReadReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_IER);
    XMat_mul_WriteReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_IER, Register & (~Mask));
}

void XMat_mul_InterruptClear(XMat_mul *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMat_mul_WriteReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_ISR, Mask);
}

u32 XMat_mul_InterruptGetEnabled(XMat_mul *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMat_mul_ReadReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_IER);
}

u32 XMat_mul_InterruptGetStatus(XMat_mul *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMat_mul_ReadReg(InstancePtr->Control_BaseAddress, XMAT_MUL_CONTROL_ADDR_ISR);
}

