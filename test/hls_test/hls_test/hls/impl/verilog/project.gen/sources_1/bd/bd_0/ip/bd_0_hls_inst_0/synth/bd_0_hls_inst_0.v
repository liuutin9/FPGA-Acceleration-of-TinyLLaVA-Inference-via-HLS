// (c) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// (c) Copyright 2022-2025 Advanced Micro Devices, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of AMD and is protected under U.S. and international copyright
// and other intellectual property laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// AMD, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND AMD HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) AMD shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or AMD had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// AMD products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of AMD products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: xilinx.com:hls:mat_mul:1.0
// IP Revision: 2114071781

(* X_CORE_INFO = "mat_mul,Vivado 2024.2" *)
(* CHECK_LICENSE_TYPE = "bd_0_hls_inst_0,mat_mul,{}" *)
(* CORE_GENERATION_INFO = "bd_0_hls_inst_0,mat_mul,{x_ipProduct=Vivado 2024.2,x_ipVendor=xilinx.com,x_ipLibrary=hls,x_ipName=mat_mul,x_ipVersion=1.0,x_ipCoreRevision=2114071781,x_ipLanguage=VERILOG,x_ipSimLanguage=MIXED,C_S_AXI_CONTROL_ADDR_WIDTH=4,C_S_AXI_CONTROL_DATA_WIDTH=32}" *)
(* IP_DEFINITION_SOURCE = "HLS" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module bd_0_hls_inst_0 (
  s_axi_control_ARADDR,
  s_axi_control_ARREADY,
  s_axi_control_ARVALID,
  s_axi_control_AWADDR,
  s_axi_control_AWREADY,
  s_axi_control_AWVALID,
  s_axi_control_BREADY,
  s_axi_control_BRESP,
  s_axi_control_BVALID,
  s_axi_control_RDATA,
  s_axi_control_RREADY,
  s_axi_control_RRESP,
  s_axi_control_RVALID,
  s_axi_control_WDATA,
  s_axi_control_WREADY,
  s_axi_control_WSTRB,
  s_axi_control_WVALID,
  ap_clk,
  ap_rst_n,
  interrupt,
  in1_Addr_A,
  in1_Clk_A,
  in1_Din_A,
  in1_Dout_A,
  in1_EN_A,
  in1_Rst_A,
  in1_WEN_A,
  in1_Addr_B,
  in1_Clk_B,
  in1_Din_B,
  in1_Dout_B,
  in1_EN_B,
  in1_Rst_B,
  in1_WEN_B,
  in2_Addr_A,
  in2_Clk_A,
  in2_Din_A,
  in2_Dout_A,
  in2_EN_A,
  in2_Rst_A,
  in2_WEN_A,
  in2_Addr_B,
  in2_Clk_B,
  in2_Din_B,
  in2_Dout_B,
  in2_EN_B,
  in2_Rst_B,
  in2_WEN_B,
  out_r_Addr_A,
  out_r_Clk_A,
  out_r_Din_A,
  out_r_Dout_A,
  out_r_EN_A,
  out_r_Rst_A,
  out_r_WEN_A
);

(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARADDR" *)
(* X_INTERFACE_MODE = "slave" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_control, ADDR_WIDTH 4, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 300000000.0, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, NUM_READ_THREADS 1, NUM_WRITE_THREAD\
S 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
input wire [3 : 0] s_axi_control_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARREADY" *)
output wire s_axi_control_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARVALID" *)
input wire s_axi_control_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWADDR" *)
input wire [3 : 0] s_axi_control_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWREADY" *)
output wire s_axi_control_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWVALID" *)
input wire s_axi_control_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BREADY" *)
input wire s_axi_control_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BRESP" *)
output wire [1 : 0] s_axi_control_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BVALID" *)
output wire s_axi_control_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RDATA" *)
output wire [31 : 0] s_axi_control_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RREADY" *)
input wire s_axi_control_RREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RRESP" *)
output wire [1 : 0] s_axi_control_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RVALID" *)
output wire s_axi_control_RVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WDATA" *)
input wire [31 : 0] s_axi_control_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WREADY" *)
output wire s_axi_control_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WSTRB" *)
input wire [3 : 0] s_axi_control_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WVALID" *)
input wire s_axi_control_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *)
(* X_INTERFACE_MODE = "slave" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF s_axi_control, ASSOCIATED_RESET ap_rst_n, FREQ_HZ 300000000.0, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, INSERT_VIP 0" *)
input wire ap_clk;
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *)
(* X_INTERFACE_MODE = "slave" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0" *)
input wire ap_rst_n;
(* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT" *)
(* X_INTERFACE_MODE = "master" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, PortWidth 1" *)
output wire interrupt;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA ADDR" *)
(* X_INTERFACE_MODE = "master" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *)
output wire [31 : 0] in1_Addr_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA CLK" *)
output wire in1_Clk_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DIN" *)
output wire [31 : 0] in1_Din_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DOUT" *)
input wire [31 : 0] in1_Dout_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA EN" *)
output wire in1_EN_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA RST" *)
output wire in1_Rst_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA WE" *)
output wire [3 : 0] in1_WEN_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB ADDR" *)
(* X_INTERFACE_MODE = "master" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *)
output wire [31 : 0] in1_Addr_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB CLK" *)
output wire in1_Clk_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DIN" *)
output wire [31 : 0] in1_Din_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DOUT" *)
input wire [31 : 0] in1_Dout_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB EN" *)
output wire in1_EN_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB RST" *)
output wire in1_Rst_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB WE" *)
output wire [3 : 0] in1_WEN_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA ADDR" *)
(* X_INTERFACE_MODE = "master" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *)
output wire [31 : 0] in2_Addr_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA CLK" *)
output wire in2_Clk_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DIN" *)
output wire [31 : 0] in2_Din_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DOUT" *)
input wire [31 : 0] in2_Dout_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA EN" *)
output wire in2_EN_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA RST" *)
output wire in2_Rst_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA WE" *)
output wire [3 : 0] in2_WEN_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB ADDR" *)
(* X_INTERFACE_MODE = "master" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *)
output wire [31 : 0] in2_Addr_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB CLK" *)
output wire in2_Clk_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DIN" *)
output wire [31 : 0] in2_Din_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DOUT" *)
input wire [31 : 0] in2_Dout_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB EN" *)
output wire in2_EN_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB RST" *)
output wire in2_Rst_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB WE" *)
output wire [3 : 0] in2_WEN_B;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA ADDR" *)
(* X_INTERFACE_MODE = "master" *)
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME out_r_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *)
output wire [31 : 0] out_r_Addr_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA CLK" *)
output wire out_r_Clk_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DIN" *)
output wire [31 : 0] out_r_Din_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DOUT" *)
input wire [31 : 0] out_r_Dout_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA EN" *)
output wire out_r_EN_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA RST" *)
output wire out_r_Rst_A;
(* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA WE" *)
output wire [3 : 0] out_r_WEN_A;

(* SDX_KERNEL = "true" *)
(* SDX_KERNEL_TYPE = "hls" *)
(* SDX_KERNEL_SYNTH_INST = "inst" *)
  mat_mul #(
    .C_S_AXI_CONTROL_ADDR_WIDTH(4),
    .C_S_AXI_CONTROL_DATA_WIDTH(32)
  ) inst (
    .s_axi_control_ARADDR(s_axi_control_ARADDR),
    .s_axi_control_ARREADY(s_axi_control_ARREADY),
    .s_axi_control_ARVALID(s_axi_control_ARVALID),
    .s_axi_control_AWADDR(s_axi_control_AWADDR),
    .s_axi_control_AWREADY(s_axi_control_AWREADY),
    .s_axi_control_AWVALID(s_axi_control_AWVALID),
    .s_axi_control_BREADY(s_axi_control_BREADY),
    .s_axi_control_BRESP(s_axi_control_BRESP),
    .s_axi_control_BVALID(s_axi_control_BVALID),
    .s_axi_control_RDATA(s_axi_control_RDATA),
    .s_axi_control_RREADY(s_axi_control_RREADY),
    .s_axi_control_RRESP(s_axi_control_RRESP),
    .s_axi_control_RVALID(s_axi_control_RVALID),
    .s_axi_control_WDATA(s_axi_control_WDATA),
    .s_axi_control_WREADY(s_axi_control_WREADY),
    .s_axi_control_WSTRB(s_axi_control_WSTRB),
    .s_axi_control_WVALID(s_axi_control_WVALID),
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .interrupt(interrupt),
    .in1_Addr_A(in1_Addr_A),
    .in1_Clk_A(in1_Clk_A),
    .in1_Din_A(in1_Din_A),
    .in1_Dout_A(in1_Dout_A),
    .in1_EN_A(in1_EN_A),
    .in1_Rst_A(in1_Rst_A),
    .in1_WEN_A(in1_WEN_A),
    .in1_Addr_B(in1_Addr_B),
    .in1_Clk_B(in1_Clk_B),
    .in1_Din_B(in1_Din_B),
    .in1_Dout_B(in1_Dout_B),
    .in1_EN_B(in1_EN_B),
    .in1_Rst_B(in1_Rst_B),
    .in1_WEN_B(in1_WEN_B),
    .in2_Addr_A(in2_Addr_A),
    .in2_Clk_A(in2_Clk_A),
    .in2_Din_A(in2_Din_A),
    .in2_Dout_A(in2_Dout_A),
    .in2_EN_A(in2_EN_A),
    .in2_Rst_A(in2_Rst_A),
    .in2_WEN_A(in2_WEN_A),
    .in2_Addr_B(in2_Addr_B),
    .in2_Clk_B(in2_Clk_B),
    .in2_Din_B(in2_Din_B),
    .in2_Dout_B(in2_Dout_B),
    .in2_EN_B(in2_EN_B),
    .in2_Rst_B(in2_Rst_B),
    .in2_WEN_B(in2_WEN_B),
    .out_r_Addr_A(out_r_Addr_A),
    .out_r_Clk_A(out_r_Clk_A),
    .out_r_Din_A(out_r_Din_A),
    .out_r_Dout_A(out_r_Dout_A),
    .out_r_EN_A(out_r_EN_A),
    .out_r_Rst_A(out_r_Rst_A),
    .out_r_WEN_A(out_r_WEN_A)
  );
endmodule
