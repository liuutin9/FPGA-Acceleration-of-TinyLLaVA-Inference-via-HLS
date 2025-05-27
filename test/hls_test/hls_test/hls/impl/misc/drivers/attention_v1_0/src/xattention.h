// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XATTENTION_H
#define XATTENTION_H

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
#include "xattention_hw.h"

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
} XAttention_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XAttention;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XAttention_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XAttention_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XAttention_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XAttention_ReadReg(BaseAddress, RegOffset) \
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
int XAttention_Initialize(XAttention *InstancePtr, UINTPTR BaseAddress);
XAttention_Config* XAttention_LookupConfig(UINTPTR BaseAddress);
#else
int XAttention_Initialize(XAttention *InstancePtr, u16 DeviceId);
XAttention_Config* XAttention_LookupConfig(u16 DeviceId);
#endif
int XAttention_CfgInitialize(XAttention *InstancePtr, XAttention_Config *ConfigPtr);
#else
int XAttention_Initialize(XAttention *InstancePtr, const char* InstanceName);
int XAttention_Release(XAttention *InstancePtr);
#endif

void XAttention_Start(XAttention *InstancePtr);
u32 XAttention_IsDone(XAttention *InstancePtr);
u32 XAttention_IsIdle(XAttention *InstancePtr);
u32 XAttention_IsReady(XAttention *InstancePtr);
void XAttention_Continue(XAttention *InstancePtr);
void XAttention_EnableAutoRestart(XAttention *InstancePtr);
void XAttention_DisableAutoRestart(XAttention *InstancePtr);

void XAttention_Set_d_k(XAttention *InstancePtr, u32 Data);
u32 XAttention_Get_d_k(XAttention *InstancePtr);

void XAttention_InterruptGlobalEnable(XAttention *InstancePtr);
void XAttention_InterruptGlobalDisable(XAttention *InstancePtr);
void XAttention_InterruptEnable(XAttention *InstancePtr, u32 Mask);
void XAttention_InterruptDisable(XAttention *InstancePtr, u32 Mask);
void XAttention_InterruptClear(XAttention *InstancePtr, u32 Mask);
u32 XAttention_InterruptGetEnabled(XAttention *InstancePtr);
u32 XAttention_InterruptGetStatus(XAttention *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
