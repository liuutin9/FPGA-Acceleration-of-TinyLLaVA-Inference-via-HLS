//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2024.2 (win64) Build 5239630 Fri Nov 08 22:35:27 MST 2024
//Date        : Tue May  6 19:42:36 2025
//Host        : Prestige14 running 64-bit major release  (build 9200)
//Command     : generate_target bd_0.bd
//Design      : bd_0
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "bd_0,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=bd_0,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=1,numReposBlks=1,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=1,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=Hierarchical}" *) (* HW_HANDOFF = "bd_0.hwdef" *) 
module bd_0
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
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.AP_CLK CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.AP_CLK, ASSOCIATED_BUSIF s_axi_control, ASSOCIATED_RESET ap_rst_n, CLK_DOMAIN bd_0_ap_clk_0, FREQ_HZ 300000000.0, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) input ap_clk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.AP_RST_N RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.AP_RST_N, INSERT_VIP 0, POLARITY ACTIVE_LOW" *) input ap_rst_n;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA ADDR" *) (* X_INTERFACE_MODE = "Master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTA, MASTER_TYPE BRAM_CTRL, MEM_ADDRESS_MODE BYTE_ADDRESS, MEM_ECC NONE, MEM_SIZE 64, MEM_WIDTH 32, READ_LATENCY 1" *) output [31:0]in1_PORTA_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA CLK" *) output in1_PORTA_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DIN" *) output [31:0]in1_PORTA_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA DOUT" *) input [31:0]in1_PORTA_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA EN" *) output in1_PORTA_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA RST" *) output in1_PORTA_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTA WE" *) output [3:0]in1_PORTA_we;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB ADDR" *) (* X_INTERFACE_MODE = "Master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in1_PORTB, MASTER_TYPE BRAM_CTRL, MEM_ADDRESS_MODE BYTE_ADDRESS, MEM_ECC NONE, MEM_SIZE 64, MEM_WIDTH 32, READ_LATENCY 1" *) output [31:0]in1_PORTB_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB CLK" *) output in1_PORTB_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DIN" *) output [31:0]in1_PORTB_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB DOUT" *) input [31:0]in1_PORTB_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB EN" *) output in1_PORTB_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB RST" *) output in1_PORTB_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in1_PORTB WE" *) output [3:0]in1_PORTB_we;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA ADDR" *) (* X_INTERFACE_MODE = "Master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTA, MASTER_TYPE BRAM_CTRL, MEM_ADDRESS_MODE BYTE_ADDRESS, MEM_ECC NONE, MEM_SIZE 64, MEM_WIDTH 32, READ_LATENCY 1" *) output [31:0]in2_PORTA_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA CLK" *) output in2_PORTA_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DIN" *) output [31:0]in2_PORTA_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA DOUT" *) input [31:0]in2_PORTA_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA EN" *) output in2_PORTA_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA RST" *) output in2_PORTA_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTA WE" *) output [3:0]in2_PORTA_we;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB ADDR" *) (* X_INTERFACE_MODE = "Master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME in2_PORTB, MASTER_TYPE BRAM_CTRL, MEM_ADDRESS_MODE BYTE_ADDRESS, MEM_ECC NONE, MEM_SIZE 64, MEM_WIDTH 32, READ_LATENCY 1" *) output [31:0]in2_PORTB_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB CLK" *) output in2_PORTB_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DIN" *) output [31:0]in2_PORTB_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB DOUT" *) input [31:0]in2_PORTB_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB EN" *) output in2_PORTB_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB RST" *) output in2_PORTB_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 in2_PORTB WE" *) output [3:0]in2_PORTB_we;
  (* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 INTR.INTERRUPT INTERRUPT" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME INTR.INTERRUPT, PortWidth 1, SENSITIVITY LEVEL_HIGH" *) output interrupt;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA ADDR" *) (* X_INTERFACE_MODE = "Master" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME out_r_PORTA, MASTER_TYPE BRAM_CTRL, MEM_ADDRESS_MODE BYTE_ADDRESS, MEM_ECC NONE, MEM_SIZE 64, MEM_WIDTH 32, READ_LATENCY 1" *) output [31:0]out_r_PORTA_addr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA CLK" *) output out_r_PORTA_clk;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DIN" *) output [31:0]out_r_PORTA_din;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA DOUT" *) input [31:0]out_r_PORTA_dout;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA EN" *) output out_r_PORTA_en;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA RST" *) output out_r_PORTA_rst;
  (* X_INTERFACE_INFO = "xilinx.com:interface:bram:1.0 out_r_PORTA WE" *) output [3:0]out_r_PORTA_we;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARADDR" *) (* X_INTERFACE_MODE = "Slave" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_control, ADDR_WIDTH 32, ARUSER_WIDTH 0, AWUSER_WIDTH 0, BUSER_WIDTH 0, CLK_DOMAIN bd_0_ap_clk_0, DATA_WIDTH 32, FREQ_HZ 300000000.0, HAS_BRESP 1, HAS_BURST 0, HAS_CACHE 0, HAS_LOCK 0, HAS_PROT 0, HAS_QOS 0, HAS_REGION 0, HAS_RRESP 1, HAS_WSTRB 1, ID_WIDTH 0, INSERT_VIP 0, MAX_BURST_LENGTH 1, NUM_READ_OUTSTANDING 1, NUM_READ_THREADS 1, NUM_WRITE_OUTSTANDING 1, NUM_WRITE_THREADS 1, PHASE 0.0, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, RUSER_BITS_PER_BYTE 0, RUSER_WIDTH 0, SUPPORTS_NARROW_BURST 0, WUSER_BITS_PER_BYTE 0, WUSER_WIDTH 0" *) input [3:0]s_axi_control_araddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARREADY" *) output s_axi_control_arready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARVALID" *) input s_axi_control_arvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWADDR" *) input [3:0]s_axi_control_awaddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWREADY" *) output s_axi_control_awready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWVALID" *) input s_axi_control_awvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BREADY" *) input s_axi_control_bready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BRESP" *) output [1:0]s_axi_control_bresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BVALID" *) output s_axi_control_bvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RDATA" *) output [31:0]s_axi_control_rdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RREADY" *) input s_axi_control_rready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RRESP" *) output [1:0]s_axi_control_rresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RVALID" *) output s_axi_control_rvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WDATA" *) input [31:0]s_axi_control_wdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WREADY" *) output s_axi_control_wready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WSTRB" *) input [3:0]s_axi_control_wstrb;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WVALID" *) input s_axi_control_wvalid;

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

  bd_0_hls_inst_0 hls_inst
       (.ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .in1_Addr_A(in1_PORTA_addr),
        .in1_Addr_B(in1_PORTB_addr),
        .in1_Clk_A(in1_PORTA_clk),
        .in1_Clk_B(in1_PORTB_clk),
        .in1_Din_A(in1_PORTA_din),
        .in1_Din_B(in1_PORTB_din),
        .in1_Dout_A(in1_PORTA_dout),
        .in1_Dout_B(in1_PORTB_dout),
        .in1_EN_A(in1_PORTA_en),
        .in1_EN_B(in1_PORTB_en),
        .in1_Rst_A(in1_PORTA_rst),
        .in1_Rst_B(in1_PORTB_rst),
        .in1_WEN_A(in1_PORTA_we),
        .in1_WEN_B(in1_PORTB_we),
        .in2_Addr_A(in2_PORTA_addr),
        .in2_Addr_B(in2_PORTB_addr),
        .in2_Clk_A(in2_PORTA_clk),
        .in2_Clk_B(in2_PORTB_clk),
        .in2_Din_A(in2_PORTA_din),
        .in2_Din_B(in2_PORTB_din),
        .in2_Dout_A(in2_PORTA_dout),
        .in2_Dout_B(in2_PORTB_dout),
        .in2_EN_A(in2_PORTA_en),
        .in2_EN_B(in2_PORTB_en),
        .in2_Rst_A(in2_PORTA_rst),
        .in2_Rst_B(in2_PORTB_rst),
        .in2_WEN_A(in2_PORTA_we),
        .in2_WEN_B(in2_PORTB_we),
        .interrupt(interrupt),
        .out_r_Addr_A(out_r_PORTA_addr),
        .out_r_Clk_A(out_r_PORTA_clk),
        .out_r_Din_A(out_r_PORTA_din),
        .out_r_Dout_A(out_r_PORTA_dout),
        .out_r_EN_A(out_r_PORTA_en),
        .out_r_Rst_A(out_r_PORTA_rst),
        .out_r_WEN_A(out_r_PORTA_we),
        .s_axi_control_ARADDR(s_axi_control_araddr),
        .s_axi_control_ARREADY(s_axi_control_arready),
        .s_axi_control_ARVALID(s_axi_control_arvalid),
        .s_axi_control_AWADDR(s_axi_control_awaddr),
        .s_axi_control_AWREADY(s_axi_control_awready),
        .s_axi_control_AWVALID(s_axi_control_awvalid),
        .s_axi_control_BREADY(s_axi_control_bready),
        .s_axi_control_BRESP(s_axi_control_bresp),
        .s_axi_control_BVALID(s_axi_control_bvalid),
        .s_axi_control_RDATA(s_axi_control_rdata),
        .s_axi_control_RREADY(s_axi_control_rready),
        .s_axi_control_RRESP(s_axi_control_rresp),
        .s_axi_control_RVALID(s_axi_control_rvalid),
        .s_axi_control_WDATA(s_axi_control_wdata),
        .s_axi_control_WREADY(s_axi_control_wready),
        .s_axi_control_WSTRB(s_axi_control_wstrb),
        .s_axi_control_WVALID(s_axi_control_wvalid));
endmodule
