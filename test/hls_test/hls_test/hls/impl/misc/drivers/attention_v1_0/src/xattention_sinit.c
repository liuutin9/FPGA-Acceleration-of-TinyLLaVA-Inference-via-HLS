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
#include "xattention.h"

extern XAttention_Config XAttention_ConfigTable[];

#ifdef SDT
XAttention_Config *XAttention_LookupConfig(UINTPTR BaseAddress) {
	XAttention_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XAttention_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XAttention_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XAttention_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAttention_Initialize(XAttention *InstancePtr, UINTPTR BaseAddress) {
	XAttention_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAttention_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAttention_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XAttention_Config *XAttention_LookupConfig(u16 DeviceId) {
	XAttention_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XATTENTION_NUM_INSTANCES; Index++) {
		if (XAttention_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XAttention_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAttention_Initialize(XAttention *InstancePtr, u16 DeviceId) {
	XAttention_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAttention_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAttention_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

