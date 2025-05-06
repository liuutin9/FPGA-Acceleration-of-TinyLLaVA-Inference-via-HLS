// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2024.2 (win64) Build 5239630 Fri Nov 08 22:35:27 MST 2024
// Date        : Tue May  6 19:44:00 2025
// Host        : Prestige14 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/liuut/Desktop/Project/test/hls_test/hls_test/hls/impl/verilog/project.gen/sources_1/bd/bd_0/ip/bd_0_hls_inst_0/bd_0_hls_inst_0_stub.v
// Design      : bd_0_hls_inst_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xcu50-fsvh2104-2-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* CHECK_LICENSE_TYPE = "bd_0_hls_inst_0,mat_mul,{}" *) (* CORE_GENERATION_INFO = "bd_0_hls_inst_0,mat_mul,{x_ipProduct=Vivado 2024.2,x_ipVendor=xilinx.com,x_ipLibrary=hls,x_ipName=mat_mul,x_ipVersion=1.0,x_ipCoreRevision=2114071781,x_ipLanguage=VERILOG,x_ipSimLanguage=MIXED,C_S_AXI_CONTROL_ADDR_WIDTH=4,C_S_AXI_CONTROL_DATA_WIDTH=32}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) 
(* IP_DEFINITION_SOURCE = "HLS" *) (* X_CORE_INFO = "mat_mul,Vivado 2024.2" *) (* hls_module = "yes" *) 
module bd_0_hls_inst_0(s_axi_control_ARADDR, 
  s_axi_control_ARREADY, s_axi_control_ARVALID, s_axi_control_AWADDR, 
  s_axi_control_AWREADY, s_axi_control_AWVALID, s_axi_control_BREADY, 
  s_axi_control_BRESP, s_axi_control_BVALID, s_axi_control_RDATA, s_axi_control_RREADY, 
  s_axi_control_RRESP, s_axi_control_RVALID, s_axi_control_WDATA, s_axi_control_WREADY, 
  s_axi_control_WSTRB, s_axi_control_WVALID, ap_clk, ap_rst_n, interrupt, in1_Addr_A, 
  in1_Clk_A, in1_Din_A, in1_Dout_A, in1_EN_A, in1_Rst_A, in1_WEN_A, in1_Addr_B, in1_Clk_B, 
  in1_Din_B, in1_Dout_B, in1_EN_B, in1_Rst_B, in1_WEN_B, in2_Addr_A, in2_Clk_A, in2_Din_A, 
  in2_Dout_A, in2_EN_A, in2_Rst_A, in2_WEN_A, in2_Addr_B, in2_Clk_B, in2_Din_B, in2_Dout_B, 
  in2_EN_B, in2_Rst_B, in2_WEN_B, out_r_Addr_A, out_r_Clk_A, out_r_Din_A, out_r_Dout_A, 
  out_r_EN_A, out_r_Rst_A, out_r_WEN_A)
/* synthesis syn_black_box black_box_pad_pin="s_axi_control_ARADDR[3:0],s_axi_control_ARREADY,s_axi_control_ARVALID,s_axi_control_AWADDR[3:0],s_axi_control_AWREADY,s_axi_control_AWVALID,s_axi_control_BREADY,s_axi_control_BRESP[1:0],s_axi_control_BVALID,s_axi_control_RDATA[31:0],s_axi_control_RREADY,s_axi_control_RRESP[1:0],s_axi_control_RVALID,s_axi_control_WDATA[31:0],s_axi_control_WREADY,s_axi_control_WSTRB[3:0],s_axi_control_WVALID,ap_rst_n,interrupt,in1_Addr_A[31:0],in1_Din_A[31:0],in1_Dout_A[31:0],in1_EN_A,in1_Rst_A,in1_WEN_A[3:0],in1_Addr_B[31:0],in1_Din_B[31:0],in1_Dout_B[31:0],in1_EN_B,in1_Rst_B,in1_WEN_B[3:0],in2_Addr_A[31:0],in2_Din_A[31:0],in2_Dout_A[31:0],in2_EN_A,in2_Rst_A,in2_WEN_A[3:0],in2_Addr_B[31:0],in2_Din_B[31:0],in2_Dout_B[31:0],in2_EN_B,in2_Rst_B,in2_WEN_B[3:0],out_r_Addr_A[31:0],out_r_Din_A[31:0],out_r_Dout_A[31:0],out_r_EN_A,out_r_Rst_A,out_r_WEN_A[3:0]" */
/* synthesis syn_force_seq_prim="ap_clk" */
/* synthesis syn_force_seq_prim="in1_Clk_A" */
/* synthesis syn_force_seq_prim="in1_Clk_B" */
/* synthesis syn_force_seq_prim="in2_Clk_A" */
/* synthesis syn_force_seq_prim="in2_Clk_B" */
/* synthesis syn_force_seq_prim="out_r_Clk_A" */;
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
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *) (* X_INTERFACE_MODE = "slave" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF s_axi_control, ASSOCIATED_RESET ap_rst_n, FREQ_HZ 300000000.0, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, INSERT_VIP 0" *) input ap_clk /* synthesis syn_isclock = 1 */;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *) (* X_INTERFACE_MODE = "slave" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input ap_rst_n;
  (* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, PortWidth 1" *) output interrupt;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]in1_Addr_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA CLK" *) output in1_Clk_A /* synthesis syn_isclock = 1 */;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DIN" *) output [31:0]in1_Din_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DOUT" *) input [31:0]in1_Dout_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA EN" *) output in1_EN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA RST" *) output in1_Rst_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA WE" *) output [3:0]in1_WEN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]in1_Addr_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB CLK" *) output in1_Clk_B /* synthesis syn_isclock = 1 */;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DIN" *) output [31:0]in1_Din_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DOUT" *) input [31:0]in1_Dout_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB EN" *) output in1_EN_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB RST" *) output in1_Rst_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB WE" *) output [3:0]in1_WEN_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]in2_Addr_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA CLK" *) output in2_Clk_A /* synthesis syn_isclock = 1 */;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DIN" *) output [31:0]in2_Din_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DOUT" *) input [31:0]in2_Dout_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA EN" *) output in2_EN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA RST" *) output in2_Rst_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA WE" *) output [3:0]in2_WEN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]in2_Addr_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB CLK" *) output in2_Clk_B /* synthesis syn_isclock = 1 */;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DIN" *) output [31:0]in2_Din_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DOUT" *) input [31:0]in2_Dout_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB EN" *) output in2_EN_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB RST" *) output in2_Rst_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB WE" *) output [3:0]in2_WEN_B;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA ADDR" *) (* X_INTERFACE_MODE = "master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME out_r_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE" *) output [31:0]out_r_Addr_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA CLK" *) output out_r_Clk_A /* synthesis syn_isclock = 1 */;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DIN" *) output [31:0]out_r_Din_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DOUT" *) input [31:0]out_r_Dout_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA EN" *) output out_r_EN_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA RST" *) output out_r_Rst_A;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA WE" *) output [3:0]out_r_WEN_A;
endmodule
