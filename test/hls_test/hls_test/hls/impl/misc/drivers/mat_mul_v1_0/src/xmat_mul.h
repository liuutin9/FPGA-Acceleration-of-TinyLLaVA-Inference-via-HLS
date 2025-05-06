// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XMAT_MUL_H
#define XMAT_MUL_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xmat_mul_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XMat_mul_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XMat_mul;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMat_mul_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMat_mul_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMat_mul_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMat_mul_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XMat_mul_Initialize(XMat_mul *InstancePtr, UINTPTR BaseAddress);
XMat_mul_Config* XMat_mul_LookupConfig(UINTPTR BaseAddress);
#else
int XMat_mul_Initialize(XMat_mul *InstancePtr, u16 DeviceId);
XMat_mul_Config* XMat_mul_LookupConfig(u16 DeviceId);
#endif
int XMat_mul_CfgInitialize(XMat_mul *InstancePtr, XMat_mul_Config *ConfigPtr);
#else
int XMat_mul_Initialize(XMat_mul *InstancePtr, const char* InstanceName);
int XMat_mul_Release(XMat_mul *InstancePtr);
#endif

void XMat_mul_Start(XMat_mul *InstancePtr);
u32 XMat_mul_IsDone(XMat_mul *InstancePtr);
u32 XMat_mul_IsIdle(XMat_mul *InstancePtr);
u32 XMat_mul_IsReady(XMat_mul *InstancePtr);
void XMat_mul_Continue(XMat_mul *InstancePtr);
void XMat_mul_EnableAutoRestart(XMat_mul *InstancePtr);
void XMat_mul_DisableAutoRestart(XMat_mul *InstancePtr);


void XMat_mul_InterruptGlobalEnable(XMat_mul *InstancePtr);
void XMat_mul_InterruptGlobalDisable(XMat_mul *InstancePtr);
void XMat_mul_InterruptEnable(XMat_mul *InstancePtr, u32 Mask);
void XMat_mul_InterruptDisable(XMat_mul *InstancePtr, u32 Mask);
void XMat_mul_InterruptClear(XMat_mul *InstancePtr, u32 Mask);
u32 XMat_mul_InterruptGetEnabled(XMat_mul *InstancePtr);
u32 XMat_mul_InterruptGetStatus(XMat_mul *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
