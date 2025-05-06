// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// -------------------------------------------------------------------------------

`timescale 1 ps / 1 ps

(* BLOCK_STUB = "true" *)
module bd_0 (
  ap_clk,
  ap_rst_n,
  interrupt,
  in1_PORTA_addr,
  in1_PORTA_clk,
  in1_PORTA_din,
  in1_PORTA_dout,
  in1_PORTA_en,
  in1_PORTA_rst,
  in1_PORTA_we,
  in1_PORTB_addr,
  in1_PORTB_clk,
  in1_PORTB_din,
  in1_PORTB_dout,
  in1_PORTB_en,
  in1_PORTB_rst,
  in1_PORTB_we,
  in2_PORTA_addr,
  in2_PORTA_clk,
  in2_PORTA_din,
  in2_PORTA_dout,
  in2_PORTA_en,
  in2_PORTA_rst,
  in2_PORTA_we,
  in2_PORTB_addr,
  in2_PORTB_clk,
  in2_PORTB_din,
  in2_PORTB_dout,
  in2_PORTB_en,
  in2_PORTB_rst,
  in2_PORTB_we,
  out_r_PORTA_addr,
  out_r_PORTA_clk,
  out_r_PORTA_din,
  out_r_PORTA_dout,
  out_r_PORTA_en,
  out_r_PORTA_rst,
  out_r_PORTA_we,
  s_axi_control_araddr,
  s_axi_control_arready,
  s_axi_control_arvalid,
  s_axi_control_awaddr,
  s_axi_control_awready,
  s_axi_control_awvalid,
  s_axi_control_bready,
  s_axi_control_bresp,
  s_axi_control_bvalid,
  s_axi_control_rdata,
  s_axi_control_rready,
  s_axi_control_rresp,
  s_axi_control_rvalid,
  s_axi_control_wdata,
  s_axi_control_wready,
  s_axi_control_wstrb,
  s_axi_control_wvalid
);

  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.AP_CLK CLK" *)
  (* X_INTERFACE_MODE = "slave CLK.AP_CLK" *)
  (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.AP_CLK, FREQ_HZ 300000000.0, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, ASSOCIATED_BUSIF s_axi_control, ASSOCIATED_RESET ap_rst_n, INSERT_VIP 0" *)
  input ap_clk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.AP_RST_N RST" *)
  (* X_INTERFACE_MODE = "slave RST.AP_RST_N" *)
  (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.AP_RST_N, POLARITY ACTIVE_LOW, INSERT_VIP 0" *)
  input ap_rst_n;
  (* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 INTR.INTERRUPT INTERRUPT" *)
  (* X_INTERFACE_MODE = "master INTR.INTERRUPT" *)
  (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME INTR.INTERRUPT, SENSITIVITY LEVEL_HIGH, PortWidth 1" *)
  output interrupt;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA ADDR" *)
  (* X_INTERFACE_MODE = "master in1_PORTA" *)
  (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTA, MEM_SIZE 64, MEM_WIDTH 32, MEM_ECC NONE, MASTER_TYPE BRAM_CTRL, READ_LATENCY 1, MEM_ADDRESS_MODE BYTE_ADDRESS" *)
  output [31:0]in1_PORTA_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA CLK" *)
  output in1_PORTA_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DIN" *)
  output [31:0]in1_PORTA_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DOUT" *)
  input [31:0]in1_PORTA_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA EN" *)
  output in1_PORTA_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA RST" *)
  output in1_PORTA_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA WE" *)
  output [3:0]in1_PORTA_we;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB ADDR" *)
  (* X_INTERFACE_MODE = "master in1_PORTB" *)
  (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTB, MEM_SIZE 64, MEM_WIDTH 32, MEM_ECC NONE, MASTER_TYPE BRAM_CTRL, READ_LATENCY 1, MEM_ADDRESS_MODE BYTE_ADDRESS" *)
  output [31:0]in1_PORTB_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB CLK" *)
  output in1_PORTB_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DIN" *)
  output [31:0]in1_PORTB_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DOUT" *)
  input [31:0]in1_PORTB_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB EN" *)
  output in1_PORTB_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB RST" *)
  output in1_PORTB_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB WE" *)
  output [3:0]in1_PORTB_we;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA ADDR" *)
  (* X_INTERFACE_MODE = "master in2_PORTA" *)
  (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTA, MEM_SIZE 64, MEM_WIDTH 32, MEM_ECC NONE, MASTER_TYPE BRAM_CTRL, READ_LATENCY 1, MEM_ADDRESS_MODE BYTE_ADDRESS" *)
  output [31:0]in2_PORTA_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA CLK" *)
  output in2_PORTA_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DIN" *)
  output [31:0]in2_PORTA_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DOUT" *)
  input [31:0]in2_PORTA_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA EN" *)
  output in2_PORTA_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA RST" *)
  output in2_PORTA_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA WE" *)
  output [3:0]in2_PORTA_we;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB ADDR" *)
  (* X_INTERFACE_MODE = "master in2_PORTB" *)
  (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTB, MEM_SIZE 64, MEM_WIDTH 32, MEM_ECC NONE, MASTER_TYPE BRAM_CTRL, READ_LATENCY 1, MEM_ADDRESS_MODE BYTE_ADDRESS" *)
  output [31:0]in2_PORTB_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB CLK" *)
  output in2_PORTB_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DIN" *)
  output [31:0]in2_PORTB_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DOUT" *)
  input [31:0]in2_PORTB_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB EN" *)
  output in2_PORTB_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB RST" *)
  output in2_PORTB_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB WE" *)
  output [3:0]in2_PORTB_we;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA ADDR" *)
  (* X_INTERFACE_MODE = "master out_r_PORTA" *)
  (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME out_r_PORTA, MEM_SIZE 64, MEM_WIDTH 32, MEM_ECC NONE, MASTER_TYPE BRAM_CTRL, READ_LATENCY 1, MEM_ADDRESS_MODE BYTE_ADDRESS" *)
  output [31:0]out_r_PORTA_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA CLK" *)
  output out_r_PORTA_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DIN" *)
  output [31:0]out_r_PORTA_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DOUT" *)
  input [31:0]out_r_PORTA_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA EN" *)
  output out_r_PORTA_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA RST" *)
  output out_r_PORTA_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA WE" *)
  output [3:0]out_r_PORTA_we;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARADDR" *)
  (* X_INTERFACE_MODE = "slave s_axi_control" *)
  (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_control, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 300000000.0, ID_WIDTH 0, ADDR_WIDTH 32, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
  input [3:0]s_axi_control_araddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARREADY" *)
  output s_axi_control_arready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARVALID" *)
  input s_axi_control_arvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWADDR" *)
  input [3:0]s_axi_control_awaddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWREADY" *)
  output s_axi_control_awready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWVALID" *)
  input s_axi_control_awvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BREADY" *)
  input s_axi_control_bready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BRESP" *)
  output [1:0]s_axi_control_bresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BVALID" *)
  output s_axi_control_bvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RDATA" *)
  output [31:0]s_axi_control_rdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RREADY" *)
  input s_axi_control_rready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RRESP" *)
  output [1:0]s_axi_control_rresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RVALID" *)
  output s_axi_control_rvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WDATA" *)
  input [31:0]s_axi_control_wdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WREADY" *)
  output s_axi_control_wready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WSTRB" *)
  input [3:0]s_axi_control_wstrb;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WVALID" *)
  input s_axi_control_wvalid;

  // stub module has no contents

endmodule
