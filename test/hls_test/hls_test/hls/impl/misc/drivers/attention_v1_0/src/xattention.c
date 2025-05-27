// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xattention.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XAttention_CfgInitialize(XAttention *InstancePtr, XAttention_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XAttention_Start(XAttention *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_AP_CTRL) & 0x80;
    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XAttention_IsDone(XAttention *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XAttention_IsIdle(XAttention *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XAttention_IsReady(XAttention *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XAttention_Continue(XAttention *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_AP_CTRL) & 0x80;
    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XAttention_EnableAutoRestart(XAttention *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XAttention_DisableAutoRestart(XAttention *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_AP_CTRL, 0);
}

void XAttention_Set_d_k(XAttention *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_D_K_DATA, Data);
}

u32 XAttention_Get_d_k(XAttention *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_D_K_DATA);
    return Data;
}

void XAttention_InterruptGlobalEnable(XAttention *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_GIE, 1);
}

void XAttention_InterruptGlobalDisable(XAttention *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_GIE, 0);
}

void XAttention_InterruptEnable(XAttention *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_IER);
    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_IER, Register | Mask);
}

void XAttention_InterruptDisable(XAttention *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_IER);
    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_IER, Register & (~Mask));
}

void XAttention_InterruptClear(XAttention *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAttention_WriteReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_ISR, Mask);
}

u32 XAttention_InterruptGetEnabled(XAttention *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_IER);
}

u32 XAttention_InterruptGetStatus(XAttention *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAttention_ReadReg(InstancePtr->Control_BaseAddress, XATTENTION_CONTROL_ADDR_ISR);
}

