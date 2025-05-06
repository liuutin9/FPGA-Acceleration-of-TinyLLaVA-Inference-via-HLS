// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2024.2 (win64) Build 5239630 Fri Nov 08 22:35:27 MST 2024
// Date        : Tue May  6 19:44:00 2025
// Host        : Prestige14 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/Users/liuut/Desktop/Project/test/hls_test/hls_test/hls/impl/verilog/project.gen/sources_1/bd/bd_0/ip/bd_0_hls_inst_0/bd_0_hls_inst_0_sim_netlist.v
// Design      : bd_0_hls_inst_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xcu50-fsvh2104-2-e
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "bd_0_hls_inst_0,mat_mul,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* IP_DEFINITION_SOURCE = "HLS" *) 
(* X_CORE_INFO = "mat_mul,Vivado 2024.2" *) (* hls_module = "yes" *) 
(* NotValidForBitStream *)
module bd_0_hls_inst_0
   (s_axi_control_ARADDR,
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
    out_r_WEN_A);
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARADDR" *) (* X_INTERFACE_MODE = "slave" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_control, ADDR_WIDTH 4, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 300000000.0, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) input [3:0]s_axi_control_ARADDR;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARREADY" *) output s_axi_control_ARREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARVALID" *) input s_axi_control_ARVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWADDR" *) input [3:0]s_axi_control_AWADDR;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWREADY" *) output s_axi_control_AWREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWVALID" *) input s_axi_control_AWVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BREADY" *) input s_axi_control_BREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BRESP" *) output [1:0]s_axi_control_BRESP;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BVALID" *) output s_axi_control_BVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RDATA" *) output [31:0]s_axi_control_RDATA;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RREADY" *) input s_axi_control_RREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RRESP" *) output [1:0]s_axi_control_RRESP;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RVALID" *) output s_axi_control_RVALID;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WDATA" *) input [31:0]s_axi_control_WDATA;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WREADY" *) output s_axi_control_WREADY;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WSTRB" *) input [3:0]s_axi_control_WSTRB;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WVALID" *) input s_axi_control_WVALID;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *) (* X_INTERFACE_MODE = "slave" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF s_axi_control, ASSOCIATED_RESET ap_rst_n, FREQ_HZ 300000000.0, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, INSERT_VIP 0" *) input ap_clk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *) (* X_INTERFACE_MODE = "slave" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input ap_rst_n;
  (* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, PortWidth 1" *) output interrupt;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]in1_Addr_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA CLK" *) output in1_Clk_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DIN" *) output [31:0]in1_Din_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DOUT" *) input [31:0]in1_Dout_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA EN" *) output in1_EN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA RST" *) output in1_Rst_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA WE" *) output [3:0]in1_WEN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]in1_Addr_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB CLK" *) output in1_Clk_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DIN" *) output [31:0]in1_Din_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DOUT" *) input [31:0]in1_Dout_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB EN" *) output in1_EN_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB RST" *) output in1_Rst_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB WE" *) output [3:0]in1_WEN_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]in2_Addr_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA CLK" *) output in2_Clk_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DIN" *) output [31:0]in2_Din_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DOUT" *) input [31:0]in2_Dout_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA EN" *) output in2_EN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA RST" *) output in2_Rst_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA WE" *) output [3:0]in2_WEN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]in2_Addr_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB CLK" *) output in2_Clk_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DIN" *) output [31:0]in2_Din_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DOUT" *) input [31:0]in2_Dout_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB EN" *) output in2_EN_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB RST" *) output in2_Rst_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB WE" *) output [3:0]in2_WEN_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME out_r_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]out_r_Addr_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA CLK" *) output out_r_Clk_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DIN" *) output [31:0]out_r_Din_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DOUT" *) input [31:0]out_r_Dout_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA EN" *) output out_r_EN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA RST" *) output out_r_Rst_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA WE" *) output [3:0]out_r_WEN_A;

  wire \<const0> ;
  wire \<const1> ;
  wire ap_clk;
  wire ap_rst_n;
  wire [5:3]\^in1_Addr_A ;
  wire [5:3]\^in1_Addr_B ;
  wire in1_Clk_A;
  wire in1_Clk_B;
  wire [31:0]in1_Dout_A;
  wire [31:0]in1_Dout_B;
  wire in1_EN_A;
  wire in1_EN_B;
  wire in1_Rst_A;
  wire in1_Rst_B;
  wire [5:2]\^in2_Addr_A ;
  wire [5:2]\^in2_Addr_B ;
  wire in2_Clk_A;
  wire in2_Clk_B;
  wire [31:0]in2_Dout_A;
  wire [31:0]in2_Dout_B;
  wire in2_EN_A;
  wire in2_EN_B;
  wire in2_Rst_A;
  wire in2_Rst_B;
  wire interrupt;
  wire [5:2]\^out_r_Addr_A ;
  wire out_r_Clk_A;
  wire [31:0]out_r_Din_A;
  wire out_r_EN_A;
  wire out_r_Rst_A;
  wire [3:0]out_r_WEN_A;
  wire [3:0]s_axi_control_ARADDR;
  wire s_axi_control_ARREADY;
  wire s_axi_control_ARVALID;
  wire [3:0]s_axi_control_AWADDR;
  wire s_axi_control_AWREADY;
  wire s_axi_control_AWVALID;
  wire s_axi_control_BREADY;
  wire s_axi_control_BVALID;
  wire [9:0]\^s_axi_control_RDATA ;
  wire s_axi_control_RREADY;
  wire s_axi_control_RVALID;
  wire [31:0]s_axi_control_WDATA;
  wire s_axi_control_WREADY;
  wire [3:0]s_axi_control_WSTRB;
  wire s_axi_control_WVALID;
  wire [31:0]NLW_inst_in1_Addr_A_UNCONNECTED;
  wire [31:0]NLW_inst_in1_Addr_B_UNCONNECTED;
  wire [31:0]NLW_inst_in1_Din_A_UNCONNECTED;
  wire [31:0]NLW_inst_in1_Din_B_UNCONNECTED;
  wire [3:0]NLW_inst_in1_WEN_A_UNCONNECTED;
  wire [3:0]NLW_inst_in1_WEN_B_UNCONNECTED;
  wire [31:0]NLW_inst_in2_Addr_A_UNCONNECTED;
  wire [31:0]NLW_inst_in2_Addr_B_UNCONNECTED;
  wire [31:0]NLW_inst_in2_Din_A_UNCONNECTED;
  wire [31:0]NLW_inst_in2_Din_B_UNCONNECTED;
  wire [3:0]NLW_inst_in2_WEN_A_UNCONNECTED;
  wire [3:0]NLW_inst_in2_WEN_B_UNCONNECTED;
  wire [31:0]NLW_inst_out_r_Addr_A_UNCONNECTED;
  wire [1:0]NLW_inst_s_axi_control_BRESP_UNCONNECTED;
  wire [31:5]NLW_inst_s_axi_control_RDATA_UNCONNECTED;
  wire [1:0]NLW_inst_s_axi_control_RRESP_UNCONNECTED;

  assign in1_Addr_A[31] = \<const0> ;
  assign in1_Addr_A[30] = \<const0> ;
  assign in1_Addr_A[29] = \<const0> ;
  assign in1_Addr_A[28] = \<const0> ;
  assign in1_Addr_A[27] = \<const0> ;
  assign in1_Addr_A[26] = \<const0> ;
  assign in1_Addr_A[25] = \<const0> ;
  assign in1_Addr_A[24] = \<const0> ;
  assign in1_Addr_A[23] = \<const0> ;
  assign in1_Addr_A[22] = \<const0> ;
  assign in1_Addr_A[21] = \<const0> ;
  assign in1_Addr_A[20] = \<const0> ;
  assign in1_Addr_A[19] = \<const0> ;
  assign in1_Addr_A[18] = \<const0> ;
  assign in1_Addr_A[17] = \<const0> ;
  assign in1_Addr_A[16] = \<const0> ;
  assign in1_Addr_A[15] = \<const0> ;
  assign in1_Addr_A[14] = \<const0> ;
  assign in1_Addr_A[13] = \<const0> ;
  assign in1_Addr_A[12] = \<const0> ;
  assign in1_Addr_A[11] = \<const0> ;
  assign in1_Addr_A[10] = \<const0> ;
  assign in1_Addr_A[9] = \<const0> ;
  assign in1_Addr_A[8] = \<const0> ;
  assign in1_Addr_A[7] = \<const0> ;
  assign in1_Addr_A[6] = \<const0> ;
  assign in1_Addr_A[5:3] = \^in1_Addr_A [5:3];
  assign in1_Addr_A[2] = \<const1> ;
  assign in1_Addr_A[1] = \<const0> ;
  assign in1_Addr_A[0] = \<const0> ;
  assign in1_Addr_B[31] = \<const0> ;
  assign in1_Addr_B[30] = \<const0> ;
  assign in1_Addr_B[29] = \<const0> ;
  assign in1_Addr_B[28] = \<const0> ;
  assign in1_Addr_B[27] = \<const0> ;
  assign in1_Addr_B[26] = \<const0> ;
  assign in1_Addr_B[25] = \<const0> ;
  assign in1_Addr_B[24] = \<const0> ;
  assign in1_Addr_B[23] = \<const0> ;
  assign in1_Addr_B[22] = \<const0> ;
  assign in1_Addr_B[21] = \<const0> ;
  assign in1_Addr_B[20] = \<const0> ;
  assign in1_Addr_B[19] = \<const0> ;
  assign in1_Addr_B[18] = \<const0> ;
  assign in1_Addr_B[17] = \<const0> ;
  assign in1_Addr_B[16] = \<const0> ;
  assign in1_Addr_B[15] = \<const0> ;
  assign in1_Addr_B[14] = \<const0> ;
  assign in1_Addr_B[13] = \<const0> ;
  assign in1_Addr_B[12] = \<const0> ;
  assign in1_Addr_B[11] = \<const0> ;
  assign in1_Addr_B[10] = \<const0> ;
  assign in1_Addr_B[9] = \<const0> ;
  assign in1_Addr_B[8] = \<const0> ;
  assign in1_Addr_B[7] = \<const0> ;
  assign in1_Addr_B[6] = \<const0> ;
  assign in1_Addr_B[5:3] = \^in1_Addr_B [5:3];
  assign in1_Addr_B[2] = \<const0> ;
  assign in1_Addr_B[1] = \<const0> ;
  assign in1_Addr_B[0] = \<const0> ;
  assign in1_Din_A[31] = \<const0> ;
  assign in1_Din_A[30] = \<const0> ;
  assign in1_Din_A[29] = \<const0> ;
  assign in1_Din_A[28] = \<const0> ;
  assign in1_Din_A[27] = \<const0> ;
  assign in1_Din_A[26] = \<const0> ;
  assign in1_Din_A[25] = \<const0> ;
  assign in1_Din_A[24] = \<const0> ;
  assign in1_Din_A[23] = \<const0> ;
  assign in1_Din_A[22] = \<const0> ;
  assign in1_Din_A[21] = \<const0> ;
  assign in1_Din_A[20] = \<const0> ;
  assign in1_Din_A[19] = \<const0> ;
  assign in1_Din_A[18] = \<const0> ;
  assign in1_Din_A[17] = \<const0> ;
  assign in1_Din_A[16] = \<const0> ;
  assign in1_Din_A[15] = \<const0> ;
  assign in1_Din_A[14] = \<const0> ;
  assign in1_Din_A[13] = \<const0> ;
  assign in1_Din_A[12] = \<const0> ;
  assign in1_Din_A[11] = \<const0> ;
  assign in1_Din_A[10] = \<const0> ;
  assign in1_Din_A[9] = \<const0> ;
  assign in1_Din_A[8] = \<const0> ;
  assign in1_Din_A[7] = \<const0> ;
  assign in1_Din_A[6] = \<const0> ;
  assign in1_Din_A[5] = \<const0> ;
  assign in1_Din_A[4] = \<const0> ;
  assign in1_Din_A[3] = \<const0> ;
  assign in1_Din_A[2] = \<const0> ;
  assign in1_Din_A[1] = \<const0> ;
  assign in1_Din_A[0] = \<const0> ;
  assign in1_Din_B[31] = \<const0> ;
  assign in1_Din_B[30] = \<const0> ;
  assign in1_Din_B[29] = \<const0> ;
  assign in1_Din_B[28] = \<const0> ;
  assign in1_Din_B[27] = \<const0> ;
  assign in1_Din_B[26] = \<const0> ;
  assign in1_Din_B[25] = \<const0> ;
  assign in1_Din_B[24] = \<const0> ;
  assign in1_Din_B[23] = \<const0> ;
  assign in1_Din_B[22] = \<const0> ;
  assign in1_Din_B[21] = \<const0> ;
  assign in1_Din_B[20] = \<const0> ;
  assign in1_Din_B[19] = \<const0> ;
  assign in1_Din_B[18] = \<const0> ;
  assign in1_Din_B[17] = \<const0> ;
  assign in1_Din_B[16] = \<const0> ;
  assign in1_Din_B[15] = \<const0> ;
  assign in1_Din_B[14] = \<const0> ;
  assign in1_Din_B[13] = \<const0> ;
  assign in1_Din_B[12] = \<const0> ;
  assign in1_Din_B[11] = \<const0> ;
  assign in1_Din_B[10] = \<const0> ;
  assign in1_Din_B[9] = \<const0> ;
  assign in1_Din_B[8] = \<const0> ;
  assign in1_Din_B[7] = \<const0> ;
  assign in1_Din_B[6] = \<const0> ;
  assign in1_Din_B[5] = \<const0> ;
  assign in1_Din_B[4] = \<const0> ;
  assign in1_Din_B[3] = \<const0> ;
  assign in1_Din_B[2] = \<const0> ;
  assign in1_Din_B[1] = \<const0> ;
  assign in1_Din_B[0] = \<const0> ;
  assign in1_WEN_A[3] = \<const0> ;
  assign in1_WEN_A[2] = \<const0> ;
  assign in1_WEN_A[1] = \<const0> ;
  assign in1_WEN_A[0] = \<const0> ;
  assign in1_WEN_B[3] = \<const0> ;
  assign in1_WEN_B[2] = \<const0> ;
  assign in1_WEN_B[1] = \<const0> ;
  assign in1_WEN_B[0] = \<const0> ;
  assign in2_Addr_A[31] = \<const0> ;
  assign in2_Addr_A[30] = \<const0> ;
  assign in2_Addr_A[29] = \<const0> ;
  assign in2_Addr_A[28] = \<const0> ;
  assign in2_Addr_A[27] = \<const0> ;
  assign in2_Addr_A[26] = \<const0> ;
  assign in2_Addr_A[25] = \<const0> ;
  assign in2_Addr_A[24] = \<const0> ;
  assign in2_Addr_A[23] = \<const0> ;
  assign in2_Addr_A[22] = \<const0> ;
  assign in2_Addr_A[21] = \<const0> ;
  assign in2_Addr_A[20] = \<const0> ;
  assign in2_Addr_A[19] = \<const0> ;
  assign in2_Addr_A[18] = \<const0> ;
  assign in2_Addr_A[17] = \<const0> ;
  assign in2_Addr_A[16] = \<const0> ;
  assign in2_Addr_A[15] = \<const0> ;
  assign in2_Addr_A[14] = \<const0> ;
  assign in2_Addr_A[13] = \<const0> ;
  assign in2_Addr_A[12] = \<const0> ;
  assign in2_Addr_A[11] = \<const0> ;
  assign in2_Addr_A[10] = \<const0> ;
  assign in2_Addr_A[9] = \<const0> ;
  assign in2_Addr_A[8] = \<const0> ;
  assign in2_Addr_A[7] = \<const0> ;
  assign in2_Addr_A[6] = \<const0> ;
  assign in2_Addr_A[5:2] = \^in2_Addr_A [5:2];
  assign in2_Addr_A[1] = \<const0> ;
  assign in2_Addr_A[0] = \<const0> ;
  assign in2_Addr_B[31] = \<const0> ;
  assign in2_Addr_B[30] = \<const0> ;
  assign in2_Addr_B[29] = \<const0> ;
  assign in2_Addr_B[28] = \<const0> ;
  assign in2_Addr_B[27] = \<const0> ;
  assign in2_Addr_B[26] = \<const0> ;
  assign in2_Addr_B[25] = \<const0> ;
  assign in2_Addr_B[24] = \<const0> ;
  assign in2_Addr_B[23] = \<const0> ;
  assign in2_Addr_B[22] = \<const0> ;
  assign in2_Addr_B[21] = \<const0> ;
  assign in2_Addr_B[20] = \<const0> ;
  assign in2_Addr_B[19] = \<const0> ;
  assign in2_Addr_B[18] = \<const0> ;
  assign in2_Addr_B[17] = \<const0> ;
  assign in2_Addr_B[16] = \<const0> ;
  assign in2_Addr_B[15] = \<const0> ;
  assign in2_Addr_B[14] = \<const0> ;
  assign in2_Addr_B[13] = \<const0> ;
  assign in2_Addr_B[12] = \<const0> ;
  assign in2_Addr_B[11] = \<const0> ;
  assign in2_Addr_B[10] = \<const0> ;
  assign in2_Addr_B[9] = \<const0> ;
  assign in2_Addr_B[8] = \<const0> ;
  assign in2_Addr_B[7] = \<const0> ;
  assign in2_Addr_B[6] = \<const0> ;
  assign in2_Addr_B[5:2] = \^in2_Addr_B [5:2];
  assign in2_Addr_B[1] = \<const0> ;
  assign in2_Addr_B[0] = \<const0> ;
  assign in2_Din_A[31] = \<const0> ;
  assign in2_Din_A[30] = \<const0> ;
  assign in2_Din_A[29] = \<const0> ;
  assign in2_Din_A[28] = \<const0> ;
  assign in2_Din_A[27] = \<const0> ;
  assign in2_Din_A[26] = \<const0> ;
  assign in2_Din_A[25] = \<const0> ;
  assign in2_Din_A[24] = \<const0> ;
  assign in2_Din_A[23] = \<const0> ;
  assign in2_Din_A[22] = \<const0> ;
  assign in2_Din_A[21] = \<const0> ;
  assign in2_Din_A[20] = \<const0> ;
  assign in2_Din_A[19] = \<const0> ;
  assign in2_Din_A[18] = \<const0> ;
  assign in2_Din_A[17] = \<const0> ;
  assign in2_Din_A[16] = \<const0> ;
  assign in2_Din_A[15] = \<const0> ;
  assign in2_Din_A[14] = \<const0> ;
  assign in2_Din_A[13] = \<const0> ;
  assign in2_Din_A[12] = \<const0> ;
  assign in2_Din_A[11] = \<const0> ;
  assign in2_Din_A[10] = \<const0> ;
  assign in2_Din_A[9] = \<const0> ;
  assign in2_Din_A[8] = \<const0> ;
  assign in2_Din_A[7] = \<const0> ;
  assign in2_Din_A[6] = \<const0> ;
  assign in2_Din_A[5] = \<const0> ;
  assign in2_Din_A[4] = \<const0> ;
  assign in2_Din_A[3] = \<const0> ;
  assign in2_Din_A[2] = \<const0> ;
  assign in2_Din_A[1] = \<const0> ;
  assign in2_Din_A[0] = \<const0> ;
  assign in2_Din_B[31] = \<const0> ;
  assign in2_Din_B[30] = \<const0> ;
  assign in2_Din_B[29] = \<const0> ;
  assign in2_Din_B[28] = \<const0> ;
  assign in2_Din_B[27] = \<const0> ;
  assign in2_Din_B[26] = \<const0> ;
  assign in2_Din_B[25] = \<const0> ;
  assign in2_Din_B[24] = \<const0> ;
  assign in2_Din_B[23] = \<const0> ;
  assign in2_Din_B[22] = \<const0> ;
  assign in2_Din_B[21] = \<const0> ;
  assign in2_Din_B[20] = \<const0> ;
  assign in2_Din_B[19] = \<const0> ;
  assign in2_Din_B[18] = \<const0> ;
  assign in2_Din_B[17] = \<const0> ;
  assign in2_Din_B[16] = \<const0> ;
  assign in2_Din_B[15] = \<const0> ;
  assign in2_Din_B[14] = \<const0> ;
  assign in2_Din_B[13] = \<const0> ;
  assign in2_Din_B[12] = \<const0> ;
  assign in2_Din_B[11] = \<const0> ;
  assign in2_Din_B[10] = \<const0> ;
  assign in2_Din_B[9] = \<const0> ;
  assign in2_Din_B[8] = \<const0> ;
  assign in2_Din_B[7] = \<const0> ;
  assign in2_Din_B[6] = \<const0> ;
  assign in2_Din_B[5] = \<const0> ;
  assign in2_Din_B[4] = \<const0> ;
  assign in2_Din_B[3] = \<const0> ;
  assign in2_Din_B[2] = \<const0> ;
  assign in2_Din_B[1] = \<const0> ;
  assign in2_Din_B[0] = \<const0> ;
  assign in2_WEN_A[3] = \<const0> ;
  assign in2_WEN_A[2] = \<const0> ;
  assign in2_WEN_A[1] = \<const0> ;
  assign in2_WEN_A[0] = \<const0> ;
  assign in2_WEN_B[3] = \<const0> ;
  assign in2_WEN_B[2] = \<const0> ;
  assign in2_WEN_B[1] = \<const0> ;
  assign in2_WEN_B[0] = \<const0> ;
  assign out_r_Addr_A[31] = \<const0> ;
  assign out_r_Addr_A[30] = \<const0> ;
  assign out_r_Addr_A[29] = \<const0> ;
  assign out_r_Addr_A[28] = \<const0> ;
  assign out_r_Addr_A[27] = \<const0> ;
  assign out_r_Addr_A[26] = \<const0> ;
  assign out_r_Addr_A[25] = \<const0> ;
  assign out_r_Addr_A[24] = \<const0> ;
  assign out_r_Addr_A[23] = \<const0> ;
  assign out_r_Addr_A[22] = \<const0> ;
  assign out_r_Addr_A[21] = \<const0> ;
  assign out_r_Addr_A[20] = \<const0> ;
  assign out_r_Addr_A[19] = \<const0> ;
  assign out_r_Addr_A[18] = \<const0> ;
  assign out_r_Addr_A[17] = \<const0> ;
  assign out_r_Addr_A[16] = \<const0> ;
  assign out_r_Addr_A[15] = \<const0> ;
  assign out_r_Addr_A[14] = \<const0> ;
  assign out_r_Addr_A[13] = \<const0> ;
  assign out_r_Addr_A[12] = \<const0> ;
  assign out_r_Addr_A[11] = \<const0> ;
  assign out_r_Addr_A[10] = \<const0> ;
  assign out_r_Addr_A[9] = \<const0> ;
  assign out_r_Addr_A[8] = \<const0> ;
  assign out_r_Addr_A[7] = \<const0> ;
  assign out_r_Addr_A[6] = \<const0> ;
  assign out_r_Addr_A[5:2] = \^out_r_Addr_A [5:2];
  assign out_r_Addr_A[1] = \<const0> ;
  assign out_r_Addr_A[0] = \<const0> ;
  assign s_axi_control_BRESP[1] = \<const0> ;
  assign s_axi_control_BRESP[0] = \<const0> ;
  assign s_axi_control_RDATA[31] = \<const0> ;
  assign s_axi_control_RDATA[30] = \<const0> ;
  assign s_axi_control_RDATA[29] = \<const0> ;
  assign s_axi_control_RDATA[28] = \<const0> ;
  assign s_axi_control_RDATA[27] = \<const0> ;
  assign s_axi_control_RDATA[26] = \<const0> ;
  assign s_axi_control_RDATA[25] = \<const0> ;
  assign s_axi_control_RDATA[24] = \<const0> ;
  assign s_axi_control_RDATA[23] = \<const0> ;
  assign s_axi_control_RDATA[22] = \<const0> ;
  assign s_axi_control_RDATA[21] = \<const0> ;
  assign s_axi_control_RDATA[20] = \<const0> ;
  assign s_axi_control_RDATA[19] = \<const0> ;
  assign s_axi_control_RDATA[18] = \<const0> ;
  assign s_axi_control_RDATA[17] = \<const0> ;
  assign s_axi_control_RDATA[16] = \<const0> ;
  assign s_axi_control_RDATA[15] = \<const0> ;
  assign s_axi_control_RDATA[14] = \<const0> ;
  assign s_axi_control_RDATA[13] = \<const0> ;
  assign s_axi_control_RDATA[12] = \<const0> ;
  assign s_axi_control_RDATA[11] = \<const0> ;
  assign s_axi_control_RDATA[10] = \<const0> ;
  assign s_axi_control_RDATA[9] = \^s_axi_control_RDATA [9];
  assign s_axi_control_RDATA[8] = \<const0> ;
  assign s_axi_control_RDATA[7] = \^s_axi_control_RDATA [7];
  assign s_axi_control_RDATA[6] = \<const0> ;
  assign s_axi_control_RDATA[5] = \<const0> ;
  assign s_axi_control_RDATA[4:0] = \^s_axi_control_RDATA [4:0];
  assign s_axi_control_RRESP[1] = \<const0> ;
  assign s_axi_control_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  VCC VCC
       (.P(\<const1> ));
  (* C_S_AXI_CONTROL_ADDR_WIDTH = "4" *) 
  (* C_S_AXI_CONTROL_DATA_WIDTH = "32" *) 
  (* C_S_AXI_CONTROL_WSTRB_WIDTH = "4" *) 
  (* C_S_AXI_DATA_WIDTH = "32" *) 
  (* C_S_AXI_WSTRB_WIDTH = "4" *) 
  (* SDX_KERNEL = "true" *) 
  (* SDX_KERNEL_SYNTH_INST = "inst" *) 
  (* SDX_KERNEL_TYPE = "hls" *) 
  (* ap_ST_fsm_pp0_stage0 = "1'b1" *) 
  bd_0_hls_inst_0_mat_mul inst
       (.ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .in1_Addr_A({NLW_inst_in1_Addr_A_UNCONNECTED[31:6],\^in1_Addr_A ,NLW_inst_in1_Addr_A_UNCONNECTED[2:0]}),
        .in1_Addr_B({NLW_inst_in1_Addr_B_UNCONNECTED[31:6],\^in1_Addr_B ,NLW_inst_in1_Addr_B_UNCONNECTED[2:0]}),
        .in1_Clk_A(in1_Clk_A),
        .in1_Clk_B(in1_Clk_B),
        .in1_Din_A(NLW_inst_in1_Din_A_UNCONNECTED[31:0]),
        .in1_Din_B(NLW_inst_in1_Din_B_UNCONNECTED[31:0]),
        .in1_Dout_A(in1_Dout_A),
        .in1_Dout_B(in1_Dout_B),
        .in1_EN_A(in1_EN_A),
        .in1_EN_B(in1_EN_B),
        .in1_Rst_A(in1_Rst_A),
        .in1_Rst_B(in1_Rst_B),
        .in1_WEN_A(NLW_inst_in1_WEN_A_UNCONNECTED[3:0]),
        .in1_WEN_B(NLW_inst_in1_WEN_B_UNCONNECTED[3:0]),
        .in2_Addr_A({NLW_inst_in2_Addr_A_UNCONNECTED[31:6],\^in2_Addr_A ,NLW_inst_in2_Addr_A_UNCONNECTED[1:0]}),
        .in2_Addr_B({NLW_inst_in2_Addr_B_UNCONNECTED[31:6],\^in2_Addr_B ,NLW_inst_in2_Addr_B_UNCONNECTED[1:0]}),
        .in2_Clk_A(in2_Clk_A),
        .in2_Clk_B(in2_Clk_B),
        .in2_Din_A(NLW_inst_in2_Din_A_UNCONNECTED[31:0]),
        .in2_Din_B(NLW_inst_in2_Din_B_UNCONNECTED[31:0]),
        .in2_Dout_A(in2_Dout_A),
        .in2_Dout_B(in2_Dout_B),
        .in2_EN_A(in2_EN_A),
        .in2_EN_B(in2_EN_B),
        .in2_Rst_A(in2_Rst_A),
        .in2_Rst_B(in2_Rst_B),
        .in2_WEN_A(NLW_inst_in2_WEN_A_UNCONNECTED[3:0]),
        .in2_WEN_B(NLW_inst_in2_WEN_B_UNCONNECTED[3:0]),
        .interrupt(interrupt),
        .out_r_Addr_A({NLW_inst_out_r_Addr_A_UNCONNECTED[31:6],\^out_r_Addr_A ,NLW_inst_out_r_Addr_A_UNCONNECTED[1:0]}),
        .out_r_Clk_A(out_r_Clk_A),
        .out_r_Din_A(out_r_Din_A),
        .out_r_Dout_A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .out_r_EN_A(out_r_EN_A),
        .out_r_Rst_A(out_r_Rst_A),
        .out_r_WEN_A(out_r_WEN_A),
        .s_axi_control_ARADDR(s_axi_control_ARADDR),
        .s_axi_control_ARREADY(s_axi_control_ARREADY),
        .s_axi_control_ARVALID(s_axi_control_ARVALID),
        .s_axi_control_AWADDR({s_axi_control_AWADDR[3:2],1'b0,1'b0}),
        .s_axi_control_AWREADY(s_axi_control_AWREADY),
        .s_axi_control_AWVALID(s_axi_control_AWVALID),
        .s_axi_control_BREADY(s_axi_control_BREADY),
        .s_axi_control_BRESP(NLW_inst_s_axi_control_BRESP_UNCONNECTED[1:0]),
        .s_axi_control_BVALID(s_axi_control_BVALID),
        .s_axi_control_RDATA({NLW_inst_s_axi_control_RDATA_UNCONNECTED[31:10],\^s_axi_control_RDATA }),
        .s_axi_control_RREADY(s_axi_control_RREADY),
        .s_axi_control_RRESP(NLW_inst_s_axi_control_RRESP_UNCONNECTED[1:0]),
        .s_axi_control_RVALID(s_axi_control_RVALID),
        .s_axi_control_WDATA({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,s_axi_control_WDATA[7],1'b0,1'b0,s_axi_control_WDATA[4],1'b0,1'b0,s_axi_control_WDATA[1:0]}),
        .s_axi_control_WREADY(s_axi_control_WREADY),
        .s_axi_control_WSTRB({1'b0,1'b0,1'b0,s_axi_control_WSTRB[0]}),
        .s_axi_control_WVALID(s_axi_control_WVALID));
endmodule

(* C_S_AXI_CONTROL_ADDR_WIDTH = "4" *) (* C_S_AXI_CONTROL_DATA_WIDTH = "32" *) (* C_S_AXI_CONTROL_WSTRB_WIDTH = "4" *) 
(* C_S_AXI_DATA_WIDTH = "32" *) (* C_S_AXI_WSTRB_WIDTH = "4" *) (* ORIG_REF_NAME = "mat_mul" *) 
(* ap_ST_fsm_pp0_stage0 = "1'b1" *) (* hls_module = "yes" *) 
module bd_0_hls_inst_0_mat_mul
   (ap_clk,
    ap_rst_n,
    in1_Addr_A,
    in1_EN_A,
    in1_WEN_A,
    in1_Din_A,
    in1_Dout_A,
    in1_Clk_A,
    in1_Rst_A,
    in1_Addr_B,
    in1_EN_B,
    in1_WEN_B,
    in1_Din_B,
    in1_Dout_B,
    in1_Clk_B,
    in1_Rst_B,
    in2_Addr_A,
    in2_EN_A,
    in2_WEN_A,
    in2_Din_A,
    in2_Dout_A,
    in2_Clk_A,
    in2_Rst_A,
    in2_Addr_B,
    in2_EN_B,
    in2_WEN_B,
    in2_Din_B,
    in2_Dout_B,
    in2_Clk_B,
    in2_Rst_B,
    out_r_Addr_A,
    out_r_EN_A,
    out_r_WEN_A,
    out_r_Din_A,
    out_r_Dout_A,
    out_r_Clk_A,
    out_r_Rst_A,
    s_axi_control_AWVALID,
    s_axi_control_AWREADY,
    s_axi_control_AWADDR,
    s_axi_control_WVALID,
    s_axi_control_WREADY,
    s_axi_control_WDATA,
    s_axi_control_WSTRB,
    s_axi_control_ARVALID,
    s_axi_control_ARREADY,
    s_axi_control_ARADDR,
    s_axi_control_RVALID,
    s_axi_control_RREADY,
    s_axi_control_RDATA,
    s_axi_control_RRESP,
    s_axi_control_BVALID,
    s_axi_control_BREADY,
    s_axi_control_BRESP,
    interrupt);
  input ap_clk;
  input ap_rst_n;
  output [31:0]in1_Addr_A;
  output in1_EN_A;
  output [3:0]in1_WEN_A;
  output [31:0]in1_Din_A;
  input [31:0]in1_Dout_A;
  output in1_Clk_A;
  output in1_Rst_A;
  output [31:0]in1_Addr_B;
  output in1_EN_B;
  output [3:0]in1_WEN_B;
  output [31:0]in1_Din_B;
  input [31:0]in1_Dout_B;
  output in1_Clk_B;
  output in1_Rst_B;
  output [31:0]in2_Addr_A;
  output in2_EN_A;
  output [3:0]in2_WEN_A;
  output [31:0]in2_Din_A;
  input [31:0]in2_Dout_A;
  output in2_Clk_A;
  output in2_Rst_A;
  output [31:0]in2_Addr_B;
  output in2_EN_B;
  output [3:0]in2_WEN_B;
  output [31:0]in2_Din_B;
  input [31:0]in2_Dout_B;
  output in2_Clk_B;
  output in2_Rst_B;
  output [31:0]out_r_Addr_A;
  output out_r_EN_A;
  output [3:0]out_r_WEN_A;
  output [31:0]out_r_Din_A;
  input [31:0]out_r_Dout_A;
  output out_r_Clk_A;
  output out_r_Rst_A;
  input s_axi_control_AWVALID;
  output s_axi_control_AWREADY;
  input [3:0]s_axi_control_AWADDR;
  input s_axi_control_WVALID;
  output s_axi_control_WREADY;
  input [31:0]s_axi_control_WDATA;
  input [3:0]s_axi_control_WSTRB;
  input s_axi_control_ARVALID;
  output s_axi_control_ARREADY;
  input [3:0]s_axi_control_ARADDR;
  output s_axi_control_RVALID;
  input s_axi_control_RREADY;
  output [31:0]s_axi_control_RDATA;
  output [1:0]s_axi_control_RRESP;
  output s_axi_control_BVALID;
  input s_axi_control_BREADY;
  output [1:0]s_axi_control_BRESP;
  output interrupt;

  wire \<const0> ;
  wire [3:3]add_ln16_fu_313_p2;
  wire \add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3_n_0 ;
  wire \add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3_n_0 ;
  wire \add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3_n_0 ;
  wire \add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3_n_0 ;
  wire [4:0]add_ln9_1_fu_415_p2;
  wire ap_block_pp0_stage0_subdone;
  wire ap_clk;
  wire ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2_n_0;
  wire ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg;
  wire ap_enable_reg_pp0_iter1;
  wire ap_enable_reg_pp0_iter2;
  wire ap_enable_reg_pp0_iter3;
  wire ap_enable_reg_pp0_iter4;
  wire ap_loop_exit_ready;
  wire ap_loop_exit_ready_pp0_iter3_reg;
  wire ap_loop_exit_ready_pp0_iter4_reg;
  wire ap_loop_exit_ready_pp0_iter4_reg_i_1_n_0;
  wire ap_rst_n;
  wire ap_rst_reg_1;
  wire ap_rst_reg_2;
  wire ap_rst_reg_2_i_1_n_0;
  wire ap_start;
  wire ap_start_int;
  wire [31:16]buff0_reg__1;
  wire [31:16]buff0_reg__1_0;
  wire control_s_axi_U_n_8;
  wire flow_control_loop_delay_pipe_U_n_1;
  wire flow_control_loop_delay_pipe_U_n_16;
  wire flow_control_loop_delay_pipe_U_n_26;
  wire flow_control_loop_delay_pipe_U_n_28;
  wire flow_control_loop_delay_pipe_U_n_29;
  wire flow_control_loop_delay_pipe_U_n_3;
  wire flow_control_loop_delay_pipe_U_n_30;
  wire flow_control_loop_delay_pipe_U_n_31;
  wire flow_control_loop_delay_pipe_U_n_32;
  wire flow_control_loop_delay_pipe_U_n_33;
  wire flow_control_loop_delay_pipe_U_n_5;
  wire flow_control_loop_delay_pipe_U_n_9;
  wire [1:0]i2_fu_78;
  wire \icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2_n_0 ;
  wire icmp_ln108_reg_161_pp0_iter3_reg;
  wire \icmp_ln108_reg_161_reg_n_0_[0] ;
  wire icmp_ln10_fu_435_p2;
  wire icmp_ln10_reg_591;
  wire icmp_ln9_fu_441_p2;
  wire icmp_ln9_reg_596;
  wire [5:4]\^in1_Addr_A ;
  wire [5:4]\^in1_Addr_B ;
  wire [31:0]in1_Dout_A;
  wire [31:0]in1_Dout_B;
  wire in1_EN_A;
  wire [5:2]\^in2_Addr_A ;
  wire [5:4]\^in2_Addr_B ;
  wire [31:0]in2_Dout_A;
  wire [31:0]in2_Dout_B;
  wire [4:0]indvar_flatten131_fu_74;
  wire [4:0]indvar_flatten3_fu_82;
  wire interrupt;
  wire [2:0]j4_fu_86;
  wire [2:1]k5_fu_90;
  wire mul_32s_32s_32_2_1_U1_n_16;
  wire mul_32s_32s_32_2_1_U1_n_17;
  wire mul_32s_32s_32_2_1_U1_n_18;
  wire mul_32s_32s_32_2_1_U1_n_19;
  wire mul_32s_32s_32_2_1_U1_n_20;
  wire mul_32s_32s_32_2_1_U1_n_21;
  wire mul_32s_32s_32_2_1_U1_n_22;
  wire mul_32s_32s_32_2_1_U1_n_23;
  wire mul_32s_32s_32_2_1_U1_n_24;
  wire mul_32s_32s_32_2_1_U1_n_25;
  wire mul_32s_32s_32_2_1_U1_n_26;
  wire mul_32s_32s_32_2_1_U1_n_27;
  wire mul_32s_32s_32_2_1_U1_n_28;
  wire mul_32s_32s_32_2_1_U1_n_29;
  wire mul_32s_32s_32_2_1_U1_n_30;
  wire mul_32s_32s_32_2_1_U1_n_31;
  wire mul_32s_32s_32_2_1_U2_n_17;
  wire mul_32s_32s_32_2_1_U2_n_18;
  wire mul_32s_32s_32_2_1_U2_n_19;
  wire mul_32s_32s_32_2_1_U2_n_20;
  wire mul_32s_32s_32_2_1_U2_n_21;
  wire mul_32s_32s_32_2_1_U2_n_22;
  wire mul_32s_32s_32_2_1_U2_n_23;
  wire mul_32s_32s_32_2_1_U2_n_24;
  wire mul_32s_32s_32_2_1_U2_n_25;
  wire mul_32s_32s_32_2_1_U2_n_26;
  wire mul_32s_32s_32_2_1_U2_n_27;
  wire mul_32s_32s_32_2_1_U2_n_28;
  wire mul_32s_32s_32_2_1_U2_n_29;
  wire mul_32s_32s_32_2_1_U2_n_30;
  wire mul_32s_32s_32_2_1_U2_n_31;
  wire mul_32s_32s_32_2_1_U2_n_32;
  wire [31:0]mul_ln14_1_reg_625;
  wire [31:0]mul_ln14_reg_620;
  wire \or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3_n_0 ;
  wire or_ln9_reg_552_pp0_iter3_reg;
  wire [5:2]\^out_r_Addr_A ;
  wire [31:0]out_r_Din_A;
  wire \out_r_Din_A[0]_INST_0_i_10_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_11_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_12_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_13_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_14_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_15_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_1_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_2_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_3_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_4_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_5_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_6_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_7_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_8_n_0 ;
  wire \out_r_Din_A[0]_INST_0_i_9_n_0 ;
  wire \out_r_Din_A[0]_INST_0_n_0 ;
  wire \out_r_Din_A[0]_INST_0_n_1 ;
  wire \out_r_Din_A[0]_INST_0_n_2 ;
  wire \out_r_Din_A[0]_INST_0_n_3 ;
  wire \out_r_Din_A[0]_INST_0_n_4 ;
  wire \out_r_Din_A[0]_INST_0_n_5 ;
  wire \out_r_Din_A[0]_INST_0_n_6 ;
  wire \out_r_Din_A[0]_INST_0_n_7 ;
  wire \out_r_Din_A[16]_INST_0_i_10_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_11_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_12_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_13_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_14_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_15_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_16_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_1_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_2_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_3_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_4_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_5_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_6_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_7_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_8_n_0 ;
  wire \out_r_Din_A[16]_INST_0_i_9_n_0 ;
  wire \out_r_Din_A[16]_INST_0_n_0 ;
  wire \out_r_Din_A[16]_INST_0_n_1 ;
  wire \out_r_Din_A[16]_INST_0_n_2 ;
  wire \out_r_Din_A[16]_INST_0_n_3 ;
  wire \out_r_Din_A[16]_INST_0_n_4 ;
  wire \out_r_Din_A[16]_INST_0_n_5 ;
  wire \out_r_Din_A[16]_INST_0_n_6 ;
  wire \out_r_Din_A[16]_INST_0_n_7 ;
  wire \out_r_Din_A[24]_INST_0_i_10_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_11_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_12_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_13_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_14_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_15_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_16_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_1_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_2_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_3_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_4_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_5_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_6_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_7_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_8_n_0 ;
  wire \out_r_Din_A[24]_INST_0_i_9_n_0 ;
  wire \out_r_Din_A[24]_INST_0_n_1 ;
  wire \out_r_Din_A[24]_INST_0_n_2 ;
  wire \out_r_Din_A[24]_INST_0_n_3 ;
  wire \out_r_Din_A[24]_INST_0_n_4 ;
  wire \out_r_Din_A[24]_INST_0_n_5 ;
  wire \out_r_Din_A[24]_INST_0_n_6 ;
  wire \out_r_Din_A[24]_INST_0_n_7 ;
  wire \out_r_Din_A[8]_INST_0_i_10_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_11_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_12_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_13_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_14_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_15_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_16_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_1_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_2_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_3_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_4_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_5_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_6_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_7_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_8_n_0 ;
  wire \out_r_Din_A[8]_INST_0_i_9_n_0 ;
  wire \out_r_Din_A[8]_INST_0_n_0 ;
  wire \out_r_Din_A[8]_INST_0_n_1 ;
  wire \out_r_Din_A[8]_INST_0_n_2 ;
  wire \out_r_Din_A[8]_INST_0_n_3 ;
  wire \out_r_Din_A[8]_INST_0_n_4 ;
  wire \out_r_Din_A[8]_INST_0_n_5 ;
  wire \out_r_Din_A[8]_INST_0_n_6 ;
  wire \out_r_Din_A[8]_INST_0_n_7 ;
  wire out_r_EN_A;
  wire out_r_Rst_A;
  wire [0:0]\^out_r_WEN_A ;
  wire p_1_in;
  wire p_5_in;
  wire rewind_ap_ready_reg;
  wire [3:0]s_axi_control_ARADDR;
  wire s_axi_control_ARREADY;
  wire s_axi_control_ARVALID;
  wire [3:0]s_axi_control_AWADDR;
  wire s_axi_control_AWREADY;
  wire s_axi_control_AWVALID;
  wire s_axi_control_BREADY;
  wire s_axi_control_BVALID;
  wire [9:0]\^s_axi_control_RDATA ;
  wire s_axi_control_RREADY;
  wire s_axi_control_RVALID;
  wire [31:0]s_axi_control_WDATA;
  wire s_axi_control_WREADY;
  wire [3:0]s_axi_control_WSTRB;
  wire s_axi_control_WVALID;
  wire [0:0]select_ln10_1_fu_427_p3;
  wire \sum6_fu_94_reg_n_0_[0] ;
  wire \sum6_fu_94_reg_n_0_[10] ;
  wire \sum6_fu_94_reg_n_0_[11] ;
  wire \sum6_fu_94_reg_n_0_[12] ;
  wire \sum6_fu_94_reg_n_0_[13] ;
  wire \sum6_fu_94_reg_n_0_[14] ;
  wire \sum6_fu_94_reg_n_0_[15] ;
  wire \sum6_fu_94_reg_n_0_[16] ;
  wire \sum6_fu_94_reg_n_0_[17] ;
  wire \sum6_fu_94_reg_n_0_[18] ;
  wire \sum6_fu_94_reg_n_0_[19] ;
  wire \sum6_fu_94_reg_n_0_[1] ;
  wire \sum6_fu_94_reg_n_0_[20] ;
  wire \sum6_fu_94_reg_n_0_[21] ;
  wire \sum6_fu_94_reg_n_0_[22] ;
  wire \sum6_fu_94_reg_n_0_[23] ;
  wire \sum6_fu_94_reg_n_0_[24] ;
  wire \sum6_fu_94_reg_n_0_[25] ;
  wire \sum6_fu_94_reg_n_0_[26] ;
  wire \sum6_fu_94_reg_n_0_[27] ;
  wire \sum6_fu_94_reg_n_0_[28] ;
  wire \sum6_fu_94_reg_n_0_[29] ;
  wire \sum6_fu_94_reg_n_0_[2] ;
  wire \sum6_fu_94_reg_n_0_[30] ;
  wire \sum6_fu_94_reg_n_0_[31] ;
  wire \sum6_fu_94_reg_n_0_[3] ;
  wire \sum6_fu_94_reg_n_0_[4] ;
  wire \sum6_fu_94_reg_n_0_[5] ;
  wire \sum6_fu_94_reg_n_0_[6] ;
  wire \sum6_fu_94_reg_n_0_[7] ;
  wire \sum6_fu_94_reg_n_0_[8] ;
  wire \sum6_fu_94_reg_n_0_[9] ;
  wire tmp_5_fu_401_p3;
  wire \tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3_n_0 ;
  wire tmp_5_reg_582_pp0_iter3_reg;
  wire xor_ln12_reg_586;
  wire [7:7]\NLW_out_r_Din_A[24]_INST_0_CO_UNCONNECTED ;

  assign in1_Addr_A[31] = \<const0> ;
  assign in1_Addr_A[30] = \<const0> ;
  assign in1_Addr_A[29] = \<const0> ;
  assign in1_Addr_A[28] = \<const0> ;
  assign in1_Addr_A[27] = \<const0> ;
  assign in1_Addr_A[26] = \<const0> ;
  assign in1_Addr_A[25] = \<const0> ;
  assign in1_Addr_A[24] = \<const0> ;
  assign in1_Addr_A[23] = \<const0> ;
  assign in1_Addr_A[22] = \<const0> ;
  assign in1_Addr_A[21] = \<const0> ;
  assign in1_Addr_A[20] = \<const0> ;
  assign in1_Addr_A[19] = \<const0> ;
  assign in1_Addr_A[18] = \<const0> ;
  assign in1_Addr_A[17] = \<const0> ;
  assign in1_Addr_A[16] = \<const0> ;
  assign in1_Addr_A[15] = \<const0> ;
  assign in1_Addr_A[14] = \<const0> ;
  assign in1_Addr_A[13] = \<const0> ;
  assign in1_Addr_A[12] = \<const0> ;
  assign in1_Addr_A[11] = \<const0> ;
  assign in1_Addr_A[10] = \<const0> ;
  assign in1_Addr_A[9] = \<const0> ;
  assign in1_Addr_A[8] = \<const0> ;
  assign in1_Addr_A[7] = \<const0> ;
  assign in1_Addr_A[6] = \<const0> ;
  assign in1_Addr_A[5:4] = \^in1_Addr_A [5:4];
  assign in1_Addr_A[3] = \^in2_Addr_B [5];
  assign in1_Addr_A[2] = \<const0> ;
  assign in1_Addr_A[1] = \<const0> ;
  assign in1_Addr_A[0] = \<const0> ;
  assign in1_Addr_B[31] = \<const0> ;
  assign in1_Addr_B[30] = \<const0> ;
  assign in1_Addr_B[29] = \<const0> ;
  assign in1_Addr_B[28] = \<const0> ;
  assign in1_Addr_B[27] = \<const0> ;
  assign in1_Addr_B[26] = \<const0> ;
  assign in1_Addr_B[25] = \<const0> ;
  assign in1_Addr_B[24] = \<const0> ;
  assign in1_Addr_B[23] = \<const0> ;
  assign in1_Addr_B[22] = \<const0> ;
  assign in1_Addr_B[21] = \<const0> ;
  assign in1_Addr_B[20] = \<const0> ;
  assign in1_Addr_B[19] = \<const0> ;
  assign in1_Addr_B[18] = \<const0> ;
  assign in1_Addr_B[17] = \<const0> ;
  assign in1_Addr_B[16] = \<const0> ;
  assign in1_Addr_B[15] = \<const0> ;
  assign in1_Addr_B[14] = \<const0> ;
  assign in1_Addr_B[13] = \<const0> ;
  assign in1_Addr_B[12] = \<const0> ;
  assign in1_Addr_B[11] = \<const0> ;
  assign in1_Addr_B[10] = \<const0> ;
  assign in1_Addr_B[9] = \<const0> ;
  assign in1_Addr_B[8] = \<const0> ;
  assign in1_Addr_B[7] = \<const0> ;
  assign in1_Addr_B[6] = \<const0> ;
  assign in1_Addr_B[5:4] = \^in1_Addr_B [5:4];
  assign in1_Addr_B[3] = \^in2_Addr_B [5];
  assign in1_Addr_B[2] = \<const0> ;
  assign in1_Addr_B[1] = \<const0> ;
  assign in1_Addr_B[0] = \<const0> ;
  assign in1_Clk_A = ap_clk;
  assign in1_Clk_B = ap_clk;
  assign in1_Din_A[31] = \<const0> ;
  assign in1_Din_A[30] = \<const0> ;
  assign in1_Din_A[29] = \<const0> ;
  assign in1_Din_A[28] = \<const0> ;
  assign in1_Din_A[27] = \<const0> ;
  assign in1_Din_A[26] = \<const0> ;
  assign in1_Din_A[25] = \<const0> ;
  assign in1_Din_A[24] = \<const0> ;
  assign in1_Din_A[23] = \<const0> ;
  assign in1_Din_A[22] = \<const0> ;
  assign in1_Din_A[21] = \<const0> ;
  assign in1_Din_A[20] = \<const0> ;
  assign in1_Din_A[19] = \<const0> ;
  assign in1_Din_A[18] = \<const0> ;
  assign in1_Din_A[17] = \<const0> ;
  assign in1_Din_A[16] = \<const0> ;
  assign in1_Din_A[15] = \<const0> ;
  assign in1_Din_A[14] = \<const0> ;
  assign in1_Din_A[13] = \<const0> ;
  assign in1_Din_A[12] = \<const0> ;
  assign in1_Din_A[11] = \<const0> ;
  assign in1_Din_A[10] = \<const0> ;
  assign in1_Din_A[9] = \<const0> ;
  assign in1_Din_A[8] = \<const0> ;
  assign in1_Din_A[7] = \<const0> ;
  assign in1_Din_A[6] = \<const0> ;
  assign in1_Din_A[5] = \<const0> ;
  assign in1_Din_A[4] = \<const0> ;
  assign in1_Din_A[3] = \<const0> ;
  assign in1_Din_A[2] = \<const0> ;
  assign in1_Din_A[1] = \<const0> ;
  assign in1_Din_A[0] = \<const0> ;
  assign in1_Din_B[31] = \<const0> ;
  assign in1_Din_B[30] = \<const0> ;
  assign in1_Din_B[29] = \<const0> ;
  assign in1_Din_B[28] = \<const0> ;
  assign in1_Din_B[27] = \<const0> ;
  assign in1_Din_B[26] = \<const0> ;
  assign in1_Din_B[25] = \<const0> ;
  assign in1_Din_B[24] = \<const0> ;
  assign in1_Din_B[23] = \<const0> ;
  assign in1_Din_B[22] = \<const0> ;
  assign in1_Din_B[21] = \<const0> ;
  assign in1_Din_B[20] = \<const0> ;
  assign in1_Din_B[19] = \<const0> ;
  assign in1_Din_B[18] = \<const0> ;
  assign in1_Din_B[17] = \<const0> ;
  assign in1_Din_B[16] = \<const0> ;
  assign in1_Din_B[15] = \<const0> ;
  assign in1_Din_B[14] = \<const0> ;
  assign in1_Din_B[13] = \<const0> ;
  assign in1_Din_B[12] = \<const0> ;
  assign in1_Din_B[11] = \<const0> ;
  assign in1_Din_B[10] = \<const0> ;
  assign in1_Din_B[9] = \<const0> ;
  assign in1_Din_B[8] = \<const0> ;
  assign in1_Din_B[7] = \<const0> ;
  assign in1_Din_B[6] = \<const0> ;
  assign in1_Din_B[5] = \<const0> ;
  assign in1_Din_B[4] = \<const0> ;
  assign in1_Din_B[3] = \<const0> ;
  assign in1_Din_B[2] = \<const0> ;
  assign in1_Din_B[1] = \<const0> ;
  assign in1_Din_B[0] = \<const0> ;
  assign in1_EN_B = in1_EN_A;
  assign in1_Rst_A = out_r_Rst_A;
  assign in1_Rst_B = out_r_Rst_A;
  assign in1_WEN_A[3] = \<const0> ;
  assign in1_WEN_A[2] = \<const0> ;
  assign in1_WEN_A[1] = \<const0> ;
  assign in1_WEN_A[0] = \<const0> ;
  assign in1_WEN_B[3] = \<const0> ;
  assign in1_WEN_B[2] = \<const0> ;
  assign in1_WEN_B[1] = \<const0> ;
  assign in1_WEN_B[0] = \<const0> ;
  assign in2_Addr_A[31] = \<const0> ;
  assign in2_Addr_A[30] = \<const0> ;
  assign in2_Addr_A[29] = \<const0> ;
  assign in2_Addr_A[28] = \<const0> ;
  assign in2_Addr_A[27] = \<const0> ;
  assign in2_Addr_A[26] = \<const0> ;
  assign in2_Addr_A[25] = \<const0> ;
  assign in2_Addr_A[24] = \<const0> ;
  assign in2_Addr_A[23] = \<const0> ;
  assign in2_Addr_A[22] = \<const0> ;
  assign in2_Addr_A[21] = \<const0> ;
  assign in2_Addr_A[20] = \<const0> ;
  assign in2_Addr_A[19] = \<const0> ;
  assign in2_Addr_A[18] = \<const0> ;
  assign in2_Addr_A[17] = \<const0> ;
  assign in2_Addr_A[16] = \<const0> ;
  assign in2_Addr_A[15] = \<const0> ;
  assign in2_Addr_A[14] = \<const0> ;
  assign in2_Addr_A[13] = \<const0> ;
  assign in2_Addr_A[12] = \<const0> ;
  assign in2_Addr_A[11] = \<const0> ;
  assign in2_Addr_A[10] = \<const0> ;
  assign in2_Addr_A[9] = \<const0> ;
  assign in2_Addr_A[8] = \<const0> ;
  assign in2_Addr_A[7] = \<const0> ;
  assign in2_Addr_A[6] = \<const0> ;
  assign in2_Addr_A[5:2] = \^in2_Addr_A [5:2];
  assign in2_Addr_A[1] = \<const0> ;
  assign in2_Addr_A[0] = \<const0> ;
  assign in2_Addr_B[31] = \<const0> ;
  assign in2_Addr_B[30] = \<const0> ;
  assign in2_Addr_B[29] = \<const0> ;
  assign in2_Addr_B[28] = \<const0> ;
  assign in2_Addr_B[27] = \<const0> ;
  assign in2_Addr_B[26] = \<const0> ;
  assign in2_Addr_B[25] = \<const0> ;
  assign in2_Addr_B[24] = \<const0> ;
  assign in2_Addr_B[23] = \<const0> ;
  assign in2_Addr_B[22] = \<const0> ;
  assign in2_Addr_B[21] = \<const0> ;
  assign in2_Addr_B[20] = \<const0> ;
  assign in2_Addr_B[19] = \<const0> ;
  assign in2_Addr_B[18] = \<const0> ;
  assign in2_Addr_B[17] = \<const0> ;
  assign in2_Addr_B[16] = \<const0> ;
  assign in2_Addr_B[15] = \<const0> ;
  assign in2_Addr_B[14] = \<const0> ;
  assign in2_Addr_B[13] = \<const0> ;
  assign in2_Addr_B[12] = \<const0> ;
  assign in2_Addr_B[11] = \<const0> ;
  assign in2_Addr_B[10] = \<const0> ;
  assign in2_Addr_B[9] = \<const0> ;
  assign in2_Addr_B[8] = \<const0> ;
  assign in2_Addr_B[7] = \<const0> ;
  assign in2_Addr_B[6] = \<const0> ;
  assign in2_Addr_B[5:4] = \^in2_Addr_B [5:4];
  assign in2_Addr_B[3:2] = \^in2_Addr_A [3:2];
  assign in2_Addr_B[1] = \<const0> ;
  assign in2_Addr_B[0] = \<const0> ;
  assign in2_Clk_A = ap_clk;
  assign in2_Clk_B = ap_clk;
  assign in2_Din_A[31] = \<const0> ;
  assign in2_Din_A[30] = \<const0> ;
  assign in2_Din_A[29] = \<const0> ;
  assign in2_Din_A[28] = \<const0> ;
  assign in2_Din_A[27] = \<const0> ;
  assign in2_Din_A[26] = \<const0> ;
  assign in2_Din_A[25] = \<const0> ;
  assign in2_Din_A[24] = \<const0> ;
  assign in2_Din_A[23] = \<const0> ;
  assign in2_Din_A[22] = \<const0> ;
  assign in2_Din_A[21] = \<const0> ;
  assign in2_Din_A[20] = \<const0> ;
  assign in2_Din_A[19] = \<const0> ;
  assign in2_Din_A[18] = \<const0> ;
  assign in2_Din_A[17] = \<const0> ;
  assign in2_Din_A[16] = \<const0> ;
  assign in2_Din_A[15] = \<const0> ;
  assign in2_Din_A[14] = \<const0> ;
  assign in2_Din_A[13] = \<const0> ;
  assign in2_Din_A[12] = \<const0> ;
  assign in2_Din_A[11] = \<const0> ;
  assign in2_Din_A[10] = \<const0> ;
  assign in2_Din_A[9] = \<const0> ;
  assign in2_Din_A[8] = \<const0> ;
  assign in2_Din_A[7] = \<const0> ;
  assign in2_Din_A[6] = \<const0> ;
  assign in2_Din_A[5] = \<const0> ;
  assign in2_Din_A[4] = \<const0> ;
  assign in2_Din_A[3] = \<const0> ;
  assign in2_Din_A[2] = \<const0> ;
  assign in2_Din_A[1] = \<const0> ;
  assign in2_Din_A[0] = \<const0> ;
  assign in2_Din_B[31] = \<const0> ;
  assign in2_Din_B[30] = \<const0> ;
  assign in2_Din_B[29] = \<const0> ;
  assign in2_Din_B[28] = \<const0> ;
  assign in2_Din_B[27] = \<const0> ;
  assign in2_Din_B[26] = \<const0> ;
  assign in2_Din_B[25] = \<const0> ;
  assign in2_Din_B[24] = \<const0> ;
  assign in2_Din_B[23] = \<const0> ;
  assign in2_Din_B[22] = \<const0> ;
  assign in2_Din_B[21] = \<const0> ;
  assign in2_Din_B[20] = \<const0> ;
  assign in2_Din_B[19] = \<const0> ;
  assign in2_Din_B[18] = \<const0> ;
  assign in2_Din_B[17] = \<const0> ;
  assign in2_Din_B[16] = \<const0> ;
  assign in2_Din_B[15] = \<const0> ;
  assign in2_Din_B[14] = \<const0> ;
  assign in2_Din_B[13] = \<const0> ;
  assign in2_Din_B[12] = \<const0> ;
  assign in2_Din_B[11] = \<const0> ;
  assign in2_Din_B[10] = \<const0> ;
  assign in2_Din_B[9] = \<const0> ;
  assign in2_Din_B[8] = \<const0> ;
  assign in2_Din_B[7] = \<const0> ;
  assign in2_Din_B[6] = \<const0> ;
  assign in2_Din_B[5] = \<const0> ;
  assign in2_Din_B[4] = \<const0> ;
  assign in2_Din_B[3] = \<const0> ;
  assign in2_Din_B[2] = \<const0> ;
  assign in2_Din_B[1] = \<const0> ;
  assign in2_Din_B[0] = \<const0> ;
  assign in2_EN_A = in1_EN_A;
  assign in2_EN_B = in1_EN_A;
  assign in2_Rst_A = out_r_Rst_A;
  assign in2_Rst_B = out_r_Rst_A;
  assign in2_WEN_A[3] = \<const0> ;
  assign in2_WEN_A[2] = \<const0> ;
  assign in2_WEN_A[1] = \<const0> ;
  assign in2_WEN_A[0] = \<const0> ;
  assign in2_WEN_B[3] = \<const0> ;
  assign in2_WEN_B[2] = \<const0> ;
  assign in2_WEN_B[1] = \<const0> ;
  assign in2_WEN_B[0] = \<const0> ;
  assign out_r_Addr_A[31] = \<const0> ;
  assign out_r_Addr_A[30] = \<const0> ;
  assign out_r_Addr_A[29] = \<const0> ;
  assign out_r_Addr_A[28] = \<const0> ;
  assign out_r_Addr_A[27] = \<const0> ;
  assign out_r_Addr_A[26] = \<const0> ;
  assign out_r_Addr_A[25] = \<const0> ;
  assign out_r_Addr_A[24] = \<const0> ;
  assign out_r_Addr_A[23] = \<const0> ;
  assign out_r_Addr_A[22] = \<const0> ;
  assign out_r_Addr_A[21] = \<const0> ;
  assign out_r_Addr_A[20] = \<const0> ;
  assign out_r_Addr_A[19] = \<const0> ;
  assign out_r_Addr_A[18] = \<const0> ;
  assign out_r_Addr_A[17] = \<const0> ;
  assign out_r_Addr_A[16] = \<const0> ;
  assign out_r_Addr_A[15] = \<const0> ;
  assign out_r_Addr_A[14] = \<const0> ;
  assign out_r_Addr_A[13] = \<const0> ;
  assign out_r_Addr_A[12] = \<const0> ;
  assign out_r_Addr_A[11] = \<const0> ;
  assign out_r_Addr_A[10] = \<const0> ;
  assign out_r_Addr_A[9] = \<const0> ;
  assign out_r_Addr_A[8] = \<const0> ;
  assign out_r_Addr_A[7] = \<const0> ;
  assign out_r_Addr_A[6] = \<const0> ;
  assign out_r_Addr_A[5:2] = \^out_r_Addr_A [5:2];
  assign out_r_Addr_A[1] = \<const0> ;
  assign out_r_Addr_A[0] = \<const0> ;
  assign out_r_Clk_A = ap_clk;
  assign out_r_WEN_A[3] = \^out_r_WEN_A [0];
  assign out_r_WEN_A[2] = \^out_r_WEN_A [0];
  assign out_r_WEN_A[1] = \^out_r_WEN_A [0];
  assign out_r_WEN_A[0] = \^out_r_WEN_A [0];
  assign s_axi_control_BRESP[1] = \<const0> ;
  assign s_axi_control_BRESP[0] = \<const0> ;
  assign s_axi_control_RDATA[31] = \<const0> ;
  assign s_axi_control_RDATA[30] = \<const0> ;
  assign s_axi_control_RDATA[29] = \<const0> ;
  assign s_axi_control_RDATA[28] = \<const0> ;
  assign s_axi_control_RDATA[27] = \<const0> ;
  assign s_axi_control_RDATA[26] = \<const0> ;
  assign s_axi_control_RDATA[25] = \<const0> ;
  assign s_axi_control_RDATA[24] = \<const0> ;
  assign s_axi_control_RDATA[23] = \<const0> ;
  assign s_axi_control_RDATA[22] = \<const0> ;
  assign s_axi_control_RDATA[21] = \<const0> ;
  assign s_axi_control_RDATA[20] = \<const0> ;
  assign s_axi_control_RDATA[19] = \<const0> ;
  assign s_axi_control_RDATA[18] = \<const0> ;
  assign s_axi_control_RDATA[17] = \<const0> ;
  assign s_axi_control_RDATA[16] = \<const0> ;
  assign s_axi_control_RDATA[15] = \<const0> ;
  assign s_axi_control_RDATA[14] = \<const0> ;
  assign s_axi_control_RDATA[13] = \<const0> ;
  assign s_axi_control_RDATA[12] = \<const0> ;
  assign s_axi_control_RDATA[11] = \<const0> ;
  assign s_axi_control_RDATA[10] = \<const0> ;
  assign s_axi_control_RDATA[9] = \^s_axi_control_RDATA [9];
  assign s_axi_control_RDATA[8] = \<const0> ;
  assign s_axi_control_RDATA[7] = \^s_axi_control_RDATA [7];
  assign s_axi_control_RDATA[6] = \<const0> ;
  assign s_axi_control_RDATA[5] = \<const0> ;
  assign s_axi_control_RDATA[4:0] = \^s_axi_control_RDATA [4:0];
  assign s_axi_control_RRESP[1] = \<const0> ;
  assign s_axi_control_RRESP[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  (* srl_bus_name = "inst/\\add_ln16_reg_557_pp0_iter2_reg_reg " *) 
  (* srl_name = "inst/\\add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3 " *) 
  SRL16E \add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D(\^in2_Addr_A [2]),
        .Q(\add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3_n_0 ));
  (* srl_bus_name = "inst/\\add_ln16_reg_557_pp0_iter2_reg_reg " *) 
  (* srl_name = "inst/\\add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3 " *) 
  SRL16E \add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D(\^in2_Addr_A [3]),
        .Q(\add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3_n_0 ));
  (* srl_bus_name = "inst/\\add_ln16_reg_557_pp0_iter2_reg_reg " *) 
  (* srl_name = "inst/\\add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3 " *) 
  SRL16E \add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D(flow_control_loop_delay_pipe_U_n_30),
        .Q(\add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3_n_0 ));
  (* srl_bus_name = "inst/\\add_ln16_reg_557_pp0_iter2_reg_reg " *) 
  (* srl_name = "inst/\\add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3 " *) 
  SRL16E \add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D(add_ln16_fu_313_p2),
        .Q(\add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3_n_0 ));
  FDRE \add_ln16_reg_557_pp0_iter3_reg_reg[0] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(\add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3_n_0 ),
        .Q(\^out_r_Addr_A [2]),
        .R(1'b0));
  FDRE \add_ln16_reg_557_pp0_iter3_reg_reg[1] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(\add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3_n_0 ),
        .Q(\^out_r_Addr_A [3]),
        .R(1'b0));
  FDRE \add_ln16_reg_557_pp0_iter3_reg_reg[2] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(\add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3_n_0 ),
        .Q(\^out_r_Addr_A [4]),
        .R(1'b0));
  FDRE \add_ln16_reg_557_pp0_iter3_reg_reg[3] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(\add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3_n_0 ),
        .Q(\^out_r_Addr_A [5]),
        .R(1'b0));
  (* srl_name = "inst/ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2" *) 
  SRL16E ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2
       (.A0(1'b1),
        .A1(1'b0),
        .A2(1'b0),
        .A3(1'b0),
        .CE(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D(ap_loop_exit_ready),
        .Q(ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2_n_0));
  FDRE ap_condition_exit_pp0_iter0_stage0_pp0_iter3_reg_reg
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2_n_0),
        .Q(ap_loop_exit_ready_pp0_iter3_reg),
        .R(1'b0));
  FDRE ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg_reg
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(ap_loop_exit_ready_pp0_iter3_reg),
        .Q(ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg),
        .R(1'b0));
  (* inverted = "yes" *) 
  FDRE #(
    .INIT(1'b1)) 
    ap_done_reg_reg_inv
       (.C(ap_clk),
        .CE(1'b1),
        .D(control_s_axi_U_n_8),
        .Q(ap_block_pp0_stage0_subdone),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    ap_enable_reg_pp0_iter1_reg
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(ap_start_int),
        .Q(ap_enable_reg_pp0_iter1),
        .R(out_r_Rst_A));
  FDRE #(
    .INIT(1'b0)) 
    ap_enable_reg_pp0_iter2_reg
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(ap_enable_reg_pp0_iter1),
        .Q(ap_enable_reg_pp0_iter2),
        .R(out_r_Rst_A));
  FDRE #(
    .INIT(1'b0)) 
    ap_enable_reg_pp0_iter3_reg
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(ap_enable_reg_pp0_iter2),
        .Q(ap_enable_reg_pp0_iter3),
        .R(out_r_Rst_A));
  FDRE #(
    .INIT(1'b0)) 
    ap_enable_reg_pp0_iter4_reg
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(ap_enable_reg_pp0_iter3),
        .Q(ap_enable_reg_pp0_iter4),
        .R(out_r_Rst_A));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'hE2)) 
    ap_loop_exit_ready_pp0_iter4_reg_i_1
       (.I0(ap_loop_exit_ready_pp0_iter4_reg),
        .I1(ap_block_pp0_stage0_subdone),
        .I2(ap_loop_exit_ready_pp0_iter3_reg),
        .O(ap_loop_exit_ready_pp0_iter4_reg_i_1_n_0));
  FDRE ap_loop_exit_ready_pp0_iter4_reg_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_loop_exit_ready_pp0_iter4_reg_i_1_n_0),
        .Q(ap_loop_exit_ready_pp0_iter4_reg),
        .R(1'b0));
  (* SHREG_EXTRACT = "no" *) 
  FDRE #(
    .INIT(1'b1)) 
    ap_rst_n_inv_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_rst_reg_1),
        .Q(out_r_Rst_A),
        .R(1'b0));
  (* SHREG_EXTRACT = "no" *) 
  FDRE #(
    .INIT(1'b1)) 
    ap_rst_reg_1_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_rst_reg_2),
        .Q(ap_rst_reg_1),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    ap_rst_reg_2_i_1
       (.I0(ap_rst_n),
        .O(ap_rst_reg_2_i_1_n_0));
  (* SHREG_EXTRACT = "no" *) 
  FDRE #(
    .INIT(1'b1)) 
    ap_rst_reg_2_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_rst_reg_2_i_1_n_0),
        .Q(ap_rst_reg_2),
        .R(1'b0));
  bd_0_hls_inst_0_mat_mul_control_s_axi control_s_axi_U
       (.\FSM_onehot_rstate_reg[1]_0 (s_axi_control_ARREADY),
        .\FSM_onehot_wstate_reg[1]_0 (s_axi_control_AWREADY),
        .\FSM_onehot_wstate_reg[2]_0 (s_axi_control_WREADY),
        .ap_block_pp0_stage0_subdone(ap_block_pp0_stage0_subdone),
        .ap_clk(ap_clk),
        .ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg(ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg),
        .ap_enable_reg_pp0_iter1(ap_enable_reg_pp0_iter1),
        .ap_enable_reg_pp0_iter2(ap_enable_reg_pp0_iter2),
        .ap_enable_reg_pp0_iter3(ap_enable_reg_pp0_iter3),
        .ap_enable_reg_pp0_iter4(ap_enable_reg_pp0_iter4),
        .ap_loop_exit_ready_pp0_iter4_reg(ap_loop_exit_ready_pp0_iter4_reg),
        .ap_loop_exit_ready_pp0_iter4_reg_reg(control_s_axi_U_n_8),
        .ap_start(ap_start),
        .ap_start_int(ap_start_int),
        .int_task_ap_done_reg_0(out_r_Rst_A),
        .interrupt(interrupt),
        .rewind_ap_ready_reg(rewind_ap_ready_reg),
        .s_axi_control_ARADDR(s_axi_control_ARADDR),
        .s_axi_control_ARVALID(s_axi_control_ARVALID),
        .s_axi_control_AWADDR(s_axi_control_AWADDR[3:2]),
        .s_axi_control_AWVALID(s_axi_control_AWVALID),
        .s_axi_control_BREADY(s_axi_control_BREADY),
        .s_axi_control_BVALID(s_axi_control_BVALID),
        .s_axi_control_RDATA({\^s_axi_control_RDATA [9],\^s_axi_control_RDATA [7],\^s_axi_control_RDATA [4:0]}),
        .s_axi_control_RREADY(s_axi_control_RREADY),
        .s_axi_control_RVALID(s_axi_control_RVALID),
        .s_axi_control_WDATA({s_axi_control_WDATA[7],s_axi_control_WDATA[4],s_axi_control_WDATA[1:0]}),
        .s_axi_control_WSTRB(s_axi_control_WSTRB[0]),
        .s_axi_control_WVALID(s_axi_control_WVALID));
  bd_0_hls_inst_0_mat_mul_flow_control_loop_delay_pipe flow_control_loop_delay_pipe_U
       (.D({add_ln9_1_fu_415_p2[4],flow_control_loop_delay_pipe_U_n_3,add_ln9_1_fu_415_p2[2],flow_control_loop_delay_pipe_U_n_5,add_ln9_1_fu_415_p2[0]}),
        .Q(indvar_flatten131_fu_74),
        .SR(flow_control_loop_delay_pipe_U_n_26),
        .add_ln16_fu_313_p2(add_ln16_fu_313_p2),
        .ap_block_pp0_stage0_subdone(ap_block_pp0_stage0_subdone),
        .ap_clk(ap_clk),
        .ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg(ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg),
        .ap_enable_reg_pp0_iter1(ap_enable_reg_pp0_iter1),
        .ap_loop_exit_ready(ap_loop_exit_ready),
        .ap_start(ap_start),
        .\i2_fu_78_reg[0] (flow_control_loop_delay_pipe_U_n_30),
        .\icmp_ln108_reg_161_reg[0] (flow_control_loop_delay_pipe_U_n_1),
        .\icmp_ln108_reg_161_reg[0]_0 (\icmp_ln108_reg_161_reg_n_0_[0] ),
        .icmp_ln10_fu_435_p2(icmp_ln10_fu_435_p2),
        .icmp_ln10_reg_591(icmp_ln10_reg_591),
        .icmp_ln9_fu_441_p2(icmp_ln9_fu_441_p2),
        .icmp_ln9_reg_596(icmp_ln9_reg_596),
        .in1_Addr_A(\^in1_Addr_A ),
        .in1_Addr_B(\^in1_Addr_B ),
        .\in1_Addr_B[5] (i2_fu_78),
        .in2_Addr_A(\^in2_Addr_A [5]),
        .\in2_Addr_A[4] (j4_fu_86),
        .in2_Addr_B({\^in2_Addr_B ,\^in2_Addr_A [3:2]}),
        .indvar_flatten3_fu_82(indvar_flatten3_fu_82),
        .\indvar_flatten3_fu_82_reg[0] (select_ln10_1_fu_427_p3),
        .\indvar_flatten3_fu_82_reg[0]_0 (flow_control_loop_delay_pipe_U_n_33),
        .\indvar_flatten3_fu_82_reg[1] (flow_control_loop_delay_pipe_U_n_32),
        .\indvar_flatten3_fu_82_reg[2] (flow_control_loop_delay_pipe_U_n_29),
        .\indvar_flatten3_fu_82_reg[4] (flow_control_loop_delay_pipe_U_n_16),
        .\j4_fu_86_reg[0] (\^in2_Addr_A [4]),
        .\k5_fu_90_reg[1] (flow_control_loop_delay_pipe_U_n_28),
        .\k5_fu_90_reg[2] (k5_fu_90),
        .p_1_in(p_1_in),
        .rewind_ap_ready_reg(rewind_ap_ready_reg),
        .rewind_ap_ready_reg_reg_0(in1_EN_A),
        .rewind_ap_ready_reg_reg_1(flow_control_loop_delay_pipe_U_n_31),
        .rewind_ap_ready_reg_reg_2(out_r_Rst_A),
        .xor_ln12_reg_586(xor_ln12_reg_586),
        .\xor_ln12_reg_586_reg[0] ({tmp_5_fu_401_p3,flow_control_loop_delay_pipe_U_n_9}));
  FDRE #(
    .INIT(1'b0)) 
    \i2_fu_78_reg[0] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(\^in1_Addr_A [4]),
        .Q(i2_fu_78[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \i2_fu_78_reg[1] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(\^in1_Addr_A [5]),
        .Q(i2_fu_78[1]),
        .R(1'b0));
  (* srl_bus_name = "inst/\\icmp_ln108_reg_161_pp0_iter2_reg_reg " *) 
  (* srl_name = "inst/\\icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2 " *) 
  SRL16E \icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2 
       (.A0(1'b1),
        .A1(1'b0),
        .A2(1'b0),
        .A3(1'b0),
        .CE(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D(\icmp_ln108_reg_161_reg_n_0_[0] ),
        .Q(\icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2_n_0 ));
  FDRE \icmp_ln108_reg_161_pp0_iter3_reg_reg[0] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(\icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2_n_0 ),
        .Q(icmp_ln108_reg_161_pp0_iter3_reg),
        .R(1'b0));
  FDRE \icmp_ln108_reg_161_reg[0] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(flow_control_loop_delay_pipe_U_n_1),
        .Q(\icmp_ln108_reg_161_reg_n_0_[0] ),
        .R(1'b0));
  FDRE \icmp_ln10_reg_591_reg[0] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(icmp_ln10_fu_435_p2),
        .Q(icmp_ln10_reg_591),
        .R(1'b0));
  FDRE \icmp_ln9_reg_596_reg[0] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(icmp_ln9_fu_441_p2),
        .Q(icmp_ln9_reg_596),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten131_fu_74_reg[0] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(add_ln9_1_fu_415_p2[0]),
        .Q(indvar_flatten131_fu_74[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten131_fu_74_reg[1] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(flow_control_loop_delay_pipe_U_n_5),
        .Q(indvar_flatten131_fu_74[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten131_fu_74_reg[2] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(add_ln9_1_fu_415_p2[2]),
        .Q(indvar_flatten131_fu_74[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten131_fu_74_reg[3] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(flow_control_loop_delay_pipe_U_n_3),
        .Q(indvar_flatten131_fu_74[3]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten131_fu_74_reg[4] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(add_ln9_1_fu_415_p2[4]),
        .Q(indvar_flatten131_fu_74[4]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten3_fu_82_reg[0] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(select_ln10_1_fu_427_p3),
        .Q(indvar_flatten3_fu_82[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten3_fu_82_reg[1] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(flow_control_loop_delay_pipe_U_n_33),
        .Q(indvar_flatten3_fu_82[1]),
        .R(flow_control_loop_delay_pipe_U_n_31));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten3_fu_82_reg[2] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(flow_control_loop_delay_pipe_U_n_32),
        .Q(indvar_flatten3_fu_82[2]),
        .R(flow_control_loop_delay_pipe_U_n_31));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten3_fu_82_reg[3] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(flow_control_loop_delay_pipe_U_n_29),
        .Q(indvar_flatten3_fu_82[3]),
        .R(flow_control_loop_delay_pipe_U_n_31));
  FDRE #(
    .INIT(1'b0)) 
    \indvar_flatten3_fu_82_reg[4] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(flow_control_loop_delay_pipe_U_n_16),
        .Q(indvar_flatten3_fu_82[4]),
        .R(flow_control_loop_delay_pipe_U_n_31));
  FDRE #(
    .INIT(1'b0)) 
    \j4_fu_86_reg[0] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(\^in2_Addr_A [2]),
        .Q(j4_fu_86[0]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \j4_fu_86_reg[1] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(\^in2_Addr_A [3]),
        .Q(j4_fu_86[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \j4_fu_86_reg[2] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(\^in2_Addr_B [4]),
        .Q(j4_fu_86[2]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \k5_fu_90_reg[1] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(flow_control_loop_delay_pipe_U_n_9),
        .Q(k5_fu_90[1]),
        .R(1'b0));
  FDRE #(
    .INIT(1'b0)) 
    \k5_fu_90_reg[2] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(tmp_5_fu_401_p3),
        .Q(k5_fu_90[2]),
        .R(1'b0));
  bd_0_hls_inst_0_mat_mul_mul_32s_32s_32_2_1 mul_32s_32s_32_2_1_U1
       (.CEB2(p_5_in),
        .D({buff0_reg__1,mul_32s_32s_32_2_1_U1_n_16,mul_32s_32s_32_2_1_U1_n_17,mul_32s_32s_32_2_1_U1_n_18,mul_32s_32s_32_2_1_U1_n_19,mul_32s_32s_32_2_1_U1_n_20,mul_32s_32s_32_2_1_U1_n_21,mul_32s_32s_32_2_1_U1_n_22,mul_32s_32s_32_2_1_U1_n_23,mul_32s_32s_32_2_1_U1_n_24,mul_32s_32s_32_2_1_U1_n_25,mul_32s_32s_32_2_1_U1_n_26,mul_32s_32s_32_2_1_U1_n_27,mul_32s_32s_32_2_1_U1_n_28,mul_32s_32s_32_2_1_U1_n_29,mul_32s_32s_32_2_1_U1_n_30,mul_32s_32s_32_2_1_U1_n_31}),
        .ap_block_pp0_stage0_subdone(ap_block_pp0_stage0_subdone),
        .ap_clk(ap_clk),
        .in1_Dout_B(in1_Dout_B),
        .in2_Dout_B(in2_Dout_B));
  bd_0_hls_inst_0_mat_mul_mul_32s_32s_32_2_1_0 mul_32s_32s_32_2_1_U2
       (.CEB2(p_5_in),
        .D({buff0_reg__1_0,mul_32s_32s_32_2_1_U2_n_17,mul_32s_32s_32_2_1_U2_n_18,mul_32s_32s_32_2_1_U2_n_19,mul_32s_32s_32_2_1_U2_n_20,mul_32s_32s_32_2_1_U2_n_21,mul_32s_32s_32_2_1_U2_n_22,mul_32s_32s_32_2_1_U2_n_23,mul_32s_32s_32_2_1_U2_n_24,mul_32s_32s_32_2_1_U2_n_25,mul_32s_32s_32_2_1_U2_n_26,mul_32s_32s_32_2_1_U2_n_27,mul_32s_32s_32_2_1_U2_n_28,mul_32s_32s_32_2_1_U2_n_29,mul_32s_32s_32_2_1_U2_n_30,mul_32s_32s_32_2_1_U2_n_31,mul_32s_32s_32_2_1_U2_n_32}),
        .ap_block_pp0_stage0_subdone(ap_block_pp0_stage0_subdone),
        .ap_clk(ap_clk),
        .ap_enable_reg_pp0_iter1(ap_enable_reg_pp0_iter1),
        .in1_Dout_A(in1_Dout_A),
        .in2_Dout_A(in2_Dout_A));
  FDRE \mul_ln14_1_reg_625_reg[0] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_32),
        .Q(mul_ln14_1_reg_625[0]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[10] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_22),
        .Q(mul_ln14_1_reg_625[10]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[11] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_21),
        .Q(mul_ln14_1_reg_625[11]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[12] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_20),
        .Q(mul_ln14_1_reg_625[12]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[13] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_19),
        .Q(mul_ln14_1_reg_625[13]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[14] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_18),
        .Q(mul_ln14_1_reg_625[14]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[15] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_17),
        .Q(mul_ln14_1_reg_625[15]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[16] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[16]),
        .Q(mul_ln14_1_reg_625[16]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[17] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[17]),
        .Q(mul_ln14_1_reg_625[17]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[18] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[18]),
        .Q(mul_ln14_1_reg_625[18]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[19] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[19]),
        .Q(mul_ln14_1_reg_625[19]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[1] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_31),
        .Q(mul_ln14_1_reg_625[1]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[20] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[20]),
        .Q(mul_ln14_1_reg_625[20]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[21] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[21]),
        .Q(mul_ln14_1_reg_625[21]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[22] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[22]),
        .Q(mul_ln14_1_reg_625[22]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[23] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[23]),
        .Q(mul_ln14_1_reg_625[23]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[24] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[24]),
        .Q(mul_ln14_1_reg_625[24]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[25] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[25]),
        .Q(mul_ln14_1_reg_625[25]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[26] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[26]),
        .Q(mul_ln14_1_reg_625[26]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[27] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[27]),
        .Q(mul_ln14_1_reg_625[27]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[28] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[28]),
        .Q(mul_ln14_1_reg_625[28]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[29] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[29]),
        .Q(mul_ln14_1_reg_625[29]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[2] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_30),
        .Q(mul_ln14_1_reg_625[2]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[30] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[30]),
        .Q(mul_ln14_1_reg_625[30]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[31] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1_0[31]),
        .Q(mul_ln14_1_reg_625[31]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[3] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_29),
        .Q(mul_ln14_1_reg_625[3]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[4] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_28),
        .Q(mul_ln14_1_reg_625[4]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[5] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_27),
        .Q(mul_ln14_1_reg_625[5]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[6] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_26),
        .Q(mul_ln14_1_reg_625[6]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[7] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_25),
        .Q(mul_ln14_1_reg_625[7]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[8] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_24),
        .Q(mul_ln14_1_reg_625[8]),
        .R(1'b0));
  FDRE \mul_ln14_1_reg_625_reg[9] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U2_n_23),
        .Q(mul_ln14_1_reg_625[9]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[0] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_31),
        .Q(mul_ln14_reg_620[0]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[10] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_21),
        .Q(mul_ln14_reg_620[10]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[11] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_20),
        .Q(mul_ln14_reg_620[11]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[12] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_19),
        .Q(mul_ln14_reg_620[12]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[13] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_18),
        .Q(mul_ln14_reg_620[13]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[14] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_17),
        .Q(mul_ln14_reg_620[14]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[15] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_16),
        .Q(mul_ln14_reg_620[15]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[16] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[16]),
        .Q(mul_ln14_reg_620[16]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[17] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[17]),
        .Q(mul_ln14_reg_620[17]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[18] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[18]),
        .Q(mul_ln14_reg_620[18]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[19] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[19]),
        .Q(mul_ln14_reg_620[19]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[1] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_30),
        .Q(mul_ln14_reg_620[1]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[20] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[20]),
        .Q(mul_ln14_reg_620[20]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[21] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[21]),
        .Q(mul_ln14_reg_620[21]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[22] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[22]),
        .Q(mul_ln14_reg_620[22]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[23] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[23]),
        .Q(mul_ln14_reg_620[23]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[24] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[24]),
        .Q(mul_ln14_reg_620[24]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[25] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[25]),
        .Q(mul_ln14_reg_620[25]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[26] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[26]),
        .Q(mul_ln14_reg_620[26]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[27] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[27]),
        .Q(mul_ln14_reg_620[27]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[28] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[28]),
        .Q(mul_ln14_reg_620[28]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[29] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[29]),
        .Q(mul_ln14_reg_620[29]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[2] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_29),
        .Q(mul_ln14_reg_620[2]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[30] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[30]),
        .Q(mul_ln14_reg_620[30]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[31] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(buff0_reg__1[31]),
        .Q(mul_ln14_reg_620[31]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[3] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_28),
        .Q(mul_ln14_reg_620[3]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[4] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_27),
        .Q(mul_ln14_reg_620[4]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[5] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_26),
        .Q(mul_ln14_reg_620[5]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[6] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_25),
        .Q(mul_ln14_reg_620[6]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[7] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_24),
        .Q(mul_ln14_reg_620[7]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[8] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_23),
        .Q(mul_ln14_reg_620[8]),
        .R(1'b0));
  FDRE \mul_ln14_reg_620_reg[9] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(mul_32s_32s_32_2_1_U1_n_22),
        .Q(mul_ln14_reg_620[9]),
        .R(1'b0));
  (* srl_bus_name = "inst/\\or_ln9_reg_552_pp0_iter2_reg_reg " *) 
  (* srl_name = "inst/\\or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3 " *) 
  SRL16E \or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D(p_1_in),
        .Q(\or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3_n_0 ));
  FDRE \or_ln9_reg_552_pp0_iter3_reg_reg[0] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(\or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3_n_0 ),
        .Q(or_ln9_reg_552_pp0_iter3_reg),
        .R(1'b0));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \out_r_Din_A[0]_INST_0 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\out_r_Din_A[0]_INST_0_n_0 ,\out_r_Din_A[0]_INST_0_n_1 ,\out_r_Din_A[0]_INST_0_n_2 ,\out_r_Din_A[0]_INST_0_n_3 ,\out_r_Din_A[0]_INST_0_n_4 ,\out_r_Din_A[0]_INST_0_n_5 ,\out_r_Din_A[0]_INST_0_n_6 ,\out_r_Din_A[0]_INST_0_n_7 }),
        .DI({\out_r_Din_A[0]_INST_0_i_1_n_0 ,\out_r_Din_A[0]_INST_0_i_2_n_0 ,\out_r_Din_A[0]_INST_0_i_3_n_0 ,\out_r_Din_A[0]_INST_0_i_4_n_0 ,\out_r_Din_A[0]_INST_0_i_5_n_0 ,\out_r_Din_A[0]_INST_0_i_6_n_0 ,\out_r_Din_A[0]_INST_0_i_7_n_0 ,1'b0}),
        .O(out_r_Din_A[7:0]),
        .S({\out_r_Din_A[0]_INST_0_i_8_n_0 ,\out_r_Din_A[0]_INST_0_i_9_n_0 ,\out_r_Din_A[0]_INST_0_i_10_n_0 ,\out_r_Din_A[0]_INST_0_i_11_n_0 ,\out_r_Din_A[0]_INST_0_i_12_n_0 ,\out_r_Din_A[0]_INST_0_i_13_n_0 ,\out_r_Din_A[0]_INST_0_i_14_n_0 ,\out_r_Din_A[0]_INST_0_i_15_n_0 }));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[0]_INST_0_i_1 
       (.I0(mul_ln14_reg_620[6]),
        .I1(mul_ln14_1_reg_625[6]),
        .I2(\sum6_fu_94_reg_n_0_[6] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[0]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[0]_INST_0_i_10 
       (.I0(\out_r_Din_A[0]_INST_0_i_3_n_0 ),
        .I1(mul_ln14_1_reg_625[5]),
        .I2(mul_ln14_reg_620[5]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[5] ),
        .O(\out_r_Din_A[0]_INST_0_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[0]_INST_0_i_11 
       (.I0(\out_r_Din_A[0]_INST_0_i_4_n_0 ),
        .I1(mul_ln14_1_reg_625[4]),
        .I2(mul_ln14_reg_620[4]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[4] ),
        .O(\out_r_Din_A[0]_INST_0_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[0]_INST_0_i_12 
       (.I0(\out_r_Din_A[0]_INST_0_i_5_n_0 ),
        .I1(mul_ln14_1_reg_625[3]),
        .I2(mul_ln14_reg_620[3]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[3] ),
        .O(\out_r_Din_A[0]_INST_0_i_12_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[0]_INST_0_i_13 
       (.I0(\out_r_Din_A[0]_INST_0_i_6_n_0 ),
        .I1(mul_ln14_1_reg_625[2]),
        .I2(mul_ln14_reg_620[2]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[2] ),
        .O(\out_r_Din_A[0]_INST_0_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[0]_INST_0_i_14 
       (.I0(\out_r_Din_A[0]_INST_0_i_7_n_0 ),
        .I1(mul_ln14_1_reg_625[1]),
        .I2(mul_ln14_reg_620[1]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[1] ),
        .O(\out_r_Din_A[0]_INST_0_i_14_n_0 ));
  (* HLUTNM = "lutpair0" *) 
  LUT5 #(
    .INIT(32'h66966666)) 
    \out_r_Din_A[0]_INST_0_i_15 
       (.I0(mul_ln14_reg_620[0]),
        .I1(mul_ln14_1_reg_625[0]),
        .I2(\sum6_fu_94_reg_n_0_[0] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[0]_INST_0_i_15_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[0]_INST_0_i_2 
       (.I0(mul_ln14_reg_620[5]),
        .I1(mul_ln14_1_reg_625[5]),
        .I2(\sum6_fu_94_reg_n_0_[5] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[0]_INST_0_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[0]_INST_0_i_3 
       (.I0(mul_ln14_reg_620[4]),
        .I1(mul_ln14_1_reg_625[4]),
        .I2(\sum6_fu_94_reg_n_0_[4] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[0]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[0]_INST_0_i_4 
       (.I0(mul_ln14_reg_620[3]),
        .I1(mul_ln14_1_reg_625[3]),
        .I2(\sum6_fu_94_reg_n_0_[3] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[0]_INST_0_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[0]_INST_0_i_5 
       (.I0(mul_ln14_reg_620[2]),
        .I1(mul_ln14_1_reg_625[2]),
        .I2(\sum6_fu_94_reg_n_0_[2] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[0]_INST_0_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[0]_INST_0_i_6 
       (.I0(mul_ln14_reg_620[1]),
        .I1(mul_ln14_1_reg_625[1]),
        .I2(\sum6_fu_94_reg_n_0_[1] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[0]_INST_0_i_6_n_0 ));
  (* HLUTNM = "lutpair0" *) 
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[0]_INST_0_i_7 
       (.I0(mul_ln14_reg_620[0]),
        .I1(mul_ln14_1_reg_625[0]),
        .I2(\sum6_fu_94_reg_n_0_[0] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[0]_INST_0_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[0]_INST_0_i_8 
       (.I0(\out_r_Din_A[0]_INST_0_i_1_n_0 ),
        .I1(mul_ln14_1_reg_625[7]),
        .I2(mul_ln14_reg_620[7]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[7] ),
        .O(\out_r_Din_A[0]_INST_0_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[0]_INST_0_i_9 
       (.I0(\out_r_Din_A[0]_INST_0_i_2_n_0 ),
        .I1(mul_ln14_1_reg_625[6]),
        .I2(mul_ln14_reg_620[6]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[6] ),
        .O(\out_r_Din_A[0]_INST_0_i_9_n_0 ));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \out_r_Din_A[16]_INST_0 
       (.CI(\out_r_Din_A[8]_INST_0_n_0 ),
        .CI_TOP(1'b0),
        .CO({\out_r_Din_A[16]_INST_0_n_0 ,\out_r_Din_A[16]_INST_0_n_1 ,\out_r_Din_A[16]_INST_0_n_2 ,\out_r_Din_A[16]_INST_0_n_3 ,\out_r_Din_A[16]_INST_0_n_4 ,\out_r_Din_A[16]_INST_0_n_5 ,\out_r_Din_A[16]_INST_0_n_6 ,\out_r_Din_A[16]_INST_0_n_7 }),
        .DI({\out_r_Din_A[16]_INST_0_i_1_n_0 ,\out_r_Din_A[16]_INST_0_i_2_n_0 ,\out_r_Din_A[16]_INST_0_i_3_n_0 ,\out_r_Din_A[16]_INST_0_i_4_n_0 ,\out_r_Din_A[16]_INST_0_i_5_n_0 ,\out_r_Din_A[16]_INST_0_i_6_n_0 ,\out_r_Din_A[16]_INST_0_i_7_n_0 ,\out_r_Din_A[16]_INST_0_i_8_n_0 }),
        .O(out_r_Din_A[23:16]),
        .S({\out_r_Din_A[16]_INST_0_i_9_n_0 ,\out_r_Din_A[16]_INST_0_i_10_n_0 ,\out_r_Din_A[16]_INST_0_i_11_n_0 ,\out_r_Din_A[16]_INST_0_i_12_n_0 ,\out_r_Din_A[16]_INST_0_i_13_n_0 ,\out_r_Din_A[16]_INST_0_i_14_n_0 ,\out_r_Din_A[16]_INST_0_i_15_n_0 ,\out_r_Din_A[16]_INST_0_i_16_n_0 }));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[16]_INST_0_i_1 
       (.I0(mul_ln14_reg_620[22]),
        .I1(mul_ln14_1_reg_625[22]),
        .I2(\sum6_fu_94_reg_n_0_[22] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[16]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[16]_INST_0_i_10 
       (.I0(\out_r_Din_A[16]_INST_0_i_2_n_0 ),
        .I1(mul_ln14_1_reg_625[22]),
        .I2(mul_ln14_reg_620[22]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[22] ),
        .O(\out_r_Din_A[16]_INST_0_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[16]_INST_0_i_11 
       (.I0(\out_r_Din_A[16]_INST_0_i_3_n_0 ),
        .I1(mul_ln14_1_reg_625[21]),
        .I2(mul_ln14_reg_620[21]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[21] ),
        .O(\out_r_Din_A[16]_INST_0_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[16]_INST_0_i_12 
       (.I0(\out_r_Din_A[16]_INST_0_i_4_n_0 ),
        .I1(mul_ln14_1_reg_625[20]),
        .I2(mul_ln14_reg_620[20]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[20] ),
        .O(\out_r_Din_A[16]_INST_0_i_12_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[16]_INST_0_i_13 
       (.I0(\out_r_Din_A[16]_INST_0_i_5_n_0 ),
        .I1(mul_ln14_1_reg_625[19]),
        .I2(mul_ln14_reg_620[19]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[19] ),
        .O(\out_r_Din_A[16]_INST_0_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[16]_INST_0_i_14 
       (.I0(\out_r_Din_A[16]_INST_0_i_6_n_0 ),
        .I1(mul_ln14_1_reg_625[18]),
        .I2(mul_ln14_reg_620[18]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[18] ),
        .O(\out_r_Din_A[16]_INST_0_i_14_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[16]_INST_0_i_15 
       (.I0(\out_r_Din_A[16]_INST_0_i_7_n_0 ),
        .I1(mul_ln14_1_reg_625[17]),
        .I2(mul_ln14_reg_620[17]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[17] ),
        .O(\out_r_Din_A[16]_INST_0_i_15_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[16]_INST_0_i_16 
       (.I0(\out_r_Din_A[16]_INST_0_i_8_n_0 ),
        .I1(mul_ln14_1_reg_625[16]),
        .I2(mul_ln14_reg_620[16]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[16] ),
        .O(\out_r_Din_A[16]_INST_0_i_16_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[16]_INST_0_i_2 
       (.I0(mul_ln14_reg_620[21]),
        .I1(mul_ln14_1_reg_625[21]),
        .I2(\sum6_fu_94_reg_n_0_[21] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[16]_INST_0_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[16]_INST_0_i_3 
       (.I0(mul_ln14_reg_620[20]),
        .I1(mul_ln14_1_reg_625[20]),
        .I2(\sum6_fu_94_reg_n_0_[20] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[16]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[16]_INST_0_i_4 
       (.I0(mul_ln14_reg_620[19]),
        .I1(mul_ln14_1_reg_625[19]),
        .I2(\sum6_fu_94_reg_n_0_[19] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[16]_INST_0_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[16]_INST_0_i_5 
       (.I0(mul_ln14_reg_620[18]),
        .I1(mul_ln14_1_reg_625[18]),
        .I2(\sum6_fu_94_reg_n_0_[18] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[16]_INST_0_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[16]_INST_0_i_6 
       (.I0(mul_ln14_reg_620[17]),
        .I1(mul_ln14_1_reg_625[17]),
        .I2(\sum6_fu_94_reg_n_0_[17] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[16]_INST_0_i_6_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[16]_INST_0_i_7 
       (.I0(mul_ln14_reg_620[16]),
        .I1(mul_ln14_1_reg_625[16]),
        .I2(\sum6_fu_94_reg_n_0_[16] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[16]_INST_0_i_7_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[16]_INST_0_i_8 
       (.I0(mul_ln14_reg_620[15]),
        .I1(mul_ln14_1_reg_625[15]),
        .I2(\sum6_fu_94_reg_n_0_[15] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[16]_INST_0_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[16]_INST_0_i_9 
       (.I0(\out_r_Din_A[16]_INST_0_i_1_n_0 ),
        .I1(mul_ln14_1_reg_625[23]),
        .I2(mul_ln14_reg_620[23]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[23] ),
        .O(\out_r_Din_A[16]_INST_0_i_9_n_0 ));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \out_r_Din_A[24]_INST_0 
       (.CI(\out_r_Din_A[16]_INST_0_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_out_r_Din_A[24]_INST_0_CO_UNCONNECTED [7],\out_r_Din_A[24]_INST_0_n_1 ,\out_r_Din_A[24]_INST_0_n_2 ,\out_r_Din_A[24]_INST_0_n_3 ,\out_r_Din_A[24]_INST_0_n_4 ,\out_r_Din_A[24]_INST_0_n_5 ,\out_r_Din_A[24]_INST_0_n_6 ,\out_r_Din_A[24]_INST_0_n_7 }),
        .DI({1'b0,\out_r_Din_A[24]_INST_0_i_1_n_0 ,\out_r_Din_A[24]_INST_0_i_2_n_0 ,\out_r_Din_A[24]_INST_0_i_3_n_0 ,\out_r_Din_A[24]_INST_0_i_4_n_0 ,\out_r_Din_A[24]_INST_0_i_5_n_0 ,\out_r_Din_A[24]_INST_0_i_6_n_0 ,\out_r_Din_A[24]_INST_0_i_7_n_0 }),
        .O(out_r_Din_A[31:24]),
        .S({\out_r_Din_A[24]_INST_0_i_8_n_0 ,\out_r_Din_A[24]_INST_0_i_9_n_0 ,\out_r_Din_A[24]_INST_0_i_10_n_0 ,\out_r_Din_A[24]_INST_0_i_11_n_0 ,\out_r_Din_A[24]_INST_0_i_12_n_0 ,\out_r_Din_A[24]_INST_0_i_13_n_0 ,\out_r_Din_A[24]_INST_0_i_14_n_0 ,\out_r_Din_A[24]_INST_0_i_15_n_0 }));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[24]_INST_0_i_1 
       (.I0(mul_ln14_reg_620[29]),
        .I1(mul_ln14_1_reg_625[29]),
        .I2(\sum6_fu_94_reg_n_0_[29] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[24]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[24]_INST_0_i_10 
       (.I0(\out_r_Din_A[24]_INST_0_i_2_n_0 ),
        .I1(mul_ln14_1_reg_625[29]),
        .I2(mul_ln14_reg_620[29]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[29] ),
        .O(\out_r_Din_A[24]_INST_0_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[24]_INST_0_i_11 
       (.I0(\out_r_Din_A[24]_INST_0_i_3_n_0 ),
        .I1(mul_ln14_1_reg_625[28]),
        .I2(mul_ln14_reg_620[28]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[28] ),
        .O(\out_r_Din_A[24]_INST_0_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[24]_INST_0_i_12 
       (.I0(\out_r_Din_A[24]_INST_0_i_4_n_0 ),
        .I1(mul_ln14_1_reg_625[27]),
        .I2(mul_ln14_reg_620[27]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[27] ),
        .O(\out_r_Din_A[24]_INST_0_i_12_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[24]_INST_0_i_13 
       (.I0(\out_r_Din_A[24]_INST_0_i_5_n_0 ),
        .I1(mul_ln14_1_reg_625[26]),
        .I2(mul_ln14_reg_620[26]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[26] ),
        .O(\out_r_Din_A[24]_INST_0_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[24]_INST_0_i_14 
       (.I0(\out_r_Din_A[24]_INST_0_i_6_n_0 ),
        .I1(mul_ln14_1_reg_625[25]),
        .I2(mul_ln14_reg_620[25]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[25] ),
        .O(\out_r_Din_A[24]_INST_0_i_14_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[24]_INST_0_i_15 
       (.I0(\out_r_Din_A[24]_INST_0_i_7_n_0 ),
        .I1(mul_ln14_1_reg_625[24]),
        .I2(mul_ln14_reg_620[24]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[24] ),
        .O(\out_r_Din_A[24]_INST_0_i_15_n_0 ));
  LUT5 #(
    .INIT(32'h20DFDF20)) 
    \out_r_Din_A[24]_INST_0_i_16 
       (.I0(\sum6_fu_94_reg_n_0_[31] ),
        .I1(icmp_ln108_reg_161_pp0_iter3_reg),
        .I2(or_ln9_reg_552_pp0_iter3_reg),
        .I3(mul_ln14_reg_620[31]),
        .I4(mul_ln14_1_reg_625[31]),
        .O(\out_r_Din_A[24]_INST_0_i_16_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[24]_INST_0_i_2 
       (.I0(mul_ln14_reg_620[28]),
        .I1(mul_ln14_1_reg_625[28]),
        .I2(\sum6_fu_94_reg_n_0_[28] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[24]_INST_0_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[24]_INST_0_i_3 
       (.I0(mul_ln14_reg_620[27]),
        .I1(mul_ln14_1_reg_625[27]),
        .I2(\sum6_fu_94_reg_n_0_[27] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[24]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[24]_INST_0_i_4 
       (.I0(mul_ln14_reg_620[26]),
        .I1(mul_ln14_1_reg_625[26]),
        .I2(\sum6_fu_94_reg_n_0_[26] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[24]_INST_0_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[24]_INST_0_i_5 
       (.I0(mul_ln14_reg_620[25]),
        .I1(mul_ln14_1_reg_625[25]),
        .I2(\sum6_fu_94_reg_n_0_[25] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[24]_INST_0_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[24]_INST_0_i_6 
       (.I0(mul_ln14_reg_620[24]),
        .I1(mul_ln14_1_reg_625[24]),
        .I2(\sum6_fu_94_reg_n_0_[24] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[24]_INST_0_i_6_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[24]_INST_0_i_7 
       (.I0(mul_ln14_reg_620[23]),
        .I1(mul_ln14_1_reg_625[23]),
        .I2(\sum6_fu_94_reg_n_0_[23] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[24]_INST_0_i_7_n_0 ));
  LUT6 #(
    .INIT(64'h00DFDFFFFF202000)) 
    \out_r_Din_A[24]_INST_0_i_8 
       (.I0(or_ln9_reg_552_pp0_iter3_reg),
        .I1(icmp_ln108_reg_161_pp0_iter3_reg),
        .I2(\sum6_fu_94_reg_n_0_[30] ),
        .I3(mul_ln14_1_reg_625[30]),
        .I4(mul_ln14_reg_620[30]),
        .I5(\out_r_Din_A[24]_INST_0_i_16_n_0 ),
        .O(\out_r_Din_A[24]_INST_0_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[24]_INST_0_i_9 
       (.I0(\out_r_Din_A[24]_INST_0_i_1_n_0 ),
        .I1(mul_ln14_1_reg_625[30]),
        .I2(mul_ln14_reg_620[30]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[30] ),
        .O(\out_r_Din_A[24]_INST_0_i_9_n_0 ));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \out_r_Din_A[8]_INST_0 
       (.CI(\out_r_Din_A[0]_INST_0_n_0 ),
        .CI_TOP(1'b0),
        .CO({\out_r_Din_A[8]_INST_0_n_0 ,\out_r_Din_A[8]_INST_0_n_1 ,\out_r_Din_A[8]_INST_0_n_2 ,\out_r_Din_A[8]_INST_0_n_3 ,\out_r_Din_A[8]_INST_0_n_4 ,\out_r_Din_A[8]_INST_0_n_5 ,\out_r_Din_A[8]_INST_0_n_6 ,\out_r_Din_A[8]_INST_0_n_7 }),
        .DI({\out_r_Din_A[8]_INST_0_i_1_n_0 ,\out_r_Din_A[8]_INST_0_i_2_n_0 ,\out_r_Din_A[8]_INST_0_i_3_n_0 ,\out_r_Din_A[8]_INST_0_i_4_n_0 ,\out_r_Din_A[8]_INST_0_i_5_n_0 ,\out_r_Din_A[8]_INST_0_i_6_n_0 ,\out_r_Din_A[8]_INST_0_i_7_n_0 ,\out_r_Din_A[8]_INST_0_i_8_n_0 }),
        .O(out_r_Din_A[15:8]),
        .S({\out_r_Din_A[8]_INST_0_i_9_n_0 ,\out_r_Din_A[8]_INST_0_i_10_n_0 ,\out_r_Din_A[8]_INST_0_i_11_n_0 ,\out_r_Din_A[8]_INST_0_i_12_n_0 ,\out_r_Din_A[8]_INST_0_i_13_n_0 ,\out_r_Din_A[8]_INST_0_i_14_n_0 ,\out_r_Din_A[8]_INST_0_i_15_n_0 ,\out_r_Din_A[8]_INST_0_i_16_n_0 }));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[8]_INST_0_i_1 
       (.I0(mul_ln14_reg_620[14]),
        .I1(mul_ln14_1_reg_625[14]),
        .I2(\sum6_fu_94_reg_n_0_[14] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[8]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[8]_INST_0_i_10 
       (.I0(\out_r_Din_A[8]_INST_0_i_2_n_0 ),
        .I1(mul_ln14_1_reg_625[14]),
        .I2(mul_ln14_reg_620[14]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[14] ),
        .O(\out_r_Din_A[8]_INST_0_i_10_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[8]_INST_0_i_11 
       (.I0(\out_r_Din_A[8]_INST_0_i_3_n_0 ),
        .I1(mul_ln14_1_reg_625[13]),
        .I2(mul_ln14_reg_620[13]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[13] ),
        .O(\out_r_Din_A[8]_INST_0_i_11_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[8]_INST_0_i_12 
       (.I0(\out_r_Din_A[8]_INST_0_i_4_n_0 ),
        .I1(mul_ln14_1_reg_625[12]),
        .I2(mul_ln14_reg_620[12]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[12] ),
        .O(\out_r_Din_A[8]_INST_0_i_12_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[8]_INST_0_i_13 
       (.I0(\out_r_Din_A[8]_INST_0_i_5_n_0 ),
        .I1(mul_ln14_1_reg_625[11]),
        .I2(mul_ln14_reg_620[11]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[11] ),
        .O(\out_r_Din_A[8]_INST_0_i_13_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[8]_INST_0_i_14 
       (.I0(\out_r_Din_A[8]_INST_0_i_6_n_0 ),
        .I1(mul_ln14_1_reg_625[10]),
        .I2(mul_ln14_reg_620[10]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[10] ),
        .O(\out_r_Din_A[8]_INST_0_i_14_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[8]_INST_0_i_15 
       (.I0(\out_r_Din_A[8]_INST_0_i_7_n_0 ),
        .I1(mul_ln14_1_reg_625[9]),
        .I2(mul_ln14_reg_620[9]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[9] ),
        .O(\out_r_Din_A[8]_INST_0_i_15_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[8]_INST_0_i_16 
       (.I0(\out_r_Din_A[8]_INST_0_i_8_n_0 ),
        .I1(mul_ln14_1_reg_625[8]),
        .I2(mul_ln14_reg_620[8]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[8] ),
        .O(\out_r_Din_A[8]_INST_0_i_16_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[8]_INST_0_i_2 
       (.I0(mul_ln14_reg_620[13]),
        .I1(mul_ln14_1_reg_625[13]),
        .I2(\sum6_fu_94_reg_n_0_[13] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[8]_INST_0_i_2_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[8]_INST_0_i_3 
       (.I0(mul_ln14_reg_620[12]),
        .I1(mul_ln14_1_reg_625[12]),
        .I2(\sum6_fu_94_reg_n_0_[12] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[8]_INST_0_i_3_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[8]_INST_0_i_4 
       (.I0(mul_ln14_reg_620[11]),
        .I1(mul_ln14_1_reg_625[11]),
        .I2(\sum6_fu_94_reg_n_0_[11] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[8]_INST_0_i_4_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[8]_INST_0_i_5 
       (.I0(mul_ln14_reg_620[10]),
        .I1(mul_ln14_1_reg_625[10]),
        .I2(\sum6_fu_94_reg_n_0_[10] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[8]_INST_0_i_5_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[8]_INST_0_i_6 
       (.I0(mul_ln14_reg_620[9]),
        .I1(mul_ln14_1_reg_625[9]),
        .I2(\sum6_fu_94_reg_n_0_[9] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[8]_INST_0_i_6_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[8]_INST_0_i_7 
       (.I0(mul_ln14_reg_620[8]),
        .I1(mul_ln14_1_reg_625[8]),
        .I2(\sum6_fu_94_reg_n_0_[8] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[8]_INST_0_i_7_n_0 ));
  LUT5 #(
    .INIT(32'h88E88888)) 
    \out_r_Din_A[8]_INST_0_i_8 
       (.I0(mul_ln14_reg_620[7]),
        .I1(mul_ln14_1_reg_625[7]),
        .I2(\sum6_fu_94_reg_n_0_[7] ),
        .I3(icmp_ln108_reg_161_pp0_iter3_reg),
        .I4(or_ln9_reg_552_pp0_iter3_reg),
        .O(\out_r_Din_A[8]_INST_0_i_8_n_0 ));
  LUT6 #(
    .INIT(64'h9696699696969696)) 
    \out_r_Din_A[8]_INST_0_i_9 
       (.I0(\out_r_Din_A[8]_INST_0_i_1_n_0 ),
        .I1(mul_ln14_1_reg_625[15]),
        .I2(mul_ln14_reg_620[15]),
        .I3(or_ln9_reg_552_pp0_iter3_reg),
        .I4(icmp_ln108_reg_161_pp0_iter3_reg),
        .I5(\sum6_fu_94_reg_n_0_[15] ),
        .O(\out_r_Din_A[8]_INST_0_i_9_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    out_r_EN_A_INST_0
       (.I0(ap_enable_reg_pp0_iter4),
        .I1(ap_block_pp0_stage0_subdone),
        .O(out_r_EN_A));
  (* SOFT_HLUTNM = "soft_lutpair14" *) 
  LUT3 #(
    .INIT(8'h80)) 
    \out_r_WEN_A[0]_INST_0 
       (.I0(tmp_5_reg_582_pp0_iter3_reg),
        .I1(ap_block_pp0_stage0_subdone),
        .I2(ap_enable_reg_pp0_iter4),
        .O(\^out_r_WEN_A ));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[0] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[0]),
        .Q(\sum6_fu_94_reg_n_0_[0] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[10] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[10]),
        .Q(\sum6_fu_94_reg_n_0_[10] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[11] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[11]),
        .Q(\sum6_fu_94_reg_n_0_[11] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[12] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[12]),
        .Q(\sum6_fu_94_reg_n_0_[12] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[13] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[13]),
        .Q(\sum6_fu_94_reg_n_0_[13] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[14] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[14]),
        .Q(\sum6_fu_94_reg_n_0_[14] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[15] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[15]),
        .Q(\sum6_fu_94_reg_n_0_[15] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[16] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[16]),
        .Q(\sum6_fu_94_reg_n_0_[16] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[17] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[17]),
        .Q(\sum6_fu_94_reg_n_0_[17] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[18] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[18]),
        .Q(\sum6_fu_94_reg_n_0_[18] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[19] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[19]),
        .Q(\sum6_fu_94_reg_n_0_[19] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[1] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[1]),
        .Q(\sum6_fu_94_reg_n_0_[1] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[20] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[20]),
        .Q(\sum6_fu_94_reg_n_0_[20] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[21] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[21]),
        .Q(\sum6_fu_94_reg_n_0_[21] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[22] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[22]),
        .Q(\sum6_fu_94_reg_n_0_[22] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[23] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[23]),
        .Q(\sum6_fu_94_reg_n_0_[23] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[24] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[24]),
        .Q(\sum6_fu_94_reg_n_0_[24] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[25] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[25]),
        .Q(\sum6_fu_94_reg_n_0_[25] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[26] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[26]),
        .Q(\sum6_fu_94_reg_n_0_[26] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[27] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[27]),
        .Q(\sum6_fu_94_reg_n_0_[27] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[28] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[28]),
        .Q(\sum6_fu_94_reg_n_0_[28] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[29] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[29]),
        .Q(\sum6_fu_94_reg_n_0_[29] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[2] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[2]),
        .Q(\sum6_fu_94_reg_n_0_[2] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[30] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[30]),
        .Q(\sum6_fu_94_reg_n_0_[30] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[31] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[31]),
        .Q(\sum6_fu_94_reg_n_0_[31] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[3] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[3]),
        .Q(\sum6_fu_94_reg_n_0_[3] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[4] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[4]),
        .Q(\sum6_fu_94_reg_n_0_[4] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[5] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[5]),
        .Q(\sum6_fu_94_reg_n_0_[5] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[6] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[6]),
        .Q(\sum6_fu_94_reg_n_0_[6] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[7] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[7]),
        .Q(\sum6_fu_94_reg_n_0_[7] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[8] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[8]),
        .Q(\sum6_fu_94_reg_n_0_[8] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  FDRE #(
    .INIT(1'b0)) 
    \sum6_fu_94_reg[9] 
       (.C(ap_clk),
        .CE(out_r_EN_A),
        .D(out_r_Din_A[9]),
        .Q(\sum6_fu_94_reg_n_0_[9] ),
        .R(flow_control_loop_delay_pipe_U_n_26));
  (* srl_bus_name = "inst/\\tmp_5_reg_582_pp0_iter2_reg_reg " *) 
  (* srl_name = "inst/\\tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3 " *) 
  SRL16E \tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3 
       (.A0(1'b0),
        .A1(1'b1),
        .A2(1'b0),
        .A3(1'b0),
        .CE(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D(tmp_5_fu_401_p3),
        .Q(\tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3_n_0 ));
  FDRE \tmp_5_reg_582_pp0_iter3_reg_reg[0] 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(\tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3_n_0 ),
        .Q(tmp_5_reg_582_pp0_iter3_reg),
        .R(1'b0));
  FDRE \xor_ln12_reg_586_reg[0] 
       (.C(ap_clk),
        .CE(in1_EN_A),
        .D(flow_control_loop_delay_pipe_U_n_28),
        .Q(xor_ln12_reg_586),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "mat_mul_control_s_axi" *) 
module bd_0_hls_inst_0_mat_mul_control_s_axi
   (interrupt,
    \FSM_onehot_rstate_reg[1]_0 ,
    s_axi_control_RVALID,
    \FSM_onehot_wstate_reg[1]_0 ,
    \FSM_onehot_wstate_reg[2]_0 ,
    s_axi_control_BVALID,
    ap_start,
    ap_start_int,
    ap_loop_exit_ready_pp0_iter4_reg_reg,
    s_axi_control_RDATA,
    int_task_ap_done_reg_0,
    ap_clk,
    s_axi_control_ARVALID,
    s_axi_control_RREADY,
    s_axi_control_AWVALID,
    s_axi_control_WVALID,
    s_axi_control_BREADY,
    s_axi_control_WSTRB,
    s_axi_control_WDATA,
    rewind_ap_ready_reg,
    ap_enable_reg_pp0_iter3,
    ap_enable_reg_pp0_iter2,
    ap_enable_reg_pp0_iter1,
    ap_enable_reg_pp0_iter4,
    s_axi_control_ARADDR,
    ap_block_pp0_stage0_subdone,
    ap_loop_exit_ready_pp0_iter4_reg,
    ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg,
    s_axi_control_AWADDR);
  output interrupt;
  output \FSM_onehot_rstate_reg[1]_0 ;
  output s_axi_control_RVALID;
  output \FSM_onehot_wstate_reg[1]_0 ;
  output \FSM_onehot_wstate_reg[2]_0 ;
  output s_axi_control_BVALID;
  output ap_start;
  output ap_start_int;
  output ap_loop_exit_ready_pp0_iter4_reg_reg;
  output [6:0]s_axi_control_RDATA;
  input int_task_ap_done_reg_0;
  input ap_clk;
  input s_axi_control_ARVALID;
  input s_axi_control_RREADY;
  input s_axi_control_AWVALID;
  input s_axi_control_WVALID;
  input s_axi_control_BREADY;
  input [0:0]s_axi_control_WSTRB;
  input [3:0]s_axi_control_WDATA;
  input rewind_ap_ready_reg;
  input ap_enable_reg_pp0_iter3;
  input ap_enable_reg_pp0_iter2;
  input ap_enable_reg_pp0_iter1;
  input ap_enable_reg_pp0_iter4;
  input [3:0]s_axi_control_ARADDR;
  input ap_block_pp0_stage0_subdone;
  input ap_loop_exit_ready_pp0_iter4_reg;
  input ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg;
  input [1:0]s_axi_control_AWADDR;

  wire \FSM_onehot_rstate[1]_i_1_n_0 ;
  wire \FSM_onehot_rstate[2]_i_1_n_0 ;
  wire \FSM_onehot_rstate_reg[1]_0 ;
  wire \FSM_onehot_wstate[1]_i_1_n_0 ;
  wire \FSM_onehot_wstate[2]_i_1_n_0 ;
  wire \FSM_onehot_wstate[3]_i_1_n_0 ;
  wire \FSM_onehot_wstate_reg[1]_0 ;
  wire \FSM_onehot_wstate_reg[2]_0 ;
  wire ap_block_pp0_stage0_subdone;
  wire ap_clk;
  wire ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg;
  wire ap_enable_reg_pp0_iter1;
  wire ap_enable_reg_pp0_iter2;
  wire ap_enable_reg_pp0_iter3;
  wire ap_enable_reg_pp0_iter4;
  wire ap_idle;
  wire ap_loop_exit_ready_pp0_iter4_reg;
  wire ap_loop_exit_ready_pp0_iter4_reg_reg;
  wire ap_start;
  wire ap_start_int;
  wire ar_hs;
  wire auto_restart_done_i_1_n_0;
  wire auto_restart_done_reg_n_0;
  wire auto_restart_status_i_1_n_0;
  wire auto_restart_status_reg_n_0;
  wire int_ap_continue0;
  wire int_ap_ready;
  wire int_ap_ready_i_1_n_0;
  wire int_ap_ready_i_2_n_0;
  wire int_ap_start1;
  wire int_ap_start_i_1_n_0;
  wire int_auto_restart_i_1_n_0;
  wire int_gie_i_1_n_0;
  wire int_gie_i_2_n_0;
  wire int_gie_reg_n_0;
  wire int_ier10_out;
  wire \int_ier_reg_n_0_[0] ;
  wire int_interrupt0;
  wire int_isr7_out;
  wire \int_isr[0]_i_1_n_0 ;
  wire \int_isr[1]_i_1_n_0 ;
  wire \int_isr_reg_n_0_[0] ;
  wire \int_isr_reg_n_0_[1] ;
  wire int_task_ap_done;
  wire int_task_ap_done0;
  wire int_task_ap_done_reg_0;
  wire interrupt;
  wire [7:2]p_0_in;
  wire p_0_in__0;
  wire [1:0]rdata;
  wire \rdata[0]_i_2_n_0 ;
  wire \rdata[1]_i_2_n_0 ;
  wire \rdata[9]_i_1_n_0 ;
  wire rewind_ap_ready_reg;
  wire [3:0]s_axi_control_ARADDR;
  wire s_axi_control_ARVALID;
  wire [1:0]s_axi_control_AWADDR;
  wire s_axi_control_AWVALID;
  wire s_axi_control_BREADY;
  wire s_axi_control_BVALID;
  wire [6:0]s_axi_control_RDATA;
  wire s_axi_control_RREADY;
  wire s_axi_control_RVALID;
  wire [3:0]s_axi_control_WDATA;
  wire [0:0]s_axi_control_WSTRB;
  wire s_axi_control_WVALID;
  wire waddr;
  wire \waddr_reg_n_0_[2] ;
  wire \waddr_reg_n_0_[3] ;

  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT4 #(
    .INIT(16'h8BFB)) 
    \FSM_onehot_rstate[1]_i_1 
       (.I0(s_axi_control_RREADY),
        .I1(s_axi_control_RVALID),
        .I2(\FSM_onehot_rstate_reg[1]_0 ),
        .I3(s_axi_control_ARVALID),
        .O(\FSM_onehot_rstate[1]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_rstate[2]_i_1 
       (.I0(\FSM_onehot_rstate_reg[1]_0 ),
        .I1(s_axi_control_ARVALID),
        .I2(s_axi_control_RREADY),
        .I3(s_axi_control_RVALID),
        .O(\FSM_onehot_rstate[2]_i_1_n_0 ));
  (* FSM_ENCODED_STATES = "RDIDLE:010,RDDATA:100,iSTATE:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_rstate_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_rstate[1]_i_1_n_0 ),
        .Q(\FSM_onehot_rstate_reg[1]_0 ),
        .R(int_task_ap_done_reg_0));
  (* FSM_ENCODED_STATES = "RDIDLE:010,RDDATA:100,iSTATE:001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_rstate_reg[2] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_rstate[2]_i_1_n_0 ),
        .Q(s_axi_control_RVALID),
        .R(int_task_ap_done_reg_0));
  LUT5 #(
    .INIT(32'hAE0CAE3F)) 
    \FSM_onehot_wstate[1]_i_1 
       (.I0(s_axi_control_BREADY),
        .I1(\FSM_onehot_wstate_reg[1]_0 ),
        .I2(s_axi_control_AWVALID),
        .I3(s_axi_control_BVALID),
        .I4(\FSM_onehot_wstate_reg[2]_0 ),
        .O(\FSM_onehot_wstate[1]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_wstate[2]_i_1 
       (.I0(s_axi_control_AWVALID),
        .I1(\FSM_onehot_wstate_reg[1]_0 ),
        .I2(s_axi_control_WVALID),
        .I3(\FSM_onehot_wstate_reg[2]_0 ),
        .O(\FSM_onehot_wstate[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'h8F88)) 
    \FSM_onehot_wstate[3]_i_1 
       (.I0(s_axi_control_WVALID),
        .I1(\FSM_onehot_wstate_reg[2]_0 ),
        .I2(s_axi_control_BREADY),
        .I3(s_axi_control_BVALID),
        .O(\FSM_onehot_wstate[3]_i_1_n_0 ));
  (* FSM_ENCODED_STATES = "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_wstate_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_wstate[1]_i_1_n_0 ),
        .Q(\FSM_onehot_wstate_reg[1]_0 ),
        .R(int_task_ap_done_reg_0));
  (* FSM_ENCODED_STATES = "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_wstate_reg[2] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_wstate[2]_i_1_n_0 ),
        .Q(\FSM_onehot_wstate_reg[2]_0 ),
        .R(int_task_ap_done_reg_0));
  (* FSM_ENCODED_STATES = "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001" *) 
  FDRE #(
    .INIT(1'b0)) 
    \FSM_onehot_wstate_reg[3] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\FSM_onehot_wstate[3]_i_1_n_0 ),
        .Q(s_axi_control_BVALID),
        .R(int_task_ap_done_reg_0));
  LUT5 #(
    .INIT(32'hFFFFFFF4)) 
    ap_done_reg_inv_i_1
       (.I0(ap_loop_exit_ready_pp0_iter4_reg),
        .I1(ap_block_pp0_stage0_subdone),
        .I2(auto_restart_status_reg_n_0),
        .I3(int_task_ap_done_reg_0),
        .I4(p_0_in[4]),
        .O(ap_loop_exit_ready_pp0_iter4_reg_reg));
  LUT2 #(
    .INIT(4'h2)) 
    ap_enable_reg_pp0_iter1_i_1
       (.I0(ap_start),
        .I1(rewind_ap_ready_reg),
        .O(ap_start_int));
  LUT5 #(
    .INIT(32'h75553000)) 
    auto_restart_done_i_1
       (.I0(p_0_in[4]),
        .I1(p_0_in[2]),
        .I2(auto_restart_status_reg_n_0),
        .I3(ap_idle),
        .I4(auto_restart_done_reg_n_0),
        .O(auto_restart_done_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    auto_restart_done_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(auto_restart_done_i_1_n_0),
        .Q(auto_restart_done_reg_n_0),
        .R(int_task_ap_done_reg_0));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hBA)) 
    auto_restart_status_i_1
       (.I0(p_0_in[7]),
        .I1(ap_idle),
        .I2(auto_restart_status_reg_n_0),
        .O(auto_restart_status_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    auto_restart_status_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(auto_restart_status_i_1_n_0),
        .Q(auto_restart_status_reg_n_0),
        .R(int_task_ap_done_reg_0));
  LUT6 #(
    .INIT(64'h0000000008000000)) 
    int_ap_continue_i_1
       (.I0(s_axi_control_WDATA[2]),
        .I1(s_axi_control_WSTRB),
        .I2(\waddr_reg_n_0_[2] ),
        .I3(s_axi_control_WVALID),
        .I4(\FSM_onehot_wstate_reg[2]_0 ),
        .I5(\waddr_reg_n_0_[3] ),
        .O(int_ap_continue0));
  FDRE #(
    .INIT(1'b0)) 
    int_ap_continue_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_ap_continue0),
        .Q(p_0_in[4]),
        .R(int_task_ap_done_reg_0));
  LUT6 #(
    .INIT(64'h000000000000000D)) 
    int_ap_idle_i_1
       (.I0(ap_start),
        .I1(rewind_ap_ready_reg),
        .I2(ap_enable_reg_pp0_iter3),
        .I3(ap_enable_reg_pp0_iter2),
        .I4(ap_enable_reg_pp0_iter1),
        .I5(ap_enable_reg_pp0_iter4),
        .O(ap_idle));
  FDRE #(
    .INIT(1'b0)) 
    int_ap_idle_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_idle),
        .Q(p_0_in[2]),
        .R(int_task_ap_done_reg_0));
  LUT6 #(
    .INIT(64'hFF40FFFF40404040)) 
    int_ap_ready_i_1
       (.I0(p_0_in[7]),
        .I1(ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg),
        .I2(ap_block_pp0_stage0_subdone),
        .I3(int_ap_ready_i_2_n_0),
        .I4(ar_hs),
        .I5(int_ap_ready),
        .O(int_ap_ready_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'hFFFE)) 
    int_ap_ready_i_2
       (.I0(s_axi_control_ARADDR[3]),
        .I1(s_axi_control_ARADDR[0]),
        .I2(s_axi_control_ARADDR[1]),
        .I3(s_axi_control_ARADDR[2]),
        .O(int_ap_ready_i_2_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_ap_ready_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_ap_ready_i_1_n_0),
        .Q(int_ap_ready),
        .R(int_task_ap_done_reg_0));
  LUT6 #(
    .INIT(64'hFFBFBFBFFF808080)) 
    int_ap_start_i_1
       (.I0(p_0_in[7]),
        .I1(ap_block_pp0_stage0_subdone),
        .I2(ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg),
        .I3(int_ap_start1),
        .I4(s_axi_control_WDATA[0]),
        .I5(ap_start),
        .O(int_ap_start_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h00400000)) 
    int_ap_start_i_2
       (.I0(\waddr_reg_n_0_[3] ),
        .I1(\FSM_onehot_wstate_reg[2]_0 ),
        .I2(s_axi_control_WVALID),
        .I3(\waddr_reg_n_0_[2] ),
        .I4(s_axi_control_WSTRB),
        .O(int_ap_start1));
  FDRE #(
    .INIT(1'b0)) 
    int_ap_start_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_ap_start_i_1_n_0),
        .Q(ap_start),
        .R(int_task_ap_done_reg_0));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    int_auto_restart_i_1
       (.I0(s_axi_control_WDATA[3]),
        .I1(int_ap_start1),
        .I2(p_0_in[7]),
        .O(int_auto_restart_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_auto_restart_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_auto_restart_i_1_n_0),
        .Q(p_0_in[7]),
        .R(int_task_ap_done_reg_0));
  LUT6 #(
    .INIT(64'hEFFFFFFF20000000)) 
    int_gie_i_1
       (.I0(s_axi_control_WDATA[0]),
        .I1(\waddr_reg_n_0_[3] ),
        .I2(int_gie_i_2_n_0),
        .I3(\waddr_reg_n_0_[2] ),
        .I4(s_axi_control_WSTRB),
        .I5(int_gie_reg_n_0),
        .O(int_gie_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'h8)) 
    int_gie_i_2
       (.I0(\FSM_onehot_wstate_reg[2]_0 ),
        .I1(s_axi_control_WVALID),
        .O(int_gie_i_2_n_0));
  FDRE #(
    .INIT(1'b0)) 
    int_gie_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_gie_i_1_n_0),
        .Q(int_gie_reg_n_0),
        .R(int_task_ap_done_reg_0));
  LUT5 #(
    .INIT(32'h40000000)) 
    \int_ier[1]_i_1 
       (.I0(\waddr_reg_n_0_[2] ),
        .I1(s_axi_control_WSTRB),
        .I2(\FSM_onehot_wstate_reg[2]_0 ),
        .I3(s_axi_control_WVALID),
        .I4(\waddr_reg_n_0_[3] ),
        .O(int_ier10_out));
  FDRE #(
    .INIT(1'b0)) 
    \int_ier_reg[0] 
       (.C(ap_clk),
        .CE(int_ier10_out),
        .D(s_axi_control_WDATA[0]),
        .Q(\int_ier_reg_n_0_[0] ),
        .R(int_task_ap_done_reg_0));
  FDRE #(
    .INIT(1'b0)) 
    \int_ier_reg[1] 
       (.C(ap_clk),
        .CE(int_ier10_out),
        .D(s_axi_control_WDATA[1]),
        .Q(p_0_in__0),
        .R(int_task_ap_done_reg_0));
  LUT3 #(
    .INIT(8'hA8)) 
    int_interrupt_i_1
       (.I0(int_gie_reg_n_0),
        .I1(\int_isr_reg_n_0_[1] ),
        .I2(\int_isr_reg_n_0_[0] ),
        .O(int_interrupt0));
  FDRE #(
    .INIT(1'b0)) 
    int_interrupt_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_interrupt0),
        .Q(interrupt),
        .R(int_task_ap_done_reg_0));
  LUT6 #(
    .INIT(64'hF7FF7777F8FF8888)) 
    \int_isr[0]_i_1 
       (.I0(s_axi_control_WDATA[0]),
        .I1(int_isr7_out),
        .I2(ap_loop_exit_ready_pp0_iter4_reg),
        .I3(ap_block_pp0_stage0_subdone),
        .I4(\int_ier_reg_n_0_[0] ),
        .I5(\int_isr_reg_n_0_[0] ),
        .O(\int_isr[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h80000000)) 
    \int_isr[0]_i_2 
       (.I0(\waddr_reg_n_0_[2] ),
        .I1(s_axi_control_WSTRB),
        .I2(\FSM_onehot_wstate_reg[2]_0 ),
        .I3(s_axi_control_WVALID),
        .I4(\waddr_reg_n_0_[3] ),
        .O(int_isr7_out));
  LUT6 #(
    .INIT(64'hF7777777F8888888)) 
    \int_isr[1]_i_1 
       (.I0(s_axi_control_WDATA[1]),
        .I1(int_isr7_out),
        .I2(ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg),
        .I3(ap_block_pp0_stage0_subdone),
        .I4(p_0_in__0),
        .I5(\int_isr_reg_n_0_[1] ),
        .O(\int_isr[1]_i_1_n_0 ));
  FDRE #(
    .INIT(1'b0)) 
    \int_isr_reg[0] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_isr[0]_i_1_n_0 ),
        .Q(\int_isr_reg_n_0_[0] ),
        .R(int_task_ap_done_reg_0));
  FDRE #(
    .INIT(1'b0)) 
    \int_isr_reg[1] 
       (.C(ap_clk),
        .CE(1'b1),
        .D(\int_isr[1]_i_1_n_0 ),
        .Q(\int_isr_reg_n_0_[1] ),
        .R(int_task_ap_done_reg_0));
  LUT5 #(
    .INIT(32'h0000FF51)) 
    int_task_ap_done_i_1
       (.I0(auto_restart_status_reg_n_0),
        .I1(ap_block_pp0_stage0_subdone),
        .I2(ap_loop_exit_ready_pp0_iter4_reg),
        .I3(auto_restart_done_reg_n_0),
        .I4(p_0_in[4]),
        .O(int_task_ap_done0));
  FDRE #(
    .INIT(1'b0)) 
    int_task_ap_done_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(int_task_ap_done0),
        .Q(int_task_ap_done),
        .R(int_task_ap_done_reg_0));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT3 #(
    .INIT(8'h02)) 
    \rdata[0]_i_1 
       (.I0(\rdata[0]_i_2_n_0 ),
        .I1(s_axi_control_ARADDR[1]),
        .I2(s_axi_control_ARADDR[0]),
        .O(rdata[0]));
  LUT6 #(
    .INIT(64'hAFA0CFCFAFA0C0C0)) 
    \rdata[0]_i_2 
       (.I0(\int_isr_reg_n_0_[0] ),
        .I1(int_gie_reg_n_0),
        .I2(s_axi_control_ARADDR[2]),
        .I3(\int_ier_reg_n_0_[0] ),
        .I4(s_axi_control_ARADDR[3]),
        .I5(ap_start),
        .O(\rdata[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h00000000CCE200E2)) 
    \rdata[1]_i_1 
       (.I0(int_task_ap_done),
        .I1(s_axi_control_ARADDR[3]),
        .I2(p_0_in__0),
        .I3(s_axi_control_ARADDR[2]),
        .I4(\int_isr_reg_n_0_[1] ),
        .I5(\rdata[1]_i_2_n_0 ),
        .O(rdata[1]));
  LUT2 #(
    .INIT(4'hE)) 
    \rdata[1]_i_2 
       (.I0(s_axi_control_ARADDR[0]),
        .I1(s_axi_control_ARADDR[1]),
        .O(\rdata[1]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hFFFE000000000000)) 
    \rdata[9]_i_1 
       (.I0(s_axi_control_ARADDR[2]),
        .I1(s_axi_control_ARADDR[1]),
        .I2(s_axi_control_ARADDR[0]),
        .I3(s_axi_control_ARADDR[3]),
        .I4(\FSM_onehot_rstate_reg[1]_0 ),
        .I5(s_axi_control_ARVALID),
        .O(\rdata[9]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \rdata[9]_i_2 
       (.I0(s_axi_control_ARVALID),
        .I1(\FSM_onehot_rstate_reg[1]_0 ),
        .O(ar_hs));
  FDRE \rdata_reg[0] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(rdata[0]),
        .Q(s_axi_control_RDATA[0]),
        .R(1'b0));
  FDRE \rdata_reg[1] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(rdata[1]),
        .Q(s_axi_control_RDATA[1]),
        .R(1'b0));
  FDRE \rdata_reg[2] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(p_0_in[2]),
        .Q(s_axi_control_RDATA[2]),
        .R(\rdata[9]_i_1_n_0 ));
  FDRE \rdata_reg[3] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(int_ap_ready),
        .Q(s_axi_control_RDATA[3]),
        .R(\rdata[9]_i_1_n_0 ));
  FDRE \rdata_reg[4] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(p_0_in[4]),
        .Q(s_axi_control_RDATA[4]),
        .R(\rdata[9]_i_1_n_0 ));
  FDRE \rdata_reg[7] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(p_0_in[7]),
        .Q(s_axi_control_RDATA[5]),
        .R(\rdata[9]_i_1_n_0 ));
  FDRE \rdata_reg[9] 
       (.C(ap_clk),
        .CE(ar_hs),
        .D(interrupt),
        .Q(s_axi_control_RDATA[6]),
        .R(\rdata[9]_i_1_n_0 ));
  LUT2 #(
    .INIT(4'h8)) 
    \waddr[3]_i_1 
       (.I0(\FSM_onehot_wstate_reg[1]_0 ),
        .I1(s_axi_control_AWVALID),
        .O(waddr));
  FDRE \waddr_reg[2] 
       (.C(ap_clk),
        .CE(waddr),
        .D(s_axi_control_AWADDR[0]),
        .Q(\waddr_reg_n_0_[2] ),
        .R(1'b0));
  FDRE \waddr_reg[3] 
       (.C(ap_clk),
        .CE(waddr),
        .D(s_axi_control_AWADDR[1]),
        .Q(\waddr_reg_n_0_[3] ),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "mat_mul_flow_control_loop_delay_pipe" *) 
module bd_0_hls_inst_0_mat_mul_flow_control_loop_delay_pipe
   (rewind_ap_ready_reg,
    \icmp_ln108_reg_161_reg[0] ,
    D,
    icmp_ln9_fu_441_p2,
    \xor_ln12_reg_586_reg[0] ,
    in2_Addr_B,
    in1_Addr_B,
    \indvar_flatten3_fu_82_reg[4] ,
    icmp_ln10_fu_435_p2,
    \indvar_flatten3_fu_82_reg[0] ,
    add_ln16_fu_313_p2,
    \j4_fu_86_reg[0] ,
    in1_Addr_A,
    rewind_ap_ready_reg_reg_0,
    p_1_in,
    ap_loop_exit_ready,
    SR,
    in2_Addr_A,
    \k5_fu_90_reg[1] ,
    \indvar_flatten3_fu_82_reg[2] ,
    \i2_fu_78_reg[0] ,
    rewind_ap_ready_reg_reg_1,
    \indvar_flatten3_fu_82_reg[1] ,
    \indvar_flatten3_fu_82_reg[0]_0 ,
    rewind_ap_ready_reg_reg_2,
    ap_clk,
    \icmp_ln108_reg_161_reg[0]_0 ,
    icmp_ln10_reg_591,
    icmp_ln9_reg_596,
    ap_enable_reg_pp0_iter1,
    ap_block_pp0_stage0_subdone,
    Q,
    ap_start,
    xor_ln12_reg_586,
    \k5_fu_90_reg[2] ,
    \in1_Addr_B[5] ,
    indvar_flatten3_fu_82,
    \in2_Addr_A[4] ,
    ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg);
  output rewind_ap_ready_reg;
  output \icmp_ln108_reg_161_reg[0] ;
  output [4:0]D;
  output icmp_ln9_fu_441_p2;
  output [1:0]\xor_ln12_reg_586_reg[0] ;
  output [3:0]in2_Addr_B;
  output [1:0]in1_Addr_B;
  output \indvar_flatten3_fu_82_reg[4] ;
  output icmp_ln10_fu_435_p2;
  output [0:0]\indvar_flatten3_fu_82_reg[0] ;
  output [0:0]add_ln16_fu_313_p2;
  output \j4_fu_86_reg[0] ;
  output [1:0]in1_Addr_A;
  output rewind_ap_ready_reg_reg_0;
  output p_1_in;
  output ap_loop_exit_ready;
  output [0:0]SR;
  output [0:0]in2_Addr_A;
  output \k5_fu_90_reg[1] ;
  output \indvar_flatten3_fu_82_reg[2] ;
  output \i2_fu_78_reg[0] ;
  output rewind_ap_ready_reg_reg_1;
  output \indvar_flatten3_fu_82_reg[1] ;
  output \indvar_flatten3_fu_82_reg[0]_0 ;
  input rewind_ap_ready_reg_reg_2;
  input ap_clk;
  input \icmp_ln108_reg_161_reg[0]_0 ;
  input icmp_ln10_reg_591;
  input icmp_ln9_reg_596;
  input ap_enable_reg_pp0_iter1;
  input ap_block_pp0_stage0_subdone;
  input [4:0]Q;
  input ap_start;
  input xor_ln12_reg_586;
  input [1:0]\k5_fu_90_reg[2] ;
  input [1:0]\in1_Addr_B[5] ;
  input [4:0]indvar_flatten3_fu_82;
  input [2:0]\in2_Addr_A[4] ;
  input ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg;

  wire [4:0]D;
  wire [4:0]Q;
  wire [0:0]SR;
  wire [0:0]add_ln16_fu_313_p2;
  wire ap_block_pp0_stage0_subdone;
  wire ap_clk;
  wire ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg;
  wire ap_enable_reg_pp0_iter1;
  wire ap_loop_exit_ready;
  wire ap_loop_init;
  wire ap_loop_init_i_1_n_0;
  wire ap_start;
  wire \i2_fu_78_reg[0] ;
  wire \icmp_ln108_reg_161_reg[0] ;
  wire \icmp_ln108_reg_161_reg[0]_0 ;
  wire icmp_ln10_fu_435_p2;
  wire icmp_ln10_reg_591;
  wire \icmp_ln10_reg_591[0]_i_2_n_0 ;
  wire icmp_ln9_fu_441_p2;
  wire icmp_ln9_reg_596;
  wire [1:0]in1_Addr_A;
  wire \in1_Addr_A[4]_INST_0_i_1_n_0 ;
  wire \in1_Addr_A[5]_INST_0_i_1_n_0 ;
  wire [1:0]in1_Addr_B;
  wire \in1_Addr_B[4]_INST_0_i_1_n_0 ;
  wire [1:0]\in1_Addr_B[5] ;
  wire [0:0]in2_Addr_A;
  wire [2:0]\in2_Addr_A[4] ;
  wire [3:0]in2_Addr_B;
  wire \in2_Addr_B[5]_INST_0_i_1_n_0 ;
  wire [4:0]indvar_flatten3_fu_82;
  wire [0:0]\indvar_flatten3_fu_82_reg[0] ;
  wire \indvar_flatten3_fu_82_reg[0]_0 ;
  wire \indvar_flatten3_fu_82_reg[1] ;
  wire \indvar_flatten3_fu_82_reg[2] ;
  wire \indvar_flatten3_fu_82_reg[4] ;
  wire \j4_fu_86_reg[0] ;
  wire \k5_fu_90_reg[1] ;
  wire [1:0]\k5_fu_90_reg[2] ;
  wire p_1_in;
  wire rewind_ap_ready_reg;
  wire rewind_ap_ready_reg_i_1_n_0;
  wire rewind_ap_ready_reg_reg_0;
  wire rewind_ap_ready_reg_reg_1;
  wire rewind_ap_ready_reg_reg_2;
  wire xor_ln12_reg_586;
  wire [1:0]\xor_ln12_reg_586_reg[0] ;

  LUT6 #(
    .INIT(64'hA2AA5D555D55A2AA)) 
    \add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3_i_1 
       (.I0(\in1_Addr_B[5] [0]),
        .I1(ap_loop_init),
        .I2(rewind_ap_ready_reg),
        .I3(ap_start),
        .I4(\in1_Addr_A[5]_INST_0_i_1_n_0 ),
        .I5(\j4_fu_86_reg[0] ),
        .O(\i2_fu_78_reg[0] ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT5 #(
    .INIT(32'h9503A903)) 
    \add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3_i_1 
       (.I0(\in1_Addr_B[5] [1]),
        .I1(\j4_fu_86_reg[0] ),
        .I2(\in1_Addr_A[5]_INST_0_i_1_n_0 ),
        .I3(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I4(\in1_Addr_B[5] [0]),
        .O(add_ln16_fu_313_p2));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'h20)) 
    ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2_i_1
       (.I0(icmp_ln9_fu_441_p2),
        .I1(rewind_ap_ready_reg),
        .I2(ap_start),
        .O(ap_loop_exit_ready));
  LUT6 #(
    .INIT(64'hFFFFFFFFEFFF2000)) 
    ap_loop_init_i_1
       (.I0(icmp_ln9_fu_441_p2),
        .I1(rewind_ap_ready_reg),
        .I2(ap_start),
        .I3(ap_block_pp0_stage0_subdone),
        .I4(ap_loop_init),
        .I5(rewind_ap_ready_reg_reg_2),
        .O(ap_loop_init_i_1_n_0));
  FDRE #(
    .INIT(1'b1)) 
    ap_loop_init_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(ap_loop_init_i_1_n_0),
        .Q(ap_loop_init),
        .R(1'b0));
  LUT6 #(
    .INIT(64'h0C00ACAAAAAAAAAA)) 
    \icmp_ln108_reg_161[0]_i_1 
       (.I0(\icmp_ln108_reg_161_reg[0]_0 ),
        .I1(icmp_ln10_reg_591),
        .I2(icmp_ln9_reg_596),
        .I3(ap_enable_reg_pp0_iter1),
        .I4(ap_loop_init),
        .I5(ap_block_pp0_stage0_subdone),
        .O(\icmp_ln108_reg_161_reg[0] ));
  LUT5 #(
    .INIT(32'h01330000)) 
    \icmp_ln10_reg_591[0]_i_1 
       (.I0(indvar_flatten3_fu_82[4]),
        .I1(\icmp_ln10_reg_591[0]_i_2_n_0 ),
        .I2(indvar_flatten3_fu_82[3]),
        .I3(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I4(\in1_Addr_A[5]_INST_0_i_1_n_0 ),
        .O(icmp_ln10_fu_435_p2));
  LUT6 #(
    .INIT(64'h77F77777FFFFFFFF)) 
    \icmp_ln10_reg_591[0]_i_2 
       (.I0(indvar_flatten3_fu_82[1]),
        .I1(indvar_flatten3_fu_82[0]),
        .I2(ap_loop_init),
        .I3(rewind_ap_ready_reg),
        .I4(ap_start),
        .I5(indvar_flatten3_fu_82[2]),
        .O(\icmp_ln10_reg_591[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h8000000000000000)) 
    \icmp_ln9_reg_596[0]_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(Q[4]),
        .I4(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I5(Q[3]),
        .O(icmp_ln9_fu_441_p2));
  LUT6 #(
    .INIT(64'hB0FF4F004F004F00)) 
    \in1_Addr_A[4]_INST_0 
       (.I0(icmp_ln9_reg_596),
        .I1(ap_enable_reg_pp0_iter1),
        .I2(ap_loop_init),
        .I3(icmp_ln10_reg_591),
        .I4(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I5(\in1_Addr_B[5] [0]),
        .O(in1_Addr_A[0]));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'hDF)) 
    \in1_Addr_A[4]_INST_0_i_1 
       (.I0(ap_start),
        .I1(rewind_ap_ready_reg),
        .I2(ap_loop_init),
        .O(\in1_Addr_A[4]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hBB0BBBBB44044444)) 
    \in1_Addr_A[5]_INST_0 
       (.I0(\in1_Addr_A[5]_INST_0_i_1_n_0 ),
        .I1(\in1_Addr_B[5] [0]),
        .I2(ap_start),
        .I3(rewind_ap_ready_reg),
        .I4(ap_loop_init),
        .I5(\in1_Addr_B[5] [1]),
        .O(in1_Addr_A[1]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT4 #(
    .INIT(16'hDD5D)) 
    \in1_Addr_A[5]_INST_0_i_1 
       (.I0(icmp_ln10_reg_591),
        .I1(ap_loop_init),
        .I2(ap_enable_reg_pp0_iter1),
        .I3(icmp_ln9_reg_596),
        .O(\in1_Addr_A[5]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h0FFF78005A005A00)) 
    \in1_Addr_B[4]_INST_0 
       (.I0(\k5_fu_90_reg[2] [1]),
        .I1(xor_ln12_reg_586),
        .I2(\in1_Addr_B[5] [0]),
        .I3(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I4(icmp_ln10_reg_591),
        .I5(\in1_Addr_B[4]_INST_0_i_1_n_0 ),
        .O(in1_Addr_B[0]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT3 #(
    .INIT(8'h4F)) 
    \in1_Addr_B[4]_INST_0_i_1 
       (.I0(icmp_ln9_reg_596),
        .I1(ap_enable_reg_pp0_iter1),
        .I2(ap_loop_init),
        .O(\in1_Addr_B[4]_INST_0_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h9050A050A0A0A0A0)) 
    \in1_Addr_B[5]_INST_0 
       (.I0(\in1_Addr_B[5] [1]),
        .I1(\in2_Addr_B[5]_INST_0_i_1_n_0 ),
        .I2(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I3(\in1_Addr_A[5]_INST_0_i_1_n_0 ),
        .I4(\k5_fu_90_reg[2] [1]),
        .I5(\in1_Addr_B[5] [0]),
        .O(in1_Addr_B[1]));
  LUT6 #(
    .INIT(64'h807FFFFFFFFFFFFF)) 
    \in2_Addr_A[4]_INST_0 
       (.I0(\in2_Addr_B[5]_INST_0_i_1_n_0 ),
        .I1(\in2_Addr_A[4] [0]),
        .I2(\in2_Addr_A[4] [1]),
        .I3(\in2_Addr_A[4] [2]),
        .I4(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I5(\in1_Addr_A[5]_INST_0_i_1_n_0 ),
        .O(\j4_fu_86_reg[0] ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT2 #(
    .INIT(4'h9)) 
    \in2_Addr_A[5]_INST_0 
       (.I0(in2_Addr_B[3]),
        .I1(\j4_fu_86_reg[0] ),
        .O(in2_Addr_A));
  LUT6 #(
    .INIT(64'h66A66666AAAAAAAA)) 
    \in2_Addr_B[2]_INST_0 
       (.I0(\in2_Addr_B[5]_INST_0_i_1_n_0 ),
        .I1(\in2_Addr_A[4] [0]),
        .I2(ap_loop_init),
        .I3(rewind_ap_ready_reg),
        .I4(ap_start),
        .I5(\in1_Addr_A[5]_INST_0_i_1_n_0 ),
        .O(in2_Addr_B[0]));
  LUT6 #(
    .INIT(64'h00F0D2F000000000)) 
    \in2_Addr_B[3]_INST_0 
       (.I0(\in2_Addr_A[4] [0]),
        .I1(xor_ln12_reg_586),
        .I2(\in2_Addr_A[4] [1]),
        .I3(\in1_Addr_B[4]_INST_0_i_1_n_0 ),
        .I4(icmp_ln10_reg_591),
        .I5(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .O(in2_Addr_B[1]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \in2_Addr_B[4]_INST_0 
       (.I0(\j4_fu_86_reg[0] ),
        .O(in2_Addr_B[2]));
  LUT6 #(
    .INIT(64'h5155000000000000)) 
    \in2_Addr_B[5]_INST_0 
       (.I0(\in2_Addr_B[5]_INST_0_i_1_n_0 ),
        .I1(ap_start),
        .I2(rewind_ap_ready_reg),
        .I3(ap_loop_init),
        .I4(\in1_Addr_A[5]_INST_0_i_1_n_0 ),
        .I5(\k5_fu_90_reg[2] [0]),
        .O(in2_Addr_B[3]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'h0000005D)) 
    \in2_Addr_B[5]_INST_0_i_1 
       (.I0(ap_loop_init),
        .I1(ap_enable_reg_pp0_iter1),
        .I2(icmp_ln9_reg_596),
        .I3(icmp_ln10_reg_591),
        .I4(xor_ln12_reg_586),
        .O(\in2_Addr_B[5]_INST_0_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair12" *) 
  LUT3 #(
    .INIT(8'h40)) 
    in2_EN_B_INST_0
       (.I0(rewind_ap_ready_reg),
        .I1(ap_start),
        .I2(ap_block_pp0_stage0_subdone),
        .O(rewind_ap_ready_reg_reg_0));
  LUT2 #(
    .INIT(4'hB)) 
    \indvar_flatten131_fu_74[0]_i_1 
       (.I0(ap_loop_init),
        .I1(Q[0]),
        .O(D[0]));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT3 #(
    .INIT(8'h12)) 
    \indvar_flatten131_fu_74[1]_i_1 
       (.I0(Q[1]),
        .I1(ap_loop_init),
        .I2(Q[0]),
        .O(D[1]));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT4 #(
    .INIT(16'h0708)) 
    \indvar_flatten131_fu_74[2]_i_1 
       (.I0(Q[1]),
        .I1(Q[0]),
        .I2(ap_loop_init),
        .I3(Q[2]),
        .O(D[2]));
  LUT5 #(
    .INIT(32'h7F008000)) 
    \indvar_flatten131_fu_74[3]_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .I2(Q[2]),
        .I3(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I4(Q[3]),
        .O(D[3]));
  LUT6 #(
    .INIT(64'h7FFF000080000000)) 
    \indvar_flatten131_fu_74[4]_i_1 
       (.I0(Q[2]),
        .I1(Q[1]),
        .I2(Q[0]),
        .I3(Q[3]),
        .I4(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I5(Q[4]),
        .O(D[4]));
  LUT6 #(
    .INIT(64'h7F77FFFF77777777)) 
    \indvar_flatten3_fu_82[0]_i_1 
       (.I0(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I1(indvar_flatten3_fu_82[0]),
        .I2(icmp_ln9_reg_596),
        .I3(ap_enable_reg_pp0_iter1),
        .I4(ap_loop_init),
        .I5(icmp_ln10_reg_591),
        .O(\indvar_flatten3_fu_82_reg[0] ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT3 #(
    .INIT(8'h12)) 
    \indvar_flatten3_fu_82[1]_i_1 
       (.I0(indvar_flatten3_fu_82[0]),
        .I1(ap_loop_init),
        .I2(indvar_flatten3_fu_82[1]),
        .O(\indvar_flatten3_fu_82_reg[0]_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT4 #(
    .INIT(16'h0708)) 
    \indvar_flatten3_fu_82[2]_i_1 
       (.I0(indvar_flatten3_fu_82[1]),
        .I1(indvar_flatten3_fu_82[0]),
        .I2(ap_loop_init),
        .I3(indvar_flatten3_fu_82[2]),
        .O(\indvar_flatten3_fu_82_reg[1] ));
  LUT5 #(
    .INIT(32'h7F008000)) 
    \indvar_flatten3_fu_82[3]_i_1 
       (.I0(indvar_flatten3_fu_82[2]),
        .I1(indvar_flatten3_fu_82[0]),
        .I2(indvar_flatten3_fu_82[1]),
        .I3(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I4(indvar_flatten3_fu_82[3]),
        .O(\indvar_flatten3_fu_82_reg[2] ));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT4 #(
    .INIT(16'h1000)) 
    \indvar_flatten3_fu_82[4]_i_1 
       (.I0(\in1_Addr_A[5]_INST_0_i_1_n_0 ),
        .I1(rewind_ap_ready_reg),
        .I2(ap_start),
        .I3(ap_block_pp0_stage0_subdone),
        .O(rewind_ap_ready_reg_reg_1));
  LUT6 #(
    .INIT(64'h4888888888888888)) 
    \indvar_flatten3_fu_82[4]_i_2 
       (.I0(indvar_flatten3_fu_82[4]),
        .I1(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I2(indvar_flatten3_fu_82[3]),
        .I3(indvar_flatten3_fu_82[2]),
        .I4(indvar_flatten3_fu_82[0]),
        .I5(indvar_flatten3_fu_82[1]),
        .O(\indvar_flatten3_fu_82_reg[4] ));
  (* SOFT_HLUTNM = "soft_lutpair13" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \k5_fu_90[1]_i_1 
       (.I0(in2_Addr_B[3]),
        .O(\xor_ln12_reg_586_reg[0] [0]));
  LUT6 #(
    .INIT(64'h000008CC08CC0000)) 
    \k5_fu_90[2]_i_1 
       (.I0(xor_ln12_reg_586),
        .I1(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I2(icmp_ln10_reg_591),
        .I3(\in1_Addr_B[4]_INST_0_i_1_n_0 ),
        .I4(\k5_fu_90_reg[2] [1]),
        .I5(\k5_fu_90_reg[2] [0]),
        .O(\xor_ln12_reg_586_reg[0] [1]));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT5 #(
    .INIT(32'hFEFFEEEE)) 
    \or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3_i_1 
       (.I0(xor_ln12_reg_586),
        .I1(icmp_ln10_reg_591),
        .I2(icmp_ln9_reg_596),
        .I3(ap_enable_reg_pp0_iter1),
        .I4(ap_loop_init),
        .O(p_1_in));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT5 #(
    .INIT(32'h54F0F0F0)) 
    rewind_ap_ready_reg_i_1
       (.I0(ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg),
        .I1(icmp_ln9_fu_441_p2),
        .I2(rewind_ap_ready_reg),
        .I3(ap_start),
        .I4(ap_block_pp0_stage0_subdone),
        .O(rewind_ap_ready_reg_i_1_n_0));
  FDRE #(
    .INIT(1'b0)) 
    rewind_ap_ready_reg_reg
       (.C(ap_clk),
        .CE(1'b1),
        .D(rewind_ap_ready_reg_i_1_n_0),
        .Q(rewind_ap_ready_reg),
        .R(rewind_ap_ready_reg_reg_2));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT4 #(
    .INIT(16'h0800)) 
    \sum6_fu_94[31]_i_1 
       (.I0(ap_block_pp0_stage0_subdone),
        .I1(ap_loop_init),
        .I2(rewind_ap_ready_reg),
        .I3(ap_start),
        .O(SR));
  LUT6 #(
    .INIT(64'hF999FFFFF9F9FFFF)) 
    \xor_ln12_reg_586[0]_i_1 
       (.I0(\k5_fu_90_reg[2] [0]),
        .I1(\k5_fu_90_reg[2] [1]),
        .I2(\in1_Addr_B[4]_INST_0_i_1_n_0 ),
        .I3(icmp_ln10_reg_591),
        .I4(\in1_Addr_A[4]_INST_0_i_1_n_0 ),
        .I5(xor_ln12_reg_586),
        .O(\k5_fu_90_reg[1] ));
endmodule

(* ORIG_REF_NAME = "mat_mul_mul_32s_32s_32_2_1" *) 
module bd_0_hls_inst_0_mat_mul_mul_32s_32s_32_2_1
   (D,
    CEB2,
    ap_block_pp0_stage0_subdone,
    ap_clk,
    in2_Dout_B,
    in1_Dout_B);
  output [31:0]D;
  input CEB2;
  input ap_block_pp0_stage0_subdone;
  input ap_clk;
  input [31:0]in2_Dout_B;
  input [31:0]in1_Dout_B;

  wire CEB2;
  wire [31:0]D;
  wire ap_block_pp0_stage0_subdone;
  wire ap_clk;
  wire \buff0_reg[16]__0_n_0 ;
  wire buff0_reg_n_100;
  wire buff0_reg_n_101;
  wire buff0_reg_n_102;
  wire buff0_reg_n_103;
  wire buff0_reg_n_104;
  wire buff0_reg_n_105;
  wire buff0_reg_n_58;
  wire buff0_reg_n_59;
  wire buff0_reg_n_60;
  wire buff0_reg_n_61;
  wire buff0_reg_n_62;
  wire buff0_reg_n_63;
  wire buff0_reg_n_64;
  wire buff0_reg_n_65;
  wire buff0_reg_n_66;
  wire buff0_reg_n_67;
  wire buff0_reg_n_68;
  wire buff0_reg_n_69;
  wire buff0_reg_n_70;
  wire buff0_reg_n_71;
  wire buff0_reg_n_72;
  wire buff0_reg_n_73;
  wire buff0_reg_n_74;
  wire buff0_reg_n_75;
  wire buff0_reg_n_76;
  wire buff0_reg_n_77;
  wire buff0_reg_n_78;
  wire buff0_reg_n_79;
  wire buff0_reg_n_80;
  wire buff0_reg_n_81;
  wire buff0_reg_n_82;
  wire buff0_reg_n_83;
  wire buff0_reg_n_84;
  wire buff0_reg_n_85;
  wire buff0_reg_n_86;
  wire buff0_reg_n_87;
  wire buff0_reg_n_88;
  wire buff0_reg_n_89;
  wire buff0_reg_n_90;
  wire buff0_reg_n_91;
  wire buff0_reg_n_92;
  wire buff0_reg_n_93;
  wire buff0_reg_n_94;
  wire buff0_reg_n_95;
  wire buff0_reg_n_96;
  wire buff0_reg_n_97;
  wire buff0_reg_n_98;
  wire buff0_reg_n_99;
  wire [31:0]in1_Dout_B;
  wire [31:0]in2_Dout_B;
  wire \mul_ln14_reg_620[23]_i_2_n_0 ;
  wire \mul_ln14_reg_620[23]_i_3_n_0 ;
  wire \mul_ln14_reg_620[23]_i_4_n_0 ;
  wire \mul_ln14_reg_620[23]_i_5_n_0 ;
  wire \mul_ln14_reg_620[23]_i_6_n_0 ;
  wire \mul_ln14_reg_620[23]_i_7_n_0 ;
  wire \mul_ln14_reg_620[23]_i_8_n_0 ;
  wire \mul_ln14_reg_620[31]_i_2_n_0 ;
  wire \mul_ln14_reg_620[31]_i_3_n_0 ;
  wire \mul_ln14_reg_620[31]_i_4_n_0 ;
  wire \mul_ln14_reg_620[31]_i_5_n_0 ;
  wire \mul_ln14_reg_620[31]_i_6_n_0 ;
  wire \mul_ln14_reg_620[31]_i_7_n_0 ;
  wire \mul_ln14_reg_620[31]_i_8_n_0 ;
  wire \mul_ln14_reg_620[31]_i_9_n_0 ;
  wire \mul_ln14_reg_620_reg[23]_i_1_n_0 ;
  wire \mul_ln14_reg_620_reg[23]_i_1_n_1 ;
  wire \mul_ln14_reg_620_reg[23]_i_1_n_2 ;
  wire \mul_ln14_reg_620_reg[23]_i_1_n_3 ;
  wire \mul_ln14_reg_620_reg[23]_i_1_n_4 ;
  wire \mul_ln14_reg_620_reg[23]_i_1_n_5 ;
  wire \mul_ln14_reg_620_reg[23]_i_1_n_6 ;
  wire \mul_ln14_reg_620_reg[23]_i_1_n_7 ;
  wire \mul_ln14_reg_620_reg[31]_i_1_n_1 ;
  wire \mul_ln14_reg_620_reg[31]_i_1_n_2 ;
  wire \mul_ln14_reg_620_reg[31]_i_1_n_3 ;
  wire \mul_ln14_reg_620_reg[31]_i_1_n_4 ;
  wire \mul_ln14_reg_620_reg[31]_i_1_n_5 ;
  wire \mul_ln14_reg_620_reg[31]_i_1_n_6 ;
  wire \mul_ln14_reg_620_reg[31]_i_1_n_7 ;
  wire tmp_product__0_n_100;
  wire tmp_product__0_n_101;
  wire tmp_product__0_n_102;
  wire tmp_product__0_n_103;
  wire tmp_product__0_n_104;
  wire tmp_product__0_n_105;
  wire tmp_product__0_n_106;
  wire tmp_product__0_n_107;
  wire tmp_product__0_n_108;
  wire tmp_product__0_n_109;
  wire tmp_product__0_n_110;
  wire tmp_product__0_n_111;
  wire tmp_product__0_n_112;
  wire tmp_product__0_n_113;
  wire tmp_product__0_n_114;
  wire tmp_product__0_n_115;
  wire tmp_product__0_n_116;
  wire tmp_product__0_n_117;
  wire tmp_product__0_n_118;
  wire tmp_product__0_n_119;
  wire tmp_product__0_n_120;
  wire tmp_product__0_n_121;
  wire tmp_product__0_n_122;
  wire tmp_product__0_n_123;
  wire tmp_product__0_n_124;
  wire tmp_product__0_n_125;
  wire tmp_product__0_n_126;
  wire tmp_product__0_n_127;
  wire tmp_product__0_n_128;
  wire tmp_product__0_n_129;
  wire tmp_product__0_n_130;
  wire tmp_product__0_n_131;
  wire tmp_product__0_n_132;
  wire tmp_product__0_n_133;
  wire tmp_product__0_n_134;
  wire tmp_product__0_n_135;
  wire tmp_product__0_n_136;
  wire tmp_product__0_n_137;
  wire tmp_product__0_n_138;
  wire tmp_product__0_n_139;
  wire tmp_product__0_n_140;
  wire tmp_product__0_n_141;
  wire tmp_product__0_n_142;
  wire tmp_product__0_n_143;
  wire tmp_product__0_n_144;
  wire tmp_product__0_n_145;
  wire tmp_product__0_n_146;
  wire tmp_product__0_n_147;
  wire tmp_product__0_n_148;
  wire tmp_product__0_n_149;
  wire tmp_product__0_n_150;
  wire tmp_product__0_n_151;
  wire tmp_product__0_n_152;
  wire tmp_product__0_n_153;
  wire tmp_product__0_n_24;
  wire tmp_product__0_n_25;
  wire tmp_product__0_n_26;
  wire tmp_product__0_n_27;
  wire tmp_product__0_n_28;
  wire tmp_product__0_n_29;
  wire tmp_product__0_n_30;
  wire tmp_product__0_n_31;
  wire tmp_product__0_n_32;
  wire tmp_product__0_n_33;
  wire tmp_product__0_n_34;
  wire tmp_product__0_n_35;
  wire tmp_product__0_n_36;
  wire tmp_product__0_n_37;
  wire tmp_product__0_n_38;
  wire tmp_product__0_n_39;
  wire tmp_product__0_n_40;
  wire tmp_product__0_n_41;
  wire tmp_product__0_n_42;
  wire tmp_product__0_n_43;
  wire tmp_product__0_n_44;
  wire tmp_product__0_n_45;
  wire tmp_product__0_n_46;
  wire tmp_product__0_n_47;
  wire tmp_product__0_n_48;
  wire tmp_product__0_n_49;
  wire tmp_product__0_n_50;
  wire tmp_product__0_n_51;
  wire tmp_product__0_n_52;
  wire tmp_product__0_n_53;
  wire tmp_product__0_n_58;
  wire tmp_product__0_n_59;
  wire tmp_product__0_n_60;
  wire tmp_product__0_n_61;
  wire tmp_product__0_n_62;
  wire tmp_product__0_n_63;
  wire tmp_product__0_n_64;
  wire tmp_product__0_n_65;
  wire tmp_product__0_n_66;
  wire tmp_product__0_n_67;
  wire tmp_product__0_n_68;
  wire tmp_product__0_n_69;
  wire tmp_product__0_n_70;
  wire tmp_product__0_n_71;
  wire tmp_product__0_n_72;
  wire tmp_product__0_n_73;
  wire tmp_product__0_n_74;
  wire tmp_product__0_n_75;
  wire tmp_product__0_n_76;
  wire tmp_product__0_n_77;
  wire tmp_product__0_n_78;
  wire tmp_product__0_n_79;
  wire tmp_product__0_n_80;
  wire tmp_product__0_n_81;
  wire tmp_product__0_n_82;
  wire tmp_product__0_n_83;
  wire tmp_product__0_n_84;
  wire tmp_product__0_n_85;
  wire tmp_product__0_n_86;
  wire tmp_product__0_n_87;
  wire tmp_product__0_n_88;
  wire tmp_product__0_n_89;
  wire tmp_product__0_n_90;
  wire tmp_product__0_n_91;
  wire tmp_product__0_n_92;
  wire tmp_product__0_n_93;
  wire tmp_product__0_n_94;
  wire tmp_product__0_n_95;
  wire tmp_product__0_n_96;
  wire tmp_product__0_n_97;
  wire tmp_product__0_n_98;
  wire tmp_product__0_n_99;
  wire tmp_product_n_100;
  wire tmp_product_n_101;
  wire tmp_product_n_102;
  wire tmp_product_n_103;
  wire tmp_product_n_104;
  wire tmp_product_n_105;
  wire tmp_product_n_106;
  wire tmp_product_n_107;
  wire tmp_product_n_108;
  wire tmp_product_n_109;
  wire tmp_product_n_110;
  wire tmp_product_n_111;
  wire tmp_product_n_112;
  wire tmp_product_n_113;
  wire tmp_product_n_114;
  wire tmp_product_n_115;
  wire tmp_product_n_116;
  wire tmp_product_n_117;
  wire tmp_product_n_118;
  wire tmp_product_n_119;
  wire tmp_product_n_120;
  wire tmp_product_n_121;
  wire tmp_product_n_122;
  wire tmp_product_n_123;
  wire tmp_product_n_124;
  wire tmp_product_n_125;
  wire tmp_product_n_126;
  wire tmp_product_n_127;
  wire tmp_product_n_128;
  wire tmp_product_n_129;
  wire tmp_product_n_130;
  wire tmp_product_n_131;
  wire tmp_product_n_132;
  wire tmp_product_n_133;
  wire tmp_product_n_134;
  wire tmp_product_n_135;
  wire tmp_product_n_136;
  wire tmp_product_n_137;
  wire tmp_product_n_138;
  wire tmp_product_n_139;
  wire tmp_product_n_140;
  wire tmp_product_n_141;
  wire tmp_product_n_142;
  wire tmp_product_n_143;
  wire tmp_product_n_144;
  wire tmp_product_n_145;
  wire tmp_product_n_146;
  wire tmp_product_n_147;
  wire tmp_product_n_148;
  wire tmp_product_n_149;
  wire tmp_product_n_150;
  wire tmp_product_n_151;
  wire tmp_product_n_152;
  wire tmp_product_n_153;
  wire tmp_product_n_58;
  wire tmp_product_n_59;
  wire tmp_product_n_60;
  wire tmp_product_n_61;
  wire tmp_product_n_62;
  wire tmp_product_n_63;
  wire tmp_product_n_64;
  wire tmp_product_n_65;
  wire tmp_product_n_66;
  wire tmp_product_n_67;
  wire tmp_product_n_68;
  wire tmp_product_n_69;
  wire tmp_product_n_70;
  wire tmp_product_n_71;
  wire tmp_product_n_72;
  wire tmp_product_n_73;
  wire tmp_product_n_74;
  wire tmp_product_n_75;
  wire tmp_product_n_76;
  wire tmp_product_n_77;
  wire tmp_product_n_78;
  wire tmp_product_n_79;
  wire tmp_product_n_80;
  wire tmp_product_n_81;
  wire tmp_product_n_82;
  wire tmp_product_n_83;
  wire tmp_product_n_84;
  wire tmp_product_n_85;
  wire tmp_product_n_86;
  wire tmp_product_n_87;
  wire tmp_product_n_88;
  wire tmp_product_n_89;
  wire tmp_product_n_90;
  wire tmp_product_n_91;
  wire tmp_product_n_92;
  wire tmp_product_n_93;
  wire tmp_product_n_94;
  wire tmp_product_n_95;
  wire tmp_product_n_96;
  wire tmp_product_n_97;
  wire tmp_product_n_98;
  wire tmp_product_n_99;
  wire NLW_buff0_reg_CARRYCASCOUT_UNCONNECTED;
  wire NLW_buff0_reg_MULTSIGNOUT_UNCONNECTED;
  wire NLW_buff0_reg_OVERFLOW_UNCONNECTED;
  wire NLW_buff0_reg_PATTERNBDETECT_UNCONNECTED;
  wire NLW_buff0_reg_PATTERNDETECT_UNCONNECTED;
  wire NLW_buff0_reg_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_buff0_reg_ACOUT_UNCONNECTED;
  wire [17:0]NLW_buff0_reg_BCOUT_UNCONNECTED;
  wire [3:0]NLW_buff0_reg_CARRYOUT_UNCONNECTED;
  wire [47:0]NLW_buff0_reg_PCOUT_UNCONNECTED;
  wire [7:0]NLW_buff0_reg_XOROUT_UNCONNECTED;
  wire [7:7]\NLW_mul_ln14_reg_620_reg[31]_i_1_CO_UNCONNECTED ;
  wire NLW_tmp_product_CARRYCASCOUT_UNCONNECTED;
  wire NLW_tmp_product_MULTSIGNOUT_UNCONNECTED;
  wire NLW_tmp_product_OVERFLOW_UNCONNECTED;
  wire NLW_tmp_product_PATTERNBDETECT_UNCONNECTED;
  wire NLW_tmp_product_PATTERNDETECT_UNCONNECTED;
  wire NLW_tmp_product_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_tmp_product_ACOUT_UNCONNECTED;
  wire [17:0]NLW_tmp_product_BCOUT_UNCONNECTED;
  wire [3:0]NLW_tmp_product_CARRYOUT_UNCONNECTED;
  wire [7:0]NLW_tmp_product_XOROUT_UNCONNECTED;
  wire NLW_tmp_product__0_CARRYCASCOUT_UNCONNECTED;
  wire NLW_tmp_product__0_MULTSIGNOUT_UNCONNECTED;
  wire NLW_tmp_product__0_OVERFLOW_UNCONNECTED;
  wire NLW_tmp_product__0_PATTERNBDETECT_UNCONNECTED;
  wire NLW_tmp_product__0_PATTERNDETECT_UNCONNECTED;
  wire NLW_tmp_product__0_UNDERFLOW_UNCONNECTED;
  wire [17:0]NLW_tmp_product__0_BCOUT_UNCONNECTED;
  wire [3:0]NLW_tmp_product__0_CARRYOUT_UNCONNECTED;
  wire [7:0]NLW_tmp_product__0_XOROUT_UNCONNECTED;

  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 18x15 4}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("CASCADE"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(1),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    buff0_reg
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACIN({tmp_product__0_n_24,tmp_product__0_n_25,tmp_product__0_n_26,tmp_product__0_n_27,tmp_product__0_n_28,tmp_product__0_n_29,tmp_product__0_n_30,tmp_product__0_n_31,tmp_product__0_n_32,tmp_product__0_n_33,tmp_product__0_n_34,tmp_product__0_n_35,tmp_product__0_n_36,tmp_product__0_n_37,tmp_product__0_n_38,tmp_product__0_n_39,tmp_product__0_n_40,tmp_product__0_n_41,tmp_product__0_n_42,tmp_product__0_n_43,tmp_product__0_n_44,tmp_product__0_n_45,tmp_product__0_n_46,tmp_product__0_n_47,tmp_product__0_n_48,tmp_product__0_n_49,tmp_product__0_n_50,tmp_product__0_n_51,tmp_product__0_n_52,tmp_product__0_n_53}),
        .ACOUT(NLW_buff0_reg_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({in1_Dout_B[31],in1_Dout_B[31],in1_Dout_B[31],in1_Dout_B[31:17]}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_buff0_reg_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_buff0_reg_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_buff0_reg_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(CEB2),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_buff0_reg_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_buff0_reg_OVERFLOW_UNCONNECTED),
        .P({buff0_reg_n_58,buff0_reg_n_59,buff0_reg_n_60,buff0_reg_n_61,buff0_reg_n_62,buff0_reg_n_63,buff0_reg_n_64,buff0_reg_n_65,buff0_reg_n_66,buff0_reg_n_67,buff0_reg_n_68,buff0_reg_n_69,buff0_reg_n_70,buff0_reg_n_71,buff0_reg_n_72,buff0_reg_n_73,buff0_reg_n_74,buff0_reg_n_75,buff0_reg_n_76,buff0_reg_n_77,buff0_reg_n_78,buff0_reg_n_79,buff0_reg_n_80,buff0_reg_n_81,buff0_reg_n_82,buff0_reg_n_83,buff0_reg_n_84,buff0_reg_n_85,buff0_reg_n_86,buff0_reg_n_87,buff0_reg_n_88,buff0_reg_n_89,buff0_reg_n_90,buff0_reg_n_91,buff0_reg_n_92,buff0_reg_n_93,buff0_reg_n_94,buff0_reg_n_95,buff0_reg_n_96,buff0_reg_n_97,buff0_reg_n_98,buff0_reg_n_99,buff0_reg_n_100,buff0_reg_n_101,buff0_reg_n_102,buff0_reg_n_103,buff0_reg_n_104,buff0_reg_n_105}),
        .PATTERNBDETECT(NLW_buff0_reg_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_buff0_reg_PATTERNDETECT_UNCONNECTED),
        .PCIN({tmp_product__0_n_106,tmp_product__0_n_107,tmp_product__0_n_108,tmp_product__0_n_109,tmp_product__0_n_110,tmp_product__0_n_111,tmp_product__0_n_112,tmp_product__0_n_113,tmp_product__0_n_114,tmp_product__0_n_115,tmp_product__0_n_116,tmp_product__0_n_117,tmp_product__0_n_118,tmp_product__0_n_119,tmp_product__0_n_120,tmp_product__0_n_121,tmp_product__0_n_122,tmp_product__0_n_123,tmp_product__0_n_124,tmp_product__0_n_125,tmp_product__0_n_126,tmp_product__0_n_127,tmp_product__0_n_128,tmp_product__0_n_129,tmp_product__0_n_130,tmp_product__0_n_131,tmp_product__0_n_132,tmp_product__0_n_133,tmp_product__0_n_134,tmp_product__0_n_135,tmp_product__0_n_136,tmp_product__0_n_137,tmp_product__0_n_138,tmp_product__0_n_139,tmp_product__0_n_140,tmp_product__0_n_141,tmp_product__0_n_142,tmp_product__0_n_143,tmp_product__0_n_144,tmp_product__0_n_145,tmp_product__0_n_146,tmp_product__0_n_147,tmp_product__0_n_148,tmp_product__0_n_149,tmp_product__0_n_150,tmp_product__0_n_151,tmp_product__0_n_152,tmp_product__0_n_153}),
        .PCOUT(NLW_buff0_reg_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_buff0_reg_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_buff0_reg_XOROUT_UNCONNECTED[7:0]));
  FDRE \buff0_reg[0]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_105),
        .Q(D[0]),
        .R(1'b0));
  FDRE \buff0_reg[10]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_95),
        .Q(D[10]),
        .R(1'b0));
  FDRE \buff0_reg[11]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_94),
        .Q(D[11]),
        .R(1'b0));
  FDRE \buff0_reg[12]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_93),
        .Q(D[12]),
        .R(1'b0));
  FDRE \buff0_reg[13]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_92),
        .Q(D[13]),
        .R(1'b0));
  FDRE \buff0_reg[14]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_91),
        .Q(D[14]),
        .R(1'b0));
  FDRE \buff0_reg[15]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_90),
        .Q(D[15]),
        .R(1'b0));
  FDRE \buff0_reg[16]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_89),
        .Q(\buff0_reg[16]__0_n_0 ),
        .R(1'b0));
  FDRE \buff0_reg[1]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_104),
        .Q(D[1]),
        .R(1'b0));
  FDRE \buff0_reg[2]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_103),
        .Q(D[2]),
        .R(1'b0));
  FDRE \buff0_reg[3]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_102),
        .Q(D[3]),
        .R(1'b0));
  FDRE \buff0_reg[4]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_101),
        .Q(D[4]),
        .R(1'b0));
  FDRE \buff0_reg[5]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_100),
        .Q(D[5]),
        .R(1'b0));
  FDRE \buff0_reg[6]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_99),
        .Q(D[6]),
        .R(1'b0));
  FDRE \buff0_reg[7]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_98),
        .Q(D[7]),
        .R(1'b0));
  FDRE \buff0_reg[8]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_97),
        .Q(D[8]),
        .R(1'b0));
  FDRE \buff0_reg[9]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_96),
        .Q(D[9]),
        .R(1'b0));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[23]_i_2 
       (.I0(buff0_reg_n_99),
        .I1(tmp_product_n_99),
        .O(\mul_ln14_reg_620[23]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[23]_i_3 
       (.I0(buff0_reg_n_100),
        .I1(tmp_product_n_100),
        .O(\mul_ln14_reg_620[23]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[23]_i_4 
       (.I0(buff0_reg_n_101),
        .I1(tmp_product_n_101),
        .O(\mul_ln14_reg_620[23]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[23]_i_5 
       (.I0(buff0_reg_n_102),
        .I1(tmp_product_n_102),
        .O(\mul_ln14_reg_620[23]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[23]_i_6 
       (.I0(buff0_reg_n_103),
        .I1(tmp_product_n_103),
        .O(\mul_ln14_reg_620[23]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[23]_i_7 
       (.I0(buff0_reg_n_104),
        .I1(tmp_product_n_104),
        .O(\mul_ln14_reg_620[23]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[23]_i_8 
       (.I0(buff0_reg_n_105),
        .I1(tmp_product_n_105),
        .O(\mul_ln14_reg_620[23]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[31]_i_2 
       (.I0(buff0_reg_n_91),
        .I1(tmp_product_n_91),
        .O(\mul_ln14_reg_620[31]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[31]_i_3 
       (.I0(buff0_reg_n_92),
        .I1(tmp_product_n_92),
        .O(\mul_ln14_reg_620[31]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[31]_i_4 
       (.I0(buff0_reg_n_93),
        .I1(tmp_product_n_93),
        .O(\mul_ln14_reg_620[31]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[31]_i_5 
       (.I0(buff0_reg_n_94),
        .I1(tmp_product_n_94),
        .O(\mul_ln14_reg_620[31]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[31]_i_6 
       (.I0(buff0_reg_n_95),
        .I1(tmp_product_n_95),
        .O(\mul_ln14_reg_620[31]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[31]_i_7 
       (.I0(buff0_reg_n_96),
        .I1(tmp_product_n_96),
        .O(\mul_ln14_reg_620[31]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[31]_i_8 
       (.I0(buff0_reg_n_97),
        .I1(tmp_product_n_97),
        .O(\mul_ln14_reg_620[31]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_reg_620[31]_i_9 
       (.I0(buff0_reg_n_98),
        .I1(tmp_product_n_98),
        .O(\mul_ln14_reg_620[31]_i_9_n_0 ));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \mul_ln14_reg_620_reg[23]_i_1 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\mul_ln14_reg_620_reg[23]_i_1_n_0 ,\mul_ln14_reg_620_reg[23]_i_1_n_1 ,\mul_ln14_reg_620_reg[23]_i_1_n_2 ,\mul_ln14_reg_620_reg[23]_i_1_n_3 ,\mul_ln14_reg_620_reg[23]_i_1_n_4 ,\mul_ln14_reg_620_reg[23]_i_1_n_5 ,\mul_ln14_reg_620_reg[23]_i_1_n_6 ,\mul_ln14_reg_620_reg[23]_i_1_n_7 }),
        .DI({buff0_reg_n_99,buff0_reg_n_100,buff0_reg_n_101,buff0_reg_n_102,buff0_reg_n_103,buff0_reg_n_104,buff0_reg_n_105,1'b0}),
        .O(D[23:16]),
        .S({\mul_ln14_reg_620[23]_i_2_n_0 ,\mul_ln14_reg_620[23]_i_3_n_0 ,\mul_ln14_reg_620[23]_i_4_n_0 ,\mul_ln14_reg_620[23]_i_5_n_0 ,\mul_ln14_reg_620[23]_i_6_n_0 ,\mul_ln14_reg_620[23]_i_7_n_0 ,\mul_ln14_reg_620[23]_i_8_n_0 ,\buff0_reg[16]__0_n_0 }));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \mul_ln14_reg_620_reg[31]_i_1 
       (.CI(\mul_ln14_reg_620_reg[23]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_mul_ln14_reg_620_reg[31]_i_1_CO_UNCONNECTED [7],\mul_ln14_reg_620_reg[31]_i_1_n_1 ,\mul_ln14_reg_620_reg[31]_i_1_n_2 ,\mul_ln14_reg_620_reg[31]_i_1_n_3 ,\mul_ln14_reg_620_reg[31]_i_1_n_4 ,\mul_ln14_reg_620_reg[31]_i_1_n_5 ,\mul_ln14_reg_620_reg[31]_i_1_n_6 ,\mul_ln14_reg_620_reg[31]_i_1_n_7 }),
        .DI({1'b0,buff0_reg_n_92,buff0_reg_n_93,buff0_reg_n_94,buff0_reg_n_95,buff0_reg_n_96,buff0_reg_n_97,buff0_reg_n_98}),
        .O(D[31:24]),
        .S({\mul_ln14_reg_620[31]_i_2_n_0 ,\mul_ln14_reg_620[31]_i_3_n_0 ,\mul_ln14_reg_620[31]_i_4_n_0 ,\mul_ln14_reg_620[31]_i_5_n_0 ,\mul_ln14_reg_620[31]_i_6_n_0 ,\mul_ln14_reg_620[31]_i_7_n_0 ,\mul_ln14_reg_620[31]_i_8_n_0 ,\mul_ln14_reg_620[31]_i_9_n_0 }));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 15x18 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(1),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    tmp_product
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,in1_Dout_B[16:0]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_tmp_product_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({in2_Dout_B[31],in2_Dout_B[31],in2_Dout_B[31],in2_Dout_B[31:17]}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_tmp_product_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_tmp_product_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_tmp_product_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEB2),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(CEB2),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_tmp_product_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_tmp_product_OVERFLOW_UNCONNECTED),
        .P({tmp_product_n_58,tmp_product_n_59,tmp_product_n_60,tmp_product_n_61,tmp_product_n_62,tmp_product_n_63,tmp_product_n_64,tmp_product_n_65,tmp_product_n_66,tmp_product_n_67,tmp_product_n_68,tmp_product_n_69,tmp_product_n_70,tmp_product_n_71,tmp_product_n_72,tmp_product_n_73,tmp_product_n_74,tmp_product_n_75,tmp_product_n_76,tmp_product_n_77,tmp_product_n_78,tmp_product_n_79,tmp_product_n_80,tmp_product_n_81,tmp_product_n_82,tmp_product_n_83,tmp_product_n_84,tmp_product_n_85,tmp_product_n_86,tmp_product_n_87,tmp_product_n_88,tmp_product_n_89,tmp_product_n_90,tmp_product_n_91,tmp_product_n_92,tmp_product_n_93,tmp_product_n_94,tmp_product_n_95,tmp_product_n_96,tmp_product_n_97,tmp_product_n_98,tmp_product_n_99,tmp_product_n_100,tmp_product_n_101,tmp_product_n_102,tmp_product_n_103,tmp_product_n_104,tmp_product_n_105}),
        .PATTERNBDETECT(NLW_tmp_product_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_tmp_product_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT({tmp_product_n_106,tmp_product_n_107,tmp_product_n_108,tmp_product_n_109,tmp_product_n_110,tmp_product_n_111,tmp_product_n_112,tmp_product_n_113,tmp_product_n_114,tmp_product_n_115,tmp_product_n_116,tmp_product_n_117,tmp_product_n_118,tmp_product_n_119,tmp_product_n_120,tmp_product_n_121,tmp_product_n_122,tmp_product_n_123,tmp_product_n_124,tmp_product_n_125,tmp_product_n_126,tmp_product_n_127,tmp_product_n_128,tmp_product_n_129,tmp_product_n_130,tmp_product_n_131,tmp_product_n_132,tmp_product_n_133,tmp_product_n_134,tmp_product_n_135,tmp_product_n_136,tmp_product_n_137,tmp_product_n_138,tmp_product_n_139,tmp_product_n_140,tmp_product_n_141,tmp_product_n_142,tmp_product_n_143,tmp_product_n_144,tmp_product_n_145,tmp_product_n_146,tmp_product_n_147,tmp_product_n_148,tmp_product_n_149,tmp_product_n_150,tmp_product_n_151,tmp_product_n_152,tmp_product_n_153}),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_tmp_product_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_tmp_product_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 18x18 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    tmp_product__0
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,in2_Dout_B[16:0]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT({tmp_product__0_n_24,tmp_product__0_n_25,tmp_product__0_n_26,tmp_product__0_n_27,tmp_product__0_n_28,tmp_product__0_n_29,tmp_product__0_n_30,tmp_product__0_n_31,tmp_product__0_n_32,tmp_product__0_n_33,tmp_product__0_n_34,tmp_product__0_n_35,tmp_product__0_n_36,tmp_product__0_n_37,tmp_product__0_n_38,tmp_product__0_n_39,tmp_product__0_n_40,tmp_product__0_n_41,tmp_product__0_n_42,tmp_product__0_n_43,tmp_product__0_n_44,tmp_product__0_n_45,tmp_product__0_n_46,tmp_product__0_n_47,tmp_product__0_n_48,tmp_product__0_n_49,tmp_product__0_n_50,tmp_product__0_n_51,tmp_product__0_n_52,tmp_product__0_n_53}),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,in1_Dout_B[16:0]}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_tmp_product__0_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_tmp_product__0_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_tmp_product__0_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEB2),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(CEB2),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(ap_clk),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_tmp_product__0_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_tmp_product__0_OVERFLOW_UNCONNECTED),
        .P({tmp_product__0_n_58,tmp_product__0_n_59,tmp_product__0_n_60,tmp_product__0_n_61,tmp_product__0_n_62,tmp_product__0_n_63,tmp_product__0_n_64,tmp_product__0_n_65,tmp_product__0_n_66,tmp_product__0_n_67,tmp_product__0_n_68,tmp_product__0_n_69,tmp_product__0_n_70,tmp_product__0_n_71,tmp_product__0_n_72,tmp_product__0_n_73,tmp_product__0_n_74,tmp_product__0_n_75,tmp_product__0_n_76,tmp_product__0_n_77,tmp_product__0_n_78,tmp_product__0_n_79,tmp_product__0_n_80,tmp_product__0_n_81,tmp_product__0_n_82,tmp_product__0_n_83,tmp_product__0_n_84,tmp_product__0_n_85,tmp_product__0_n_86,tmp_product__0_n_87,tmp_product__0_n_88,tmp_product__0_n_89,tmp_product__0_n_90,tmp_product__0_n_91,tmp_product__0_n_92,tmp_product__0_n_93,tmp_product__0_n_94,tmp_product__0_n_95,tmp_product__0_n_96,tmp_product__0_n_97,tmp_product__0_n_98,tmp_product__0_n_99,tmp_product__0_n_100,tmp_product__0_n_101,tmp_product__0_n_102,tmp_product__0_n_103,tmp_product__0_n_104,tmp_product__0_n_105}),
        .PATTERNBDETECT(NLW_tmp_product__0_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_tmp_product__0_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT({tmp_product__0_n_106,tmp_product__0_n_107,tmp_product__0_n_108,tmp_product__0_n_109,tmp_product__0_n_110,tmp_product__0_n_111,tmp_product__0_n_112,tmp_product__0_n_113,tmp_product__0_n_114,tmp_product__0_n_115,tmp_product__0_n_116,tmp_product__0_n_117,tmp_product__0_n_118,tmp_product__0_n_119,tmp_product__0_n_120,tmp_product__0_n_121,tmp_product__0_n_122,tmp_product__0_n_123,tmp_product__0_n_124,tmp_product__0_n_125,tmp_product__0_n_126,tmp_product__0_n_127,tmp_product__0_n_128,tmp_product__0_n_129,tmp_product__0_n_130,tmp_product__0_n_131,tmp_product__0_n_132,tmp_product__0_n_133,tmp_product__0_n_134,tmp_product__0_n_135,tmp_product__0_n_136,tmp_product__0_n_137,tmp_product__0_n_138,tmp_product__0_n_139,tmp_product__0_n_140,tmp_product__0_n_141,tmp_product__0_n_142,tmp_product__0_n_143,tmp_product__0_n_144,tmp_product__0_n_145,tmp_product__0_n_146,tmp_product__0_n_147,tmp_product__0_n_148,tmp_product__0_n_149,tmp_product__0_n_150,tmp_product__0_n_151,tmp_product__0_n_152,tmp_product__0_n_153}),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_tmp_product__0_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_tmp_product__0_XOROUT_UNCONNECTED[7:0]));
endmodule

(* ORIG_REF_NAME = "mat_mul_mul_32s_32s_32_2_1" *) 
module bd_0_hls_inst_0_mat_mul_mul_32s_32s_32_2_1_0
   (CEB2,
    D,
    ap_block_pp0_stage0_subdone,
    ap_clk,
    in2_Dout_A,
    in1_Dout_A,
    ap_enable_reg_pp0_iter1);
  output CEB2;
  output [31:0]D;
  input ap_block_pp0_stage0_subdone;
  input ap_clk;
  input [31:0]in2_Dout_A;
  input [31:0]in1_Dout_A;
  input ap_enable_reg_pp0_iter1;

  wire CEB2;
  wire [31:0]D;
  wire ap_block_pp0_stage0_subdone;
  wire ap_clk;
  wire ap_enable_reg_pp0_iter1;
  wire \buff0_reg[16]__0_n_0 ;
  wire buff0_reg_n_100;
  wire buff0_reg_n_101;
  wire buff0_reg_n_102;
  wire buff0_reg_n_103;
  wire buff0_reg_n_104;
  wire buff0_reg_n_105;
  wire buff0_reg_n_58;
  wire buff0_reg_n_59;
  wire buff0_reg_n_60;
  wire buff0_reg_n_61;
  wire buff0_reg_n_62;
  wire buff0_reg_n_63;
  wire buff0_reg_n_64;
  wire buff0_reg_n_65;
  wire buff0_reg_n_66;
  wire buff0_reg_n_67;
  wire buff0_reg_n_68;
  wire buff0_reg_n_69;
  wire buff0_reg_n_70;
  wire buff0_reg_n_71;
  wire buff0_reg_n_72;
  wire buff0_reg_n_73;
  wire buff0_reg_n_74;
  wire buff0_reg_n_75;
  wire buff0_reg_n_76;
  wire buff0_reg_n_77;
  wire buff0_reg_n_78;
  wire buff0_reg_n_79;
  wire buff0_reg_n_80;
  wire buff0_reg_n_81;
  wire buff0_reg_n_82;
  wire buff0_reg_n_83;
  wire buff0_reg_n_84;
  wire buff0_reg_n_85;
  wire buff0_reg_n_86;
  wire buff0_reg_n_87;
  wire buff0_reg_n_88;
  wire buff0_reg_n_89;
  wire buff0_reg_n_90;
  wire buff0_reg_n_91;
  wire buff0_reg_n_92;
  wire buff0_reg_n_93;
  wire buff0_reg_n_94;
  wire buff0_reg_n_95;
  wire buff0_reg_n_96;
  wire buff0_reg_n_97;
  wire buff0_reg_n_98;
  wire buff0_reg_n_99;
  wire [31:0]in1_Dout_A;
  wire [31:0]in2_Dout_A;
  wire \mul_ln14_1_reg_625[23]_i_2_n_0 ;
  wire \mul_ln14_1_reg_625[23]_i_3_n_0 ;
  wire \mul_ln14_1_reg_625[23]_i_4_n_0 ;
  wire \mul_ln14_1_reg_625[23]_i_5_n_0 ;
  wire \mul_ln14_1_reg_625[23]_i_6_n_0 ;
  wire \mul_ln14_1_reg_625[23]_i_7_n_0 ;
  wire \mul_ln14_1_reg_625[23]_i_8_n_0 ;
  wire \mul_ln14_1_reg_625[31]_i_2_n_0 ;
  wire \mul_ln14_1_reg_625[31]_i_3_n_0 ;
  wire \mul_ln14_1_reg_625[31]_i_4_n_0 ;
  wire \mul_ln14_1_reg_625[31]_i_5_n_0 ;
  wire \mul_ln14_1_reg_625[31]_i_6_n_0 ;
  wire \mul_ln14_1_reg_625[31]_i_7_n_0 ;
  wire \mul_ln14_1_reg_625[31]_i_8_n_0 ;
  wire \mul_ln14_1_reg_625[31]_i_9_n_0 ;
  wire \mul_ln14_1_reg_625_reg[23]_i_1_n_0 ;
  wire \mul_ln14_1_reg_625_reg[23]_i_1_n_1 ;
  wire \mul_ln14_1_reg_625_reg[23]_i_1_n_2 ;
  wire \mul_ln14_1_reg_625_reg[23]_i_1_n_3 ;
  wire \mul_ln14_1_reg_625_reg[23]_i_1_n_4 ;
  wire \mul_ln14_1_reg_625_reg[23]_i_1_n_5 ;
  wire \mul_ln14_1_reg_625_reg[23]_i_1_n_6 ;
  wire \mul_ln14_1_reg_625_reg[23]_i_1_n_7 ;
  wire \mul_ln14_1_reg_625_reg[31]_i_1_n_1 ;
  wire \mul_ln14_1_reg_625_reg[31]_i_1_n_2 ;
  wire \mul_ln14_1_reg_625_reg[31]_i_1_n_3 ;
  wire \mul_ln14_1_reg_625_reg[31]_i_1_n_4 ;
  wire \mul_ln14_1_reg_625_reg[31]_i_1_n_5 ;
  wire \mul_ln14_1_reg_625_reg[31]_i_1_n_6 ;
  wire \mul_ln14_1_reg_625_reg[31]_i_1_n_7 ;
  wire tmp_product__0_n_100;
  wire tmp_product__0_n_101;
  wire tmp_product__0_n_102;
  wire tmp_product__0_n_103;
  wire tmp_product__0_n_104;
  wire tmp_product__0_n_105;
  wire tmp_product__0_n_106;
  wire tmp_product__0_n_107;
  wire tmp_product__0_n_108;
  wire tmp_product__0_n_109;
  wire tmp_product__0_n_110;
  wire tmp_product__0_n_111;
  wire tmp_product__0_n_112;
  wire tmp_product__0_n_113;
  wire tmp_product__0_n_114;
  wire tmp_product__0_n_115;
  wire tmp_product__0_n_116;
  wire tmp_product__0_n_117;
  wire tmp_product__0_n_118;
  wire tmp_product__0_n_119;
  wire tmp_product__0_n_120;
  wire tmp_product__0_n_121;
  wire tmp_product__0_n_122;
  wire tmp_product__0_n_123;
  wire tmp_product__0_n_124;
  wire tmp_product__0_n_125;
  wire tmp_product__0_n_126;
  wire tmp_product__0_n_127;
  wire tmp_product__0_n_128;
  wire tmp_product__0_n_129;
  wire tmp_product__0_n_130;
  wire tmp_product__0_n_131;
  wire tmp_product__0_n_132;
  wire tmp_product__0_n_133;
  wire tmp_product__0_n_134;
  wire tmp_product__0_n_135;
  wire tmp_product__0_n_136;
  wire tmp_product__0_n_137;
  wire tmp_product__0_n_138;
  wire tmp_product__0_n_139;
  wire tmp_product__0_n_140;
  wire tmp_product__0_n_141;
  wire tmp_product__0_n_142;
  wire tmp_product__0_n_143;
  wire tmp_product__0_n_144;
  wire tmp_product__0_n_145;
  wire tmp_product__0_n_146;
  wire tmp_product__0_n_147;
  wire tmp_product__0_n_148;
  wire tmp_product__0_n_149;
  wire tmp_product__0_n_150;
  wire tmp_product__0_n_151;
  wire tmp_product__0_n_152;
  wire tmp_product__0_n_153;
  wire tmp_product__0_n_24;
  wire tmp_product__0_n_25;
  wire tmp_product__0_n_26;
  wire tmp_product__0_n_27;
  wire tmp_product__0_n_28;
  wire tmp_product__0_n_29;
  wire tmp_product__0_n_30;
  wire tmp_product__0_n_31;
  wire tmp_product__0_n_32;
  wire tmp_product__0_n_33;
  wire tmp_product__0_n_34;
  wire tmp_product__0_n_35;
  wire tmp_product__0_n_36;
  wire tmp_product__0_n_37;
  wire tmp_product__0_n_38;
  wire tmp_product__0_n_39;
  wire tmp_product__0_n_40;
  wire tmp_product__0_n_41;
  wire tmp_product__0_n_42;
  wire tmp_product__0_n_43;
  wire tmp_product__0_n_44;
  wire tmp_product__0_n_45;
  wire tmp_product__0_n_46;
  wire tmp_product__0_n_47;
  wire tmp_product__0_n_48;
  wire tmp_product__0_n_49;
  wire tmp_product__0_n_50;
  wire tmp_product__0_n_51;
  wire tmp_product__0_n_52;
  wire tmp_product__0_n_53;
  wire tmp_product__0_n_58;
  wire tmp_product__0_n_59;
  wire tmp_product__0_n_60;
  wire tmp_product__0_n_61;
  wire tmp_product__0_n_62;
  wire tmp_product__0_n_63;
  wire tmp_product__0_n_64;
  wire tmp_product__0_n_65;
  wire tmp_product__0_n_66;
  wire tmp_product__0_n_67;
  wire tmp_product__0_n_68;
  wire tmp_product__0_n_69;
  wire tmp_product__0_n_70;
  wire tmp_product__0_n_71;
  wire tmp_product__0_n_72;
  wire tmp_product__0_n_73;
  wire tmp_product__0_n_74;
  wire tmp_product__0_n_75;
  wire tmp_product__0_n_76;
  wire tmp_product__0_n_77;
  wire tmp_product__0_n_78;
  wire tmp_product__0_n_79;
  wire tmp_product__0_n_80;
  wire tmp_product__0_n_81;
  wire tmp_product__0_n_82;
  wire tmp_product__0_n_83;
  wire tmp_product__0_n_84;
  wire tmp_product__0_n_85;
  wire tmp_product__0_n_86;
  wire tmp_product__0_n_87;
  wire tmp_product__0_n_88;
  wire tmp_product__0_n_89;
  wire tmp_product__0_n_90;
  wire tmp_product__0_n_91;
  wire tmp_product__0_n_92;
  wire tmp_product__0_n_93;
  wire tmp_product__0_n_94;
  wire tmp_product__0_n_95;
  wire tmp_product__0_n_96;
  wire tmp_product__0_n_97;
  wire tmp_product__0_n_98;
  wire tmp_product__0_n_99;
  wire tmp_product_n_100;
  wire tmp_product_n_101;
  wire tmp_product_n_102;
  wire tmp_product_n_103;
  wire tmp_product_n_104;
  wire tmp_product_n_105;
  wire tmp_product_n_106;
  wire tmp_product_n_107;
  wire tmp_product_n_108;
  wire tmp_product_n_109;
  wire tmp_product_n_110;
  wire tmp_product_n_111;
  wire tmp_product_n_112;
  wire tmp_product_n_113;
  wire tmp_product_n_114;
  wire tmp_product_n_115;
  wire tmp_product_n_116;
  wire tmp_product_n_117;
  wire tmp_product_n_118;
  wire tmp_product_n_119;
  wire tmp_product_n_120;
  wire tmp_product_n_121;
  wire tmp_product_n_122;
  wire tmp_product_n_123;
  wire tmp_product_n_124;
  wire tmp_product_n_125;
  wire tmp_product_n_126;
  wire tmp_product_n_127;
  wire tmp_product_n_128;
  wire tmp_product_n_129;
  wire tmp_product_n_130;
  wire tmp_product_n_131;
  wire tmp_product_n_132;
  wire tmp_product_n_133;
  wire tmp_product_n_134;
  wire tmp_product_n_135;
  wire tmp_product_n_136;
  wire tmp_product_n_137;
  wire tmp_product_n_138;
  wire tmp_product_n_139;
  wire tmp_product_n_140;
  wire tmp_product_n_141;
  wire tmp_product_n_142;
  wire tmp_product_n_143;
  wire tmp_product_n_144;
  wire tmp_product_n_145;
  wire tmp_product_n_146;
  wire tmp_product_n_147;
  wire tmp_product_n_148;
  wire tmp_product_n_149;
  wire tmp_product_n_150;
  wire tmp_product_n_151;
  wire tmp_product_n_152;
  wire tmp_product_n_153;
  wire tmp_product_n_58;
  wire tmp_product_n_59;
  wire tmp_product_n_60;
  wire tmp_product_n_61;
  wire tmp_product_n_62;
  wire tmp_product_n_63;
  wire tmp_product_n_64;
  wire tmp_product_n_65;
  wire tmp_product_n_66;
  wire tmp_product_n_67;
  wire tmp_product_n_68;
  wire tmp_product_n_69;
  wire tmp_product_n_70;
  wire tmp_product_n_71;
  wire tmp_product_n_72;
  wire tmp_product_n_73;
  wire tmp_product_n_74;
  wire tmp_product_n_75;
  wire tmp_product_n_76;
  wire tmp_product_n_77;
  wire tmp_product_n_78;
  wire tmp_product_n_79;
  wire tmp_product_n_80;
  wire tmp_product_n_81;
  wire tmp_product_n_82;
  wire tmp_product_n_83;
  wire tmp_product_n_84;
  wire tmp_product_n_85;
  wire tmp_product_n_86;
  wire tmp_product_n_87;
  wire tmp_product_n_88;
  wire tmp_product_n_89;
  wire tmp_product_n_90;
  wire tmp_product_n_91;
  wire tmp_product_n_92;
  wire tmp_product_n_93;
  wire tmp_product_n_94;
  wire tmp_product_n_95;
  wire tmp_product_n_96;
  wire tmp_product_n_97;
  wire tmp_product_n_98;
  wire tmp_product_n_99;
  wire NLW_buff0_reg_CARRYCASCOUT_UNCONNECTED;
  wire NLW_buff0_reg_MULTSIGNOUT_UNCONNECTED;
  wire NLW_buff0_reg_OVERFLOW_UNCONNECTED;
  wire NLW_buff0_reg_PATTERNBDETECT_UNCONNECTED;
  wire NLW_buff0_reg_PATTERNDETECT_UNCONNECTED;
  wire NLW_buff0_reg_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_buff0_reg_ACOUT_UNCONNECTED;
  wire [17:0]NLW_buff0_reg_BCOUT_UNCONNECTED;
  wire [3:0]NLW_buff0_reg_CARRYOUT_UNCONNECTED;
  wire [47:0]NLW_buff0_reg_PCOUT_UNCONNECTED;
  wire [7:0]NLW_buff0_reg_XOROUT_UNCONNECTED;
  wire [7:7]\NLW_mul_ln14_1_reg_625_reg[31]_i_1_CO_UNCONNECTED ;
  wire NLW_tmp_product_CARRYCASCOUT_UNCONNECTED;
  wire NLW_tmp_product_MULTSIGNOUT_UNCONNECTED;
  wire NLW_tmp_product_OVERFLOW_UNCONNECTED;
  wire NLW_tmp_product_PATTERNBDETECT_UNCONNECTED;
  wire NLW_tmp_product_PATTERNDETECT_UNCONNECTED;
  wire NLW_tmp_product_UNDERFLOW_UNCONNECTED;
  wire [29:0]NLW_tmp_product_ACOUT_UNCONNECTED;
  wire [17:0]NLW_tmp_product_BCOUT_UNCONNECTED;
  wire [3:0]NLW_tmp_product_CARRYOUT_UNCONNECTED;
  wire [7:0]NLW_tmp_product_XOROUT_UNCONNECTED;
  wire NLW_tmp_product__0_CARRYCASCOUT_UNCONNECTED;
  wire NLW_tmp_product__0_MULTSIGNOUT_UNCONNECTED;
  wire NLW_tmp_product__0_OVERFLOW_UNCONNECTED;
  wire NLW_tmp_product__0_PATTERNBDETECT_UNCONNECTED;
  wire NLW_tmp_product__0_PATTERNDETECT_UNCONNECTED;
  wire NLW_tmp_product__0_UNDERFLOW_UNCONNECTED;
  wire [17:0]NLW_tmp_product__0_BCOUT_UNCONNECTED;
  wire [3:0]NLW_tmp_product__0_CARRYOUT_UNCONNECTED;
  wire [7:0]NLW_tmp_product__0_XOROUT_UNCONNECTED;

  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 18x15 4}}" *) 
  DSP48E2 #(
    .ACASCREG(0),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(0),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("CASCADE"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(1),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    buff0_reg
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACIN({tmp_product__0_n_24,tmp_product__0_n_25,tmp_product__0_n_26,tmp_product__0_n_27,tmp_product__0_n_28,tmp_product__0_n_29,tmp_product__0_n_30,tmp_product__0_n_31,tmp_product__0_n_32,tmp_product__0_n_33,tmp_product__0_n_34,tmp_product__0_n_35,tmp_product__0_n_36,tmp_product__0_n_37,tmp_product__0_n_38,tmp_product__0_n_39,tmp_product__0_n_40,tmp_product__0_n_41,tmp_product__0_n_42,tmp_product__0_n_43,tmp_product__0_n_44,tmp_product__0_n_45,tmp_product__0_n_46,tmp_product__0_n_47,tmp_product__0_n_48,tmp_product__0_n_49,tmp_product__0_n_50,tmp_product__0_n_51,tmp_product__0_n_52,tmp_product__0_n_53}),
        .ACOUT(NLW_buff0_reg_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({in1_Dout_A[31],in1_Dout_A[31],in1_Dout_A[31],in1_Dout_A[31:17]}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_buff0_reg_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_buff0_reg_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_buff0_reg_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(1'b0),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(CEB2),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_buff0_reg_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_buff0_reg_OVERFLOW_UNCONNECTED),
        .P({buff0_reg_n_58,buff0_reg_n_59,buff0_reg_n_60,buff0_reg_n_61,buff0_reg_n_62,buff0_reg_n_63,buff0_reg_n_64,buff0_reg_n_65,buff0_reg_n_66,buff0_reg_n_67,buff0_reg_n_68,buff0_reg_n_69,buff0_reg_n_70,buff0_reg_n_71,buff0_reg_n_72,buff0_reg_n_73,buff0_reg_n_74,buff0_reg_n_75,buff0_reg_n_76,buff0_reg_n_77,buff0_reg_n_78,buff0_reg_n_79,buff0_reg_n_80,buff0_reg_n_81,buff0_reg_n_82,buff0_reg_n_83,buff0_reg_n_84,buff0_reg_n_85,buff0_reg_n_86,buff0_reg_n_87,buff0_reg_n_88,buff0_reg_n_89,buff0_reg_n_90,buff0_reg_n_91,buff0_reg_n_92,buff0_reg_n_93,buff0_reg_n_94,buff0_reg_n_95,buff0_reg_n_96,buff0_reg_n_97,buff0_reg_n_98,buff0_reg_n_99,buff0_reg_n_100,buff0_reg_n_101,buff0_reg_n_102,buff0_reg_n_103,buff0_reg_n_104,buff0_reg_n_105}),
        .PATTERNBDETECT(NLW_buff0_reg_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_buff0_reg_PATTERNDETECT_UNCONNECTED),
        .PCIN({tmp_product__0_n_106,tmp_product__0_n_107,tmp_product__0_n_108,tmp_product__0_n_109,tmp_product__0_n_110,tmp_product__0_n_111,tmp_product__0_n_112,tmp_product__0_n_113,tmp_product__0_n_114,tmp_product__0_n_115,tmp_product__0_n_116,tmp_product__0_n_117,tmp_product__0_n_118,tmp_product__0_n_119,tmp_product__0_n_120,tmp_product__0_n_121,tmp_product__0_n_122,tmp_product__0_n_123,tmp_product__0_n_124,tmp_product__0_n_125,tmp_product__0_n_126,tmp_product__0_n_127,tmp_product__0_n_128,tmp_product__0_n_129,tmp_product__0_n_130,tmp_product__0_n_131,tmp_product__0_n_132,tmp_product__0_n_133,tmp_product__0_n_134,tmp_product__0_n_135,tmp_product__0_n_136,tmp_product__0_n_137,tmp_product__0_n_138,tmp_product__0_n_139,tmp_product__0_n_140,tmp_product__0_n_141,tmp_product__0_n_142,tmp_product__0_n_143,tmp_product__0_n_144,tmp_product__0_n_145,tmp_product__0_n_146,tmp_product__0_n_147,tmp_product__0_n_148,tmp_product__0_n_149,tmp_product__0_n_150,tmp_product__0_n_151,tmp_product__0_n_152,tmp_product__0_n_153}),
        .PCOUT(NLW_buff0_reg_PCOUT_UNCONNECTED[47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_buff0_reg_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_buff0_reg_XOROUT_UNCONNECTED[7:0]));
  FDRE \buff0_reg[0]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_105),
        .Q(D[0]),
        .R(1'b0));
  FDRE \buff0_reg[10]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_95),
        .Q(D[10]),
        .R(1'b0));
  FDRE \buff0_reg[11]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_94),
        .Q(D[11]),
        .R(1'b0));
  FDRE \buff0_reg[12]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_93),
        .Q(D[12]),
        .R(1'b0));
  FDRE \buff0_reg[13]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_92),
        .Q(D[13]),
        .R(1'b0));
  FDRE \buff0_reg[14]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_91),
        .Q(D[14]),
        .R(1'b0));
  FDRE \buff0_reg[15]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_90),
        .Q(D[15]),
        .R(1'b0));
  FDRE \buff0_reg[16]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_89),
        .Q(\buff0_reg[16]__0_n_0 ),
        .R(1'b0));
  FDRE \buff0_reg[1]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_104),
        .Q(D[1]),
        .R(1'b0));
  FDRE \buff0_reg[2]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_103),
        .Q(D[2]),
        .R(1'b0));
  FDRE \buff0_reg[3]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_102),
        .Q(D[3]),
        .R(1'b0));
  FDRE \buff0_reg[4]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_101),
        .Q(D[4]),
        .R(1'b0));
  FDRE \buff0_reg[5]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_100),
        .Q(D[5]),
        .R(1'b0));
  FDRE \buff0_reg[6]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_99),
        .Q(D[6]),
        .R(1'b0));
  FDRE \buff0_reg[7]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_98),
        .Q(D[7]),
        .R(1'b0));
  FDRE \buff0_reg[8]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_97),
        .Q(D[8]),
        .R(1'b0));
  FDRE \buff0_reg[9]__0 
       (.C(ap_clk),
        .CE(ap_block_pp0_stage0_subdone),
        .D(tmp_product__0_n_96),
        .Q(D[9]),
        .R(1'b0));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[23]_i_2 
       (.I0(buff0_reg_n_99),
        .I1(tmp_product_n_99),
        .O(\mul_ln14_1_reg_625[23]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[23]_i_3 
       (.I0(buff0_reg_n_100),
        .I1(tmp_product_n_100),
        .O(\mul_ln14_1_reg_625[23]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[23]_i_4 
       (.I0(buff0_reg_n_101),
        .I1(tmp_product_n_101),
        .O(\mul_ln14_1_reg_625[23]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[23]_i_5 
       (.I0(buff0_reg_n_102),
        .I1(tmp_product_n_102),
        .O(\mul_ln14_1_reg_625[23]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[23]_i_6 
       (.I0(buff0_reg_n_103),
        .I1(tmp_product_n_103),
        .O(\mul_ln14_1_reg_625[23]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[23]_i_7 
       (.I0(buff0_reg_n_104),
        .I1(tmp_product_n_104),
        .O(\mul_ln14_1_reg_625[23]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[23]_i_8 
       (.I0(buff0_reg_n_105),
        .I1(tmp_product_n_105),
        .O(\mul_ln14_1_reg_625[23]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[31]_i_2 
       (.I0(buff0_reg_n_91),
        .I1(tmp_product_n_91),
        .O(\mul_ln14_1_reg_625[31]_i_2_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[31]_i_3 
       (.I0(buff0_reg_n_92),
        .I1(tmp_product_n_92),
        .O(\mul_ln14_1_reg_625[31]_i_3_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[31]_i_4 
       (.I0(buff0_reg_n_93),
        .I1(tmp_product_n_93),
        .O(\mul_ln14_1_reg_625[31]_i_4_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[31]_i_5 
       (.I0(buff0_reg_n_94),
        .I1(tmp_product_n_94),
        .O(\mul_ln14_1_reg_625[31]_i_5_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[31]_i_6 
       (.I0(buff0_reg_n_95),
        .I1(tmp_product_n_95),
        .O(\mul_ln14_1_reg_625[31]_i_6_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[31]_i_7 
       (.I0(buff0_reg_n_96),
        .I1(tmp_product_n_96),
        .O(\mul_ln14_1_reg_625[31]_i_7_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[31]_i_8 
       (.I0(buff0_reg_n_97),
        .I1(tmp_product_n_97),
        .O(\mul_ln14_1_reg_625[31]_i_8_n_0 ));
  LUT2 #(
    .INIT(4'h6)) 
    \mul_ln14_1_reg_625[31]_i_9 
       (.I0(buff0_reg_n_98),
        .I1(tmp_product_n_98),
        .O(\mul_ln14_1_reg_625[31]_i_9_n_0 ));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \mul_ln14_1_reg_625_reg[23]_i_1 
       (.CI(1'b0),
        .CI_TOP(1'b0),
        .CO({\mul_ln14_1_reg_625_reg[23]_i_1_n_0 ,\mul_ln14_1_reg_625_reg[23]_i_1_n_1 ,\mul_ln14_1_reg_625_reg[23]_i_1_n_2 ,\mul_ln14_1_reg_625_reg[23]_i_1_n_3 ,\mul_ln14_1_reg_625_reg[23]_i_1_n_4 ,\mul_ln14_1_reg_625_reg[23]_i_1_n_5 ,\mul_ln14_1_reg_625_reg[23]_i_1_n_6 ,\mul_ln14_1_reg_625_reg[23]_i_1_n_7 }),
        .DI({buff0_reg_n_99,buff0_reg_n_100,buff0_reg_n_101,buff0_reg_n_102,buff0_reg_n_103,buff0_reg_n_104,buff0_reg_n_105,1'b0}),
        .O(D[23:16]),
        .S({\mul_ln14_1_reg_625[23]_i_2_n_0 ,\mul_ln14_1_reg_625[23]_i_3_n_0 ,\mul_ln14_1_reg_625[23]_i_4_n_0 ,\mul_ln14_1_reg_625[23]_i_5_n_0 ,\mul_ln14_1_reg_625[23]_i_6_n_0 ,\mul_ln14_1_reg_625[23]_i_7_n_0 ,\mul_ln14_1_reg_625[23]_i_8_n_0 ,\buff0_reg[16]__0_n_0 }));
  (* ADDER_THRESHOLD = "35" *) 
  CARRY8 \mul_ln14_1_reg_625_reg[31]_i_1 
       (.CI(\mul_ln14_1_reg_625_reg[23]_i_1_n_0 ),
        .CI_TOP(1'b0),
        .CO({\NLW_mul_ln14_1_reg_625_reg[31]_i_1_CO_UNCONNECTED [7],\mul_ln14_1_reg_625_reg[31]_i_1_n_1 ,\mul_ln14_1_reg_625_reg[31]_i_1_n_2 ,\mul_ln14_1_reg_625_reg[31]_i_1_n_3 ,\mul_ln14_1_reg_625_reg[31]_i_1_n_4 ,\mul_ln14_1_reg_625_reg[31]_i_1_n_5 ,\mul_ln14_1_reg_625_reg[31]_i_1_n_6 ,\mul_ln14_1_reg_625_reg[31]_i_1_n_7 }),
        .DI({1'b0,buff0_reg_n_92,buff0_reg_n_93,buff0_reg_n_94,buff0_reg_n_95,buff0_reg_n_96,buff0_reg_n_97,buff0_reg_n_98}),
        .O(D[31:24]),
        .S({\mul_ln14_1_reg_625[31]_i_2_n_0 ,\mul_ln14_1_reg_625[31]_i_3_n_0 ,\mul_ln14_1_reg_625[31]_i_4_n_0 ,\mul_ln14_1_reg_625[31]_i_5_n_0 ,\mul_ln14_1_reg_625[31]_i_6_n_0 ,\mul_ln14_1_reg_625[31]_i_7_n_0 ,\mul_ln14_1_reg_625[31]_i_8_n_0 ,\mul_ln14_1_reg_625[31]_i_9_n_0 }));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 15x18 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(1),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    tmp_product
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,in1_Dout_A[16:0]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(NLW_tmp_product_ACOUT_UNCONNECTED[29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({in2_Dout_A[31],in2_Dout_A[31],in2_Dout_A[31],in2_Dout_A[31:17]}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_tmp_product_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_tmp_product_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_tmp_product_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEB2),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(CEB2),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(ap_block_pp0_stage0_subdone),
        .CLK(ap_clk),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_tmp_product_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_tmp_product_OVERFLOW_UNCONNECTED),
        .P({tmp_product_n_58,tmp_product_n_59,tmp_product_n_60,tmp_product_n_61,tmp_product_n_62,tmp_product_n_63,tmp_product_n_64,tmp_product_n_65,tmp_product_n_66,tmp_product_n_67,tmp_product_n_68,tmp_product_n_69,tmp_product_n_70,tmp_product_n_71,tmp_product_n_72,tmp_product_n_73,tmp_product_n_74,tmp_product_n_75,tmp_product_n_76,tmp_product_n_77,tmp_product_n_78,tmp_product_n_79,tmp_product_n_80,tmp_product_n_81,tmp_product_n_82,tmp_product_n_83,tmp_product_n_84,tmp_product_n_85,tmp_product_n_86,tmp_product_n_87,tmp_product_n_88,tmp_product_n_89,tmp_product_n_90,tmp_product_n_91,tmp_product_n_92,tmp_product_n_93,tmp_product_n_94,tmp_product_n_95,tmp_product_n_96,tmp_product_n_97,tmp_product_n_98,tmp_product_n_99,tmp_product_n_100,tmp_product_n_101,tmp_product_n_102,tmp_product_n_103,tmp_product_n_104,tmp_product_n_105}),
        .PATTERNBDETECT(NLW_tmp_product_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_tmp_product_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT({tmp_product_n_106,tmp_product_n_107,tmp_product_n_108,tmp_product_n_109,tmp_product_n_110,tmp_product_n_111,tmp_product_n_112,tmp_product_n_113,tmp_product_n_114,tmp_product_n_115,tmp_product_n_116,tmp_product_n_117,tmp_product_n_118,tmp_product_n_119,tmp_product_n_120,tmp_product_n_121,tmp_product_n_122,tmp_product_n_123,tmp_product_n_124,tmp_product_n_125,tmp_product_n_126,tmp_product_n_127,tmp_product_n_128,tmp_product_n_129,tmp_product_n_130,tmp_product_n_131,tmp_product_n_132,tmp_product_n_133,tmp_product_n_134,tmp_product_n_135,tmp_product_n_136,tmp_product_n_137,tmp_product_n_138,tmp_product_n_139,tmp_product_n_140,tmp_product_n_141,tmp_product_n_142,tmp_product_n_143,tmp_product_n_144,tmp_product_n_145,tmp_product_n_146,tmp_product_n_147,tmp_product_n_148,tmp_product_n_149,tmp_product_n_150,tmp_product_n_151,tmp_product_n_152,tmp_product_n_153}),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_tmp_product_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_tmp_product_XOROUT_UNCONNECTED[7:0]));
  (* KEEP_HIERARCHY = "yes" *) 
  (* METHODOLOGY_DRC_VIOS = "{SYNTH-10 {cell *THIS*} {string 18x18 4}}" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(1),
    .ALUMODEREG(0),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .AUTORESET_PRIORITY("RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BMULTSEL("B"),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(0),
    .CARRYINSELREG(0),
    .CREG(1),
    .DREG(1),
    .INMODEREG(0),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(0),
    .PATTERN(48'h000000000000),
    .PREADDINSEL("A"),
    .PREG(0),
    .RND(48'h000000000000),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("MULTIPLY"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48"),
    .USE_WIDEXOR("FALSE"),
    .XORSIMD("XOR24_48_96")) 
    tmp_product__0
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,in2_Dout_A[16:0]}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT({tmp_product__0_n_24,tmp_product__0_n_25,tmp_product__0_n_26,tmp_product__0_n_27,tmp_product__0_n_28,tmp_product__0_n_29,tmp_product__0_n_30,tmp_product__0_n_31,tmp_product__0_n_32,tmp_product__0_n_33,tmp_product__0_n_34,tmp_product__0_n_35,tmp_product__0_n_36,tmp_product__0_n_37,tmp_product__0_n_38,tmp_product__0_n_39,tmp_product__0_n_40,tmp_product__0_n_41,tmp_product__0_n_42,tmp_product__0_n_43,tmp_product__0_n_44,tmp_product__0_n_45,tmp_product__0_n_46,tmp_product__0_n_47,tmp_product__0_n_48,tmp_product__0_n_49,tmp_product__0_n_50,tmp_product__0_n_51,tmp_product__0_n_52,tmp_product__0_n_53}),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,in1_Dout_A[16:0]}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(NLW_tmp_product__0_BCOUT_UNCONNECTED[17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(NLW_tmp_product__0_CARRYCASCOUT_UNCONNECTED),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(NLW_tmp_product__0_CARRYOUT_UNCONNECTED[3:0]),
        .CEA1(1'b0),
        .CEA2(CEB2),
        .CEAD(1'b0),
        .CEALUMODE(1'b0),
        .CEB1(1'b0),
        .CEB2(CEB2),
        .CEC(1'b0),
        .CECARRYIN(1'b0),
        .CECTRL(1'b0),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b0),
        .CLK(ap_clk),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(NLW_tmp_product__0_MULTSIGNOUT_UNCONNECTED),
        .OPMODE({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1,1'b0,1'b1}),
        .OVERFLOW(NLW_tmp_product__0_OVERFLOW_UNCONNECTED),
        .P({tmp_product__0_n_58,tmp_product__0_n_59,tmp_product__0_n_60,tmp_product__0_n_61,tmp_product__0_n_62,tmp_product__0_n_63,tmp_product__0_n_64,tmp_product__0_n_65,tmp_product__0_n_66,tmp_product__0_n_67,tmp_product__0_n_68,tmp_product__0_n_69,tmp_product__0_n_70,tmp_product__0_n_71,tmp_product__0_n_72,tmp_product__0_n_73,tmp_product__0_n_74,tmp_product__0_n_75,tmp_product__0_n_76,tmp_product__0_n_77,tmp_product__0_n_78,tmp_product__0_n_79,tmp_product__0_n_80,tmp_product__0_n_81,tmp_product__0_n_82,tmp_product__0_n_83,tmp_product__0_n_84,tmp_product__0_n_85,tmp_product__0_n_86,tmp_product__0_n_87,tmp_product__0_n_88,tmp_product__0_n_89,tmp_product__0_n_90,tmp_product__0_n_91,tmp_product__0_n_92,tmp_product__0_n_93,tmp_product__0_n_94,tmp_product__0_n_95,tmp_product__0_n_96,tmp_product__0_n_97,tmp_product__0_n_98,tmp_product__0_n_99,tmp_product__0_n_100,tmp_product__0_n_101,tmp_product__0_n_102,tmp_product__0_n_103,tmp_product__0_n_104,tmp_product__0_n_105}),
        .PATTERNBDETECT(NLW_tmp_product__0_PATTERNBDETECT_UNCONNECTED),
        .PATTERNDETECT(NLW_tmp_product__0_PATTERNDETECT_UNCONNECTED),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT({tmp_product__0_n_106,tmp_product__0_n_107,tmp_product__0_n_108,tmp_product__0_n_109,tmp_product__0_n_110,tmp_product__0_n_111,tmp_product__0_n_112,tmp_product__0_n_113,tmp_product__0_n_114,tmp_product__0_n_115,tmp_product__0_n_116,tmp_product__0_n_117,tmp_product__0_n_118,tmp_product__0_n_119,tmp_product__0_n_120,tmp_product__0_n_121,tmp_product__0_n_122,tmp_product__0_n_123,tmp_product__0_n_124,tmp_product__0_n_125,tmp_product__0_n_126,tmp_product__0_n_127,tmp_product__0_n_128,tmp_product__0_n_129,tmp_product__0_n_130,tmp_product__0_n_131,tmp_product__0_n_132,tmp_product__0_n_133,tmp_product__0_n_134,tmp_product__0_n_135,tmp_product__0_n_136,tmp_product__0_n_137,tmp_product__0_n_138,tmp_product__0_n_139,tmp_product__0_n_140,tmp_product__0_n_141,tmp_product__0_n_142,tmp_product__0_n_143,tmp_product__0_n_144,tmp_product__0_n_145,tmp_product__0_n_146,tmp_product__0_n_147,tmp_product__0_n_148,tmp_product__0_n_149,tmp_product__0_n_150,tmp_product__0_n_151,tmp_product__0_n_152,tmp_product__0_n_153}),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(NLW_tmp_product__0_UNDERFLOW_UNCONNECTED),
        .XOROUT(NLW_tmp_product__0_XOROUT_UNCONNECTED[7:0]));
  LUT2 #(
    .INIT(4'h8)) 
    tmp_product_i_1
       (.I0(ap_enable_reg_pp0_iter1),
        .I1(ap_block_pp0_stage0_subdone),
        .O(CEB2));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
