//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2024.2 (win64) Build 5239630 Fri Nov 08 22:35:27 MST 2024
//Date        : Tue May  6 19:42:36 2025
//Host        : Prestige14 running 64-bit major release  (build 9200)
//Command     : generate_target bd_0_wrapper.bd
//Design      : bd_0_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module bd_0_wrapper
   (ap_clk,
    ap_rst_n,
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
    interrupt,
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
    s_axi_control_wvalid);
  input ap_clk;
  input ap_rst_n;
  output [31:0]in1_PORTA_addr;
  output in1_PORTA_clk;
  output [31:0]in1_PORTA_din;
  input [31:0]in1_PORTA_dout;
  output in1_PORTA_en;
  output in1_PORTA_rst;
  output [3:0]in1_PORTA_we;
  output [31:0]in1_PORTB_addr;
  output in1_PORTB_clk;
  output [31:0]in1_PORTB_din;
  input [31:0]in1_PORTB_dout;
  output in1_PORTB_en;
  output in1_PORTB_rst;
  output [3:0]in1_PORTB_we;
  output [31:0]in2_PORTA_addr;
  output in2_PORTA_clk;
  output [31:0]in2_PORTA_din;
  input [31:0]in2_PORTA_dout;
  output in2_PORTA_en;
  output in2_PORTA_rst;
  output [3:0]in2_PORTA_we;
  output [31:0]in2_PORTB_addr;
  output in2_PORTB_clk;
  output [31:0]in2_PORTB_din;
  input [31:0]in2_PORTB_dout;
  output in2_PORTB_en;
  output in2_PORTB_rst;
  output [3:0]in2_PORTB_we;
  output interrupt;
  output [31:0]out_r_PORTA_addr;
  output out_r_PORTA_clk;
  output [31:0]out_r_PORTA_din;
  input [31:0]out_r_PORTA_dout;
  output out_r_PORTA_en;
  output out_r_PORTA_rst;
  output [3:0]out_r_PORTA_we;
  input [3:0]s_axi_control_araddr;
  output s_axi_control_arready;
  input s_axi_control_arvalid;
  input [3:0]s_axi_control_awaddr;
  output s_axi_control_awready;
  input s_axi_control_awvalid;
  input s_axi_control_bready;
  output [1:0]s_axi_control_bresp;
  output s_axi_control_bvalid;
  output [31:0]s_axi_control_rdata;
  input s_axi_control_rready;
  output [1:0]s_axi_control_rresp;
  output s_axi_control_rvalid;
  input [31:0]s_axi_control_wdata;
  output s_axi_control_wready;
  input [3:0]s_axi_control_wstrb;
  input s_axi_control_wvalid;

  wire ap_clk;
  wire ap_rst_n;
  wire [31:0]in1_PORTA_addr;
  wire in1_PORTA_clk;
  wire [31:0]in1_PORTA_din;
  wire [31:0]in1_PORTA_dout;
  wire in1_PORTA_en;
  wire in1_PORTA_rst;
  wire [3:0]in1_PORTA_we;
  wire [31:0]in1_PORTB_addr;
  wire in1_PORTB_clk;
  wire [31:0]in1_PORTB_din;
  wire [31:0]in1_PORTB_dout;
  wire in1_PORTB_en;
  wire in1_PORTB_rst;
  wire [3:0]in1_PORTB_we;
  wire [31:0]in2_PORTA_addr;
  wire in2_PORTA_clk;
  wire [31:0]in2_PORTA_din;
  wire [31:0]in2_PORTA_dout;
  wire in2_PORTA_en;
  wire in2_PORTA_rst;
  wire [3:0]in2_PORTA_we;
  wire [31:0]in2_PORTB_addr;
  wire in2_PORTB_clk;
  wire [31:0]in2_PORTB_din;
  wire [31:0]in2_PORTB_dout;
  wire in2_PORTB_en;
  wire in2_PORTB_rst;
  wire [3:0]in2_PORTB_we;
  wire interrupt;
  wire [31:0]out_r_PORTA_addr;
  wire out_r_PORTA_clk;
  wire [31:0]out_r_PORTA_din;
  wire [31:0]out_r_PORTA_dout;
  wire out_r_PORTA_en;
  wire out_r_PORTA_rst;
  wire [3:0]out_r_PORTA_we;
  wire [3:0]s_axi_control_araddr;
  wire s_axi_control_arready;
  wire s_axi_control_arvalid;
  wire [3:0]s_axi_control_awaddr;
  wire s_axi_control_awready;
  wire s_axi_control_awvalid;
  wire s_axi_control_bready;
  wire [1:0]s_axi_control_bresp;
  wire s_axi_control_bvalid;
  wire [31:0]s_axi_control_rdata;
  wire s_axi_control_rready;
  wire [1:0]s_axi_control_rresp;
  wire s_axi_control_rvalid;
  wire [31:0]s_axi_control_wdata;
  wire s_axi_control_wready;
  wire [3:0]s_axi_control_wstrb;
  wire s_axi_control_wvalid;

  bd_0 bd_0_i
       (.ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .in1_PORTA_addr(in1_PORTA_addr),
        .in1_PORTA_clk(in1_PORTA_clk),
        .in1_PORTA_din(in1_PORTA_din),
        .in1_PORTA_dout(in1_PORTA_dout),
        .in1_PORTA_en(in1_PORTA_en),
        .in1_PORTA_rst(in1_PORTA_rst),
        .in1_PORTA_we(in1_PORTA_we),
        .in1_PORTB_addr(in1_PORTB_addr),
        .in1_PORTB_clk(in1_PORTB_clk),
        .in1_PORTB_din(in1_PORTB_din),
        .in1_PORTB_dout(in1_PORTB_dout),
        .in1_PORTB_en(in1_PORTB_en),
        .in1_PORTB_rst(in1_PORTB_rst),
        .in1_PORTB_we(in1_PORTB_we),
        .in2_PORTA_addr(in2_PORTA_addr),
        .in2_PORTA_clk(in2_PORTA_clk),
        .in2_PORTA_din(in2_PORTA_din),
        .in2_PORTA_dout(in2_PORTA_dout),
        .in2_PORTA_en(in2_PORTA_en),
        .in2_PORTA_rst(in2_PORTA_rst),
        .in2_PORTA_we(in2_PORTA_we),
        .in2_PORTB_addr(in2_PORTB_addr),
        .in2_PORTB_clk(in2_PORTB_clk),
        .in2_PORTB_din(in2_PORTB_din),
        .in2_PORTB_dout(in2_PORTB_dout),
        .in2_PORTB_en(in2_PORTB_en),
        .in2_PORTB_rst(in2_PORTB_rst),
        .in2_PORTB_we(in2_PORTB_we),
        .interrupt(interrupt),
        .out_r_PORTA_addr(out_r_PORTA_addr),
        .out_r_PORTA_clk(out_r_PORTA_clk),
        .out_r_PORTA_din(out_r_PORTA_din),
        .out_r_PORTA_dout(out_r_PORTA_dout),
        .out_r_PORTA_en(out_r_PORTA_en),
        .out_r_PORTA_rst(out_r_PORTA_rst),
        .out_r_PORTA_we(out_r_PORTA_we),
        .s_axi_control_araddr(s_axi_control_araddr),
        .s_axi_control_arready(s_axi_control_arready),
        .s_axi_control_arvalid(s_axi_control_arvalid),
        .s_axi_control_awaddr(s_axi_control_awaddr),
        .s_axi_control_awready(s_axi_control_awready),
        .s_axi_control_awvalid(s_axi_control_awvalid),
        .s_axi_control_bready(s_axi_control_bready),
        .s_axi_control_bresp(s_axi_control_bresp),
        .s_axi_control_bvalid(s_axi_control_bvalid),
        .s_axi_control_rdata(s_axi_control_rdata),
        .s_axi_control_rready(s_axi_control_rready),
        .s_axi_control_rresp(s_axi_control_rresp),
        .s_axi_control_rvalid(s_axi_control_rvalid),
        .s_axi_control_wdata(s_axi_control_wdata),
        .s_axi_control_wready(s_axi_control_wready),
        .s_axi_control_wstrb(s_axi_control_wstrb),
        .s_axi_control_wvalid(s_axi_control_wvalid));
endmodule
