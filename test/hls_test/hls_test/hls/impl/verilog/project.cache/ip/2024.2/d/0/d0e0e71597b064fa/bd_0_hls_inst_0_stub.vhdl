-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2024.2 (win64) Build 5239630 Fri Nov 08 22:35:27 MST 2024
-- Date        : Tue May  6 19:43:58 2025
-- Host        : Prestige14 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ bd_0_hls_inst_0_stub.vhdl
-- Design      : bd_0_hls_inst_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xcu50-fsvh2104-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  Port ( 
    s_axi_control_ARADDR : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_control_ARREADY : out STD_LOGIC;
    s_axi_control_ARVALID : in STD_LOGIC;
    s_axi_control_AWADDR : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_control_AWREADY : out STD_LOGIC;
    s_axi_control_AWVALID : in STD_LOGIC;
    s_axi_control_BREADY : in STD_LOGIC;
    s_axi_control_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_control_BVALID : out STD_LOGIC;
    s_axi_control_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_control_RREADY : in STD_LOGIC;
    s_axi_control_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_control_RVALID : out STD_LOGIC;
    s_axi_control_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_control_WREADY : out STD_LOGIC;
    s_axi_control_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_control_WVALID : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    interrupt : out STD_LOGIC;
    in1_Addr_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Clk_A : out STD_LOGIC;
    in1_Din_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Dout_A : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_EN_A : out STD_LOGIC;
    in1_Rst_A : out STD_LOGIC;
    in1_WEN_A : out STD_LOGIC_VECTOR ( 3 downto 0 );
    in1_Addr_B : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Clk_B : out STD_LOGIC;
    in1_Din_B : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Dout_B : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_EN_B : out STD_LOGIC;
    in1_Rst_B : out STD_LOGIC;
    in1_WEN_B : out STD_LOGIC_VECTOR ( 3 downto 0 );
    in2_Addr_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_Clk_A : out STD_LOGIC;
    in2_Din_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_Dout_A : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_EN_A : out STD_LOGIC;
    in2_Rst_A : out STD_LOGIC;
    in2_WEN_A : out STD_LOGIC_VECTOR ( 3 downto 0 );
    in2_Addr_B : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_Clk_B : out STD_LOGIC;
    in2_Din_B : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_Dout_B : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_EN_B : out STD_LOGIC;
    in2_Rst_B : out STD_LOGIC;
    in2_WEN_B : out STD_LOGIC_VECTOR ( 3 downto 0 );
    out_r_Addr_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    out_r_Clk_A : out STD_LOGIC;
    out_r_Din_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    out_r_Dout_A : in STD_LOGIC_VECTOR ( 31 downto 0 );
    out_r_EN_A : out STD_LOGIC;
    out_r_Rst_A : out STD_LOGIC;
    out_r_WEN_A : out STD_LOGIC_VECTOR ( 3 downto 0 )
  );

  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "bd_0_hls_inst_0,mat_mul,{}";
  attribute CORE_GENERATION_INFO : string;
  attribute CORE_GENERATION_INFO of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "bd_0_hls_inst_0,mat_mul,{x_ipProduct=Vivado 2024.2,x_ipVendor=xilinx.com,x_ipLibrary=hls,x_ipName=mat_mul,x_ipVersion=1.0,x_ipCoreRevision=2114071781,x_ipLanguage=VERILOG,x_ipSimLanguage=MIXED,C_S_AXI_CONTROL_ADDR_WIDTH=4,C_S_AXI_CONTROL_DATA_WIDTH=32}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "HLS";
  attribute hls_module : string;
  attribute hls_module of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture stub of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  attribute syn_black_box : boolean;
  attribute black_box_pad_pin : string;
  attribute syn_black_box of stub : architecture is true;
  attribute black_box_pad_pin of stub : architecture is "s_axi_control_ARADDR[3:0],s_axi_control_ARREADY,s_axi_control_ARVALID,s_axi_control_AWADDR[3:0],s_axi_control_AWREADY,s_axi_control_AWVALID,s_axi_control_BREADY,s_axi_control_BRESP[1:0],s_axi_control_BVALID,s_axi_control_RDATA[31:0],s_axi_control_RREADY,s_axi_control_RRESP[1:0],s_axi_control_RVALID,s_axi_control_WDATA[31:0],s_axi_control_WREADY,s_axi_control_WSTRB[3:0],s_axi_control_WVALID,ap_clk,ap_rst_n,interrupt,in1_Addr_A[31:0],in1_Clk_A,in1_Din_A[31:0],in1_Dout_A[31:0],in1_EN_A,in1_Rst_A,in1_WEN_A[3:0],in1_Addr_B[31:0],in1_Clk_B,in1_Din_B[31:0],in1_Dout_B[31:0],in1_EN_B,in1_Rst_B,in1_WEN_B[3:0],in2_Addr_A[31:0],in2_Clk_A,in2_Din_A[31:0],in2_Dout_A[31:0],in2_EN_A,in2_Rst_A,in2_WEN_A[3:0],in2_Addr_B[31:0],in2_Clk_B,in2_Din_B[31:0],in2_Dout_B[31:0],in2_EN_B,in2_Rst_B,in2_WEN_B[3:0],out_r_Addr_A[31:0],out_r_Clk_A,out_r_Din_A[31:0],out_r_Dout_A[31:0],out_r_EN_A,out_r_Rst_A,out_r_WEN_A[3:0]";
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of s_axi_control_ARADDR : signal is "xilinx.com:interface:aximm:1.0 s_axi_control ARADDR";
  attribute X_INTERFACE_MODE : string;
  attribute X_INTERFACE_MODE of s_axi_control_ARADDR : signal is "slave";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of s_axi_control_ARADDR : signal is "XIL_INTERFACENAME s_axi_control, ADDR_WIDTH 4, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 300000000.0, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s_axi_control_ARREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control ARREADY";
  attribute X_INTERFACE_INFO of s_axi_control_ARVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control ARVALID";
  attribute X_INTERFACE_INFO of s_axi_control_AWADDR : signal is "xilinx.com:interface:aximm:1.0 s_axi_control AWADDR";
  attribute X_INTERFACE_INFO of s_axi_control_AWREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control AWREADY";
  attribute X_INTERFACE_INFO of s_axi_control_AWVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control AWVALID";
  attribute X_INTERFACE_INFO of s_axi_control_BREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control BREADY";
  attribute X_INTERFACE_INFO of s_axi_control_BRESP : signal is "xilinx.com:interface:aximm:1.0 s_axi_control BRESP";
  attribute X_INTERFACE_INFO of s_axi_control_BVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control BVALID";
  attribute X_INTERFACE_INFO of s_axi_control_RDATA : signal is "xilinx.com:interface:aximm:1.0 s_axi_control RDATA";
  attribute X_INTERFACE_INFO of s_axi_control_RREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control RREADY";
  attribute X_INTERFACE_INFO of s_axi_control_RRESP : signal is "xilinx.com:interface:aximm:1.0 s_axi_control RRESP";
  attribute X_INTERFACE_INFO of s_axi_control_RVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control RVALID";
  attribute X_INTERFACE_INFO of s_axi_control_WDATA : signal is "xilinx.com:interface:aximm:1.0 s_axi_control WDATA";
  attribute X_INTERFACE_INFO of s_axi_control_WREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control WREADY";
  attribute X_INTERFACE_INFO of s_axi_control_WSTRB : signal is "xilinx.com:interface:aximm:1.0 s_axi_control WSTRB";
  attribute X_INTERFACE_INFO of s_axi_control_WVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control WVALID";
  attribute X_INTERFACE_INFO of ap_clk : signal is "xilinx.com:signal:clock:1.0 ap_clk CLK";
  attribute X_INTERFACE_MODE of ap_clk : signal is "slave";
  attribute X_INTERFACE_PARAMETER of ap_clk : signal is "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF s_axi_control, ASSOCIATED_RESET ap_rst_n, FREQ_HZ 300000000.0, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of ap_rst_n : signal is "xilinx.com:signal:reset:1.0 ap_rst_n RST";
  attribute X_INTERFACE_MODE of ap_rst_n : signal is "slave";
  attribute X_INTERFACE_PARAMETER of ap_rst_n : signal is "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of interrupt : signal is "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT";
  attribute X_INTERFACE_MODE of interrupt : signal is "master";
  attribute X_INTERFACE_PARAMETER of interrupt : signal is "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, PortWidth 1";
  attribute X_INTERFACE_INFO of in1_Addr_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA ADDR";
  attribute X_INTERFACE_MODE of in1_Addr_A : signal is "master";
  attribute X_INTERFACE_PARAMETER of in1_Addr_A : signal is "XIL_INTERFACENAME in1_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of in1_Clk_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA CLK";
  attribute X_INTERFACE_INFO of in1_Din_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA DIN";
  attribute X_INTERFACE_INFO of in1_Dout_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA DOUT";
  attribute X_INTERFACE_INFO of in1_EN_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA EN";
  attribute X_INTERFACE_INFO of in1_Rst_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA RST";
  attribute X_INTERFACE_INFO of in1_WEN_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA WE";
  attribute X_INTERFACE_INFO of in1_Addr_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB ADDR";
  attribute X_INTERFACE_MODE of in1_Addr_B : signal is "master";
  attribute X_INTERFACE_PARAMETER of in1_Addr_B : signal is "XIL_INTERFACENAME in1_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of in1_Clk_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB CLK";
  attribute X_INTERFACE_INFO of in1_Din_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB DIN";
  attribute X_INTERFACE_INFO of in1_Dout_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB DOUT";
  attribute X_INTERFACE_INFO of in1_EN_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB EN";
  attribute X_INTERFACE_INFO of in1_Rst_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB RST";
  attribute X_INTERFACE_INFO of in1_WEN_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB WE";
  attribute X_INTERFACE_INFO of in2_Addr_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA ADDR";
  attribute X_INTERFACE_MODE of in2_Addr_A : signal is "master";
  attribute X_INTERFACE_PARAMETER of in2_Addr_A : signal is "XIL_INTERFACENAME in2_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of in2_Clk_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA CLK";
  attribute X_INTERFACE_INFO of in2_Din_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA DIN";
  attribute X_INTERFACE_INFO of in2_Dout_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA DOUT";
  attribute X_INTERFACE_INFO of in2_EN_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA EN";
  attribute X_INTERFACE_INFO of in2_Rst_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA RST";
  attribute X_INTERFACE_INFO of in2_WEN_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA WE";
  attribute X_INTERFACE_INFO of in2_Addr_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB ADDR";
  attribute X_INTERFACE_MODE of in2_Addr_B : signal is "master";
  attribute X_INTERFACE_PARAMETER of in2_Addr_B : signal is "XIL_INTERFACENAME in2_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of in2_Clk_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB CLK";
  attribute X_INTERFACE_INFO of in2_Din_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB DIN";
  attribute X_INTERFACE_INFO of in2_Dout_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB DOUT";
  attribute X_INTERFACE_INFO of in2_EN_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB EN";
  attribute X_INTERFACE_INFO of in2_Rst_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB RST";
  attribute X_INTERFACE_INFO of in2_WEN_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB WE";
  attribute X_INTERFACE_INFO of out_r_Addr_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA ADDR";
  attribute X_INTERFACE_MODE of out_r_Addr_A : signal is "master";
  attribute X_INTERFACE_PARAMETER of out_r_Addr_A : signal is "XIL_INTERFACENAME out_r_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of out_r_Clk_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA CLK";
  attribute X_INTERFACE_INFO of out_r_Din_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA DIN";
  attribute X_INTERFACE_INFO of out_r_Dout_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA DOUT";
  attribute X_INTERFACE_INFO of out_r_EN_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA EN";
  attribute X_INTERFACE_INFO of out_r_Rst_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA RST";
  attribute X_INTERFACE_INFO of out_r_WEN_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA WE";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of stub : architecture is "mat_mul,Vivado 2024.2";
begin
end;
