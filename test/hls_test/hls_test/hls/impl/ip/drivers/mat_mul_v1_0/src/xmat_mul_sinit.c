// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xmat_mul.h"

extern XMat_mul_Config XMat_mul_ConfigTable[];

#ifdef SDT
XMat_mul_Config *XMat_mul_LookupConfig(UINTPTR BaseAddress) {
	XMat_mul_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XMat_mul_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XMat_mul_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XMat_mul_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMat_mul_Initialize(XMat_mul *InstancePtr, UINTPTR BaseAddress) {
	XMat_mul_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMat_mul_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMat_mul_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XMat_mul_Config *XMat_mul_LookupConfig(u16 DeviceId) {
	XMat_mul_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMAT_MUL_NUM_INSTANCES; Index++) {
		if (XMat_mul_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMat_mul_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMat_mul_Initialize(XMat_mul *InstancePtr, u16 DeviceId) {
	XMat_mul_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMat_mul_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMat_mul_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

