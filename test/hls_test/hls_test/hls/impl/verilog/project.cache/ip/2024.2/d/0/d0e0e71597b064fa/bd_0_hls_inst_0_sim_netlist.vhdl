-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2024.2 (win64) Build 5239630 Fri Nov 08 22:35:27 MST 2024
-- Date        : Tue May  6 19:43:58 2025
-- Host        : Prestige14 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ bd_0_hls_inst_0_sim_netlist.vhdl
-- Design      : bd_0_hls_inst_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xcu50-fsvh2104-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_control_s_axi is
  port (
    interrupt : out STD_LOGIC;
    \FSM_onehot_rstate_reg[1]_0\ : out STD_LOGIC;
    s_axi_control_RVALID : out STD_LOGIC;
    \FSM_onehot_wstate_reg[1]_0\ : out STD_LOGIC;
    \FSM_onehot_wstate_reg[2]_0\ : out STD_LOGIC;
    s_axi_control_BVALID : out STD_LOGIC;
    ap_start : out STD_LOGIC;
    ap_start_int : out STD_LOGIC;
    ap_loop_exit_ready_pp0_iter4_reg_reg : out STD_LOGIC;
    s_axi_control_RDATA : out STD_LOGIC_VECTOR ( 6 downto 0 );
    int_task_ap_done_reg_0 : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    s_axi_control_ARVALID : in STD_LOGIC;
    s_axi_control_RREADY : in STD_LOGIC;
    s_axi_control_AWVALID : in STD_LOGIC;
    s_axi_control_WVALID : in STD_LOGIC;
    s_axi_control_BREADY : in STD_LOGIC;
    s_axi_control_WSTRB : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_control_WDATA : in STD_LOGIC_VECTOR ( 3 downto 0 );
    rewind_ap_ready_reg : in STD_LOGIC;
    ap_enable_reg_pp0_iter3 : in STD_LOGIC;
    ap_enable_reg_pp0_iter2 : in STD_LOGIC;
    ap_enable_reg_pp0_iter1 : in STD_LOGIC;
    ap_enable_reg_pp0_iter4 : in STD_LOGIC;
    s_axi_control_ARADDR : in STD_LOGIC_VECTOR ( 3 downto 0 );
    ap_block_pp0_stage0_subdone : in STD_LOGIC;
    ap_loop_exit_ready_pp0_iter4_reg : in STD_LOGIC;
    ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg : in STD_LOGIC;
    s_axi_control_AWADDR : in STD_LOGIC_VECTOR ( 1 downto 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_control_s_axi;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_control_s_axi is
  signal \FSM_onehot_rstate[1]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_rstate[2]_i_1_n_0\ : STD_LOGIC;
  signal \^fsm_onehot_rstate_reg[1]_0\ : STD_LOGIC;
  signal \FSM_onehot_wstate[1]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_wstate[2]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_wstate[3]_i_1_n_0\ : STD_LOGIC;
  signal \^fsm_onehot_wstate_reg[1]_0\ : STD_LOGIC;
  signal \^fsm_onehot_wstate_reg[2]_0\ : STD_LOGIC;
  signal ap_idle : STD_LOGIC;
  signal \^ap_start\ : STD_LOGIC;
  signal ar_hs : STD_LOGIC;
  signal auto_restart_done_i_1_n_0 : STD_LOGIC;
  signal auto_restart_done_reg_n_0 : STD_LOGIC;
  signal auto_restart_status_i_1_n_0 : STD_LOGIC;
  signal auto_restart_status_reg_n_0 : STD_LOGIC;
  signal int_ap_continue0 : STD_LOGIC;
  signal int_ap_ready : STD_LOGIC;
  signal int_ap_ready_i_1_n_0 : STD_LOGIC;
  signal int_ap_ready_i_2_n_0 : STD_LOGIC;
  signal int_ap_start1 : STD_LOGIC;
  signal int_ap_start_i_1_n_0 : STD_LOGIC;
  signal int_auto_restart_i_1_n_0 : STD_LOGIC;
  signal int_gie_i_1_n_0 : STD_LOGIC;
  signal int_gie_i_2_n_0 : STD_LOGIC;
  signal int_gie_reg_n_0 : STD_LOGIC;
  signal int_ier10_out : STD_LOGIC;
  signal \int_ier_reg_n_0_[0]\ : STD_LOGIC;
  signal int_interrupt0 : STD_LOGIC;
  signal int_isr7_out : STD_LOGIC;
  signal \int_isr[0]_i_1_n_0\ : STD_LOGIC;
  signal \int_isr[1]_i_1_n_0\ : STD_LOGIC;
  signal \int_isr_reg_n_0_[0]\ : STD_LOGIC;
  signal \int_isr_reg_n_0_[1]\ : STD_LOGIC;
  signal int_task_ap_done : STD_LOGIC;
  signal int_task_ap_done0 : STD_LOGIC;
  signal \^interrupt\ : STD_LOGIC;
  signal p_0_in : STD_LOGIC_VECTOR ( 7 downto 2 );
  signal \p_0_in__0\ : STD_LOGIC;
  signal rdata : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \rdata[0]_i_2_n_0\ : STD_LOGIC;
  signal \rdata[1]_i_2_n_0\ : STD_LOGIC;
  signal \rdata[9]_i_1_n_0\ : STD_LOGIC;
  signal \^s_axi_control_bvalid\ : STD_LOGIC;
  signal \^s_axi_control_rvalid\ : STD_LOGIC;
  signal waddr : STD_LOGIC;
  signal \waddr_reg_n_0_[2]\ : STD_LOGIC;
  signal \waddr_reg_n_0_[3]\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \FSM_onehot_rstate[1]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \FSM_onehot_rstate[2]_i_1\ : label is "soft_lutpair2";
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_rstate_reg[1]\ : label is "RDIDLE:010,RDDATA:100,iSTATE:001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_rstate_reg[2]\ : label is "RDIDLE:010,RDDATA:100,iSTATE:001";
  attribute SOFT_HLUTNM of \FSM_onehot_wstate[3]_i_1\ : label is "soft_lutpair1";
  attribute FSM_ENCODED_STATES of \FSM_onehot_wstate_reg[1]\ : label is "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_wstate_reg[2]\ : label is "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001";
  attribute FSM_ENCODED_STATES of \FSM_onehot_wstate_reg[3]\ : label is "WRDATA:0100,WRRESP:1000,WRIDLE:0010,iSTATE:0001";
  attribute SOFT_HLUTNM of auto_restart_status_i_1 : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of int_ap_ready_i_2 : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of int_ap_start_i_2 : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of int_auto_restart_i_1 : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of int_gie_i_2 : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \int_isr[0]_i_2\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \rdata[0]_i_1\ : label is "soft_lutpair3";
begin
  \FSM_onehot_rstate_reg[1]_0\ <= \^fsm_onehot_rstate_reg[1]_0\;
  \FSM_onehot_wstate_reg[1]_0\ <= \^fsm_onehot_wstate_reg[1]_0\;
  \FSM_onehot_wstate_reg[2]_0\ <= \^fsm_onehot_wstate_reg[2]_0\;
  ap_start <= \^ap_start\;
  interrupt <= \^interrupt\;
  s_axi_control_BVALID <= \^s_axi_control_bvalid\;
  s_axi_control_RVALID <= \^s_axi_control_rvalid\;
\FSM_onehot_rstate[1]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8BFB"
    )
        port map (
      I0 => s_axi_control_RREADY,
      I1 => \^s_axi_control_rvalid\,
      I2 => \^fsm_onehot_rstate_reg[1]_0\,
      I3 => s_axi_control_ARVALID,
      O => \FSM_onehot_rstate[1]_i_1_n_0\
    );
\FSM_onehot_rstate[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F88"
    )
        port map (
      I0 => \^fsm_onehot_rstate_reg[1]_0\,
      I1 => s_axi_control_ARVALID,
      I2 => s_axi_control_RREADY,
      I3 => \^s_axi_control_rvalid\,
      O => \FSM_onehot_rstate[2]_i_1_n_0\
    );
\FSM_onehot_rstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \FSM_onehot_rstate[1]_i_1_n_0\,
      Q => \^fsm_onehot_rstate_reg[1]_0\,
      R => int_task_ap_done_reg_0
    );
\FSM_onehot_rstate_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \FSM_onehot_rstate[2]_i_1_n_0\,
      Q => \^s_axi_control_rvalid\,
      R => int_task_ap_done_reg_0
    );
\FSM_onehot_wstate[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"AE0CAE3F"
    )
        port map (
      I0 => s_axi_control_BREADY,
      I1 => \^fsm_onehot_wstate_reg[1]_0\,
      I2 => s_axi_control_AWVALID,
      I3 => \^s_axi_control_bvalid\,
      I4 => \^fsm_onehot_wstate_reg[2]_0\,
      O => \FSM_onehot_wstate[1]_i_1_n_0\
    );
\FSM_onehot_wstate[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F88"
    )
        port map (
      I0 => s_axi_control_AWVALID,
      I1 => \^fsm_onehot_wstate_reg[1]_0\,
      I2 => s_axi_control_WVALID,
      I3 => \^fsm_onehot_wstate_reg[2]_0\,
      O => \FSM_onehot_wstate[2]_i_1_n_0\
    );
\FSM_onehot_wstate[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8F88"
    )
        port map (
      I0 => s_axi_control_WVALID,
      I1 => \^fsm_onehot_wstate_reg[2]_0\,
      I2 => s_axi_control_BREADY,
      I3 => \^s_axi_control_bvalid\,
      O => \FSM_onehot_wstate[3]_i_1_n_0\
    );
\FSM_onehot_wstate_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \FSM_onehot_wstate[1]_i_1_n_0\,
      Q => \^fsm_onehot_wstate_reg[1]_0\,
      R => int_task_ap_done_reg_0
    );
\FSM_onehot_wstate_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \FSM_onehot_wstate[2]_i_1_n_0\,
      Q => \^fsm_onehot_wstate_reg[2]_0\,
      R => int_task_ap_done_reg_0
    );
\FSM_onehot_wstate_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \FSM_onehot_wstate[3]_i_1_n_0\,
      Q => \^s_axi_control_bvalid\,
      R => int_task_ap_done_reg_0
    );
ap_done_reg_inv_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFF4"
    )
        port map (
      I0 => ap_loop_exit_ready_pp0_iter4_reg,
      I1 => ap_block_pp0_stage0_subdone,
      I2 => auto_restart_status_reg_n_0,
      I3 => int_task_ap_done_reg_0,
      I4 => p_0_in(4),
      O => ap_loop_exit_ready_pp0_iter4_reg_reg
    );
ap_enable_reg_pp0_iter1_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => \^ap_start\,
      I1 => rewind_ap_ready_reg,
      O => ap_start_int
    );
auto_restart_done_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"75553000"
    )
        port map (
      I0 => p_0_in(4),
      I1 => p_0_in(2),
      I2 => auto_restart_status_reg_n_0,
      I3 => ap_idle,
      I4 => auto_restart_done_reg_n_0,
      O => auto_restart_done_i_1_n_0
    );
auto_restart_done_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => auto_restart_done_i_1_n_0,
      Q => auto_restart_done_reg_n_0,
      R => int_task_ap_done_reg_0
    );
auto_restart_status_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"BA"
    )
        port map (
      I0 => p_0_in(7),
      I1 => ap_idle,
      I2 => auto_restart_status_reg_n_0,
      O => auto_restart_status_i_1_n_0
    );
auto_restart_status_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => auto_restart_status_i_1_n_0,
      Q => auto_restart_status_reg_n_0,
      R => int_task_ap_done_reg_0
    );
int_ap_continue_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000008000000"
    )
        port map (
      I0 => s_axi_control_WDATA(2),
      I1 => s_axi_control_WSTRB(0),
      I2 => \waddr_reg_n_0_[2]\,
      I3 => s_axi_control_WVALID,
      I4 => \^fsm_onehot_wstate_reg[2]_0\,
      I5 => \waddr_reg_n_0_[3]\,
      O => int_ap_continue0
    );
int_ap_continue_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_ap_continue0,
      Q => p_0_in(4),
      R => int_task_ap_done_reg_0
    );
int_ap_idle_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000000000000000D"
    )
        port map (
      I0 => \^ap_start\,
      I1 => rewind_ap_ready_reg,
      I2 => ap_enable_reg_pp0_iter3,
      I3 => ap_enable_reg_pp0_iter2,
      I4 => ap_enable_reg_pp0_iter1,
      I5 => ap_enable_reg_pp0_iter4,
      O => ap_idle
    );
int_ap_idle_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => ap_idle,
      Q => p_0_in(2),
      R => int_task_ap_done_reg_0
    );
int_ap_ready_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FF40FFFF40404040"
    )
        port map (
      I0 => p_0_in(7),
      I1 => ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg,
      I2 => ap_block_pp0_stage0_subdone,
      I3 => int_ap_ready_i_2_n_0,
      I4 => ar_hs,
      I5 => int_ap_ready,
      O => int_ap_ready_i_1_n_0
    );
int_ap_ready_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => s_axi_control_ARADDR(3),
      I1 => s_axi_control_ARADDR(0),
      I2 => s_axi_control_ARADDR(1),
      I3 => s_axi_control_ARADDR(2),
      O => int_ap_ready_i_2_n_0
    );
int_ap_ready_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_ap_ready_i_1_n_0,
      Q => int_ap_ready,
      R => int_task_ap_done_reg_0
    );
int_ap_start_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFBFBFBFFF808080"
    )
        port map (
      I0 => p_0_in(7),
      I1 => ap_block_pp0_stage0_subdone,
      I2 => ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg,
      I3 => int_ap_start1,
      I4 => s_axi_control_WDATA(0),
      I5 => \^ap_start\,
      O => int_ap_start_i_1_n_0
    );
int_ap_start_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00400000"
    )
        port map (
      I0 => \waddr_reg_n_0_[3]\,
      I1 => \^fsm_onehot_wstate_reg[2]_0\,
      I2 => s_axi_control_WVALID,
      I3 => \waddr_reg_n_0_[2]\,
      I4 => s_axi_control_WSTRB(0),
      O => int_ap_start1
    );
int_ap_start_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_ap_start_i_1_n_0,
      Q => \^ap_start\,
      R => int_task_ap_done_reg_0
    );
int_auto_restart_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => s_axi_control_WDATA(3),
      I1 => int_ap_start1,
      I2 => p_0_in(7),
      O => int_auto_restart_i_1_n_0
    );
int_auto_restart_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_auto_restart_i_1_n_0,
      Q => p_0_in(7),
      R => int_task_ap_done_reg_0
    );
int_gie_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFFFFFFF20000000"
    )
        port map (
      I0 => s_axi_control_WDATA(0),
      I1 => \waddr_reg_n_0_[3]\,
      I2 => int_gie_i_2_n_0,
      I3 => \waddr_reg_n_0_[2]\,
      I4 => s_axi_control_WSTRB(0),
      I5 => int_gie_reg_n_0,
      O => int_gie_i_1_n_0
    );
int_gie_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^fsm_onehot_wstate_reg[2]_0\,
      I1 => s_axi_control_WVALID,
      O => int_gie_i_2_n_0
    );
int_gie_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_gie_i_1_n_0,
      Q => int_gie_reg_n_0,
      R => int_task_ap_done_reg_0
    );
\int_ier[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"40000000"
    )
        port map (
      I0 => \waddr_reg_n_0_[2]\,
      I1 => s_axi_control_WSTRB(0),
      I2 => \^fsm_onehot_wstate_reg[2]_0\,
      I3 => s_axi_control_WVALID,
      I4 => \waddr_reg_n_0_[3]\,
      O => int_ier10_out
    );
\int_ier_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => int_ier10_out,
      D => s_axi_control_WDATA(0),
      Q => \int_ier_reg_n_0_[0]\,
      R => int_task_ap_done_reg_0
    );
\int_ier_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => int_ier10_out,
      D => s_axi_control_WDATA(1),
      Q => \p_0_in__0\,
      R => int_task_ap_done_reg_0
    );
int_interrupt_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => int_gie_reg_n_0,
      I1 => \int_isr_reg_n_0_[1]\,
      I2 => \int_isr_reg_n_0_[0]\,
      O => int_interrupt0
    );
int_interrupt_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_interrupt0,
      Q => \^interrupt\,
      R => int_task_ap_done_reg_0
    );
\int_isr[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F7FF7777F8FF8888"
    )
        port map (
      I0 => s_axi_control_WDATA(0),
      I1 => int_isr7_out,
      I2 => ap_loop_exit_ready_pp0_iter4_reg,
      I3 => ap_block_pp0_stage0_subdone,
      I4 => \int_ier_reg_n_0_[0]\,
      I5 => \int_isr_reg_n_0_[0]\,
      O => \int_isr[0]_i_1_n_0\
    );
\int_isr[0]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"80000000"
    )
        port map (
      I0 => \waddr_reg_n_0_[2]\,
      I1 => s_axi_control_WSTRB(0),
      I2 => \^fsm_onehot_wstate_reg[2]_0\,
      I3 => s_axi_control_WVALID,
      I4 => \waddr_reg_n_0_[3]\,
      O => int_isr7_out
    );
\int_isr[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F7777777F8888888"
    )
        port map (
      I0 => s_axi_control_WDATA(1),
      I1 => int_isr7_out,
      I2 => ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg,
      I3 => ap_block_pp0_stage0_subdone,
      I4 => \p_0_in__0\,
      I5 => \int_isr_reg_n_0_[1]\,
      O => \int_isr[1]_i_1_n_0\
    );
\int_isr_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_isr[0]_i_1_n_0\,
      Q => \int_isr_reg_n_0_[0]\,
      R => int_task_ap_done_reg_0
    );
\int_isr_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => \int_isr[1]_i_1_n_0\,
      Q => \int_isr_reg_n_0_[1]\,
      R => int_task_ap_done_reg_0
    );
int_task_ap_done_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000FF51"
    )
        port map (
      I0 => auto_restart_status_reg_n_0,
      I1 => ap_block_pp0_stage0_subdone,
      I2 => ap_loop_exit_ready_pp0_iter4_reg,
      I3 => auto_restart_done_reg_n_0,
      I4 => p_0_in(4),
      O => int_task_ap_done0
    );
int_task_ap_done_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => int_task_ap_done0,
      Q => int_task_ap_done,
      R => int_task_ap_done_reg_0
    );
\rdata[0]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => \rdata[0]_i_2_n_0\,
      I1 => s_axi_control_ARADDR(1),
      I2 => s_axi_control_ARADDR(0),
      O => rdata(0)
    );
\rdata[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AFA0CFCFAFA0C0C0"
    )
        port map (
      I0 => \int_isr_reg_n_0_[0]\,
      I1 => int_gie_reg_n_0,
      I2 => s_axi_control_ARADDR(2),
      I3 => \int_ier_reg_n_0_[0]\,
      I4 => s_axi_control_ARADDR(3),
      I5 => \^ap_start\,
      O => \rdata[0]_i_2_n_0\
    );
\rdata[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000CCE200E2"
    )
        port map (
      I0 => int_task_ap_done,
      I1 => s_axi_control_ARADDR(3),
      I2 => \p_0_in__0\,
      I3 => s_axi_control_ARADDR(2),
      I4 => \int_isr_reg_n_0_[1]\,
      I5 => \rdata[1]_i_2_n_0\,
      O => rdata(1)
    );
\rdata[1]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"E"
    )
        port map (
      I0 => s_axi_control_ARADDR(0),
      I1 => s_axi_control_ARADDR(1),
      O => \rdata[1]_i_2_n_0\
    );
\rdata[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFE000000000000"
    )
        port map (
      I0 => s_axi_control_ARADDR(2),
      I1 => s_axi_control_ARADDR(1),
      I2 => s_axi_control_ARADDR(0),
      I3 => s_axi_control_ARADDR(3),
      I4 => \^fsm_onehot_rstate_reg[1]_0\,
      I5 => s_axi_control_ARVALID,
      O => \rdata[9]_i_1_n_0\
    );
\rdata[9]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => s_axi_control_ARVALID,
      I1 => \^fsm_onehot_rstate_reg[1]_0\,
      O => ar_hs
    );
\rdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ar_hs,
      D => rdata(0),
      Q => s_axi_control_RDATA(0),
      R => '0'
    );
\rdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ar_hs,
      D => rdata(1),
      Q => s_axi_control_RDATA(1),
      R => '0'
    );
\rdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ar_hs,
      D => p_0_in(2),
      Q => s_axi_control_RDATA(2),
      R => \rdata[9]_i_1_n_0\
    );
\rdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ar_hs,
      D => int_ap_ready,
      Q => s_axi_control_RDATA(3),
      R => \rdata[9]_i_1_n_0\
    );
\rdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ar_hs,
      D => p_0_in(4),
      Q => s_axi_control_RDATA(4),
      R => \rdata[9]_i_1_n_0\
    );
\rdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ar_hs,
      D => p_0_in(7),
      Q => s_axi_control_RDATA(5),
      R => \rdata[9]_i_1_n_0\
    );
\rdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ar_hs,
      D => \^interrupt\,
      Q => s_axi_control_RDATA(6),
      R => \rdata[9]_i_1_n_0\
    );
\waddr[3]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^fsm_onehot_wstate_reg[1]_0\,
      I1 => s_axi_control_AWVALID,
      O => waddr
    );
\waddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => waddr,
      D => s_axi_control_AWADDR(0),
      Q => \waddr_reg_n_0_[2]\,
      R => '0'
    );
\waddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => waddr,
      D => s_axi_control_AWADDR(1),
      Q => \waddr_reg_n_0_[3]\,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_flow_control_loop_delay_pipe is
  port (
    rewind_ap_ready_reg : out STD_LOGIC;
    \icmp_ln108_reg_161_reg[0]\ : out STD_LOGIC;
    D : out STD_LOGIC_VECTOR ( 4 downto 0 );
    icmp_ln9_fu_441_p2 : out STD_LOGIC;
    \xor_ln12_reg_586_reg[0]\ : out STD_LOGIC_VECTOR ( 1 downto 0 );
    in2_Addr_B : out STD_LOGIC_VECTOR ( 3 downto 0 );
    in1_Addr_B : out STD_LOGIC_VECTOR ( 1 downto 0 );
    \indvar_flatten3_fu_82_reg[4]\ : out STD_LOGIC;
    icmp_ln10_fu_435_p2 : out STD_LOGIC;
    \indvar_flatten3_fu_82_reg[0]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    add_ln16_fu_313_p2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    \j4_fu_86_reg[0]\ : out STD_LOGIC;
    in1_Addr_A : out STD_LOGIC_VECTOR ( 1 downto 0 );
    rewind_ap_ready_reg_reg_0 : out STD_LOGIC;
    p_1_in : out STD_LOGIC;
    ap_loop_exit_ready : out STD_LOGIC;
    SR : out STD_LOGIC_VECTOR ( 0 to 0 );
    in2_Addr_A : out STD_LOGIC_VECTOR ( 0 to 0 );
    \k5_fu_90_reg[1]\ : out STD_LOGIC;
    \indvar_flatten3_fu_82_reg[2]\ : out STD_LOGIC;
    \i2_fu_78_reg[0]\ : out STD_LOGIC;
    rewind_ap_ready_reg_reg_1 : out STD_LOGIC;
    \indvar_flatten3_fu_82_reg[1]\ : out STD_LOGIC;
    \indvar_flatten3_fu_82_reg[0]_0\ : out STD_LOGIC;
    rewind_ap_ready_reg_reg_2 : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    \icmp_ln108_reg_161_reg[0]_0\ : in STD_LOGIC;
    icmp_ln10_reg_591 : in STD_LOGIC;
    icmp_ln9_reg_596 : in STD_LOGIC;
    ap_enable_reg_pp0_iter1 : in STD_LOGIC;
    ap_block_pp0_stage0_subdone : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 4 downto 0 );
    ap_start : in STD_LOGIC;
    xor_ln12_reg_586 : in STD_LOGIC;
    \k5_fu_90_reg[2]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    \in1_Addr_B[5]\ : in STD_LOGIC_VECTOR ( 1 downto 0 );
    indvar_flatten3_fu_82 : in STD_LOGIC_VECTOR ( 4 downto 0 );
    \in2_Addr_A[4]\ : in STD_LOGIC_VECTOR ( 2 downto 0 );
    ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_flow_control_loop_delay_pipe;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_flow_control_loop_delay_pipe is
  signal ap_loop_init : STD_LOGIC;
  signal ap_loop_init_i_1_n_0 : STD_LOGIC;
  signal \icmp_ln10_reg_591[0]_i_2_n_0\ : STD_LOGIC;
  signal \^icmp_ln9_fu_441_p2\ : STD_LOGIC;
  signal \in1_Addr_A[4]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \in1_Addr_A[5]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \in1_Addr_B[4]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \^in2_addr_b\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \in2_Addr_B[5]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \^j4_fu_86_reg[0]\ : STD_LOGIC;
  signal \^rewind_ap_ready_reg\ : STD_LOGIC;
  signal rewind_ap_ready_reg_i_1_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3_i_1\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2_i_1 : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \in1_Addr_A[4]_INST_0_i_1\ : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \in1_Addr_A[5]_INST_0_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \in1_Addr_B[4]_INST_0_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \in2_Addr_A[5]_INST_0\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \in2_Addr_B[4]_INST_0\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \in2_Addr_B[5]_INST_0_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of in2_EN_B_INST_0 : label is "soft_lutpair12";
  attribute SOFT_HLUTNM of \indvar_flatten131_fu_74[1]_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \indvar_flatten131_fu_74[2]_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of \indvar_flatten3_fu_82[1]_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \indvar_flatten3_fu_82[2]_i_1\ : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \indvar_flatten3_fu_82[4]_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \k5_fu_90[1]_i_1\ : label is "soft_lutpair13";
  attribute SOFT_HLUTNM of \or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3_i_1\ : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of rewind_ap_ready_reg_i_1 : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \sum6_fu_94[31]_i_1\ : label is "soft_lutpair9";
begin
  icmp_ln9_fu_441_p2 <= \^icmp_ln9_fu_441_p2\;
  in2_Addr_B(3 downto 0) <= \^in2_addr_b\(3 downto 0);
  \j4_fu_86_reg[0]\ <= \^j4_fu_86_reg[0]\;
  rewind_ap_ready_reg <= \^rewind_ap_ready_reg\;
\add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A2AA5D555D55A2AA"
    )
        port map (
      I0 => \in1_Addr_B[5]\(0),
      I1 => ap_loop_init,
      I2 => \^rewind_ap_ready_reg\,
      I3 => ap_start,
      I4 => \in1_Addr_A[5]_INST_0_i_1_n_0\,
      I5 => \^j4_fu_86_reg[0]\,
      O => \i2_fu_78_reg[0]\
    );
\add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"9503A903"
    )
        port map (
      I0 => \in1_Addr_B[5]\(1),
      I1 => \^j4_fu_86_reg[0]\,
      I2 => \in1_Addr_A[5]_INST_0_i_1_n_0\,
      I3 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I4 => \in1_Addr_B[5]\(0),
      O => add_ln16_fu_313_p2(0)
    );
ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"20"
    )
        port map (
      I0 => \^icmp_ln9_fu_441_p2\,
      I1 => \^rewind_ap_ready_reg\,
      I2 => ap_start,
      O => ap_loop_exit_ready
    );
ap_loop_init_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFEFFF2000"
    )
        port map (
      I0 => \^icmp_ln9_fu_441_p2\,
      I1 => \^rewind_ap_ready_reg\,
      I2 => ap_start,
      I3 => ap_block_pp0_stage0_subdone,
      I4 => ap_loop_init,
      I5 => rewind_ap_ready_reg_reg_2,
      O => ap_loop_init_i_1_n_0
    );
ap_loop_init_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => ap_loop_init_i_1_n_0,
      Q => ap_loop_init,
      R => '0'
    );
\icmp_ln108_reg_161[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0C00ACAAAAAAAAAA"
    )
        port map (
      I0 => \icmp_ln108_reg_161_reg[0]_0\,
      I1 => icmp_ln10_reg_591,
      I2 => icmp_ln9_reg_596,
      I3 => ap_enable_reg_pp0_iter1,
      I4 => ap_loop_init,
      I5 => ap_block_pp0_stage0_subdone,
      O => \icmp_ln108_reg_161_reg[0]\
    );
\icmp_ln10_reg_591[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"01330000"
    )
        port map (
      I0 => indvar_flatten3_fu_82(4),
      I1 => \icmp_ln10_reg_591[0]_i_2_n_0\,
      I2 => indvar_flatten3_fu_82(3),
      I3 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I4 => \in1_Addr_A[5]_INST_0_i_1_n_0\,
      O => icmp_ln10_fu_435_p2
    );
\icmp_ln10_reg_591[0]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"77F77777FFFFFFFF"
    )
        port map (
      I0 => indvar_flatten3_fu_82(1),
      I1 => indvar_flatten3_fu_82(0),
      I2 => ap_loop_init,
      I3 => \^rewind_ap_ready_reg\,
      I4 => ap_start,
      I5 => indvar_flatten3_fu_82(2),
      O => \icmp_ln10_reg_591[0]_i_2_n_0\
    );
\icmp_ln9_reg_596[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"8000000000000000"
    )
        port map (
      I0 => Q(0),
      I1 => Q(1),
      I2 => Q(2),
      I3 => Q(4),
      I4 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I5 => Q(3),
      O => \^icmp_ln9_fu_441_p2\
    );
\in1_Addr_A[4]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"B0FF4F004F004F00"
    )
        port map (
      I0 => icmp_ln9_reg_596,
      I1 => ap_enable_reg_pp0_iter1,
      I2 => ap_loop_init,
      I3 => icmp_ln10_reg_591,
      I4 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I5 => \in1_Addr_B[5]\(0),
      O => in1_Addr_A(0)
    );
\in1_Addr_A[4]_INST_0_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"DF"
    )
        port map (
      I0 => ap_start,
      I1 => \^rewind_ap_ready_reg\,
      I2 => ap_loop_init,
      O => \in1_Addr_A[4]_INST_0_i_1_n_0\
    );
\in1_Addr_A[5]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BB0BBBBB44044444"
    )
        port map (
      I0 => \in1_Addr_A[5]_INST_0_i_1_n_0\,
      I1 => \in1_Addr_B[5]\(0),
      I2 => ap_start,
      I3 => \^rewind_ap_ready_reg\,
      I4 => ap_loop_init,
      I5 => \in1_Addr_B[5]\(1),
      O => in1_Addr_A(1)
    );
\in1_Addr_A[5]_INST_0_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"DD5D"
    )
        port map (
      I0 => icmp_ln10_reg_591,
      I1 => ap_loop_init,
      I2 => ap_enable_reg_pp0_iter1,
      I3 => icmp_ln9_reg_596,
      O => \in1_Addr_A[5]_INST_0_i_1_n_0\
    );
\in1_Addr_B[4]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0FFF78005A005A00"
    )
        port map (
      I0 => \k5_fu_90_reg[2]\(1),
      I1 => xor_ln12_reg_586,
      I2 => \in1_Addr_B[5]\(0),
      I3 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I4 => icmp_ln10_reg_591,
      I5 => \in1_Addr_B[4]_INST_0_i_1_n_0\,
      O => in1_Addr_B(0)
    );
\in1_Addr_B[4]_INST_0_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"4F"
    )
        port map (
      I0 => icmp_ln9_reg_596,
      I1 => ap_enable_reg_pp0_iter1,
      I2 => ap_loop_init,
      O => \in1_Addr_B[4]_INST_0_i_1_n_0\
    );
\in1_Addr_B[5]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9050A050A0A0A0A0"
    )
        port map (
      I0 => \in1_Addr_B[5]\(1),
      I1 => \in2_Addr_B[5]_INST_0_i_1_n_0\,
      I2 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I3 => \in1_Addr_A[5]_INST_0_i_1_n_0\,
      I4 => \k5_fu_90_reg[2]\(1),
      I5 => \in1_Addr_B[5]\(0),
      O => in1_Addr_B(1)
    );
\in2_Addr_A[4]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"807FFFFFFFFFFFFF"
    )
        port map (
      I0 => \in2_Addr_B[5]_INST_0_i_1_n_0\,
      I1 => \in2_Addr_A[4]\(0),
      I2 => \in2_Addr_A[4]\(1),
      I3 => \in2_Addr_A[4]\(2),
      I4 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I5 => \in1_Addr_A[5]_INST_0_i_1_n_0\,
      O => \^j4_fu_86_reg[0]\
    );
\in2_Addr_A[5]_INST_0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"9"
    )
        port map (
      I0 => \^in2_addr_b\(3),
      I1 => \^j4_fu_86_reg[0]\,
      O => in2_Addr_A(0)
    );
\in2_Addr_B[2]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"66A66666AAAAAAAA"
    )
        port map (
      I0 => \in2_Addr_B[5]_INST_0_i_1_n_0\,
      I1 => \in2_Addr_A[4]\(0),
      I2 => ap_loop_init,
      I3 => \^rewind_ap_ready_reg\,
      I4 => ap_start,
      I5 => \in1_Addr_A[5]_INST_0_i_1_n_0\,
      O => \^in2_addr_b\(0)
    );
\in2_Addr_B[3]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00F0D2F000000000"
    )
        port map (
      I0 => \in2_Addr_A[4]\(0),
      I1 => xor_ln12_reg_586,
      I2 => \in2_Addr_A[4]\(1),
      I3 => \in1_Addr_B[4]_INST_0_i_1_n_0\,
      I4 => icmp_ln10_reg_591,
      I5 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      O => \^in2_addr_b\(1)
    );
\in2_Addr_B[4]_INST_0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^j4_fu_86_reg[0]\,
      O => \^in2_addr_b\(2)
    );
\in2_Addr_B[5]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"5155000000000000"
    )
        port map (
      I0 => \in2_Addr_B[5]_INST_0_i_1_n_0\,
      I1 => ap_start,
      I2 => \^rewind_ap_ready_reg\,
      I3 => ap_loop_init,
      I4 => \in1_Addr_A[5]_INST_0_i_1_n_0\,
      I5 => \k5_fu_90_reg[2]\(0),
      O => \^in2_addr_b\(3)
    );
\in2_Addr_B[5]_INST_0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000005D"
    )
        port map (
      I0 => ap_loop_init,
      I1 => ap_enable_reg_pp0_iter1,
      I2 => icmp_ln9_reg_596,
      I3 => icmp_ln10_reg_591,
      I4 => xor_ln12_reg_586,
      O => \in2_Addr_B[5]_INST_0_i_1_n_0\
    );
in2_EN_B_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => \^rewind_ap_ready_reg\,
      I1 => ap_start,
      I2 => ap_block_pp0_stage0_subdone,
      O => rewind_ap_ready_reg_reg_0
    );
\indvar_flatten131_fu_74[0]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => ap_loop_init,
      I1 => Q(0),
      O => D(0)
    );
\indvar_flatten131_fu_74[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"12"
    )
        port map (
      I0 => Q(1),
      I1 => ap_loop_init,
      I2 => Q(0),
      O => D(1)
    );
\indvar_flatten131_fu_74[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0708"
    )
        port map (
      I0 => Q(1),
      I1 => Q(0),
      I2 => ap_loop_init,
      I3 => Q(2),
      O => D(2)
    );
\indvar_flatten131_fu_74[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7F008000"
    )
        port map (
      I0 => Q(0),
      I1 => Q(1),
      I2 => Q(2),
      I3 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I4 => Q(3),
      O => D(3)
    );
\indvar_flatten131_fu_74[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF000080000000"
    )
        port map (
      I0 => Q(2),
      I1 => Q(1),
      I2 => Q(0),
      I3 => Q(3),
      I4 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I5 => Q(4),
      O => D(4)
    );
\indvar_flatten3_fu_82[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7F77FFFF77777777"
    )
        port map (
      I0 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I1 => indvar_flatten3_fu_82(0),
      I2 => icmp_ln9_reg_596,
      I3 => ap_enable_reg_pp0_iter1,
      I4 => ap_loop_init,
      I5 => icmp_ln10_reg_591,
      O => \indvar_flatten3_fu_82_reg[0]\(0)
    );
\indvar_flatten3_fu_82[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"12"
    )
        port map (
      I0 => indvar_flatten3_fu_82(0),
      I1 => ap_loop_init,
      I2 => indvar_flatten3_fu_82(1),
      O => \indvar_flatten3_fu_82_reg[0]_0\
    );
\indvar_flatten3_fu_82[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0708"
    )
        port map (
      I0 => indvar_flatten3_fu_82(1),
      I1 => indvar_flatten3_fu_82(0),
      I2 => ap_loop_init,
      I3 => indvar_flatten3_fu_82(2),
      O => \indvar_flatten3_fu_82_reg[1]\
    );
\indvar_flatten3_fu_82[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7F008000"
    )
        port map (
      I0 => indvar_flatten3_fu_82(2),
      I1 => indvar_flatten3_fu_82(0),
      I2 => indvar_flatten3_fu_82(1),
      I3 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I4 => indvar_flatten3_fu_82(3),
      O => \indvar_flatten3_fu_82_reg[2]\
    );
\indvar_flatten3_fu_82[4]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"1000"
    )
        port map (
      I0 => \in1_Addr_A[5]_INST_0_i_1_n_0\,
      I1 => \^rewind_ap_ready_reg\,
      I2 => ap_start,
      I3 => ap_block_pp0_stage0_subdone,
      O => rewind_ap_ready_reg_reg_1
    );
\indvar_flatten3_fu_82[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"4888888888888888"
    )
        port map (
      I0 => indvar_flatten3_fu_82(4),
      I1 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I2 => indvar_flatten3_fu_82(3),
      I3 => indvar_flatten3_fu_82(2),
      I4 => indvar_flatten3_fu_82(0),
      I5 => indvar_flatten3_fu_82(1),
      O => \indvar_flatten3_fu_82_reg[4]\
    );
\k5_fu_90[1]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^in2_addr_b\(3),
      O => \xor_ln12_reg_586_reg[0]\(0)
    );
\k5_fu_90[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"000008CC08CC0000"
    )
        port map (
      I0 => xor_ln12_reg_586,
      I1 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I2 => icmp_ln10_reg_591,
      I3 => \in1_Addr_B[4]_INST_0_i_1_n_0\,
      I4 => \k5_fu_90_reg[2]\(1),
      I5 => \k5_fu_90_reg[2]\(0),
      O => \xor_ln12_reg_586_reg[0]\(1)
    );
\or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FEFFEEEE"
    )
        port map (
      I0 => xor_ln12_reg_586,
      I1 => icmp_ln10_reg_591,
      I2 => icmp_ln9_reg_596,
      I3 => ap_enable_reg_pp0_iter1,
      I4 => ap_loop_init,
      O => p_1_in
    );
rewind_ap_ready_reg_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"54F0F0F0"
    )
        port map (
      I0 => ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg,
      I1 => \^icmp_ln9_fu_441_p2\,
      I2 => \^rewind_ap_ready_reg\,
      I3 => ap_start,
      I4 => ap_block_pp0_stage0_subdone,
      O => rewind_ap_ready_reg_i_1_n_0
    );
rewind_ap_ready_reg_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => ap_clk,
      CE => '1',
      D => rewind_ap_ready_reg_i_1_n_0,
      Q => \^rewind_ap_ready_reg\,
      R => rewind_ap_ready_reg_reg_2
    );
\sum6_fu_94[31]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0800"
    )
        port map (
      I0 => ap_block_pp0_stage0_subdone,
      I1 => ap_loop_init,
      I2 => \^rewind_ap_ready_reg\,
      I3 => ap_start,
      O => SR(0)
    );
\xor_ln12_reg_586[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F999FFFFF9F9FFFF"
    )
        port map (
      I0 => \k5_fu_90_reg[2]\(0),
      I1 => \k5_fu_90_reg[2]\(1),
      I2 => \in1_Addr_B[4]_INST_0_i_1_n_0\,
      I3 => icmp_ln10_reg_591,
      I4 => \in1_Addr_A[4]_INST_0_i_1_n_0\,
      I5 => xor_ln12_reg_586,
      O => \k5_fu_90_reg[1]\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_mul_32s_32s_32_2_1 is
  port (
    D : out STD_LOGIC_VECTOR ( 31 downto 0 );
    CEB2 : in STD_LOGIC;
    ap_block_pp0_stage0_subdone : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    in2_Dout_B : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Dout_B : in STD_LOGIC_VECTOR ( 31 downto 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_mul_32s_32s_32_2_1;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_mul_32s_32s_32_2_1 is
  signal \buff0_reg[16]__0_n_0\ : STD_LOGIC;
  signal buff0_reg_n_100 : STD_LOGIC;
  signal buff0_reg_n_101 : STD_LOGIC;
  signal buff0_reg_n_102 : STD_LOGIC;
  signal buff0_reg_n_103 : STD_LOGIC;
  signal buff0_reg_n_104 : STD_LOGIC;
  signal buff0_reg_n_105 : STD_LOGIC;
  signal buff0_reg_n_58 : STD_LOGIC;
  signal buff0_reg_n_59 : STD_LOGIC;
  signal buff0_reg_n_60 : STD_LOGIC;
  signal buff0_reg_n_61 : STD_LOGIC;
  signal buff0_reg_n_62 : STD_LOGIC;
  signal buff0_reg_n_63 : STD_LOGIC;
  signal buff0_reg_n_64 : STD_LOGIC;
  signal buff0_reg_n_65 : STD_LOGIC;
  signal buff0_reg_n_66 : STD_LOGIC;
  signal buff0_reg_n_67 : STD_LOGIC;
  signal buff0_reg_n_68 : STD_LOGIC;
  signal buff0_reg_n_69 : STD_LOGIC;
  signal buff0_reg_n_70 : STD_LOGIC;
  signal buff0_reg_n_71 : STD_LOGIC;
  signal buff0_reg_n_72 : STD_LOGIC;
  signal buff0_reg_n_73 : STD_LOGIC;
  signal buff0_reg_n_74 : STD_LOGIC;
  signal buff0_reg_n_75 : STD_LOGIC;
  signal buff0_reg_n_76 : STD_LOGIC;
  signal buff0_reg_n_77 : STD_LOGIC;
  signal buff0_reg_n_78 : STD_LOGIC;
  signal buff0_reg_n_79 : STD_LOGIC;
  signal buff0_reg_n_80 : STD_LOGIC;
  signal buff0_reg_n_81 : STD_LOGIC;
  signal buff0_reg_n_82 : STD_LOGIC;
  signal buff0_reg_n_83 : STD_LOGIC;
  signal buff0_reg_n_84 : STD_LOGIC;
  signal buff0_reg_n_85 : STD_LOGIC;
  signal buff0_reg_n_86 : STD_LOGIC;
  signal buff0_reg_n_87 : STD_LOGIC;
  signal buff0_reg_n_88 : STD_LOGIC;
  signal buff0_reg_n_89 : STD_LOGIC;
  signal buff0_reg_n_90 : STD_LOGIC;
  signal buff0_reg_n_91 : STD_LOGIC;
  signal buff0_reg_n_92 : STD_LOGIC;
  signal buff0_reg_n_93 : STD_LOGIC;
  signal buff0_reg_n_94 : STD_LOGIC;
  signal buff0_reg_n_95 : STD_LOGIC;
  signal buff0_reg_n_96 : STD_LOGIC;
  signal buff0_reg_n_97 : STD_LOGIC;
  signal buff0_reg_n_98 : STD_LOGIC;
  signal buff0_reg_n_99 : STD_LOGIC;
  signal \mul_ln14_reg_620[23]_i_2_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[23]_i_3_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[23]_i_4_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[23]_i_5_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[23]_i_6_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[23]_i_7_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[23]_i_8_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[31]_i_2_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[31]_i_3_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[31]_i_4_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[31]_i_5_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[31]_i_6_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[31]_i_7_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[31]_i_8_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620[31]_i_9_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[23]_i_1_n_0\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[23]_i_1_n_1\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[23]_i_1_n_2\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[23]_i_1_n_3\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[23]_i_1_n_4\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[23]_i_1_n_5\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[23]_i_1_n_6\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[23]_i_1_n_7\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[31]_i_1_n_1\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[31]_i_1_n_2\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[31]_i_1_n_3\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[31]_i_1_n_4\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[31]_i_1_n_5\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[31]_i_1_n_6\ : STD_LOGIC;
  signal \mul_ln14_reg_620_reg[31]_i_1_n_7\ : STD_LOGIC;
  signal \tmp_product__0_n_100\ : STD_LOGIC;
  signal \tmp_product__0_n_101\ : STD_LOGIC;
  signal \tmp_product__0_n_102\ : STD_LOGIC;
  signal \tmp_product__0_n_103\ : STD_LOGIC;
  signal \tmp_product__0_n_104\ : STD_LOGIC;
  signal \tmp_product__0_n_105\ : STD_LOGIC;
  signal \tmp_product__0_n_106\ : STD_LOGIC;
  signal \tmp_product__0_n_107\ : STD_LOGIC;
  signal \tmp_product__0_n_108\ : STD_LOGIC;
  signal \tmp_product__0_n_109\ : STD_LOGIC;
  signal \tmp_product__0_n_110\ : STD_LOGIC;
  signal \tmp_product__0_n_111\ : STD_LOGIC;
  signal \tmp_product__0_n_112\ : STD_LOGIC;
  signal \tmp_product__0_n_113\ : STD_LOGIC;
  signal \tmp_product__0_n_114\ : STD_LOGIC;
  signal \tmp_product__0_n_115\ : STD_LOGIC;
  signal \tmp_product__0_n_116\ : STD_LOGIC;
  signal \tmp_product__0_n_117\ : STD_LOGIC;
  signal \tmp_product__0_n_118\ : STD_LOGIC;
  signal \tmp_product__0_n_119\ : STD_LOGIC;
  signal \tmp_product__0_n_120\ : STD_LOGIC;
  signal \tmp_product__0_n_121\ : STD_LOGIC;
  signal \tmp_product__0_n_122\ : STD_LOGIC;
  signal \tmp_product__0_n_123\ : STD_LOGIC;
  signal \tmp_product__0_n_124\ : STD_LOGIC;
  signal \tmp_product__0_n_125\ : STD_LOGIC;
  signal \tmp_product__0_n_126\ : STD_LOGIC;
  signal \tmp_product__0_n_127\ : STD_LOGIC;
  signal \tmp_product__0_n_128\ : STD_LOGIC;
  signal \tmp_product__0_n_129\ : STD_LOGIC;
  signal \tmp_product__0_n_130\ : STD_LOGIC;
  signal \tmp_product__0_n_131\ : STD_LOGIC;
  signal \tmp_product__0_n_132\ : STD_LOGIC;
  signal \tmp_product__0_n_133\ : STD_LOGIC;
  signal \tmp_product__0_n_134\ : STD_LOGIC;
  signal \tmp_product__0_n_135\ : STD_LOGIC;
  signal \tmp_product__0_n_136\ : STD_LOGIC;
  signal \tmp_product__0_n_137\ : STD_LOGIC;
  signal \tmp_product__0_n_138\ : STD_LOGIC;
  signal \tmp_product__0_n_139\ : STD_LOGIC;
  signal \tmp_product__0_n_140\ : STD_LOGIC;
  signal \tmp_product__0_n_141\ : STD_LOGIC;
  signal \tmp_product__0_n_142\ : STD_LOGIC;
  signal \tmp_product__0_n_143\ : STD_LOGIC;
  signal \tmp_product__0_n_144\ : STD_LOGIC;
  signal \tmp_product__0_n_145\ : STD_LOGIC;
  signal \tmp_product__0_n_146\ : STD_LOGIC;
  signal \tmp_product__0_n_147\ : STD_LOGIC;
  signal \tmp_product__0_n_148\ : STD_LOGIC;
  signal \tmp_product__0_n_149\ : STD_LOGIC;
  signal \tmp_product__0_n_150\ : STD_LOGIC;
  signal \tmp_product__0_n_151\ : STD_LOGIC;
  signal \tmp_product__0_n_152\ : STD_LOGIC;
  signal \tmp_product__0_n_153\ : STD_LOGIC;
  signal \tmp_product__0_n_24\ : STD_LOGIC;
  signal \tmp_product__0_n_25\ : STD_LOGIC;
  signal \tmp_product__0_n_26\ : STD_LOGIC;
  signal \tmp_product__0_n_27\ : STD_LOGIC;
  signal \tmp_product__0_n_28\ : STD_LOGIC;
  signal \tmp_product__0_n_29\ : STD_LOGIC;
  signal \tmp_product__0_n_30\ : STD_LOGIC;
  signal \tmp_product__0_n_31\ : STD_LOGIC;
  signal \tmp_product__0_n_32\ : STD_LOGIC;
  signal \tmp_product__0_n_33\ : STD_LOGIC;
  signal \tmp_product__0_n_34\ : STD_LOGIC;
  signal \tmp_product__0_n_35\ : STD_LOGIC;
  signal \tmp_product__0_n_36\ : STD_LOGIC;
  signal \tmp_product__0_n_37\ : STD_LOGIC;
  signal \tmp_product__0_n_38\ : STD_LOGIC;
  signal \tmp_product__0_n_39\ : STD_LOGIC;
  signal \tmp_product__0_n_40\ : STD_LOGIC;
  signal \tmp_product__0_n_41\ : STD_LOGIC;
  signal \tmp_product__0_n_42\ : STD_LOGIC;
  signal \tmp_product__0_n_43\ : STD_LOGIC;
  signal \tmp_product__0_n_44\ : STD_LOGIC;
  signal \tmp_product__0_n_45\ : STD_LOGIC;
  signal \tmp_product__0_n_46\ : STD_LOGIC;
  signal \tmp_product__0_n_47\ : STD_LOGIC;
  signal \tmp_product__0_n_48\ : STD_LOGIC;
  signal \tmp_product__0_n_49\ : STD_LOGIC;
  signal \tmp_product__0_n_50\ : STD_LOGIC;
  signal \tmp_product__0_n_51\ : STD_LOGIC;
  signal \tmp_product__0_n_52\ : STD_LOGIC;
  signal \tmp_product__0_n_53\ : STD_LOGIC;
  signal \tmp_product__0_n_58\ : STD_LOGIC;
  signal \tmp_product__0_n_59\ : STD_LOGIC;
  signal \tmp_product__0_n_60\ : STD_LOGIC;
  signal \tmp_product__0_n_61\ : STD_LOGIC;
  signal \tmp_product__0_n_62\ : STD_LOGIC;
  signal \tmp_product__0_n_63\ : STD_LOGIC;
  signal \tmp_product__0_n_64\ : STD_LOGIC;
  signal \tmp_product__0_n_65\ : STD_LOGIC;
  signal \tmp_product__0_n_66\ : STD_LOGIC;
  signal \tmp_product__0_n_67\ : STD_LOGIC;
  signal \tmp_product__0_n_68\ : STD_LOGIC;
  signal \tmp_product__0_n_69\ : STD_LOGIC;
  signal \tmp_product__0_n_70\ : STD_LOGIC;
  signal \tmp_product__0_n_71\ : STD_LOGIC;
  signal \tmp_product__0_n_72\ : STD_LOGIC;
  signal \tmp_product__0_n_73\ : STD_LOGIC;
  signal \tmp_product__0_n_74\ : STD_LOGIC;
  signal \tmp_product__0_n_75\ : STD_LOGIC;
  signal \tmp_product__0_n_76\ : STD_LOGIC;
  signal \tmp_product__0_n_77\ : STD_LOGIC;
  signal \tmp_product__0_n_78\ : STD_LOGIC;
  signal \tmp_product__0_n_79\ : STD_LOGIC;
  signal \tmp_product__0_n_80\ : STD_LOGIC;
  signal \tmp_product__0_n_81\ : STD_LOGIC;
  signal \tmp_product__0_n_82\ : STD_LOGIC;
  signal \tmp_product__0_n_83\ : STD_LOGIC;
  signal \tmp_product__0_n_84\ : STD_LOGIC;
  signal \tmp_product__0_n_85\ : STD_LOGIC;
  signal \tmp_product__0_n_86\ : STD_LOGIC;
  signal \tmp_product__0_n_87\ : STD_LOGIC;
  signal \tmp_product__0_n_88\ : STD_LOGIC;
  signal \tmp_product__0_n_89\ : STD_LOGIC;
  signal \tmp_product__0_n_90\ : STD_LOGIC;
  signal \tmp_product__0_n_91\ : STD_LOGIC;
  signal \tmp_product__0_n_92\ : STD_LOGIC;
  signal \tmp_product__0_n_93\ : STD_LOGIC;
  signal \tmp_product__0_n_94\ : STD_LOGIC;
  signal \tmp_product__0_n_95\ : STD_LOGIC;
  signal \tmp_product__0_n_96\ : STD_LOGIC;
  signal \tmp_product__0_n_97\ : STD_LOGIC;
  signal \tmp_product__0_n_98\ : STD_LOGIC;
  signal \tmp_product__0_n_99\ : STD_LOGIC;
  signal tmp_product_n_100 : STD_LOGIC;
  signal tmp_product_n_101 : STD_LOGIC;
  signal tmp_product_n_102 : STD_LOGIC;
  signal tmp_product_n_103 : STD_LOGIC;
  signal tmp_product_n_104 : STD_LOGIC;
  signal tmp_product_n_105 : STD_LOGIC;
  signal tmp_product_n_106 : STD_LOGIC;
  signal tmp_product_n_107 : STD_LOGIC;
  signal tmp_product_n_108 : STD_LOGIC;
  signal tmp_product_n_109 : STD_LOGIC;
  signal tmp_product_n_110 : STD_LOGIC;
  signal tmp_product_n_111 : STD_LOGIC;
  signal tmp_product_n_112 : STD_LOGIC;
  signal tmp_product_n_113 : STD_LOGIC;
  signal tmp_product_n_114 : STD_LOGIC;
  signal tmp_product_n_115 : STD_LOGIC;
  signal tmp_product_n_116 : STD_LOGIC;
  signal tmp_product_n_117 : STD_LOGIC;
  signal tmp_product_n_118 : STD_LOGIC;
  signal tmp_product_n_119 : STD_LOGIC;
  signal tmp_product_n_120 : STD_LOGIC;
  signal tmp_product_n_121 : STD_LOGIC;
  signal tmp_product_n_122 : STD_LOGIC;
  signal tmp_product_n_123 : STD_LOGIC;
  signal tmp_product_n_124 : STD_LOGIC;
  signal tmp_product_n_125 : STD_LOGIC;
  signal tmp_product_n_126 : STD_LOGIC;
  signal tmp_product_n_127 : STD_LOGIC;
  signal tmp_product_n_128 : STD_LOGIC;
  signal tmp_product_n_129 : STD_LOGIC;
  signal tmp_product_n_130 : STD_LOGIC;
  signal tmp_product_n_131 : STD_LOGIC;
  signal tmp_product_n_132 : STD_LOGIC;
  signal tmp_product_n_133 : STD_LOGIC;
  signal tmp_product_n_134 : STD_LOGIC;
  signal tmp_product_n_135 : STD_LOGIC;
  signal tmp_product_n_136 : STD_LOGIC;
  signal tmp_product_n_137 : STD_LOGIC;
  signal tmp_product_n_138 : STD_LOGIC;
  signal tmp_product_n_139 : STD_LOGIC;
  signal tmp_product_n_140 : STD_LOGIC;
  signal tmp_product_n_141 : STD_LOGIC;
  signal tmp_product_n_142 : STD_LOGIC;
  signal tmp_product_n_143 : STD_LOGIC;
  signal tmp_product_n_144 : STD_LOGIC;
  signal tmp_product_n_145 : STD_LOGIC;
  signal tmp_product_n_146 : STD_LOGIC;
  signal tmp_product_n_147 : STD_LOGIC;
  signal tmp_product_n_148 : STD_LOGIC;
  signal tmp_product_n_149 : STD_LOGIC;
  signal tmp_product_n_150 : STD_LOGIC;
  signal tmp_product_n_151 : STD_LOGIC;
  signal tmp_product_n_152 : STD_LOGIC;
  signal tmp_product_n_153 : STD_LOGIC;
  signal tmp_product_n_58 : STD_LOGIC;
  signal tmp_product_n_59 : STD_LOGIC;
  signal tmp_product_n_60 : STD_LOGIC;
  signal tmp_product_n_61 : STD_LOGIC;
  signal tmp_product_n_62 : STD_LOGIC;
  signal tmp_product_n_63 : STD_LOGIC;
  signal tmp_product_n_64 : STD_LOGIC;
  signal tmp_product_n_65 : STD_LOGIC;
  signal tmp_product_n_66 : STD_LOGIC;
  signal tmp_product_n_67 : STD_LOGIC;
  signal tmp_product_n_68 : STD_LOGIC;
  signal tmp_product_n_69 : STD_LOGIC;
  signal tmp_product_n_70 : STD_LOGIC;
  signal tmp_product_n_71 : STD_LOGIC;
  signal tmp_product_n_72 : STD_LOGIC;
  signal tmp_product_n_73 : STD_LOGIC;
  signal tmp_product_n_74 : STD_LOGIC;
  signal tmp_product_n_75 : STD_LOGIC;
  signal tmp_product_n_76 : STD_LOGIC;
  signal tmp_product_n_77 : STD_LOGIC;
  signal tmp_product_n_78 : STD_LOGIC;
  signal tmp_product_n_79 : STD_LOGIC;
  signal tmp_product_n_80 : STD_LOGIC;
  signal tmp_product_n_81 : STD_LOGIC;
  signal tmp_product_n_82 : STD_LOGIC;
  signal tmp_product_n_83 : STD_LOGIC;
  signal tmp_product_n_84 : STD_LOGIC;
  signal tmp_product_n_85 : STD_LOGIC;
  signal tmp_product_n_86 : STD_LOGIC;
  signal tmp_product_n_87 : STD_LOGIC;
  signal tmp_product_n_88 : STD_LOGIC;
  signal tmp_product_n_89 : STD_LOGIC;
  signal tmp_product_n_90 : STD_LOGIC;
  signal tmp_product_n_91 : STD_LOGIC;
  signal tmp_product_n_92 : STD_LOGIC;
  signal tmp_product_n_93 : STD_LOGIC;
  signal tmp_product_n_94 : STD_LOGIC;
  signal tmp_product_n_95 : STD_LOGIC;
  signal tmp_product_n_96 : STD_LOGIC;
  signal tmp_product_n_97 : STD_LOGIC;
  signal tmp_product_n_98 : STD_LOGIC;
  signal tmp_product_n_99 : STD_LOGIC;
  signal NLW_buff0_reg_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_buff0_reg_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_buff0_reg_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_buff0_reg_PCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal NLW_buff0_reg_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_mul_ln14_reg_620_reg[31]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_tmp_product_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_tmp_product_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_tmp_product_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_tmp_product_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_tmp_product__0_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_tmp_product__0_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_tmp_product__0_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of buff0_reg : label is "yes";
  attribute METHODOLOGY_DRC_VIOS : string;
  attribute METHODOLOGY_DRC_VIOS of buff0_reg : label is "{SYNTH-10 {cell *THIS*} {string 18x15 4}}";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \mul_ln14_reg_620_reg[23]_i_1\ : label is 35;
  attribute ADDER_THRESHOLD of \mul_ln14_reg_620_reg[31]_i_1\ : label is 35;
  attribute KEEP_HIERARCHY of tmp_product : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of tmp_product : label is "{SYNTH-10 {cell *THIS*} {string 15x18 4}}";
  attribute KEEP_HIERARCHY of \tmp_product__0\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \tmp_product__0\ : label is "{SYNTH-10 {cell *THIS*} {string 18x18 4}}";
begin
buff0_reg: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "CASCADE",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
      B_INPUT => "DIRECT",
      CARRYINREG => 0,
      CARRYINSELREG => 0,
      CREG => 1,
      DREG => 1,
      INMODEREG => 0,
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 0,
      PATTERN => X"000000000000",
      PREADDINSEL => "A",
      PREG => 1,
      RND => X"000000000000",
      SEL_MASK => "MASK",
      SEL_PATTERN => "PATTERN",
      USE_MULT => "MULTIPLY",
      USE_PATTERN_DETECT => "NO_PATDET",
      USE_SIMD => "ONE48",
      USE_WIDEXOR => "FALSE",
      XORSIMD => "XOR24_48_96"
    )
        port map (
      A(29 downto 0) => B"000000000000000000000000000000",
      ACIN(29) => \tmp_product__0_n_24\,
      ACIN(28) => \tmp_product__0_n_25\,
      ACIN(27) => \tmp_product__0_n_26\,
      ACIN(26) => \tmp_product__0_n_27\,
      ACIN(25) => \tmp_product__0_n_28\,
      ACIN(24) => \tmp_product__0_n_29\,
      ACIN(23) => \tmp_product__0_n_30\,
      ACIN(22) => \tmp_product__0_n_31\,
      ACIN(21) => \tmp_product__0_n_32\,
      ACIN(20) => \tmp_product__0_n_33\,
      ACIN(19) => \tmp_product__0_n_34\,
      ACIN(18) => \tmp_product__0_n_35\,
      ACIN(17) => \tmp_product__0_n_36\,
      ACIN(16) => \tmp_product__0_n_37\,
      ACIN(15) => \tmp_product__0_n_38\,
      ACIN(14) => \tmp_product__0_n_39\,
      ACIN(13) => \tmp_product__0_n_40\,
      ACIN(12) => \tmp_product__0_n_41\,
      ACIN(11) => \tmp_product__0_n_42\,
      ACIN(10) => \tmp_product__0_n_43\,
      ACIN(9) => \tmp_product__0_n_44\,
      ACIN(8) => \tmp_product__0_n_45\,
      ACIN(7) => \tmp_product__0_n_46\,
      ACIN(6) => \tmp_product__0_n_47\,
      ACIN(5) => \tmp_product__0_n_48\,
      ACIN(4) => \tmp_product__0_n_49\,
      ACIN(3) => \tmp_product__0_n_50\,
      ACIN(2) => \tmp_product__0_n_51\,
      ACIN(1) => \tmp_product__0_n_52\,
      ACIN(0) => \tmp_product__0_n_53\,
      ACOUT(29 downto 0) => NLW_buff0_reg_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => in1_Dout_B(31),
      B(16) => in1_Dout_B(31),
      B(15) => in1_Dout_B(31),
      B(14 downto 0) => in1_Dout_B(31 downto 17),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_buff0_reg_BCOUT_UNCONNECTED(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_buff0_reg_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_buff0_reg_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => CEB2,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => ap_block_pp0_stage0_subdone,
      CLK => ap_clk,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_buff0_reg_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 0) => B"001010101",
      OVERFLOW => NLW_buff0_reg_OVERFLOW_UNCONNECTED,
      P(47) => buff0_reg_n_58,
      P(46) => buff0_reg_n_59,
      P(45) => buff0_reg_n_60,
      P(44) => buff0_reg_n_61,
      P(43) => buff0_reg_n_62,
      P(42) => buff0_reg_n_63,
      P(41) => buff0_reg_n_64,
      P(40) => buff0_reg_n_65,
      P(39) => buff0_reg_n_66,
      P(38) => buff0_reg_n_67,
      P(37) => buff0_reg_n_68,
      P(36) => buff0_reg_n_69,
      P(35) => buff0_reg_n_70,
      P(34) => buff0_reg_n_71,
      P(33) => buff0_reg_n_72,
      P(32) => buff0_reg_n_73,
      P(31) => buff0_reg_n_74,
      P(30) => buff0_reg_n_75,
      P(29) => buff0_reg_n_76,
      P(28) => buff0_reg_n_77,
      P(27) => buff0_reg_n_78,
      P(26) => buff0_reg_n_79,
      P(25) => buff0_reg_n_80,
      P(24) => buff0_reg_n_81,
      P(23) => buff0_reg_n_82,
      P(22) => buff0_reg_n_83,
      P(21) => buff0_reg_n_84,
      P(20) => buff0_reg_n_85,
      P(19) => buff0_reg_n_86,
      P(18) => buff0_reg_n_87,
      P(17) => buff0_reg_n_88,
      P(16) => buff0_reg_n_89,
      P(15) => buff0_reg_n_90,
      P(14) => buff0_reg_n_91,
      P(13) => buff0_reg_n_92,
      P(12) => buff0_reg_n_93,
      P(11) => buff0_reg_n_94,
      P(10) => buff0_reg_n_95,
      P(9) => buff0_reg_n_96,
      P(8) => buff0_reg_n_97,
      P(7) => buff0_reg_n_98,
      P(6) => buff0_reg_n_99,
      P(5) => buff0_reg_n_100,
      P(4) => buff0_reg_n_101,
      P(3) => buff0_reg_n_102,
      P(2) => buff0_reg_n_103,
      P(1) => buff0_reg_n_104,
      P(0) => buff0_reg_n_105,
      PATTERNBDETECT => NLW_buff0_reg_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_buff0_reg_PATTERNDETECT_UNCONNECTED,
      PCIN(47) => \tmp_product__0_n_106\,
      PCIN(46) => \tmp_product__0_n_107\,
      PCIN(45) => \tmp_product__0_n_108\,
      PCIN(44) => \tmp_product__0_n_109\,
      PCIN(43) => \tmp_product__0_n_110\,
      PCIN(42) => \tmp_product__0_n_111\,
      PCIN(41) => \tmp_product__0_n_112\,
      PCIN(40) => \tmp_product__0_n_113\,
      PCIN(39) => \tmp_product__0_n_114\,
      PCIN(38) => \tmp_product__0_n_115\,
      PCIN(37) => \tmp_product__0_n_116\,
      PCIN(36) => \tmp_product__0_n_117\,
      PCIN(35) => \tmp_product__0_n_118\,
      PCIN(34) => \tmp_product__0_n_119\,
      PCIN(33) => \tmp_product__0_n_120\,
      PCIN(32) => \tmp_product__0_n_121\,
      PCIN(31) => \tmp_product__0_n_122\,
      PCIN(30) => \tmp_product__0_n_123\,
      PCIN(29) => \tmp_product__0_n_124\,
      PCIN(28) => \tmp_product__0_n_125\,
      PCIN(27) => \tmp_product__0_n_126\,
      PCIN(26) => \tmp_product__0_n_127\,
      PCIN(25) => \tmp_product__0_n_128\,
      PCIN(24) => \tmp_product__0_n_129\,
      PCIN(23) => \tmp_product__0_n_130\,
      PCIN(22) => \tmp_product__0_n_131\,
      PCIN(21) => \tmp_product__0_n_132\,
      PCIN(20) => \tmp_product__0_n_133\,
      PCIN(19) => \tmp_product__0_n_134\,
      PCIN(18) => \tmp_product__0_n_135\,
      PCIN(17) => \tmp_product__0_n_136\,
      PCIN(16) => \tmp_product__0_n_137\,
      PCIN(15) => \tmp_product__0_n_138\,
      PCIN(14) => \tmp_product__0_n_139\,
      PCIN(13) => \tmp_product__0_n_140\,
      PCIN(12) => \tmp_product__0_n_141\,
      PCIN(11) => \tmp_product__0_n_142\,
      PCIN(10) => \tmp_product__0_n_143\,
      PCIN(9) => \tmp_product__0_n_144\,
      PCIN(8) => \tmp_product__0_n_145\,
      PCIN(7) => \tmp_product__0_n_146\,
      PCIN(6) => \tmp_product__0_n_147\,
      PCIN(5) => \tmp_product__0_n_148\,
      PCIN(4) => \tmp_product__0_n_149\,
      PCIN(3) => \tmp_product__0_n_150\,
      PCIN(2) => \tmp_product__0_n_151\,
      PCIN(1) => \tmp_product__0_n_152\,
      PCIN(0) => \tmp_product__0_n_153\,
      PCOUT(47 downto 0) => NLW_buff0_reg_PCOUT_UNCONNECTED(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => '0',
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => NLW_buff0_reg_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_buff0_reg_XOROUT_UNCONNECTED(7 downto 0)
    );
\buff0_reg[0]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_105\,
      Q => D(0),
      R => '0'
    );
\buff0_reg[10]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_95\,
      Q => D(10),
      R => '0'
    );
\buff0_reg[11]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_94\,
      Q => D(11),
      R => '0'
    );
\buff0_reg[12]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_93\,
      Q => D(12),
      R => '0'
    );
\buff0_reg[13]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_92\,
      Q => D(13),
      R => '0'
    );
\buff0_reg[14]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_91\,
      Q => D(14),
      R => '0'
    );
\buff0_reg[15]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_90\,
      Q => D(15),
      R => '0'
    );
\buff0_reg[16]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_89\,
      Q => \buff0_reg[16]__0_n_0\,
      R => '0'
    );
\buff0_reg[1]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_104\,
      Q => D(1),
      R => '0'
    );
\buff0_reg[2]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_103\,
      Q => D(2),
      R => '0'
    );
\buff0_reg[3]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_102\,
      Q => D(3),
      R => '0'
    );
\buff0_reg[4]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_101\,
      Q => D(4),
      R => '0'
    );
\buff0_reg[5]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_100\,
      Q => D(5),
      R => '0'
    );
\buff0_reg[6]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_99\,
      Q => D(6),
      R => '0'
    );
\buff0_reg[7]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_98\,
      Q => D(7),
      R => '0'
    );
\buff0_reg[8]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_97\,
      Q => D(8),
      R => '0'
    );
\buff0_reg[9]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_96\,
      Q => D(9),
      R => '0'
    );
\mul_ln14_reg_620[23]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_99,
      I1 => tmp_product_n_99,
      O => \mul_ln14_reg_620[23]_i_2_n_0\
    );
\mul_ln14_reg_620[23]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_100,
      I1 => tmp_product_n_100,
      O => \mul_ln14_reg_620[23]_i_3_n_0\
    );
\mul_ln14_reg_620[23]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_101,
      I1 => tmp_product_n_101,
      O => \mul_ln14_reg_620[23]_i_4_n_0\
    );
\mul_ln14_reg_620[23]_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_102,
      I1 => tmp_product_n_102,
      O => \mul_ln14_reg_620[23]_i_5_n_0\
    );
\mul_ln14_reg_620[23]_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_103,
      I1 => tmp_product_n_103,
      O => \mul_ln14_reg_620[23]_i_6_n_0\
    );
\mul_ln14_reg_620[23]_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_104,
      I1 => tmp_product_n_104,
      O => \mul_ln14_reg_620[23]_i_7_n_0\
    );
\mul_ln14_reg_620[23]_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_105,
      I1 => tmp_product_n_105,
      O => \mul_ln14_reg_620[23]_i_8_n_0\
    );
\mul_ln14_reg_620[31]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_91,
      I1 => tmp_product_n_91,
      O => \mul_ln14_reg_620[31]_i_2_n_0\
    );
\mul_ln14_reg_620[31]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_92,
      I1 => tmp_product_n_92,
      O => \mul_ln14_reg_620[31]_i_3_n_0\
    );
\mul_ln14_reg_620[31]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_93,
      I1 => tmp_product_n_93,
      O => \mul_ln14_reg_620[31]_i_4_n_0\
    );
\mul_ln14_reg_620[31]_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_94,
      I1 => tmp_product_n_94,
      O => \mul_ln14_reg_620[31]_i_5_n_0\
    );
\mul_ln14_reg_620[31]_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_95,
      I1 => tmp_product_n_95,
      O => \mul_ln14_reg_620[31]_i_6_n_0\
    );
\mul_ln14_reg_620[31]_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_96,
      I1 => tmp_product_n_96,
      O => \mul_ln14_reg_620[31]_i_7_n_0\
    );
\mul_ln14_reg_620[31]_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_97,
      I1 => tmp_product_n_97,
      O => \mul_ln14_reg_620[31]_i_8_n_0\
    );
\mul_ln14_reg_620[31]_i_9\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_98,
      I1 => tmp_product_n_98,
      O => \mul_ln14_reg_620[31]_i_9_n_0\
    );
\mul_ln14_reg_620_reg[23]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \mul_ln14_reg_620_reg[23]_i_1_n_0\,
      CO(6) => \mul_ln14_reg_620_reg[23]_i_1_n_1\,
      CO(5) => \mul_ln14_reg_620_reg[23]_i_1_n_2\,
      CO(4) => \mul_ln14_reg_620_reg[23]_i_1_n_3\,
      CO(3) => \mul_ln14_reg_620_reg[23]_i_1_n_4\,
      CO(2) => \mul_ln14_reg_620_reg[23]_i_1_n_5\,
      CO(1) => \mul_ln14_reg_620_reg[23]_i_1_n_6\,
      CO(0) => \mul_ln14_reg_620_reg[23]_i_1_n_7\,
      DI(7) => buff0_reg_n_99,
      DI(6) => buff0_reg_n_100,
      DI(5) => buff0_reg_n_101,
      DI(4) => buff0_reg_n_102,
      DI(3) => buff0_reg_n_103,
      DI(2) => buff0_reg_n_104,
      DI(1) => buff0_reg_n_105,
      DI(0) => '0',
      O(7 downto 0) => D(23 downto 16),
      S(7) => \mul_ln14_reg_620[23]_i_2_n_0\,
      S(6) => \mul_ln14_reg_620[23]_i_3_n_0\,
      S(5) => \mul_ln14_reg_620[23]_i_4_n_0\,
      S(4) => \mul_ln14_reg_620[23]_i_5_n_0\,
      S(3) => \mul_ln14_reg_620[23]_i_6_n_0\,
      S(2) => \mul_ln14_reg_620[23]_i_7_n_0\,
      S(1) => \mul_ln14_reg_620[23]_i_8_n_0\,
      S(0) => \buff0_reg[16]__0_n_0\
    );
\mul_ln14_reg_620_reg[31]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \mul_ln14_reg_620_reg[23]_i_1_n_0\,
      CI_TOP => '0',
      CO(7) => \NLW_mul_ln14_reg_620_reg[31]_i_1_CO_UNCONNECTED\(7),
      CO(6) => \mul_ln14_reg_620_reg[31]_i_1_n_1\,
      CO(5) => \mul_ln14_reg_620_reg[31]_i_1_n_2\,
      CO(4) => \mul_ln14_reg_620_reg[31]_i_1_n_3\,
      CO(3) => \mul_ln14_reg_620_reg[31]_i_1_n_4\,
      CO(2) => \mul_ln14_reg_620_reg[31]_i_1_n_5\,
      CO(1) => \mul_ln14_reg_620_reg[31]_i_1_n_6\,
      CO(0) => \mul_ln14_reg_620_reg[31]_i_1_n_7\,
      DI(7) => '0',
      DI(6) => buff0_reg_n_92,
      DI(5) => buff0_reg_n_93,
      DI(4) => buff0_reg_n_94,
      DI(3) => buff0_reg_n_95,
      DI(2) => buff0_reg_n_96,
      DI(1) => buff0_reg_n_97,
      DI(0) => buff0_reg_n_98,
      O(7 downto 0) => D(31 downto 24),
      S(7) => \mul_ln14_reg_620[31]_i_2_n_0\,
      S(6) => \mul_ln14_reg_620[31]_i_3_n_0\,
      S(5) => \mul_ln14_reg_620[31]_i_4_n_0\,
      S(4) => \mul_ln14_reg_620[31]_i_5_n_0\,
      S(3) => \mul_ln14_reg_620[31]_i_6_n_0\,
      S(2) => \mul_ln14_reg_620[31]_i_7_n_0\,
      S(1) => \mul_ln14_reg_620[31]_i_8_n_0\,
      S(0) => \mul_ln14_reg_620[31]_i_9_n_0\
    );
tmp_product: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
      B_INPUT => "DIRECT",
      CARRYINREG => 0,
      CARRYINSELREG => 0,
      CREG => 1,
      DREG => 1,
      INMODEREG => 0,
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 0,
      PATTERN => X"000000000000",
      PREADDINSEL => "A",
      PREG => 1,
      RND => X"000000000000",
      SEL_MASK => "MASK",
      SEL_PATTERN => "PATTERN",
      USE_MULT => "MULTIPLY",
      USE_PATTERN_DETECT => "NO_PATDET",
      USE_SIMD => "ONE48",
      USE_WIDEXOR => "FALSE",
      XORSIMD => "XOR24_48_96"
    )
        port map (
      A(29 downto 17) => B"0000000000000",
      A(16 downto 0) => in1_Dout_B(16 downto 0),
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => NLW_tmp_product_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => in2_Dout_B(31),
      B(16) => in2_Dout_B(31),
      B(15) => in2_Dout_B(31),
      B(14 downto 0) => in2_Dout_B(31 downto 17),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_tmp_product_BCOUT_UNCONNECTED(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_tmp_product_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_tmp_product_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => '0',
      CEA2 => CEB2,
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => CEB2,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => ap_block_pp0_stage0_subdone,
      CLK => ap_clk,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_tmp_product_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 0) => B"000000101",
      OVERFLOW => NLW_tmp_product_OVERFLOW_UNCONNECTED,
      P(47) => tmp_product_n_58,
      P(46) => tmp_product_n_59,
      P(45) => tmp_product_n_60,
      P(44) => tmp_product_n_61,
      P(43) => tmp_product_n_62,
      P(42) => tmp_product_n_63,
      P(41) => tmp_product_n_64,
      P(40) => tmp_product_n_65,
      P(39) => tmp_product_n_66,
      P(38) => tmp_product_n_67,
      P(37) => tmp_product_n_68,
      P(36) => tmp_product_n_69,
      P(35) => tmp_product_n_70,
      P(34) => tmp_product_n_71,
      P(33) => tmp_product_n_72,
      P(32) => tmp_product_n_73,
      P(31) => tmp_product_n_74,
      P(30) => tmp_product_n_75,
      P(29) => tmp_product_n_76,
      P(28) => tmp_product_n_77,
      P(27) => tmp_product_n_78,
      P(26) => tmp_product_n_79,
      P(25) => tmp_product_n_80,
      P(24) => tmp_product_n_81,
      P(23) => tmp_product_n_82,
      P(22) => tmp_product_n_83,
      P(21) => tmp_product_n_84,
      P(20) => tmp_product_n_85,
      P(19) => tmp_product_n_86,
      P(18) => tmp_product_n_87,
      P(17) => tmp_product_n_88,
      P(16) => tmp_product_n_89,
      P(15) => tmp_product_n_90,
      P(14) => tmp_product_n_91,
      P(13) => tmp_product_n_92,
      P(12) => tmp_product_n_93,
      P(11) => tmp_product_n_94,
      P(10) => tmp_product_n_95,
      P(9) => tmp_product_n_96,
      P(8) => tmp_product_n_97,
      P(7) => tmp_product_n_98,
      P(6) => tmp_product_n_99,
      P(5) => tmp_product_n_100,
      P(4) => tmp_product_n_101,
      P(3) => tmp_product_n_102,
      P(2) => tmp_product_n_103,
      P(1) => tmp_product_n_104,
      P(0) => tmp_product_n_105,
      PATTERNBDETECT => NLW_tmp_product_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_tmp_product_PATTERNDETECT_UNCONNECTED,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47) => tmp_product_n_106,
      PCOUT(46) => tmp_product_n_107,
      PCOUT(45) => tmp_product_n_108,
      PCOUT(44) => tmp_product_n_109,
      PCOUT(43) => tmp_product_n_110,
      PCOUT(42) => tmp_product_n_111,
      PCOUT(41) => tmp_product_n_112,
      PCOUT(40) => tmp_product_n_113,
      PCOUT(39) => tmp_product_n_114,
      PCOUT(38) => tmp_product_n_115,
      PCOUT(37) => tmp_product_n_116,
      PCOUT(36) => tmp_product_n_117,
      PCOUT(35) => tmp_product_n_118,
      PCOUT(34) => tmp_product_n_119,
      PCOUT(33) => tmp_product_n_120,
      PCOUT(32) => tmp_product_n_121,
      PCOUT(31) => tmp_product_n_122,
      PCOUT(30) => tmp_product_n_123,
      PCOUT(29) => tmp_product_n_124,
      PCOUT(28) => tmp_product_n_125,
      PCOUT(27) => tmp_product_n_126,
      PCOUT(26) => tmp_product_n_127,
      PCOUT(25) => tmp_product_n_128,
      PCOUT(24) => tmp_product_n_129,
      PCOUT(23) => tmp_product_n_130,
      PCOUT(22) => tmp_product_n_131,
      PCOUT(21) => tmp_product_n_132,
      PCOUT(20) => tmp_product_n_133,
      PCOUT(19) => tmp_product_n_134,
      PCOUT(18) => tmp_product_n_135,
      PCOUT(17) => tmp_product_n_136,
      PCOUT(16) => tmp_product_n_137,
      PCOUT(15) => tmp_product_n_138,
      PCOUT(14) => tmp_product_n_139,
      PCOUT(13) => tmp_product_n_140,
      PCOUT(12) => tmp_product_n_141,
      PCOUT(11) => tmp_product_n_142,
      PCOUT(10) => tmp_product_n_143,
      PCOUT(9) => tmp_product_n_144,
      PCOUT(8) => tmp_product_n_145,
      PCOUT(7) => tmp_product_n_146,
      PCOUT(6) => tmp_product_n_147,
      PCOUT(5) => tmp_product_n_148,
      PCOUT(4) => tmp_product_n_149,
      PCOUT(3) => tmp_product_n_150,
      PCOUT(2) => tmp_product_n_151,
      PCOUT(1) => tmp_product_n_152,
      PCOUT(0) => tmp_product_n_153,
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => '0',
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => NLW_tmp_product_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_tmp_product_XOROUT_UNCONNECTED(7 downto 0)
    );
\tmp_product__0\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
      B_INPUT => "DIRECT",
      CARRYINREG => 0,
      CARRYINSELREG => 0,
      CREG => 1,
      DREG => 1,
      INMODEREG => 0,
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 0,
      PATTERN => X"000000000000",
      PREADDINSEL => "A",
      PREG => 0,
      RND => X"000000000000",
      SEL_MASK => "MASK",
      SEL_PATTERN => "PATTERN",
      USE_MULT => "MULTIPLY",
      USE_PATTERN_DETECT => "NO_PATDET",
      USE_SIMD => "ONE48",
      USE_WIDEXOR => "FALSE",
      XORSIMD => "XOR24_48_96"
    )
        port map (
      A(29 downto 17) => B"0000000000000",
      A(16 downto 0) => in2_Dout_B(16 downto 0),
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29) => \tmp_product__0_n_24\,
      ACOUT(28) => \tmp_product__0_n_25\,
      ACOUT(27) => \tmp_product__0_n_26\,
      ACOUT(26) => \tmp_product__0_n_27\,
      ACOUT(25) => \tmp_product__0_n_28\,
      ACOUT(24) => \tmp_product__0_n_29\,
      ACOUT(23) => \tmp_product__0_n_30\,
      ACOUT(22) => \tmp_product__0_n_31\,
      ACOUT(21) => \tmp_product__0_n_32\,
      ACOUT(20) => \tmp_product__0_n_33\,
      ACOUT(19) => \tmp_product__0_n_34\,
      ACOUT(18) => \tmp_product__0_n_35\,
      ACOUT(17) => \tmp_product__0_n_36\,
      ACOUT(16) => \tmp_product__0_n_37\,
      ACOUT(15) => \tmp_product__0_n_38\,
      ACOUT(14) => \tmp_product__0_n_39\,
      ACOUT(13) => \tmp_product__0_n_40\,
      ACOUT(12) => \tmp_product__0_n_41\,
      ACOUT(11) => \tmp_product__0_n_42\,
      ACOUT(10) => \tmp_product__0_n_43\,
      ACOUT(9) => \tmp_product__0_n_44\,
      ACOUT(8) => \tmp_product__0_n_45\,
      ACOUT(7) => \tmp_product__0_n_46\,
      ACOUT(6) => \tmp_product__0_n_47\,
      ACOUT(5) => \tmp_product__0_n_48\,
      ACOUT(4) => \tmp_product__0_n_49\,
      ACOUT(3) => \tmp_product__0_n_50\,
      ACOUT(2) => \tmp_product__0_n_51\,
      ACOUT(1) => \tmp_product__0_n_52\,
      ACOUT(0) => \tmp_product__0_n_53\,
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => in1_Dout_B(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_tmp_product__0_BCOUT_UNCONNECTED\(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_tmp_product__0_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_tmp_product__0_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => CEB2,
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => CEB2,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => ap_clk,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_tmp_product__0_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 0) => B"000000101",
      OVERFLOW => \NLW_tmp_product__0_OVERFLOW_UNCONNECTED\,
      P(47) => \tmp_product__0_n_58\,
      P(46) => \tmp_product__0_n_59\,
      P(45) => \tmp_product__0_n_60\,
      P(44) => \tmp_product__0_n_61\,
      P(43) => \tmp_product__0_n_62\,
      P(42) => \tmp_product__0_n_63\,
      P(41) => \tmp_product__0_n_64\,
      P(40) => \tmp_product__0_n_65\,
      P(39) => \tmp_product__0_n_66\,
      P(38) => \tmp_product__0_n_67\,
      P(37) => \tmp_product__0_n_68\,
      P(36) => \tmp_product__0_n_69\,
      P(35) => \tmp_product__0_n_70\,
      P(34) => \tmp_product__0_n_71\,
      P(33) => \tmp_product__0_n_72\,
      P(32) => \tmp_product__0_n_73\,
      P(31) => \tmp_product__0_n_74\,
      P(30) => \tmp_product__0_n_75\,
      P(29) => \tmp_product__0_n_76\,
      P(28) => \tmp_product__0_n_77\,
      P(27) => \tmp_product__0_n_78\,
      P(26) => \tmp_product__0_n_79\,
      P(25) => \tmp_product__0_n_80\,
      P(24) => \tmp_product__0_n_81\,
      P(23) => \tmp_product__0_n_82\,
      P(22) => \tmp_product__0_n_83\,
      P(21) => \tmp_product__0_n_84\,
      P(20) => \tmp_product__0_n_85\,
      P(19) => \tmp_product__0_n_86\,
      P(18) => \tmp_product__0_n_87\,
      P(17) => \tmp_product__0_n_88\,
      P(16) => \tmp_product__0_n_89\,
      P(15) => \tmp_product__0_n_90\,
      P(14) => \tmp_product__0_n_91\,
      P(13) => \tmp_product__0_n_92\,
      P(12) => \tmp_product__0_n_93\,
      P(11) => \tmp_product__0_n_94\,
      P(10) => \tmp_product__0_n_95\,
      P(9) => \tmp_product__0_n_96\,
      P(8) => \tmp_product__0_n_97\,
      P(7) => \tmp_product__0_n_98\,
      P(6) => \tmp_product__0_n_99\,
      P(5) => \tmp_product__0_n_100\,
      P(4) => \tmp_product__0_n_101\,
      P(3) => \tmp_product__0_n_102\,
      P(2) => \tmp_product__0_n_103\,
      P(1) => \tmp_product__0_n_104\,
      P(0) => \tmp_product__0_n_105\,
      PATTERNBDETECT => \NLW_tmp_product__0_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_tmp_product__0_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47) => \tmp_product__0_n_106\,
      PCOUT(46) => \tmp_product__0_n_107\,
      PCOUT(45) => \tmp_product__0_n_108\,
      PCOUT(44) => \tmp_product__0_n_109\,
      PCOUT(43) => \tmp_product__0_n_110\,
      PCOUT(42) => \tmp_product__0_n_111\,
      PCOUT(41) => \tmp_product__0_n_112\,
      PCOUT(40) => \tmp_product__0_n_113\,
      PCOUT(39) => \tmp_product__0_n_114\,
      PCOUT(38) => \tmp_product__0_n_115\,
      PCOUT(37) => \tmp_product__0_n_116\,
      PCOUT(36) => \tmp_product__0_n_117\,
      PCOUT(35) => \tmp_product__0_n_118\,
      PCOUT(34) => \tmp_product__0_n_119\,
      PCOUT(33) => \tmp_product__0_n_120\,
      PCOUT(32) => \tmp_product__0_n_121\,
      PCOUT(31) => \tmp_product__0_n_122\,
      PCOUT(30) => \tmp_product__0_n_123\,
      PCOUT(29) => \tmp_product__0_n_124\,
      PCOUT(28) => \tmp_product__0_n_125\,
      PCOUT(27) => \tmp_product__0_n_126\,
      PCOUT(26) => \tmp_product__0_n_127\,
      PCOUT(25) => \tmp_product__0_n_128\,
      PCOUT(24) => \tmp_product__0_n_129\,
      PCOUT(23) => \tmp_product__0_n_130\,
      PCOUT(22) => \tmp_product__0_n_131\,
      PCOUT(21) => \tmp_product__0_n_132\,
      PCOUT(20) => \tmp_product__0_n_133\,
      PCOUT(19) => \tmp_product__0_n_134\,
      PCOUT(18) => \tmp_product__0_n_135\,
      PCOUT(17) => \tmp_product__0_n_136\,
      PCOUT(16) => \tmp_product__0_n_137\,
      PCOUT(15) => \tmp_product__0_n_138\,
      PCOUT(14) => \tmp_product__0_n_139\,
      PCOUT(13) => \tmp_product__0_n_140\,
      PCOUT(12) => \tmp_product__0_n_141\,
      PCOUT(11) => \tmp_product__0_n_142\,
      PCOUT(10) => \tmp_product__0_n_143\,
      PCOUT(9) => \tmp_product__0_n_144\,
      PCOUT(8) => \tmp_product__0_n_145\,
      PCOUT(7) => \tmp_product__0_n_146\,
      PCOUT(6) => \tmp_product__0_n_147\,
      PCOUT(5) => \tmp_product__0_n_148\,
      PCOUT(4) => \tmp_product__0_n_149\,
      PCOUT(3) => \tmp_product__0_n_150\,
      PCOUT(2) => \tmp_product__0_n_151\,
      PCOUT(1) => \tmp_product__0_n_152\,
      PCOUT(0) => \tmp_product__0_n_153\,
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => '0',
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_tmp_product__0_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_tmp_product__0_XOROUT_UNCONNECTED\(7 downto 0)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_mul_32s_32s_32_2_1_0 is
  port (
    CEB2 : out STD_LOGIC;
    D : out STD_LOGIC_VECTOR ( 31 downto 0 );
    ap_block_pp0_stage0_subdone : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    in2_Dout_A : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Dout_A : in STD_LOGIC_VECTOR ( 31 downto 0 );
    ap_enable_reg_pp0_iter1 : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_mul_32s_32s_32_2_1_0 : entity is "mat_mul_mul_32s_32s_32_2_1";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_mul_32s_32s_32_2_1_0;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_mul_32s_32s_32_2_1_0 is
  signal \^ceb2\ : STD_LOGIC;
  signal \buff0_reg[16]__0_n_0\ : STD_LOGIC;
  signal buff0_reg_n_100 : STD_LOGIC;
  signal buff0_reg_n_101 : STD_LOGIC;
  signal buff0_reg_n_102 : STD_LOGIC;
  signal buff0_reg_n_103 : STD_LOGIC;
  signal buff0_reg_n_104 : STD_LOGIC;
  signal buff0_reg_n_105 : STD_LOGIC;
  signal buff0_reg_n_58 : STD_LOGIC;
  signal buff0_reg_n_59 : STD_LOGIC;
  signal buff0_reg_n_60 : STD_LOGIC;
  signal buff0_reg_n_61 : STD_LOGIC;
  signal buff0_reg_n_62 : STD_LOGIC;
  signal buff0_reg_n_63 : STD_LOGIC;
  signal buff0_reg_n_64 : STD_LOGIC;
  signal buff0_reg_n_65 : STD_LOGIC;
  signal buff0_reg_n_66 : STD_LOGIC;
  signal buff0_reg_n_67 : STD_LOGIC;
  signal buff0_reg_n_68 : STD_LOGIC;
  signal buff0_reg_n_69 : STD_LOGIC;
  signal buff0_reg_n_70 : STD_LOGIC;
  signal buff0_reg_n_71 : STD_LOGIC;
  signal buff0_reg_n_72 : STD_LOGIC;
  signal buff0_reg_n_73 : STD_LOGIC;
  signal buff0_reg_n_74 : STD_LOGIC;
  signal buff0_reg_n_75 : STD_LOGIC;
  signal buff0_reg_n_76 : STD_LOGIC;
  signal buff0_reg_n_77 : STD_LOGIC;
  signal buff0_reg_n_78 : STD_LOGIC;
  signal buff0_reg_n_79 : STD_LOGIC;
  signal buff0_reg_n_80 : STD_LOGIC;
  signal buff0_reg_n_81 : STD_LOGIC;
  signal buff0_reg_n_82 : STD_LOGIC;
  signal buff0_reg_n_83 : STD_LOGIC;
  signal buff0_reg_n_84 : STD_LOGIC;
  signal buff0_reg_n_85 : STD_LOGIC;
  signal buff0_reg_n_86 : STD_LOGIC;
  signal buff0_reg_n_87 : STD_LOGIC;
  signal buff0_reg_n_88 : STD_LOGIC;
  signal buff0_reg_n_89 : STD_LOGIC;
  signal buff0_reg_n_90 : STD_LOGIC;
  signal buff0_reg_n_91 : STD_LOGIC;
  signal buff0_reg_n_92 : STD_LOGIC;
  signal buff0_reg_n_93 : STD_LOGIC;
  signal buff0_reg_n_94 : STD_LOGIC;
  signal buff0_reg_n_95 : STD_LOGIC;
  signal buff0_reg_n_96 : STD_LOGIC;
  signal buff0_reg_n_97 : STD_LOGIC;
  signal buff0_reg_n_98 : STD_LOGIC;
  signal buff0_reg_n_99 : STD_LOGIC;
  signal \mul_ln14_1_reg_625[23]_i_2_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[23]_i_3_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[23]_i_4_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[23]_i_5_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[23]_i_6_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[23]_i_7_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[23]_i_8_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[31]_i_2_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[31]_i_3_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[31]_i_4_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[31]_i_5_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[31]_i_6_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[31]_i_7_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[31]_i_8_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625[31]_i_9_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[23]_i_1_n_0\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[23]_i_1_n_1\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[23]_i_1_n_2\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[23]_i_1_n_3\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[23]_i_1_n_4\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[23]_i_1_n_5\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[23]_i_1_n_6\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[23]_i_1_n_7\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[31]_i_1_n_1\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[31]_i_1_n_2\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[31]_i_1_n_3\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[31]_i_1_n_4\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[31]_i_1_n_5\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[31]_i_1_n_6\ : STD_LOGIC;
  signal \mul_ln14_1_reg_625_reg[31]_i_1_n_7\ : STD_LOGIC;
  signal \tmp_product__0_n_100\ : STD_LOGIC;
  signal \tmp_product__0_n_101\ : STD_LOGIC;
  signal \tmp_product__0_n_102\ : STD_LOGIC;
  signal \tmp_product__0_n_103\ : STD_LOGIC;
  signal \tmp_product__0_n_104\ : STD_LOGIC;
  signal \tmp_product__0_n_105\ : STD_LOGIC;
  signal \tmp_product__0_n_106\ : STD_LOGIC;
  signal \tmp_product__0_n_107\ : STD_LOGIC;
  signal \tmp_product__0_n_108\ : STD_LOGIC;
  signal \tmp_product__0_n_109\ : STD_LOGIC;
  signal \tmp_product__0_n_110\ : STD_LOGIC;
  signal \tmp_product__0_n_111\ : STD_LOGIC;
  signal \tmp_product__0_n_112\ : STD_LOGIC;
  signal \tmp_product__0_n_113\ : STD_LOGIC;
  signal \tmp_product__0_n_114\ : STD_LOGIC;
  signal \tmp_product__0_n_115\ : STD_LOGIC;
  signal \tmp_product__0_n_116\ : STD_LOGIC;
  signal \tmp_product__0_n_117\ : STD_LOGIC;
  signal \tmp_product__0_n_118\ : STD_LOGIC;
  signal \tmp_product__0_n_119\ : STD_LOGIC;
  signal \tmp_product__0_n_120\ : STD_LOGIC;
  signal \tmp_product__0_n_121\ : STD_LOGIC;
  signal \tmp_product__0_n_122\ : STD_LOGIC;
  signal \tmp_product__0_n_123\ : STD_LOGIC;
  signal \tmp_product__0_n_124\ : STD_LOGIC;
  signal \tmp_product__0_n_125\ : STD_LOGIC;
  signal \tmp_product__0_n_126\ : STD_LOGIC;
  signal \tmp_product__0_n_127\ : STD_LOGIC;
  signal \tmp_product__0_n_128\ : STD_LOGIC;
  signal \tmp_product__0_n_129\ : STD_LOGIC;
  signal \tmp_product__0_n_130\ : STD_LOGIC;
  signal \tmp_product__0_n_131\ : STD_LOGIC;
  signal \tmp_product__0_n_132\ : STD_LOGIC;
  signal \tmp_product__0_n_133\ : STD_LOGIC;
  signal \tmp_product__0_n_134\ : STD_LOGIC;
  signal \tmp_product__0_n_135\ : STD_LOGIC;
  signal \tmp_product__0_n_136\ : STD_LOGIC;
  signal \tmp_product__0_n_137\ : STD_LOGIC;
  signal \tmp_product__0_n_138\ : STD_LOGIC;
  signal \tmp_product__0_n_139\ : STD_LOGIC;
  signal \tmp_product__0_n_140\ : STD_LOGIC;
  signal \tmp_product__0_n_141\ : STD_LOGIC;
  signal \tmp_product__0_n_142\ : STD_LOGIC;
  signal \tmp_product__0_n_143\ : STD_LOGIC;
  signal \tmp_product__0_n_144\ : STD_LOGIC;
  signal \tmp_product__0_n_145\ : STD_LOGIC;
  signal \tmp_product__0_n_146\ : STD_LOGIC;
  signal \tmp_product__0_n_147\ : STD_LOGIC;
  signal \tmp_product__0_n_148\ : STD_LOGIC;
  signal \tmp_product__0_n_149\ : STD_LOGIC;
  signal \tmp_product__0_n_150\ : STD_LOGIC;
  signal \tmp_product__0_n_151\ : STD_LOGIC;
  signal \tmp_product__0_n_152\ : STD_LOGIC;
  signal \tmp_product__0_n_153\ : STD_LOGIC;
  signal \tmp_product__0_n_24\ : STD_LOGIC;
  signal \tmp_product__0_n_25\ : STD_LOGIC;
  signal \tmp_product__0_n_26\ : STD_LOGIC;
  signal \tmp_product__0_n_27\ : STD_LOGIC;
  signal \tmp_product__0_n_28\ : STD_LOGIC;
  signal \tmp_product__0_n_29\ : STD_LOGIC;
  signal \tmp_product__0_n_30\ : STD_LOGIC;
  signal \tmp_product__0_n_31\ : STD_LOGIC;
  signal \tmp_product__0_n_32\ : STD_LOGIC;
  signal \tmp_product__0_n_33\ : STD_LOGIC;
  signal \tmp_product__0_n_34\ : STD_LOGIC;
  signal \tmp_product__0_n_35\ : STD_LOGIC;
  signal \tmp_product__0_n_36\ : STD_LOGIC;
  signal \tmp_product__0_n_37\ : STD_LOGIC;
  signal \tmp_product__0_n_38\ : STD_LOGIC;
  signal \tmp_product__0_n_39\ : STD_LOGIC;
  signal \tmp_product__0_n_40\ : STD_LOGIC;
  signal \tmp_product__0_n_41\ : STD_LOGIC;
  signal \tmp_product__0_n_42\ : STD_LOGIC;
  signal \tmp_product__0_n_43\ : STD_LOGIC;
  signal \tmp_product__0_n_44\ : STD_LOGIC;
  signal \tmp_product__0_n_45\ : STD_LOGIC;
  signal \tmp_product__0_n_46\ : STD_LOGIC;
  signal \tmp_product__0_n_47\ : STD_LOGIC;
  signal \tmp_product__0_n_48\ : STD_LOGIC;
  signal \tmp_product__0_n_49\ : STD_LOGIC;
  signal \tmp_product__0_n_50\ : STD_LOGIC;
  signal \tmp_product__0_n_51\ : STD_LOGIC;
  signal \tmp_product__0_n_52\ : STD_LOGIC;
  signal \tmp_product__0_n_53\ : STD_LOGIC;
  signal \tmp_product__0_n_58\ : STD_LOGIC;
  signal \tmp_product__0_n_59\ : STD_LOGIC;
  signal \tmp_product__0_n_60\ : STD_LOGIC;
  signal \tmp_product__0_n_61\ : STD_LOGIC;
  signal \tmp_product__0_n_62\ : STD_LOGIC;
  signal \tmp_product__0_n_63\ : STD_LOGIC;
  signal \tmp_product__0_n_64\ : STD_LOGIC;
  signal \tmp_product__0_n_65\ : STD_LOGIC;
  signal \tmp_product__0_n_66\ : STD_LOGIC;
  signal \tmp_product__0_n_67\ : STD_LOGIC;
  signal \tmp_product__0_n_68\ : STD_LOGIC;
  signal \tmp_product__0_n_69\ : STD_LOGIC;
  signal \tmp_product__0_n_70\ : STD_LOGIC;
  signal \tmp_product__0_n_71\ : STD_LOGIC;
  signal \tmp_product__0_n_72\ : STD_LOGIC;
  signal \tmp_product__0_n_73\ : STD_LOGIC;
  signal \tmp_product__0_n_74\ : STD_LOGIC;
  signal \tmp_product__0_n_75\ : STD_LOGIC;
  signal \tmp_product__0_n_76\ : STD_LOGIC;
  signal \tmp_product__0_n_77\ : STD_LOGIC;
  signal \tmp_product__0_n_78\ : STD_LOGIC;
  signal \tmp_product__0_n_79\ : STD_LOGIC;
  signal \tmp_product__0_n_80\ : STD_LOGIC;
  signal \tmp_product__0_n_81\ : STD_LOGIC;
  signal \tmp_product__0_n_82\ : STD_LOGIC;
  signal \tmp_product__0_n_83\ : STD_LOGIC;
  signal \tmp_product__0_n_84\ : STD_LOGIC;
  signal \tmp_product__0_n_85\ : STD_LOGIC;
  signal \tmp_product__0_n_86\ : STD_LOGIC;
  signal \tmp_product__0_n_87\ : STD_LOGIC;
  signal \tmp_product__0_n_88\ : STD_LOGIC;
  signal \tmp_product__0_n_89\ : STD_LOGIC;
  signal \tmp_product__0_n_90\ : STD_LOGIC;
  signal \tmp_product__0_n_91\ : STD_LOGIC;
  signal \tmp_product__0_n_92\ : STD_LOGIC;
  signal \tmp_product__0_n_93\ : STD_LOGIC;
  signal \tmp_product__0_n_94\ : STD_LOGIC;
  signal \tmp_product__0_n_95\ : STD_LOGIC;
  signal \tmp_product__0_n_96\ : STD_LOGIC;
  signal \tmp_product__0_n_97\ : STD_LOGIC;
  signal \tmp_product__0_n_98\ : STD_LOGIC;
  signal \tmp_product__0_n_99\ : STD_LOGIC;
  signal tmp_product_n_100 : STD_LOGIC;
  signal tmp_product_n_101 : STD_LOGIC;
  signal tmp_product_n_102 : STD_LOGIC;
  signal tmp_product_n_103 : STD_LOGIC;
  signal tmp_product_n_104 : STD_LOGIC;
  signal tmp_product_n_105 : STD_LOGIC;
  signal tmp_product_n_106 : STD_LOGIC;
  signal tmp_product_n_107 : STD_LOGIC;
  signal tmp_product_n_108 : STD_LOGIC;
  signal tmp_product_n_109 : STD_LOGIC;
  signal tmp_product_n_110 : STD_LOGIC;
  signal tmp_product_n_111 : STD_LOGIC;
  signal tmp_product_n_112 : STD_LOGIC;
  signal tmp_product_n_113 : STD_LOGIC;
  signal tmp_product_n_114 : STD_LOGIC;
  signal tmp_product_n_115 : STD_LOGIC;
  signal tmp_product_n_116 : STD_LOGIC;
  signal tmp_product_n_117 : STD_LOGIC;
  signal tmp_product_n_118 : STD_LOGIC;
  signal tmp_product_n_119 : STD_LOGIC;
  signal tmp_product_n_120 : STD_LOGIC;
  signal tmp_product_n_121 : STD_LOGIC;
  signal tmp_product_n_122 : STD_LOGIC;
  signal tmp_product_n_123 : STD_LOGIC;
  signal tmp_product_n_124 : STD_LOGIC;
  signal tmp_product_n_125 : STD_LOGIC;
  signal tmp_product_n_126 : STD_LOGIC;
  signal tmp_product_n_127 : STD_LOGIC;
  signal tmp_product_n_128 : STD_LOGIC;
  signal tmp_product_n_129 : STD_LOGIC;
  signal tmp_product_n_130 : STD_LOGIC;
  signal tmp_product_n_131 : STD_LOGIC;
  signal tmp_product_n_132 : STD_LOGIC;
  signal tmp_product_n_133 : STD_LOGIC;
  signal tmp_product_n_134 : STD_LOGIC;
  signal tmp_product_n_135 : STD_LOGIC;
  signal tmp_product_n_136 : STD_LOGIC;
  signal tmp_product_n_137 : STD_LOGIC;
  signal tmp_product_n_138 : STD_LOGIC;
  signal tmp_product_n_139 : STD_LOGIC;
  signal tmp_product_n_140 : STD_LOGIC;
  signal tmp_product_n_141 : STD_LOGIC;
  signal tmp_product_n_142 : STD_LOGIC;
  signal tmp_product_n_143 : STD_LOGIC;
  signal tmp_product_n_144 : STD_LOGIC;
  signal tmp_product_n_145 : STD_LOGIC;
  signal tmp_product_n_146 : STD_LOGIC;
  signal tmp_product_n_147 : STD_LOGIC;
  signal tmp_product_n_148 : STD_LOGIC;
  signal tmp_product_n_149 : STD_LOGIC;
  signal tmp_product_n_150 : STD_LOGIC;
  signal tmp_product_n_151 : STD_LOGIC;
  signal tmp_product_n_152 : STD_LOGIC;
  signal tmp_product_n_153 : STD_LOGIC;
  signal tmp_product_n_58 : STD_LOGIC;
  signal tmp_product_n_59 : STD_LOGIC;
  signal tmp_product_n_60 : STD_LOGIC;
  signal tmp_product_n_61 : STD_LOGIC;
  signal tmp_product_n_62 : STD_LOGIC;
  signal tmp_product_n_63 : STD_LOGIC;
  signal tmp_product_n_64 : STD_LOGIC;
  signal tmp_product_n_65 : STD_LOGIC;
  signal tmp_product_n_66 : STD_LOGIC;
  signal tmp_product_n_67 : STD_LOGIC;
  signal tmp_product_n_68 : STD_LOGIC;
  signal tmp_product_n_69 : STD_LOGIC;
  signal tmp_product_n_70 : STD_LOGIC;
  signal tmp_product_n_71 : STD_LOGIC;
  signal tmp_product_n_72 : STD_LOGIC;
  signal tmp_product_n_73 : STD_LOGIC;
  signal tmp_product_n_74 : STD_LOGIC;
  signal tmp_product_n_75 : STD_LOGIC;
  signal tmp_product_n_76 : STD_LOGIC;
  signal tmp_product_n_77 : STD_LOGIC;
  signal tmp_product_n_78 : STD_LOGIC;
  signal tmp_product_n_79 : STD_LOGIC;
  signal tmp_product_n_80 : STD_LOGIC;
  signal tmp_product_n_81 : STD_LOGIC;
  signal tmp_product_n_82 : STD_LOGIC;
  signal tmp_product_n_83 : STD_LOGIC;
  signal tmp_product_n_84 : STD_LOGIC;
  signal tmp_product_n_85 : STD_LOGIC;
  signal tmp_product_n_86 : STD_LOGIC;
  signal tmp_product_n_87 : STD_LOGIC;
  signal tmp_product_n_88 : STD_LOGIC;
  signal tmp_product_n_89 : STD_LOGIC;
  signal tmp_product_n_90 : STD_LOGIC;
  signal tmp_product_n_91 : STD_LOGIC;
  signal tmp_product_n_92 : STD_LOGIC;
  signal tmp_product_n_93 : STD_LOGIC;
  signal tmp_product_n_94 : STD_LOGIC;
  signal tmp_product_n_95 : STD_LOGIC;
  signal tmp_product_n_96 : STD_LOGIC;
  signal tmp_product_n_97 : STD_LOGIC;
  signal tmp_product_n_98 : STD_LOGIC;
  signal tmp_product_n_99 : STD_LOGIC;
  signal NLW_buff0_reg_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_buff0_reg_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_buff0_reg_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_buff0_reg_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_buff0_reg_PCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal NLW_buff0_reg_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_mul_ln14_1_reg_625_reg[31]_i_1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  signal NLW_tmp_product_CARRYCASCOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_MULTSIGNOUT_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_OVERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_PATTERNBDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_PATTERNDETECT_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_UNDERFLOW_UNCONNECTED : STD_LOGIC;
  signal NLW_tmp_product_ACOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal NLW_tmp_product_BCOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal NLW_tmp_product_CARRYOUT_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_tmp_product_XOROUT_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal \NLW_tmp_product__0_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_tmp_product__0_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_tmp_product__0_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_tmp_product__0_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute KEEP_HIERARCHY : string;
  attribute KEEP_HIERARCHY of buff0_reg : label is "yes";
  attribute METHODOLOGY_DRC_VIOS : string;
  attribute METHODOLOGY_DRC_VIOS of buff0_reg : label is "{SYNTH-10 {cell *THIS*} {string 18x15 4}}";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \mul_ln14_1_reg_625_reg[23]_i_1\ : label is 35;
  attribute ADDER_THRESHOLD of \mul_ln14_1_reg_625_reg[31]_i_1\ : label is 35;
  attribute KEEP_HIERARCHY of tmp_product : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of tmp_product : label is "{SYNTH-10 {cell *THIS*} {string 15x18 4}}";
  attribute KEEP_HIERARCHY of \tmp_product__0\ : label is "yes";
  attribute METHODOLOGY_DRC_VIOS of \tmp_product__0\ : label is "{SYNTH-10 {cell *THIS*} {string 18x18 4}}";
begin
  CEB2 <= \^ceb2\;
buff0_reg: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 0,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 0,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "CASCADE",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
      B_INPUT => "DIRECT",
      CARRYINREG => 0,
      CARRYINSELREG => 0,
      CREG => 1,
      DREG => 1,
      INMODEREG => 0,
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 0,
      PATTERN => X"000000000000",
      PREADDINSEL => "A",
      PREG => 1,
      RND => X"000000000000",
      SEL_MASK => "MASK",
      SEL_PATTERN => "PATTERN",
      USE_MULT => "MULTIPLY",
      USE_PATTERN_DETECT => "NO_PATDET",
      USE_SIMD => "ONE48",
      USE_WIDEXOR => "FALSE",
      XORSIMD => "XOR24_48_96"
    )
        port map (
      A(29 downto 0) => B"000000000000000000000000000000",
      ACIN(29) => \tmp_product__0_n_24\,
      ACIN(28) => \tmp_product__0_n_25\,
      ACIN(27) => \tmp_product__0_n_26\,
      ACIN(26) => \tmp_product__0_n_27\,
      ACIN(25) => \tmp_product__0_n_28\,
      ACIN(24) => \tmp_product__0_n_29\,
      ACIN(23) => \tmp_product__0_n_30\,
      ACIN(22) => \tmp_product__0_n_31\,
      ACIN(21) => \tmp_product__0_n_32\,
      ACIN(20) => \tmp_product__0_n_33\,
      ACIN(19) => \tmp_product__0_n_34\,
      ACIN(18) => \tmp_product__0_n_35\,
      ACIN(17) => \tmp_product__0_n_36\,
      ACIN(16) => \tmp_product__0_n_37\,
      ACIN(15) => \tmp_product__0_n_38\,
      ACIN(14) => \tmp_product__0_n_39\,
      ACIN(13) => \tmp_product__0_n_40\,
      ACIN(12) => \tmp_product__0_n_41\,
      ACIN(11) => \tmp_product__0_n_42\,
      ACIN(10) => \tmp_product__0_n_43\,
      ACIN(9) => \tmp_product__0_n_44\,
      ACIN(8) => \tmp_product__0_n_45\,
      ACIN(7) => \tmp_product__0_n_46\,
      ACIN(6) => \tmp_product__0_n_47\,
      ACIN(5) => \tmp_product__0_n_48\,
      ACIN(4) => \tmp_product__0_n_49\,
      ACIN(3) => \tmp_product__0_n_50\,
      ACIN(2) => \tmp_product__0_n_51\,
      ACIN(1) => \tmp_product__0_n_52\,
      ACIN(0) => \tmp_product__0_n_53\,
      ACOUT(29 downto 0) => NLW_buff0_reg_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => in1_Dout_A(31),
      B(16) => in1_Dout_A(31),
      B(15) => in1_Dout_A(31),
      B(14 downto 0) => in1_Dout_A(31 downto 17),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_buff0_reg_BCOUT_UNCONNECTED(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_buff0_reg_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_buff0_reg_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => '0',
      CEA2 => '0',
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => \^ceb2\,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => ap_block_pp0_stage0_subdone,
      CLK => ap_clk,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_buff0_reg_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 0) => B"001010101",
      OVERFLOW => NLW_buff0_reg_OVERFLOW_UNCONNECTED,
      P(47) => buff0_reg_n_58,
      P(46) => buff0_reg_n_59,
      P(45) => buff0_reg_n_60,
      P(44) => buff0_reg_n_61,
      P(43) => buff0_reg_n_62,
      P(42) => buff0_reg_n_63,
      P(41) => buff0_reg_n_64,
      P(40) => buff0_reg_n_65,
      P(39) => buff0_reg_n_66,
      P(38) => buff0_reg_n_67,
      P(37) => buff0_reg_n_68,
      P(36) => buff0_reg_n_69,
      P(35) => buff0_reg_n_70,
      P(34) => buff0_reg_n_71,
      P(33) => buff0_reg_n_72,
      P(32) => buff0_reg_n_73,
      P(31) => buff0_reg_n_74,
      P(30) => buff0_reg_n_75,
      P(29) => buff0_reg_n_76,
      P(28) => buff0_reg_n_77,
      P(27) => buff0_reg_n_78,
      P(26) => buff0_reg_n_79,
      P(25) => buff0_reg_n_80,
      P(24) => buff0_reg_n_81,
      P(23) => buff0_reg_n_82,
      P(22) => buff0_reg_n_83,
      P(21) => buff0_reg_n_84,
      P(20) => buff0_reg_n_85,
      P(19) => buff0_reg_n_86,
      P(18) => buff0_reg_n_87,
      P(17) => buff0_reg_n_88,
      P(16) => buff0_reg_n_89,
      P(15) => buff0_reg_n_90,
      P(14) => buff0_reg_n_91,
      P(13) => buff0_reg_n_92,
      P(12) => buff0_reg_n_93,
      P(11) => buff0_reg_n_94,
      P(10) => buff0_reg_n_95,
      P(9) => buff0_reg_n_96,
      P(8) => buff0_reg_n_97,
      P(7) => buff0_reg_n_98,
      P(6) => buff0_reg_n_99,
      P(5) => buff0_reg_n_100,
      P(4) => buff0_reg_n_101,
      P(3) => buff0_reg_n_102,
      P(2) => buff0_reg_n_103,
      P(1) => buff0_reg_n_104,
      P(0) => buff0_reg_n_105,
      PATTERNBDETECT => NLW_buff0_reg_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_buff0_reg_PATTERNDETECT_UNCONNECTED,
      PCIN(47) => \tmp_product__0_n_106\,
      PCIN(46) => \tmp_product__0_n_107\,
      PCIN(45) => \tmp_product__0_n_108\,
      PCIN(44) => \tmp_product__0_n_109\,
      PCIN(43) => \tmp_product__0_n_110\,
      PCIN(42) => \tmp_product__0_n_111\,
      PCIN(41) => \tmp_product__0_n_112\,
      PCIN(40) => \tmp_product__0_n_113\,
      PCIN(39) => \tmp_product__0_n_114\,
      PCIN(38) => \tmp_product__0_n_115\,
      PCIN(37) => \tmp_product__0_n_116\,
      PCIN(36) => \tmp_product__0_n_117\,
      PCIN(35) => \tmp_product__0_n_118\,
      PCIN(34) => \tmp_product__0_n_119\,
      PCIN(33) => \tmp_product__0_n_120\,
      PCIN(32) => \tmp_product__0_n_121\,
      PCIN(31) => \tmp_product__0_n_122\,
      PCIN(30) => \tmp_product__0_n_123\,
      PCIN(29) => \tmp_product__0_n_124\,
      PCIN(28) => \tmp_product__0_n_125\,
      PCIN(27) => \tmp_product__0_n_126\,
      PCIN(26) => \tmp_product__0_n_127\,
      PCIN(25) => \tmp_product__0_n_128\,
      PCIN(24) => \tmp_product__0_n_129\,
      PCIN(23) => \tmp_product__0_n_130\,
      PCIN(22) => \tmp_product__0_n_131\,
      PCIN(21) => \tmp_product__0_n_132\,
      PCIN(20) => \tmp_product__0_n_133\,
      PCIN(19) => \tmp_product__0_n_134\,
      PCIN(18) => \tmp_product__0_n_135\,
      PCIN(17) => \tmp_product__0_n_136\,
      PCIN(16) => \tmp_product__0_n_137\,
      PCIN(15) => \tmp_product__0_n_138\,
      PCIN(14) => \tmp_product__0_n_139\,
      PCIN(13) => \tmp_product__0_n_140\,
      PCIN(12) => \tmp_product__0_n_141\,
      PCIN(11) => \tmp_product__0_n_142\,
      PCIN(10) => \tmp_product__0_n_143\,
      PCIN(9) => \tmp_product__0_n_144\,
      PCIN(8) => \tmp_product__0_n_145\,
      PCIN(7) => \tmp_product__0_n_146\,
      PCIN(6) => \tmp_product__0_n_147\,
      PCIN(5) => \tmp_product__0_n_148\,
      PCIN(4) => \tmp_product__0_n_149\,
      PCIN(3) => \tmp_product__0_n_150\,
      PCIN(2) => \tmp_product__0_n_151\,
      PCIN(1) => \tmp_product__0_n_152\,
      PCIN(0) => \tmp_product__0_n_153\,
      PCOUT(47 downto 0) => NLW_buff0_reg_PCOUT_UNCONNECTED(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => '0',
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => NLW_buff0_reg_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_buff0_reg_XOROUT_UNCONNECTED(7 downto 0)
    );
\buff0_reg[0]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_105\,
      Q => D(0),
      R => '0'
    );
\buff0_reg[10]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_95\,
      Q => D(10),
      R => '0'
    );
\buff0_reg[11]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_94\,
      Q => D(11),
      R => '0'
    );
\buff0_reg[12]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_93\,
      Q => D(12),
      R => '0'
    );
\buff0_reg[13]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_92\,
      Q => D(13),
      R => '0'
    );
\buff0_reg[14]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_91\,
      Q => D(14),
      R => '0'
    );
\buff0_reg[15]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_90\,
      Q => D(15),
      R => '0'
    );
\buff0_reg[16]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_89\,
      Q => \buff0_reg[16]__0_n_0\,
      R => '0'
    );
\buff0_reg[1]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_104\,
      Q => D(1),
      R => '0'
    );
\buff0_reg[2]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_103\,
      Q => D(2),
      R => '0'
    );
\buff0_reg[3]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_102\,
      Q => D(3),
      R => '0'
    );
\buff0_reg[4]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_101\,
      Q => D(4),
      R => '0'
    );
\buff0_reg[5]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_100\,
      Q => D(5),
      R => '0'
    );
\buff0_reg[6]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_99\,
      Q => D(6),
      R => '0'
    );
\buff0_reg[7]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_98\,
      Q => D(7),
      R => '0'
    );
\buff0_reg[8]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_97\,
      Q => D(8),
      R => '0'
    );
\buff0_reg[9]__0\: unisim.vcomponents.FDRE
     port map (
      C => ap_clk,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_product__0_n_96\,
      Q => D(9),
      R => '0'
    );
\mul_ln14_1_reg_625[23]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_99,
      I1 => tmp_product_n_99,
      O => \mul_ln14_1_reg_625[23]_i_2_n_0\
    );
\mul_ln14_1_reg_625[23]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_100,
      I1 => tmp_product_n_100,
      O => \mul_ln14_1_reg_625[23]_i_3_n_0\
    );
\mul_ln14_1_reg_625[23]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_101,
      I1 => tmp_product_n_101,
      O => \mul_ln14_1_reg_625[23]_i_4_n_0\
    );
\mul_ln14_1_reg_625[23]_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_102,
      I1 => tmp_product_n_102,
      O => \mul_ln14_1_reg_625[23]_i_5_n_0\
    );
\mul_ln14_1_reg_625[23]_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_103,
      I1 => tmp_product_n_103,
      O => \mul_ln14_1_reg_625[23]_i_6_n_0\
    );
\mul_ln14_1_reg_625[23]_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_104,
      I1 => tmp_product_n_104,
      O => \mul_ln14_1_reg_625[23]_i_7_n_0\
    );
\mul_ln14_1_reg_625[23]_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_105,
      I1 => tmp_product_n_105,
      O => \mul_ln14_1_reg_625[23]_i_8_n_0\
    );
\mul_ln14_1_reg_625[31]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_91,
      I1 => tmp_product_n_91,
      O => \mul_ln14_1_reg_625[31]_i_2_n_0\
    );
\mul_ln14_1_reg_625[31]_i_3\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_92,
      I1 => tmp_product_n_92,
      O => \mul_ln14_1_reg_625[31]_i_3_n_0\
    );
\mul_ln14_1_reg_625[31]_i_4\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_93,
      I1 => tmp_product_n_93,
      O => \mul_ln14_1_reg_625[31]_i_4_n_0\
    );
\mul_ln14_1_reg_625[31]_i_5\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_94,
      I1 => tmp_product_n_94,
      O => \mul_ln14_1_reg_625[31]_i_5_n_0\
    );
\mul_ln14_1_reg_625[31]_i_6\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_95,
      I1 => tmp_product_n_95,
      O => \mul_ln14_1_reg_625[31]_i_6_n_0\
    );
\mul_ln14_1_reg_625[31]_i_7\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_96,
      I1 => tmp_product_n_96,
      O => \mul_ln14_1_reg_625[31]_i_7_n_0\
    );
\mul_ln14_1_reg_625[31]_i_8\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_97,
      I1 => tmp_product_n_97,
      O => \mul_ln14_1_reg_625[31]_i_8_n_0\
    );
\mul_ln14_1_reg_625[31]_i_9\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => buff0_reg_n_98,
      I1 => tmp_product_n_98,
      O => \mul_ln14_1_reg_625[31]_i_9_n_0\
    );
\mul_ln14_1_reg_625_reg[23]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \mul_ln14_1_reg_625_reg[23]_i_1_n_0\,
      CO(6) => \mul_ln14_1_reg_625_reg[23]_i_1_n_1\,
      CO(5) => \mul_ln14_1_reg_625_reg[23]_i_1_n_2\,
      CO(4) => \mul_ln14_1_reg_625_reg[23]_i_1_n_3\,
      CO(3) => \mul_ln14_1_reg_625_reg[23]_i_1_n_4\,
      CO(2) => \mul_ln14_1_reg_625_reg[23]_i_1_n_5\,
      CO(1) => \mul_ln14_1_reg_625_reg[23]_i_1_n_6\,
      CO(0) => \mul_ln14_1_reg_625_reg[23]_i_1_n_7\,
      DI(7) => buff0_reg_n_99,
      DI(6) => buff0_reg_n_100,
      DI(5) => buff0_reg_n_101,
      DI(4) => buff0_reg_n_102,
      DI(3) => buff0_reg_n_103,
      DI(2) => buff0_reg_n_104,
      DI(1) => buff0_reg_n_105,
      DI(0) => '0',
      O(7 downto 0) => D(23 downto 16),
      S(7) => \mul_ln14_1_reg_625[23]_i_2_n_0\,
      S(6) => \mul_ln14_1_reg_625[23]_i_3_n_0\,
      S(5) => \mul_ln14_1_reg_625[23]_i_4_n_0\,
      S(4) => \mul_ln14_1_reg_625[23]_i_5_n_0\,
      S(3) => \mul_ln14_1_reg_625[23]_i_6_n_0\,
      S(2) => \mul_ln14_1_reg_625[23]_i_7_n_0\,
      S(1) => \mul_ln14_1_reg_625[23]_i_8_n_0\,
      S(0) => \buff0_reg[16]__0_n_0\
    );
\mul_ln14_1_reg_625_reg[31]_i_1\: unisim.vcomponents.CARRY8
     port map (
      CI => \mul_ln14_1_reg_625_reg[23]_i_1_n_0\,
      CI_TOP => '0',
      CO(7) => \NLW_mul_ln14_1_reg_625_reg[31]_i_1_CO_UNCONNECTED\(7),
      CO(6) => \mul_ln14_1_reg_625_reg[31]_i_1_n_1\,
      CO(5) => \mul_ln14_1_reg_625_reg[31]_i_1_n_2\,
      CO(4) => \mul_ln14_1_reg_625_reg[31]_i_1_n_3\,
      CO(3) => \mul_ln14_1_reg_625_reg[31]_i_1_n_4\,
      CO(2) => \mul_ln14_1_reg_625_reg[31]_i_1_n_5\,
      CO(1) => \mul_ln14_1_reg_625_reg[31]_i_1_n_6\,
      CO(0) => \mul_ln14_1_reg_625_reg[31]_i_1_n_7\,
      DI(7) => '0',
      DI(6) => buff0_reg_n_92,
      DI(5) => buff0_reg_n_93,
      DI(4) => buff0_reg_n_94,
      DI(3) => buff0_reg_n_95,
      DI(2) => buff0_reg_n_96,
      DI(1) => buff0_reg_n_97,
      DI(0) => buff0_reg_n_98,
      O(7 downto 0) => D(31 downto 24),
      S(7) => \mul_ln14_1_reg_625[31]_i_2_n_0\,
      S(6) => \mul_ln14_1_reg_625[31]_i_3_n_0\,
      S(5) => \mul_ln14_1_reg_625[31]_i_4_n_0\,
      S(4) => \mul_ln14_1_reg_625[31]_i_5_n_0\,
      S(3) => \mul_ln14_1_reg_625[31]_i_6_n_0\,
      S(2) => \mul_ln14_1_reg_625[31]_i_7_n_0\,
      S(1) => \mul_ln14_1_reg_625[31]_i_8_n_0\,
      S(0) => \mul_ln14_1_reg_625[31]_i_9_n_0\
    );
tmp_product: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
      B_INPUT => "DIRECT",
      CARRYINREG => 0,
      CARRYINSELREG => 0,
      CREG => 1,
      DREG => 1,
      INMODEREG => 0,
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 0,
      PATTERN => X"000000000000",
      PREADDINSEL => "A",
      PREG => 1,
      RND => X"000000000000",
      SEL_MASK => "MASK",
      SEL_PATTERN => "PATTERN",
      USE_MULT => "MULTIPLY",
      USE_PATTERN_DETECT => "NO_PATDET",
      USE_SIMD => "ONE48",
      USE_WIDEXOR => "FALSE",
      XORSIMD => "XOR24_48_96"
    )
        port map (
      A(29 downto 17) => B"0000000000000",
      A(16 downto 0) => in1_Dout_A(16 downto 0),
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => NLW_tmp_product_ACOUT_UNCONNECTED(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17) => in2_Dout_A(31),
      B(16) => in2_Dout_A(31),
      B(15) => in2_Dout_A(31),
      B(14 downto 0) => in2_Dout_A(31 downto 17),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => NLW_tmp_product_BCOUT_UNCONNECTED(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => NLW_tmp_product_CARRYCASCOUT_UNCONNECTED,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => NLW_tmp_product_CARRYOUT_UNCONNECTED(3 downto 0),
      CEA1 => '0',
      CEA2 => \^ceb2\,
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => \^ceb2\,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => ap_block_pp0_stage0_subdone,
      CLK => ap_clk,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => NLW_tmp_product_MULTSIGNOUT_UNCONNECTED,
      OPMODE(8 downto 0) => B"000000101",
      OVERFLOW => NLW_tmp_product_OVERFLOW_UNCONNECTED,
      P(47) => tmp_product_n_58,
      P(46) => tmp_product_n_59,
      P(45) => tmp_product_n_60,
      P(44) => tmp_product_n_61,
      P(43) => tmp_product_n_62,
      P(42) => tmp_product_n_63,
      P(41) => tmp_product_n_64,
      P(40) => tmp_product_n_65,
      P(39) => tmp_product_n_66,
      P(38) => tmp_product_n_67,
      P(37) => tmp_product_n_68,
      P(36) => tmp_product_n_69,
      P(35) => tmp_product_n_70,
      P(34) => tmp_product_n_71,
      P(33) => tmp_product_n_72,
      P(32) => tmp_product_n_73,
      P(31) => tmp_product_n_74,
      P(30) => tmp_product_n_75,
      P(29) => tmp_product_n_76,
      P(28) => tmp_product_n_77,
      P(27) => tmp_product_n_78,
      P(26) => tmp_product_n_79,
      P(25) => tmp_product_n_80,
      P(24) => tmp_product_n_81,
      P(23) => tmp_product_n_82,
      P(22) => tmp_product_n_83,
      P(21) => tmp_product_n_84,
      P(20) => tmp_product_n_85,
      P(19) => tmp_product_n_86,
      P(18) => tmp_product_n_87,
      P(17) => tmp_product_n_88,
      P(16) => tmp_product_n_89,
      P(15) => tmp_product_n_90,
      P(14) => tmp_product_n_91,
      P(13) => tmp_product_n_92,
      P(12) => tmp_product_n_93,
      P(11) => tmp_product_n_94,
      P(10) => tmp_product_n_95,
      P(9) => tmp_product_n_96,
      P(8) => tmp_product_n_97,
      P(7) => tmp_product_n_98,
      P(6) => tmp_product_n_99,
      P(5) => tmp_product_n_100,
      P(4) => tmp_product_n_101,
      P(3) => tmp_product_n_102,
      P(2) => tmp_product_n_103,
      P(1) => tmp_product_n_104,
      P(0) => tmp_product_n_105,
      PATTERNBDETECT => NLW_tmp_product_PATTERNBDETECT_UNCONNECTED,
      PATTERNDETECT => NLW_tmp_product_PATTERNDETECT_UNCONNECTED,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47) => tmp_product_n_106,
      PCOUT(46) => tmp_product_n_107,
      PCOUT(45) => tmp_product_n_108,
      PCOUT(44) => tmp_product_n_109,
      PCOUT(43) => tmp_product_n_110,
      PCOUT(42) => tmp_product_n_111,
      PCOUT(41) => tmp_product_n_112,
      PCOUT(40) => tmp_product_n_113,
      PCOUT(39) => tmp_product_n_114,
      PCOUT(38) => tmp_product_n_115,
      PCOUT(37) => tmp_product_n_116,
      PCOUT(36) => tmp_product_n_117,
      PCOUT(35) => tmp_product_n_118,
      PCOUT(34) => tmp_product_n_119,
      PCOUT(33) => tmp_product_n_120,
      PCOUT(32) => tmp_product_n_121,
      PCOUT(31) => tmp_product_n_122,
      PCOUT(30) => tmp_product_n_123,
      PCOUT(29) => tmp_product_n_124,
      PCOUT(28) => tmp_product_n_125,
      PCOUT(27) => tmp_product_n_126,
      PCOUT(26) => tmp_product_n_127,
      PCOUT(25) => tmp_product_n_128,
      PCOUT(24) => tmp_product_n_129,
      PCOUT(23) => tmp_product_n_130,
      PCOUT(22) => tmp_product_n_131,
      PCOUT(21) => tmp_product_n_132,
      PCOUT(20) => tmp_product_n_133,
      PCOUT(19) => tmp_product_n_134,
      PCOUT(18) => tmp_product_n_135,
      PCOUT(17) => tmp_product_n_136,
      PCOUT(16) => tmp_product_n_137,
      PCOUT(15) => tmp_product_n_138,
      PCOUT(14) => tmp_product_n_139,
      PCOUT(13) => tmp_product_n_140,
      PCOUT(12) => tmp_product_n_141,
      PCOUT(11) => tmp_product_n_142,
      PCOUT(10) => tmp_product_n_143,
      PCOUT(9) => tmp_product_n_144,
      PCOUT(8) => tmp_product_n_145,
      PCOUT(7) => tmp_product_n_146,
      PCOUT(6) => tmp_product_n_147,
      PCOUT(5) => tmp_product_n_148,
      PCOUT(4) => tmp_product_n_149,
      PCOUT(3) => tmp_product_n_150,
      PCOUT(2) => tmp_product_n_151,
      PCOUT(1) => tmp_product_n_152,
      PCOUT(0) => tmp_product_n_153,
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => '0',
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => NLW_tmp_product_UNDERFLOW_UNCONNECTED,
      XOROUT(7 downto 0) => NLW_tmp_product_XOROUT_UNCONNECTED(7 downto 0)
    );
\tmp_product__0\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 1,
      ALUMODEREG => 0,
      AMULTSEL => "A",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      AUTORESET_PRIORITY => "RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BMULTSEL => "B",
      BREG => 1,
      B_INPUT => "DIRECT",
      CARRYINREG => 0,
      CARRYINSELREG => 0,
      CREG => 1,
      DREG => 1,
      INMODEREG => 0,
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 0,
      PATTERN => X"000000000000",
      PREADDINSEL => "A",
      PREG => 0,
      RND => X"000000000000",
      SEL_MASK => "MASK",
      SEL_PATTERN => "PATTERN",
      USE_MULT => "MULTIPLY",
      USE_PATTERN_DETECT => "NO_PATDET",
      USE_SIMD => "ONE48",
      USE_WIDEXOR => "FALSE",
      XORSIMD => "XOR24_48_96"
    )
        port map (
      A(29 downto 17) => B"0000000000000",
      A(16 downto 0) => in2_Dout_A(16 downto 0),
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29) => \tmp_product__0_n_24\,
      ACOUT(28) => \tmp_product__0_n_25\,
      ACOUT(27) => \tmp_product__0_n_26\,
      ACOUT(26) => \tmp_product__0_n_27\,
      ACOUT(25) => \tmp_product__0_n_28\,
      ACOUT(24) => \tmp_product__0_n_29\,
      ACOUT(23) => \tmp_product__0_n_30\,
      ACOUT(22) => \tmp_product__0_n_31\,
      ACOUT(21) => \tmp_product__0_n_32\,
      ACOUT(20) => \tmp_product__0_n_33\,
      ACOUT(19) => \tmp_product__0_n_34\,
      ACOUT(18) => \tmp_product__0_n_35\,
      ACOUT(17) => \tmp_product__0_n_36\,
      ACOUT(16) => \tmp_product__0_n_37\,
      ACOUT(15) => \tmp_product__0_n_38\,
      ACOUT(14) => \tmp_product__0_n_39\,
      ACOUT(13) => \tmp_product__0_n_40\,
      ACOUT(12) => \tmp_product__0_n_41\,
      ACOUT(11) => \tmp_product__0_n_42\,
      ACOUT(10) => \tmp_product__0_n_43\,
      ACOUT(9) => \tmp_product__0_n_44\,
      ACOUT(8) => \tmp_product__0_n_45\,
      ACOUT(7) => \tmp_product__0_n_46\,
      ACOUT(6) => \tmp_product__0_n_47\,
      ACOUT(5) => \tmp_product__0_n_48\,
      ACOUT(4) => \tmp_product__0_n_49\,
      ACOUT(3) => \tmp_product__0_n_50\,
      ACOUT(2) => \tmp_product__0_n_51\,
      ACOUT(1) => \tmp_product__0_n_52\,
      ACOUT(0) => \tmp_product__0_n_53\,
      ALUMODE(3 downto 0) => B"0000",
      B(17) => '0',
      B(16 downto 0) => in1_Dout_A(16 downto 0),
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_tmp_product__0_BCOUT_UNCONNECTED\(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_tmp_product__0_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_tmp_product__0_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => \^ceb2\,
      CEAD => '0',
      CEALUMODE => '0',
      CEB1 => '0',
      CEB2 => \^ceb2\,
      CEC => '0',
      CECARRYIN => '0',
      CECTRL => '0',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '0',
      CLK => ap_clk,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_tmp_product__0_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 0) => B"000000101",
      OVERFLOW => \NLW_tmp_product__0_OVERFLOW_UNCONNECTED\,
      P(47) => \tmp_product__0_n_58\,
      P(46) => \tmp_product__0_n_59\,
      P(45) => \tmp_product__0_n_60\,
      P(44) => \tmp_product__0_n_61\,
      P(43) => \tmp_product__0_n_62\,
      P(42) => \tmp_product__0_n_63\,
      P(41) => \tmp_product__0_n_64\,
      P(40) => \tmp_product__0_n_65\,
      P(39) => \tmp_product__0_n_66\,
      P(38) => \tmp_product__0_n_67\,
      P(37) => \tmp_product__0_n_68\,
      P(36) => \tmp_product__0_n_69\,
      P(35) => \tmp_product__0_n_70\,
      P(34) => \tmp_product__0_n_71\,
      P(33) => \tmp_product__0_n_72\,
      P(32) => \tmp_product__0_n_73\,
      P(31) => \tmp_product__0_n_74\,
      P(30) => \tmp_product__0_n_75\,
      P(29) => \tmp_product__0_n_76\,
      P(28) => \tmp_product__0_n_77\,
      P(27) => \tmp_product__0_n_78\,
      P(26) => \tmp_product__0_n_79\,
      P(25) => \tmp_product__0_n_80\,
      P(24) => \tmp_product__0_n_81\,
      P(23) => \tmp_product__0_n_82\,
      P(22) => \tmp_product__0_n_83\,
      P(21) => \tmp_product__0_n_84\,
      P(20) => \tmp_product__0_n_85\,
      P(19) => \tmp_product__0_n_86\,
      P(18) => \tmp_product__0_n_87\,
      P(17) => \tmp_product__0_n_88\,
      P(16) => \tmp_product__0_n_89\,
      P(15) => \tmp_product__0_n_90\,
      P(14) => \tmp_product__0_n_91\,
      P(13) => \tmp_product__0_n_92\,
      P(12) => \tmp_product__0_n_93\,
      P(11) => \tmp_product__0_n_94\,
      P(10) => \tmp_product__0_n_95\,
      P(9) => \tmp_product__0_n_96\,
      P(8) => \tmp_product__0_n_97\,
      P(7) => \tmp_product__0_n_98\,
      P(6) => \tmp_product__0_n_99\,
      P(5) => \tmp_product__0_n_100\,
      P(4) => \tmp_product__0_n_101\,
      P(3) => \tmp_product__0_n_102\,
      P(2) => \tmp_product__0_n_103\,
      P(1) => \tmp_product__0_n_104\,
      P(0) => \tmp_product__0_n_105\,
      PATTERNBDETECT => \NLW_tmp_product__0_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_tmp_product__0_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47) => \tmp_product__0_n_106\,
      PCOUT(46) => \tmp_product__0_n_107\,
      PCOUT(45) => \tmp_product__0_n_108\,
      PCOUT(44) => \tmp_product__0_n_109\,
      PCOUT(43) => \tmp_product__0_n_110\,
      PCOUT(42) => \tmp_product__0_n_111\,
      PCOUT(41) => \tmp_product__0_n_112\,
      PCOUT(40) => \tmp_product__0_n_113\,
      PCOUT(39) => \tmp_product__0_n_114\,
      PCOUT(38) => \tmp_product__0_n_115\,
      PCOUT(37) => \tmp_product__0_n_116\,
      PCOUT(36) => \tmp_product__0_n_117\,
      PCOUT(35) => \tmp_product__0_n_118\,
      PCOUT(34) => \tmp_product__0_n_119\,
      PCOUT(33) => \tmp_product__0_n_120\,
      PCOUT(32) => \tmp_product__0_n_121\,
      PCOUT(31) => \tmp_product__0_n_122\,
      PCOUT(30) => \tmp_product__0_n_123\,
      PCOUT(29) => \tmp_product__0_n_124\,
      PCOUT(28) => \tmp_product__0_n_125\,
      PCOUT(27) => \tmp_product__0_n_126\,
      PCOUT(26) => \tmp_product__0_n_127\,
      PCOUT(25) => \tmp_product__0_n_128\,
      PCOUT(24) => \tmp_product__0_n_129\,
      PCOUT(23) => \tmp_product__0_n_130\,
      PCOUT(22) => \tmp_product__0_n_131\,
      PCOUT(21) => \tmp_product__0_n_132\,
      PCOUT(20) => \tmp_product__0_n_133\,
      PCOUT(19) => \tmp_product__0_n_134\,
      PCOUT(18) => \tmp_product__0_n_135\,
      PCOUT(17) => \tmp_product__0_n_136\,
      PCOUT(16) => \tmp_product__0_n_137\,
      PCOUT(15) => \tmp_product__0_n_138\,
      PCOUT(14) => \tmp_product__0_n_139\,
      PCOUT(13) => \tmp_product__0_n_140\,
      PCOUT(12) => \tmp_product__0_n_141\,
      PCOUT(11) => \tmp_product__0_n_142\,
      PCOUT(10) => \tmp_product__0_n_143\,
      PCOUT(9) => \tmp_product__0_n_144\,
      PCOUT(8) => \tmp_product__0_n_145\,
      PCOUT(7) => \tmp_product__0_n_146\,
      PCOUT(6) => \tmp_product__0_n_147\,
      PCOUT(5) => \tmp_product__0_n_148\,
      PCOUT(4) => \tmp_product__0_n_149\,
      PCOUT(3) => \tmp_product__0_n_150\,
      PCOUT(2) => \tmp_product__0_n_151\,
      PCOUT(1) => \tmp_product__0_n_152\,
      PCOUT(0) => \tmp_product__0_n_153\,
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => '0',
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_tmp_product__0_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_tmp_product__0_XOROUT_UNCONNECTED\(7 downto 0)
    );
tmp_product_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => ap_enable_reg_pp0_iter1,
      I1 => ap_block_pp0_stage0_subdone,
      O => \^ceb2\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul is
  port (
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    in1_Addr_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_EN_A : out STD_LOGIC;
    in1_WEN_A : out STD_LOGIC_VECTOR ( 3 downto 0 );
    in1_Din_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Dout_A : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Clk_A : out STD_LOGIC;
    in1_Rst_A : out STD_LOGIC;
    in1_Addr_B : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_EN_B : out STD_LOGIC;
    in1_WEN_B : out STD_LOGIC_VECTOR ( 3 downto 0 );
    in1_Din_B : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Dout_B : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in1_Clk_B : out STD_LOGIC;
    in1_Rst_B : out STD_LOGIC;
    in2_Addr_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_EN_A : out STD_LOGIC;
    in2_WEN_A : out STD_LOGIC_VECTOR ( 3 downto 0 );
    in2_Din_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_Dout_A : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_Clk_A : out STD_LOGIC;
    in2_Rst_A : out STD_LOGIC;
    in2_Addr_B : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_EN_B : out STD_LOGIC;
    in2_WEN_B : out STD_LOGIC_VECTOR ( 3 downto 0 );
    in2_Din_B : out STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_Dout_B : in STD_LOGIC_VECTOR ( 31 downto 0 );
    in2_Clk_B : out STD_LOGIC;
    in2_Rst_B : out STD_LOGIC;
    out_r_Addr_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    out_r_EN_A : out STD_LOGIC;
    out_r_WEN_A : out STD_LOGIC_VECTOR ( 3 downto 0 );
    out_r_Din_A : out STD_LOGIC_VECTOR ( 31 downto 0 );
    out_r_Dout_A : in STD_LOGIC_VECTOR ( 31 downto 0 );
    out_r_Clk_A : out STD_LOGIC;
    out_r_Rst_A : out STD_LOGIC;
    s_axi_control_AWVALID : in STD_LOGIC;
    s_axi_control_AWREADY : out STD_LOGIC;
    s_axi_control_AWADDR : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_control_WVALID : in STD_LOGIC;
    s_axi_control_WREADY : out STD_LOGIC;
    s_axi_control_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_control_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_control_ARVALID : in STD_LOGIC;
    s_axi_control_ARREADY : out STD_LOGIC;
    s_axi_control_ARADDR : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_control_RVALID : out STD_LOGIC;
    s_axi_control_RREADY : in STD_LOGIC;
    s_axi_control_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_control_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_control_BVALID : out STD_LOGIC;
    s_axi_control_BREADY : in STD_LOGIC;
    s_axi_control_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    interrupt : out STD_LOGIC
  );
  attribute C_S_AXI_CONTROL_ADDR_WIDTH : integer;
  attribute C_S_AXI_CONTROL_ADDR_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul : entity is 4;
  attribute C_S_AXI_CONTROL_DATA_WIDTH : integer;
  attribute C_S_AXI_CONTROL_DATA_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul : entity is 32;
  attribute C_S_AXI_CONTROL_WSTRB_WIDTH : integer;
  attribute C_S_AXI_CONTROL_WSTRB_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul : entity is 4;
  attribute C_S_AXI_DATA_WIDTH : integer;
  attribute C_S_AXI_DATA_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul : entity is 32;
  attribute C_S_AXI_WSTRB_WIDTH : integer;
  attribute C_S_AXI_WSTRB_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul : entity is 4;
  attribute ap_ST_fsm_pp0_stage0 : string;
  attribute ap_ST_fsm_pp0_stage0 of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul : entity is "1'b1";
  attribute hls_module : string;
  attribute hls_module of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul : entity is "yes";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul is
  signal \<const0>\ : STD_LOGIC;
  signal add_ln16_fu_313_p2 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal \add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3_n_0\ : STD_LOGIC;
  signal \add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3_n_0\ : STD_LOGIC;
  signal \add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3_n_0\ : STD_LOGIC;
  signal \add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3_n_0\ : STD_LOGIC;
  signal add_ln9_1_fu_415_p2 : STD_LOGIC_VECTOR ( 4 downto 0 );
  signal ap_block_pp0_stage0_subdone : STD_LOGIC;
  signal \^ap_clk\ : STD_LOGIC;
  signal ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2_n_0 : STD_LOGIC;
  signal ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg : STD_LOGIC;
  signal ap_enable_reg_pp0_iter1 : STD_LOGIC;
  signal ap_enable_reg_pp0_iter2 : STD_LOGIC;
  signal ap_enable_reg_pp0_iter3 : STD_LOGIC;
  signal ap_enable_reg_pp0_iter4 : STD_LOGIC;
  signal ap_loop_exit_ready : STD_LOGIC;
  signal ap_loop_exit_ready_pp0_iter3_reg : STD_LOGIC;
  signal ap_loop_exit_ready_pp0_iter4_reg : STD_LOGIC;
  signal ap_loop_exit_ready_pp0_iter4_reg_i_1_n_0 : STD_LOGIC;
  signal ap_rst_reg_1 : STD_LOGIC;
  signal ap_rst_reg_2 : STD_LOGIC;
  signal ap_rst_reg_2_i_1_n_0 : STD_LOGIC;
  signal ap_start : STD_LOGIC;
  signal ap_start_int : STD_LOGIC;
  signal \buff0_reg__1\ : STD_LOGIC_VECTOR ( 31 downto 16 );
  signal \buff0_reg__1_0\ : STD_LOGIC_VECTOR ( 31 downto 16 );
  signal control_s_axi_U_n_8 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_1 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_16 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_26 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_28 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_29 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_3 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_30 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_31 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_32 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_33 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_5 : STD_LOGIC;
  signal flow_control_loop_delay_pipe_U_n_9 : STD_LOGIC;
  signal i2_fu_78 : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2_n_0\ : STD_LOGIC;
  signal icmp_ln108_reg_161_pp0_iter3_reg : STD_LOGIC;
  signal \icmp_ln108_reg_161_reg_n_0_[0]\ : STD_LOGIC;
  signal icmp_ln10_fu_435_p2 : STD_LOGIC;
  signal icmp_ln10_reg_591 : STD_LOGIC;
  signal icmp_ln9_fu_441_p2 : STD_LOGIC;
  signal icmp_ln9_reg_596 : STD_LOGIC;
  signal \^in1_addr_a\ : STD_LOGIC_VECTOR ( 5 downto 4 );
  signal \^in1_addr_b\ : STD_LOGIC_VECTOR ( 5 downto 4 );
  signal \^in1_en_a\ : STD_LOGIC;
  signal \^in2_addr_a\ : STD_LOGIC_VECTOR ( 5 downto 2 );
  signal \^in2_addr_b\ : STD_LOGIC_VECTOR ( 5 downto 4 );
  signal indvar_flatten131_fu_74 : STD_LOGIC_VECTOR ( 4 downto 0 );
  signal indvar_flatten3_fu_82 : STD_LOGIC_VECTOR ( 4 downto 0 );
  signal j4_fu_86 : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal k5_fu_90 : STD_LOGIC_VECTOR ( 2 downto 1 );
  signal mul_32s_32s_32_2_1_U1_n_16 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_17 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_18 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_19 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_20 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_21 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_22 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_23 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_24 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_25 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_26 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_27 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_28 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_29 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_30 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U1_n_31 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_17 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_18 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_19 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_20 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_21 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_22 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_23 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_24 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_25 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_26 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_27 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_28 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_29 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_30 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_31 : STD_LOGIC;
  signal mul_32s_32s_32_2_1_U2_n_32 : STD_LOGIC;
  signal mul_ln14_1_reg_625 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal mul_ln14_reg_620 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3_n_0\ : STD_LOGIC;
  signal or_ln9_reg_552_pp0_iter3_reg : STD_LOGIC;
  signal \^out_r_addr_a\ : STD_LOGIC_VECTOR ( 5 downto 2 );
  signal \^out_r_din_a\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \out_r_Din_A[0]_INST_0_i_10_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_11_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_12_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_13_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_14_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_15_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_5_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_6_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_7_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_8_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_i_9_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_n_1\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_n_2\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_n_3\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_n_4\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_n_5\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_n_6\ : STD_LOGIC;
  signal \out_r_Din_A[0]_INST_0_n_7\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_10_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_11_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_12_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_13_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_14_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_15_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_16_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_5_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_6_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_7_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_8_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_i_9_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_n_1\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_n_2\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_n_3\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_n_4\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_n_5\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_n_6\ : STD_LOGIC;
  signal \out_r_Din_A[16]_INST_0_n_7\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_10_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_11_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_12_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_13_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_14_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_15_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_16_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_5_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_6_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_7_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_8_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_i_9_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_n_1\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_n_2\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_n_3\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_n_4\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_n_5\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_n_6\ : STD_LOGIC;
  signal \out_r_Din_A[24]_INST_0_n_7\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_10_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_11_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_12_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_13_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_14_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_15_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_16_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_1_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_2_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_3_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_4_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_5_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_6_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_7_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_8_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_i_9_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_n_0\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_n_1\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_n_2\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_n_3\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_n_4\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_n_5\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_n_6\ : STD_LOGIC;
  signal \out_r_Din_A[8]_INST_0_n_7\ : STD_LOGIC;
  signal \^out_r_en_a\ : STD_LOGIC;
  signal \^out_r_rst_a\ : STD_LOGIC;
  signal \^out_r_wen_a\ : STD_LOGIC_VECTOR ( 0 to 0 );
  signal p_1_in : STD_LOGIC;
  signal p_5_in : STD_LOGIC;
  signal rewind_ap_ready_reg : STD_LOGIC;
  signal \^s_axi_control_rdata\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal select_ln10_1_fu_427_p3 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \sum6_fu_94_reg_n_0_[0]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[10]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[11]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[12]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[13]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[14]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[15]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[16]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[17]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[18]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[19]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[1]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[20]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[21]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[22]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[23]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[24]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[25]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[26]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[27]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[28]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[29]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[2]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[30]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[31]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[3]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[4]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[5]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[6]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[7]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[8]\ : STD_LOGIC;
  signal \sum6_fu_94_reg_n_0_[9]\ : STD_LOGIC;
  signal tmp_5_fu_401_p3 : STD_LOGIC;
  signal \tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3_n_0\ : STD_LOGIC;
  signal tmp_5_reg_582_pp0_iter3_reg : STD_LOGIC;
  signal xor_ln12_reg_586 : STD_LOGIC;
  signal \NLW_out_r_Din_A[24]_INST_0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 to 7 );
  attribute srl_bus_name : string;
  attribute srl_bus_name of \add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3\ : label is "inst/\add_ln16_reg_557_pp0_iter2_reg_reg ";
  attribute srl_name : string;
  attribute srl_name of \add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3\ : label is "inst/\add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3 ";
  attribute srl_bus_name of \add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3\ : label is "inst/\add_ln16_reg_557_pp0_iter2_reg_reg ";
  attribute srl_name of \add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3\ : label is "inst/\add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3 ";
  attribute srl_bus_name of \add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3\ : label is "inst/\add_ln16_reg_557_pp0_iter2_reg_reg ";
  attribute srl_name of \add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3\ : label is "inst/\add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3 ";
  attribute srl_bus_name of \add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3\ : label is "inst/\add_ln16_reg_557_pp0_iter2_reg_reg ";
  attribute srl_name of \add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3\ : label is "inst/\add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3 ";
  attribute srl_name of ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2 : label is "inst/ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2";
  attribute inverted : string;
  attribute inverted of ap_done_reg_reg_inv : label is "yes";
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of ap_loop_exit_ready_pp0_iter4_reg_i_1 : label is "soft_lutpair14";
  attribute SHREG_EXTRACT : string;
  attribute SHREG_EXTRACT of ap_rst_n_inv_reg : label is "no";
  attribute SHREG_EXTRACT of ap_rst_reg_1_reg : label is "no";
  attribute SHREG_EXTRACT of ap_rst_reg_2_reg : label is "no";
  attribute srl_bus_name of \icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2\ : label is "inst/\icmp_ln108_reg_161_pp0_iter2_reg_reg ";
  attribute srl_name of \icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2\ : label is "inst/\icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2 ";
  attribute srl_bus_name of \or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3\ : label is "inst/\or_ln9_reg_552_pp0_iter2_reg_reg ";
  attribute srl_name of \or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3\ : label is "inst/\or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3 ";
  attribute ADDER_THRESHOLD : integer;
  attribute ADDER_THRESHOLD of \out_r_Din_A[0]_INST_0\ : label is 35;
  attribute HLUTNM : string;
  attribute HLUTNM of \out_r_Din_A[0]_INST_0_i_15\ : label is "lutpair0";
  attribute HLUTNM of \out_r_Din_A[0]_INST_0_i_7\ : label is "lutpair0";
  attribute ADDER_THRESHOLD of \out_r_Din_A[16]_INST_0\ : label is 35;
  attribute ADDER_THRESHOLD of \out_r_Din_A[24]_INST_0\ : label is 35;
  attribute ADDER_THRESHOLD of \out_r_Din_A[8]_INST_0\ : label is 35;
  attribute SOFT_HLUTNM of \out_r_WEN_A[0]_INST_0\ : label is "soft_lutpair14";
  attribute srl_bus_name of \tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3\ : label is "inst/\tmp_5_reg_582_pp0_iter2_reg_reg ";
  attribute srl_name of \tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3\ : label is "inst/\tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3 ";
begin
  \^ap_clk\ <= ap_clk;
  in1_Addr_A(31) <= \<const0>\;
  in1_Addr_A(30) <= \<const0>\;
  in1_Addr_A(29) <= \<const0>\;
  in1_Addr_A(28) <= \<const0>\;
  in1_Addr_A(27) <= \<const0>\;
  in1_Addr_A(26) <= \<const0>\;
  in1_Addr_A(25) <= \<const0>\;
  in1_Addr_A(24) <= \<const0>\;
  in1_Addr_A(23) <= \<const0>\;
  in1_Addr_A(22) <= \<const0>\;
  in1_Addr_A(21) <= \<const0>\;
  in1_Addr_A(20) <= \<const0>\;
  in1_Addr_A(19) <= \<const0>\;
  in1_Addr_A(18) <= \<const0>\;
  in1_Addr_A(17) <= \<const0>\;
  in1_Addr_A(16) <= \<const0>\;
  in1_Addr_A(15) <= \<const0>\;
  in1_Addr_A(14) <= \<const0>\;
  in1_Addr_A(13) <= \<const0>\;
  in1_Addr_A(12) <= \<const0>\;
  in1_Addr_A(11) <= \<const0>\;
  in1_Addr_A(10) <= \<const0>\;
  in1_Addr_A(9) <= \<const0>\;
  in1_Addr_A(8) <= \<const0>\;
  in1_Addr_A(7) <= \<const0>\;
  in1_Addr_A(6) <= \<const0>\;
  in1_Addr_A(5 downto 4) <= \^in1_addr_a\(5 downto 4);
  in1_Addr_A(3) <= \^in2_addr_b\(5);
  in1_Addr_A(2) <= \<const0>\;
  in1_Addr_A(1) <= \<const0>\;
  in1_Addr_A(0) <= \<const0>\;
  in1_Addr_B(31) <= \<const0>\;
  in1_Addr_B(30) <= \<const0>\;
  in1_Addr_B(29) <= \<const0>\;
  in1_Addr_B(28) <= \<const0>\;
  in1_Addr_B(27) <= \<const0>\;
  in1_Addr_B(26) <= \<const0>\;
  in1_Addr_B(25) <= \<const0>\;
  in1_Addr_B(24) <= \<const0>\;
  in1_Addr_B(23) <= \<const0>\;
  in1_Addr_B(22) <= \<const0>\;
  in1_Addr_B(21) <= \<const0>\;
  in1_Addr_B(20) <= \<const0>\;
  in1_Addr_B(19) <= \<const0>\;
  in1_Addr_B(18) <= \<const0>\;
  in1_Addr_B(17) <= \<const0>\;
  in1_Addr_B(16) <= \<const0>\;
  in1_Addr_B(15) <= \<const0>\;
  in1_Addr_B(14) <= \<const0>\;
  in1_Addr_B(13) <= \<const0>\;
  in1_Addr_B(12) <= \<const0>\;
  in1_Addr_B(11) <= \<const0>\;
  in1_Addr_B(10) <= \<const0>\;
  in1_Addr_B(9) <= \<const0>\;
  in1_Addr_B(8) <= \<const0>\;
  in1_Addr_B(7) <= \<const0>\;
  in1_Addr_B(6) <= \<const0>\;
  in1_Addr_B(5 downto 4) <= \^in1_addr_b\(5 downto 4);
  in1_Addr_B(3) <= \^in2_addr_b\(5);
  in1_Addr_B(2) <= \<const0>\;
  in1_Addr_B(1) <= \<const0>\;
  in1_Addr_B(0) <= \<const0>\;
  in1_Clk_A <= \^ap_clk\;
  in1_Clk_B <= \^ap_clk\;
  in1_Din_A(31) <= \<const0>\;
  in1_Din_A(30) <= \<const0>\;
  in1_Din_A(29) <= \<const0>\;
  in1_Din_A(28) <= \<const0>\;
  in1_Din_A(27) <= \<const0>\;
  in1_Din_A(26) <= \<const0>\;
  in1_Din_A(25) <= \<const0>\;
  in1_Din_A(24) <= \<const0>\;
  in1_Din_A(23) <= \<const0>\;
  in1_Din_A(22) <= \<const0>\;
  in1_Din_A(21) <= \<const0>\;
  in1_Din_A(20) <= \<const0>\;
  in1_Din_A(19) <= \<const0>\;
  in1_Din_A(18) <= \<const0>\;
  in1_Din_A(17) <= \<const0>\;
  in1_Din_A(16) <= \<const0>\;
  in1_Din_A(15) <= \<const0>\;
  in1_Din_A(14) <= \<const0>\;
  in1_Din_A(13) <= \<const0>\;
  in1_Din_A(12) <= \<const0>\;
  in1_Din_A(11) <= \<const0>\;
  in1_Din_A(10) <= \<const0>\;
  in1_Din_A(9) <= \<const0>\;
  in1_Din_A(8) <= \<const0>\;
  in1_Din_A(7) <= \<const0>\;
  in1_Din_A(6) <= \<const0>\;
  in1_Din_A(5) <= \<const0>\;
  in1_Din_A(4) <= \<const0>\;
  in1_Din_A(3) <= \<const0>\;
  in1_Din_A(2) <= \<const0>\;
  in1_Din_A(1) <= \<const0>\;
  in1_Din_A(0) <= \<const0>\;
  in1_Din_B(31) <= \<const0>\;
  in1_Din_B(30) <= \<const0>\;
  in1_Din_B(29) <= \<const0>\;
  in1_Din_B(28) <= \<const0>\;
  in1_Din_B(27) <= \<const0>\;
  in1_Din_B(26) <= \<const0>\;
  in1_Din_B(25) <= \<const0>\;
  in1_Din_B(24) <= \<const0>\;
  in1_Din_B(23) <= \<const0>\;
  in1_Din_B(22) <= \<const0>\;
  in1_Din_B(21) <= \<const0>\;
  in1_Din_B(20) <= \<const0>\;
  in1_Din_B(19) <= \<const0>\;
  in1_Din_B(18) <= \<const0>\;
  in1_Din_B(17) <= \<const0>\;
  in1_Din_B(16) <= \<const0>\;
  in1_Din_B(15) <= \<const0>\;
  in1_Din_B(14) <= \<const0>\;
  in1_Din_B(13) <= \<const0>\;
  in1_Din_B(12) <= \<const0>\;
  in1_Din_B(11) <= \<const0>\;
  in1_Din_B(10) <= \<const0>\;
  in1_Din_B(9) <= \<const0>\;
  in1_Din_B(8) <= \<const0>\;
  in1_Din_B(7) <= \<const0>\;
  in1_Din_B(6) <= \<const0>\;
  in1_Din_B(5) <= \<const0>\;
  in1_Din_B(4) <= \<const0>\;
  in1_Din_B(3) <= \<const0>\;
  in1_Din_B(2) <= \<const0>\;
  in1_Din_B(1) <= \<const0>\;
  in1_Din_B(0) <= \<const0>\;
  in1_EN_A <= \^in1_en_a\;
  in1_EN_B <= \^in1_en_a\;
  in1_Rst_A <= \^out_r_rst_a\;
  in1_Rst_B <= \^out_r_rst_a\;
  in1_WEN_A(3) <= \<const0>\;
  in1_WEN_A(2) <= \<const0>\;
  in1_WEN_A(1) <= \<const0>\;
  in1_WEN_A(0) <= \<const0>\;
  in1_WEN_B(3) <= \<const0>\;
  in1_WEN_B(2) <= \<const0>\;
  in1_WEN_B(1) <= \<const0>\;
  in1_WEN_B(0) <= \<const0>\;
  in2_Addr_A(31) <= \<const0>\;
  in2_Addr_A(30) <= \<const0>\;
  in2_Addr_A(29) <= \<const0>\;
  in2_Addr_A(28) <= \<const0>\;
  in2_Addr_A(27) <= \<const0>\;
  in2_Addr_A(26) <= \<const0>\;
  in2_Addr_A(25) <= \<const0>\;
  in2_Addr_A(24) <= \<const0>\;
  in2_Addr_A(23) <= \<const0>\;
  in2_Addr_A(22) <= \<const0>\;
  in2_Addr_A(21) <= \<const0>\;
  in2_Addr_A(20) <= \<const0>\;
  in2_Addr_A(19) <= \<const0>\;
  in2_Addr_A(18) <= \<const0>\;
  in2_Addr_A(17) <= \<const0>\;
  in2_Addr_A(16) <= \<const0>\;
  in2_Addr_A(15) <= \<const0>\;
  in2_Addr_A(14) <= \<const0>\;
  in2_Addr_A(13) <= \<const0>\;
  in2_Addr_A(12) <= \<const0>\;
  in2_Addr_A(11) <= \<const0>\;
  in2_Addr_A(10) <= \<const0>\;
  in2_Addr_A(9) <= \<const0>\;
  in2_Addr_A(8) <= \<const0>\;
  in2_Addr_A(7) <= \<const0>\;
  in2_Addr_A(6) <= \<const0>\;
  in2_Addr_A(5 downto 2) <= \^in2_addr_a\(5 downto 2);
  in2_Addr_A(1) <= \<const0>\;
  in2_Addr_A(0) <= \<const0>\;
  in2_Addr_B(31) <= \<const0>\;
  in2_Addr_B(30) <= \<const0>\;
  in2_Addr_B(29) <= \<const0>\;
  in2_Addr_B(28) <= \<const0>\;
  in2_Addr_B(27) <= \<const0>\;
  in2_Addr_B(26) <= \<const0>\;
  in2_Addr_B(25) <= \<const0>\;
  in2_Addr_B(24) <= \<const0>\;
  in2_Addr_B(23) <= \<const0>\;
  in2_Addr_B(22) <= \<const0>\;
  in2_Addr_B(21) <= \<const0>\;
  in2_Addr_B(20) <= \<const0>\;
  in2_Addr_B(19) <= \<const0>\;
  in2_Addr_B(18) <= \<const0>\;
  in2_Addr_B(17) <= \<const0>\;
  in2_Addr_B(16) <= \<const0>\;
  in2_Addr_B(15) <= \<const0>\;
  in2_Addr_B(14) <= \<const0>\;
  in2_Addr_B(13) <= \<const0>\;
  in2_Addr_B(12) <= \<const0>\;
  in2_Addr_B(11) <= \<const0>\;
  in2_Addr_B(10) <= \<const0>\;
  in2_Addr_B(9) <= \<const0>\;
  in2_Addr_B(8) <= \<const0>\;
  in2_Addr_B(7) <= \<const0>\;
  in2_Addr_B(6) <= \<const0>\;
  in2_Addr_B(5 downto 4) <= \^in2_addr_b\(5 downto 4);
  in2_Addr_B(3 downto 2) <= \^in2_addr_a\(3 downto 2);
  in2_Addr_B(1) <= \<const0>\;
  in2_Addr_B(0) <= \<const0>\;
  in2_Clk_A <= \^ap_clk\;
  in2_Clk_B <= \^ap_clk\;
  in2_Din_A(31) <= \<const0>\;
  in2_Din_A(30) <= \<const0>\;
  in2_Din_A(29) <= \<const0>\;
  in2_Din_A(28) <= \<const0>\;
  in2_Din_A(27) <= \<const0>\;
  in2_Din_A(26) <= \<const0>\;
  in2_Din_A(25) <= \<const0>\;
  in2_Din_A(24) <= \<const0>\;
  in2_Din_A(23) <= \<const0>\;
  in2_Din_A(22) <= \<const0>\;
  in2_Din_A(21) <= \<const0>\;
  in2_Din_A(20) <= \<const0>\;
  in2_Din_A(19) <= \<const0>\;
  in2_Din_A(18) <= \<const0>\;
  in2_Din_A(17) <= \<const0>\;
  in2_Din_A(16) <= \<const0>\;
  in2_Din_A(15) <= \<const0>\;
  in2_Din_A(14) <= \<const0>\;
  in2_Din_A(13) <= \<const0>\;
  in2_Din_A(12) <= \<const0>\;
  in2_Din_A(11) <= \<const0>\;
  in2_Din_A(10) <= \<const0>\;
  in2_Din_A(9) <= \<const0>\;
  in2_Din_A(8) <= \<const0>\;
  in2_Din_A(7) <= \<const0>\;
  in2_Din_A(6) <= \<const0>\;
  in2_Din_A(5) <= \<const0>\;
  in2_Din_A(4) <= \<const0>\;
  in2_Din_A(3) <= \<const0>\;
  in2_Din_A(2) <= \<const0>\;
  in2_Din_A(1) <= \<const0>\;
  in2_Din_A(0) <= \<const0>\;
  in2_Din_B(31) <= \<const0>\;
  in2_Din_B(30) <= \<const0>\;
  in2_Din_B(29) <= \<const0>\;
  in2_Din_B(28) <= \<const0>\;
  in2_Din_B(27) <= \<const0>\;
  in2_Din_B(26) <= \<const0>\;
  in2_Din_B(25) <= \<const0>\;
  in2_Din_B(24) <= \<const0>\;
  in2_Din_B(23) <= \<const0>\;
  in2_Din_B(22) <= \<const0>\;
  in2_Din_B(21) <= \<const0>\;
  in2_Din_B(20) <= \<const0>\;
  in2_Din_B(19) <= \<const0>\;
  in2_Din_B(18) <= \<const0>\;
  in2_Din_B(17) <= \<const0>\;
  in2_Din_B(16) <= \<const0>\;
  in2_Din_B(15) <= \<const0>\;
  in2_Din_B(14) <= \<const0>\;
  in2_Din_B(13) <= \<const0>\;
  in2_Din_B(12) <= \<const0>\;
  in2_Din_B(11) <= \<const0>\;
  in2_Din_B(10) <= \<const0>\;
  in2_Din_B(9) <= \<const0>\;
  in2_Din_B(8) <= \<const0>\;
  in2_Din_B(7) <= \<const0>\;
  in2_Din_B(6) <= \<const0>\;
  in2_Din_B(5) <= \<const0>\;
  in2_Din_B(4) <= \<const0>\;
  in2_Din_B(3) <= \<const0>\;
  in2_Din_B(2) <= \<const0>\;
  in2_Din_B(1) <= \<const0>\;
  in2_Din_B(0) <= \<const0>\;
  in2_EN_A <= \^in1_en_a\;
  in2_EN_B <= \^in1_en_a\;
  in2_Rst_A <= \^out_r_rst_a\;
  in2_Rst_B <= \^out_r_rst_a\;
  in2_WEN_A(3) <= \<const0>\;
  in2_WEN_A(2) <= \<const0>\;
  in2_WEN_A(1) <= \<const0>\;
  in2_WEN_A(0) <= \<const0>\;
  in2_WEN_B(3) <= \<const0>\;
  in2_WEN_B(2) <= \<const0>\;
  in2_WEN_B(1) <= \<const0>\;
  in2_WEN_B(0) <= \<const0>\;
  out_r_Addr_A(31) <= \<const0>\;
  out_r_Addr_A(30) <= \<const0>\;
  out_r_Addr_A(29) <= \<const0>\;
  out_r_Addr_A(28) <= \<const0>\;
  out_r_Addr_A(27) <= \<const0>\;
  out_r_Addr_A(26) <= \<const0>\;
  out_r_Addr_A(25) <= \<const0>\;
  out_r_Addr_A(24) <= \<const0>\;
  out_r_Addr_A(23) <= \<const0>\;
  out_r_Addr_A(22) <= \<const0>\;
  out_r_Addr_A(21) <= \<const0>\;
  out_r_Addr_A(20) <= \<const0>\;
  out_r_Addr_A(19) <= \<const0>\;
  out_r_Addr_A(18) <= \<const0>\;
  out_r_Addr_A(17) <= \<const0>\;
  out_r_Addr_A(16) <= \<const0>\;
  out_r_Addr_A(15) <= \<const0>\;
  out_r_Addr_A(14) <= \<const0>\;
  out_r_Addr_A(13) <= \<const0>\;
  out_r_Addr_A(12) <= \<const0>\;
  out_r_Addr_A(11) <= \<const0>\;
  out_r_Addr_A(10) <= \<const0>\;
  out_r_Addr_A(9) <= \<const0>\;
  out_r_Addr_A(8) <= \<const0>\;
  out_r_Addr_A(7) <= \<const0>\;
  out_r_Addr_A(6) <= \<const0>\;
  out_r_Addr_A(5 downto 2) <= \^out_r_addr_a\(5 downto 2);
  out_r_Addr_A(1) <= \<const0>\;
  out_r_Addr_A(0) <= \<const0>\;
  out_r_Clk_A <= \^ap_clk\;
  out_r_Din_A(31 downto 0) <= \^out_r_din_a\(31 downto 0);
  out_r_EN_A <= \^out_r_en_a\;
  out_r_Rst_A <= \^out_r_rst_a\;
  out_r_WEN_A(3) <= \^out_r_wen_a\(0);
  out_r_WEN_A(2) <= \^out_r_wen_a\(0);
  out_r_WEN_A(1) <= \^out_r_wen_a\(0);
  out_r_WEN_A(0) <= \^out_r_wen_a\(0);
  s_axi_control_BRESP(1) <= \<const0>\;
  s_axi_control_BRESP(0) <= \<const0>\;
  s_axi_control_RDATA(31) <= \<const0>\;
  s_axi_control_RDATA(30) <= \<const0>\;
  s_axi_control_RDATA(29) <= \<const0>\;
  s_axi_control_RDATA(28) <= \<const0>\;
  s_axi_control_RDATA(27) <= \<const0>\;
  s_axi_control_RDATA(26) <= \<const0>\;
  s_axi_control_RDATA(25) <= \<const0>\;
  s_axi_control_RDATA(24) <= \<const0>\;
  s_axi_control_RDATA(23) <= \<const0>\;
  s_axi_control_RDATA(22) <= \<const0>\;
  s_axi_control_RDATA(21) <= \<const0>\;
  s_axi_control_RDATA(20) <= \<const0>\;
  s_axi_control_RDATA(19) <= \<const0>\;
  s_axi_control_RDATA(18) <= \<const0>\;
  s_axi_control_RDATA(17) <= \<const0>\;
  s_axi_control_RDATA(16) <= \<const0>\;
  s_axi_control_RDATA(15) <= \<const0>\;
  s_axi_control_RDATA(14) <= \<const0>\;
  s_axi_control_RDATA(13) <= \<const0>\;
  s_axi_control_RDATA(12) <= \<const0>\;
  s_axi_control_RDATA(11) <= \<const0>\;
  s_axi_control_RDATA(10) <= \<const0>\;
  s_axi_control_RDATA(9) <= \^s_axi_control_rdata\(9);
  s_axi_control_RDATA(8) <= \<const0>\;
  s_axi_control_RDATA(7) <= \^s_axi_control_rdata\(7);
  s_axi_control_RDATA(6) <= \<const0>\;
  s_axi_control_RDATA(5) <= \<const0>\;
  s_axi_control_RDATA(4 downto 0) <= \^s_axi_control_rdata\(4 downto 0);
  s_axi_control_RRESP(1) <= \<const0>\;
  s_axi_control_RRESP(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
\add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => ap_block_pp0_stage0_subdone,
      CLK => \^ap_clk\,
      D => \^in2_addr_a\(2),
      Q => \add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3_n_0\
    );
\add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => ap_block_pp0_stage0_subdone,
      CLK => \^ap_clk\,
      D => \^in2_addr_a\(3),
      Q => \add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3_n_0\
    );
\add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => ap_block_pp0_stage0_subdone,
      CLK => \^ap_clk\,
      D => flow_control_loop_delay_pipe_U_n_30,
      Q => \add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3_n_0\
    );
\add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => ap_block_pp0_stage0_subdone,
      CLK => \^ap_clk\,
      D => add_ln16_fu_313_p2(3),
      Q => \add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3_n_0\
    );
\add_ln16_reg_557_pp0_iter3_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \add_ln16_reg_557_pp0_iter2_reg_reg[0]_srl3_n_0\,
      Q => \^out_r_addr_a\(2),
      R => '0'
    );
\add_ln16_reg_557_pp0_iter3_reg_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \add_ln16_reg_557_pp0_iter2_reg_reg[1]_srl3_n_0\,
      Q => \^out_r_addr_a\(3),
      R => '0'
    );
\add_ln16_reg_557_pp0_iter3_reg_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \add_ln16_reg_557_pp0_iter2_reg_reg[2]_srl3_n_0\,
      Q => \^out_r_addr_a\(4),
      R => '0'
    );
\add_ln16_reg_557_pp0_iter3_reg_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \add_ln16_reg_557_pp0_iter2_reg_reg[3]_srl3_n_0\,
      Q => \^out_r_addr_a\(5),
      R => '0'
    );
ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2: unisim.vcomponents.SRL16E
     port map (
      A0 => '1',
      A1 => '0',
      A2 => '0',
      A3 => '0',
      CE => ap_block_pp0_stage0_subdone,
      CLK => \^ap_clk\,
      D => ap_loop_exit_ready,
      Q => ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2_n_0
    );
ap_condition_exit_pp0_iter0_stage0_pp0_iter3_reg_reg: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => ap_condition_exit_pp0_iter0_stage0_pp0_iter2_reg_reg_srl2_n_0,
      Q => ap_loop_exit_ready_pp0_iter3_reg,
      R => '0'
    );
ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg_reg: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => ap_loop_exit_ready_pp0_iter3_reg,
      Q => ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg,
      R => '0'
    );
ap_done_reg_reg_inv: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => \^ap_clk\,
      CE => '1',
      D => control_s_axi_U_n_8,
      Q => ap_block_pp0_stage0_subdone,
      R => '0'
    );
ap_enable_reg_pp0_iter1_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => ap_start_int,
      Q => ap_enable_reg_pp0_iter1,
      R => \^out_r_rst_a\
    );
ap_enable_reg_pp0_iter2_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => ap_enable_reg_pp0_iter1,
      Q => ap_enable_reg_pp0_iter2,
      R => \^out_r_rst_a\
    );
ap_enable_reg_pp0_iter3_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => ap_enable_reg_pp0_iter2,
      Q => ap_enable_reg_pp0_iter3,
      R => \^out_r_rst_a\
    );
ap_enable_reg_pp0_iter4_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => ap_enable_reg_pp0_iter3,
      Q => ap_enable_reg_pp0_iter4,
      R => \^out_r_rst_a\
    );
ap_loop_exit_ready_pp0_iter4_reg_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"E2"
    )
        port map (
      I0 => ap_loop_exit_ready_pp0_iter4_reg,
      I1 => ap_block_pp0_stage0_subdone,
      I2 => ap_loop_exit_ready_pp0_iter3_reg,
      O => ap_loop_exit_ready_pp0_iter4_reg_i_1_n_0
    );
ap_loop_exit_ready_pp0_iter4_reg_reg: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => '1',
      D => ap_loop_exit_ready_pp0_iter4_reg_i_1_n_0,
      Q => ap_loop_exit_ready_pp0_iter4_reg,
      R => '0'
    );
ap_rst_n_inv_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => \^ap_clk\,
      CE => '1',
      D => ap_rst_reg_1,
      Q => \^out_r_rst_a\,
      R => '0'
    );
ap_rst_reg_1_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => \^ap_clk\,
      CE => '1',
      D => ap_rst_reg_2,
      Q => ap_rst_reg_1,
      R => '0'
    );
ap_rst_reg_2_i_1: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => ap_rst_n,
      O => ap_rst_reg_2_i_1_n_0
    );
ap_rst_reg_2_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '1'
    )
        port map (
      C => \^ap_clk\,
      CE => '1',
      D => ap_rst_reg_2_i_1_n_0,
      Q => ap_rst_reg_2,
      R => '0'
    );
control_s_axi_U: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_control_s_axi
     port map (
      \FSM_onehot_rstate_reg[1]_0\ => s_axi_control_ARREADY,
      \FSM_onehot_wstate_reg[1]_0\ => s_axi_control_AWREADY,
      \FSM_onehot_wstate_reg[2]_0\ => s_axi_control_WREADY,
      ap_block_pp0_stage0_subdone => ap_block_pp0_stage0_subdone,
      ap_clk => \^ap_clk\,
      ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg => ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg,
      ap_enable_reg_pp0_iter1 => ap_enable_reg_pp0_iter1,
      ap_enable_reg_pp0_iter2 => ap_enable_reg_pp0_iter2,
      ap_enable_reg_pp0_iter3 => ap_enable_reg_pp0_iter3,
      ap_enable_reg_pp0_iter4 => ap_enable_reg_pp0_iter4,
      ap_loop_exit_ready_pp0_iter4_reg => ap_loop_exit_ready_pp0_iter4_reg,
      ap_loop_exit_ready_pp0_iter4_reg_reg => control_s_axi_U_n_8,
      ap_start => ap_start,
      ap_start_int => ap_start_int,
      int_task_ap_done_reg_0 => \^out_r_rst_a\,
      interrupt => interrupt,
      rewind_ap_ready_reg => rewind_ap_ready_reg,
      s_axi_control_ARADDR(3 downto 0) => s_axi_control_ARADDR(3 downto 0),
      s_axi_control_ARVALID => s_axi_control_ARVALID,
      s_axi_control_AWADDR(1 downto 0) => s_axi_control_AWADDR(3 downto 2),
      s_axi_control_AWVALID => s_axi_control_AWVALID,
      s_axi_control_BREADY => s_axi_control_BREADY,
      s_axi_control_BVALID => s_axi_control_BVALID,
      s_axi_control_RDATA(6) => \^s_axi_control_rdata\(9),
      s_axi_control_RDATA(5) => \^s_axi_control_rdata\(7),
      s_axi_control_RDATA(4 downto 0) => \^s_axi_control_rdata\(4 downto 0),
      s_axi_control_RREADY => s_axi_control_RREADY,
      s_axi_control_RVALID => s_axi_control_RVALID,
      s_axi_control_WDATA(3) => s_axi_control_WDATA(7),
      s_axi_control_WDATA(2) => s_axi_control_WDATA(4),
      s_axi_control_WDATA(1 downto 0) => s_axi_control_WDATA(1 downto 0),
      s_axi_control_WSTRB(0) => s_axi_control_WSTRB(0),
      s_axi_control_WVALID => s_axi_control_WVALID
    );
flow_control_loop_delay_pipe_U: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_flow_control_loop_delay_pipe
     port map (
      D(4) => add_ln9_1_fu_415_p2(4),
      D(3) => flow_control_loop_delay_pipe_U_n_3,
      D(2) => add_ln9_1_fu_415_p2(2),
      D(1) => flow_control_loop_delay_pipe_U_n_5,
      D(0) => add_ln9_1_fu_415_p2(0),
      Q(4 downto 0) => indvar_flatten131_fu_74(4 downto 0),
      SR(0) => flow_control_loop_delay_pipe_U_n_26,
      add_ln16_fu_313_p2(0) => add_ln16_fu_313_p2(3),
      ap_block_pp0_stage0_subdone => ap_block_pp0_stage0_subdone,
      ap_clk => \^ap_clk\,
      ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg => ap_condition_exit_pp0_iter0_stage0_pp0_iter4_reg,
      ap_enable_reg_pp0_iter1 => ap_enable_reg_pp0_iter1,
      ap_loop_exit_ready => ap_loop_exit_ready,
      ap_start => ap_start,
      \i2_fu_78_reg[0]\ => flow_control_loop_delay_pipe_U_n_30,
      \icmp_ln108_reg_161_reg[0]\ => flow_control_loop_delay_pipe_U_n_1,
      \icmp_ln108_reg_161_reg[0]_0\ => \icmp_ln108_reg_161_reg_n_0_[0]\,
      icmp_ln10_fu_435_p2 => icmp_ln10_fu_435_p2,
      icmp_ln10_reg_591 => icmp_ln10_reg_591,
      icmp_ln9_fu_441_p2 => icmp_ln9_fu_441_p2,
      icmp_ln9_reg_596 => icmp_ln9_reg_596,
      in1_Addr_A(1 downto 0) => \^in1_addr_a\(5 downto 4),
      in1_Addr_B(1 downto 0) => \^in1_addr_b\(5 downto 4),
      \in1_Addr_B[5]\(1 downto 0) => i2_fu_78(1 downto 0),
      in2_Addr_A(0) => \^in2_addr_a\(5),
      \in2_Addr_A[4]\(2 downto 0) => j4_fu_86(2 downto 0),
      in2_Addr_B(3 downto 2) => \^in2_addr_b\(5 downto 4),
      in2_Addr_B(1 downto 0) => \^in2_addr_a\(3 downto 2),
      indvar_flatten3_fu_82(4 downto 0) => indvar_flatten3_fu_82(4 downto 0),
      \indvar_flatten3_fu_82_reg[0]\(0) => select_ln10_1_fu_427_p3(0),
      \indvar_flatten3_fu_82_reg[0]_0\ => flow_control_loop_delay_pipe_U_n_33,
      \indvar_flatten3_fu_82_reg[1]\ => flow_control_loop_delay_pipe_U_n_32,
      \indvar_flatten3_fu_82_reg[2]\ => flow_control_loop_delay_pipe_U_n_29,
      \indvar_flatten3_fu_82_reg[4]\ => flow_control_loop_delay_pipe_U_n_16,
      \j4_fu_86_reg[0]\ => \^in2_addr_a\(4),
      \k5_fu_90_reg[1]\ => flow_control_loop_delay_pipe_U_n_28,
      \k5_fu_90_reg[2]\(1 downto 0) => k5_fu_90(2 downto 1),
      p_1_in => p_1_in,
      rewind_ap_ready_reg => rewind_ap_ready_reg,
      rewind_ap_ready_reg_reg_0 => \^in1_en_a\,
      rewind_ap_ready_reg_reg_1 => flow_control_loop_delay_pipe_U_n_31,
      rewind_ap_ready_reg_reg_2 => \^out_r_rst_a\,
      xor_ln12_reg_586 => xor_ln12_reg_586,
      \xor_ln12_reg_586_reg[0]\(1) => tmp_5_fu_401_p3,
      \xor_ln12_reg_586_reg[0]\(0) => flow_control_loop_delay_pipe_U_n_9
    );
\i2_fu_78_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => \^in1_addr_a\(4),
      Q => i2_fu_78(0),
      R => '0'
    );
\i2_fu_78_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => \^in1_addr_a\(5),
      Q => i2_fu_78(1),
      R => '0'
    );
\icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2\: unisim.vcomponents.SRL16E
     port map (
      A0 => '1',
      A1 => '0',
      A2 => '0',
      A3 => '0',
      CE => ap_block_pp0_stage0_subdone,
      CLK => \^ap_clk\,
      D => \icmp_ln108_reg_161_reg_n_0_[0]\,
      Q => \icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2_n_0\
    );
\icmp_ln108_reg_161_pp0_iter3_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \icmp_ln108_reg_161_pp0_iter2_reg_reg[0]_srl2_n_0\,
      Q => icmp_ln108_reg_161_pp0_iter3_reg,
      R => '0'
    );
\icmp_ln108_reg_161_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => '1',
      D => flow_control_loop_delay_pipe_U_n_1,
      Q => \icmp_ln108_reg_161_reg_n_0_[0]\,
      R => '0'
    );
\icmp_ln10_reg_591_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => icmp_ln10_fu_435_p2,
      Q => icmp_ln10_reg_591,
      R => '0'
    );
\icmp_ln9_reg_596_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => icmp_ln9_fu_441_p2,
      Q => icmp_ln9_reg_596,
      R => '0'
    );
\indvar_flatten131_fu_74_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => add_ln9_1_fu_415_p2(0),
      Q => indvar_flatten131_fu_74(0),
      R => '0'
    );
\indvar_flatten131_fu_74_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => flow_control_loop_delay_pipe_U_n_5,
      Q => indvar_flatten131_fu_74(1),
      R => '0'
    );
\indvar_flatten131_fu_74_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => add_ln9_1_fu_415_p2(2),
      Q => indvar_flatten131_fu_74(2),
      R => '0'
    );
\indvar_flatten131_fu_74_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => flow_control_loop_delay_pipe_U_n_3,
      Q => indvar_flatten131_fu_74(3),
      R => '0'
    );
\indvar_flatten131_fu_74_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => add_ln9_1_fu_415_p2(4),
      Q => indvar_flatten131_fu_74(4),
      R => '0'
    );
\indvar_flatten3_fu_82_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => select_ln10_1_fu_427_p3(0),
      Q => indvar_flatten3_fu_82(0),
      R => '0'
    );
\indvar_flatten3_fu_82_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => flow_control_loop_delay_pipe_U_n_33,
      Q => indvar_flatten3_fu_82(1),
      R => flow_control_loop_delay_pipe_U_n_31
    );
\indvar_flatten3_fu_82_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => flow_control_loop_delay_pipe_U_n_32,
      Q => indvar_flatten3_fu_82(2),
      R => flow_control_loop_delay_pipe_U_n_31
    );
\indvar_flatten3_fu_82_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => flow_control_loop_delay_pipe_U_n_29,
      Q => indvar_flatten3_fu_82(3),
      R => flow_control_loop_delay_pipe_U_n_31
    );
\indvar_flatten3_fu_82_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => flow_control_loop_delay_pipe_U_n_16,
      Q => indvar_flatten3_fu_82(4),
      R => flow_control_loop_delay_pipe_U_n_31
    );
\j4_fu_86_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => \^in2_addr_a\(2),
      Q => j4_fu_86(0),
      R => '0'
    );
\j4_fu_86_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => \^in2_addr_a\(3),
      Q => j4_fu_86(1),
      R => '0'
    );
\j4_fu_86_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => \^in2_addr_b\(4),
      Q => j4_fu_86(2),
      R => '0'
    );
\k5_fu_90_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => flow_control_loop_delay_pipe_U_n_9,
      Q => k5_fu_90(1),
      R => '0'
    );
\k5_fu_90_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => tmp_5_fu_401_p3,
      Q => k5_fu_90(2),
      R => '0'
    );
mul_32s_32s_32_2_1_U1: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_mul_32s_32s_32_2_1
     port map (
      CEB2 => p_5_in,
      D(31 downto 16) => \buff0_reg__1\(31 downto 16),
      D(15) => mul_32s_32s_32_2_1_U1_n_16,
      D(14) => mul_32s_32s_32_2_1_U1_n_17,
      D(13) => mul_32s_32s_32_2_1_U1_n_18,
      D(12) => mul_32s_32s_32_2_1_U1_n_19,
      D(11) => mul_32s_32s_32_2_1_U1_n_20,
      D(10) => mul_32s_32s_32_2_1_U1_n_21,
      D(9) => mul_32s_32s_32_2_1_U1_n_22,
      D(8) => mul_32s_32s_32_2_1_U1_n_23,
      D(7) => mul_32s_32s_32_2_1_U1_n_24,
      D(6) => mul_32s_32s_32_2_1_U1_n_25,
      D(5) => mul_32s_32s_32_2_1_U1_n_26,
      D(4) => mul_32s_32s_32_2_1_U1_n_27,
      D(3) => mul_32s_32s_32_2_1_U1_n_28,
      D(2) => mul_32s_32s_32_2_1_U1_n_29,
      D(1) => mul_32s_32s_32_2_1_U1_n_30,
      D(0) => mul_32s_32s_32_2_1_U1_n_31,
      ap_block_pp0_stage0_subdone => ap_block_pp0_stage0_subdone,
      ap_clk => \^ap_clk\,
      in1_Dout_B(31 downto 0) => in1_Dout_B(31 downto 0),
      in2_Dout_B(31 downto 0) => in2_Dout_B(31 downto 0)
    );
mul_32s_32s_32_2_1_U2: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul_mul_32s_32s_32_2_1_0
     port map (
      CEB2 => p_5_in,
      D(31 downto 16) => \buff0_reg__1_0\(31 downto 16),
      D(15) => mul_32s_32s_32_2_1_U2_n_17,
      D(14) => mul_32s_32s_32_2_1_U2_n_18,
      D(13) => mul_32s_32s_32_2_1_U2_n_19,
      D(12) => mul_32s_32s_32_2_1_U2_n_20,
      D(11) => mul_32s_32s_32_2_1_U2_n_21,
      D(10) => mul_32s_32s_32_2_1_U2_n_22,
      D(9) => mul_32s_32s_32_2_1_U2_n_23,
      D(8) => mul_32s_32s_32_2_1_U2_n_24,
      D(7) => mul_32s_32s_32_2_1_U2_n_25,
      D(6) => mul_32s_32s_32_2_1_U2_n_26,
      D(5) => mul_32s_32s_32_2_1_U2_n_27,
      D(4) => mul_32s_32s_32_2_1_U2_n_28,
      D(3) => mul_32s_32s_32_2_1_U2_n_29,
      D(2) => mul_32s_32s_32_2_1_U2_n_30,
      D(1) => mul_32s_32s_32_2_1_U2_n_31,
      D(0) => mul_32s_32s_32_2_1_U2_n_32,
      ap_block_pp0_stage0_subdone => ap_block_pp0_stage0_subdone,
      ap_clk => \^ap_clk\,
      ap_enable_reg_pp0_iter1 => ap_enable_reg_pp0_iter1,
      in1_Dout_A(31 downto 0) => in1_Dout_A(31 downto 0),
      in2_Dout_A(31 downto 0) => in2_Dout_A(31 downto 0)
    );
\mul_ln14_1_reg_625_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_32,
      Q => mul_ln14_1_reg_625(0),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_22,
      Q => mul_ln14_1_reg_625(10),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_21,
      Q => mul_ln14_1_reg_625(11),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_20,
      Q => mul_ln14_1_reg_625(12),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_19,
      Q => mul_ln14_1_reg_625(13),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_18,
      Q => mul_ln14_1_reg_625(14),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_17,
      Q => mul_ln14_1_reg_625(15),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(16),
      Q => mul_ln14_1_reg_625(16),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(17),
      Q => mul_ln14_1_reg_625(17),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(18),
      Q => mul_ln14_1_reg_625(18),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(19),
      Q => mul_ln14_1_reg_625(19),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_31,
      Q => mul_ln14_1_reg_625(1),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(20),
      Q => mul_ln14_1_reg_625(20),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(21),
      Q => mul_ln14_1_reg_625(21),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(22),
      Q => mul_ln14_1_reg_625(22),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(23),
      Q => mul_ln14_1_reg_625(23),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(24),
      Q => mul_ln14_1_reg_625(24),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(25),
      Q => mul_ln14_1_reg_625(25),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(26),
      Q => mul_ln14_1_reg_625(26),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(27),
      Q => mul_ln14_1_reg_625(27),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(28),
      Q => mul_ln14_1_reg_625(28),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(29),
      Q => mul_ln14_1_reg_625(29),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_30,
      Q => mul_ln14_1_reg_625(2),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(30),
      Q => mul_ln14_1_reg_625(30),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1_0\(31),
      Q => mul_ln14_1_reg_625(31),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_29,
      Q => mul_ln14_1_reg_625(3),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_28,
      Q => mul_ln14_1_reg_625(4),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_27,
      Q => mul_ln14_1_reg_625(5),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_26,
      Q => mul_ln14_1_reg_625(6),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_25,
      Q => mul_ln14_1_reg_625(7),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_24,
      Q => mul_ln14_1_reg_625(8),
      R => '0'
    );
\mul_ln14_1_reg_625_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U2_n_23,
      Q => mul_ln14_1_reg_625(9),
      R => '0'
    );
\mul_ln14_reg_620_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_31,
      Q => mul_ln14_reg_620(0),
      R => '0'
    );
\mul_ln14_reg_620_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_21,
      Q => mul_ln14_reg_620(10),
      R => '0'
    );
\mul_ln14_reg_620_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_20,
      Q => mul_ln14_reg_620(11),
      R => '0'
    );
\mul_ln14_reg_620_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_19,
      Q => mul_ln14_reg_620(12),
      R => '0'
    );
\mul_ln14_reg_620_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_18,
      Q => mul_ln14_reg_620(13),
      R => '0'
    );
\mul_ln14_reg_620_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_17,
      Q => mul_ln14_reg_620(14),
      R => '0'
    );
\mul_ln14_reg_620_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_16,
      Q => mul_ln14_reg_620(15),
      R => '0'
    );
\mul_ln14_reg_620_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(16),
      Q => mul_ln14_reg_620(16),
      R => '0'
    );
\mul_ln14_reg_620_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(17),
      Q => mul_ln14_reg_620(17),
      R => '0'
    );
\mul_ln14_reg_620_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(18),
      Q => mul_ln14_reg_620(18),
      R => '0'
    );
\mul_ln14_reg_620_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(19),
      Q => mul_ln14_reg_620(19),
      R => '0'
    );
\mul_ln14_reg_620_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_30,
      Q => mul_ln14_reg_620(1),
      R => '0'
    );
\mul_ln14_reg_620_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(20),
      Q => mul_ln14_reg_620(20),
      R => '0'
    );
\mul_ln14_reg_620_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(21),
      Q => mul_ln14_reg_620(21),
      R => '0'
    );
\mul_ln14_reg_620_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(22),
      Q => mul_ln14_reg_620(22),
      R => '0'
    );
\mul_ln14_reg_620_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(23),
      Q => mul_ln14_reg_620(23),
      R => '0'
    );
\mul_ln14_reg_620_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(24),
      Q => mul_ln14_reg_620(24),
      R => '0'
    );
\mul_ln14_reg_620_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(25),
      Q => mul_ln14_reg_620(25),
      R => '0'
    );
\mul_ln14_reg_620_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(26),
      Q => mul_ln14_reg_620(26),
      R => '0'
    );
\mul_ln14_reg_620_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(27),
      Q => mul_ln14_reg_620(27),
      R => '0'
    );
\mul_ln14_reg_620_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(28),
      Q => mul_ln14_reg_620(28),
      R => '0'
    );
\mul_ln14_reg_620_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(29),
      Q => mul_ln14_reg_620(29),
      R => '0'
    );
\mul_ln14_reg_620_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_29,
      Q => mul_ln14_reg_620(2),
      R => '0'
    );
\mul_ln14_reg_620_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(30),
      Q => mul_ln14_reg_620(30),
      R => '0'
    );
\mul_ln14_reg_620_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \buff0_reg__1\(31),
      Q => mul_ln14_reg_620(31),
      R => '0'
    );
\mul_ln14_reg_620_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_28,
      Q => mul_ln14_reg_620(3),
      R => '0'
    );
\mul_ln14_reg_620_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_27,
      Q => mul_ln14_reg_620(4),
      R => '0'
    );
\mul_ln14_reg_620_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_26,
      Q => mul_ln14_reg_620(5),
      R => '0'
    );
\mul_ln14_reg_620_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_25,
      Q => mul_ln14_reg_620(6),
      R => '0'
    );
\mul_ln14_reg_620_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_24,
      Q => mul_ln14_reg_620(7),
      R => '0'
    );
\mul_ln14_reg_620_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_23,
      Q => mul_ln14_reg_620(8),
      R => '0'
    );
\mul_ln14_reg_620_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => mul_32s_32s_32_2_1_U1_n_22,
      Q => mul_ln14_reg_620(9),
      R => '0'
    );
\or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => ap_block_pp0_stage0_subdone,
      CLK => \^ap_clk\,
      D => p_1_in,
      Q => \or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3_n_0\
    );
\or_ln9_reg_552_pp0_iter3_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \or_ln9_reg_552_pp0_iter2_reg_reg[0]_srl3_n_0\,
      Q => or_ln9_reg_552_pp0_iter3_reg,
      R => '0'
    );
\out_r_Din_A[0]_INST_0\: unisim.vcomponents.CARRY8
     port map (
      CI => '0',
      CI_TOP => '0',
      CO(7) => \out_r_Din_A[0]_INST_0_n_0\,
      CO(6) => \out_r_Din_A[0]_INST_0_n_1\,
      CO(5) => \out_r_Din_A[0]_INST_0_n_2\,
      CO(4) => \out_r_Din_A[0]_INST_0_n_3\,
      CO(3) => \out_r_Din_A[0]_INST_0_n_4\,
      CO(2) => \out_r_Din_A[0]_INST_0_n_5\,
      CO(1) => \out_r_Din_A[0]_INST_0_n_6\,
      CO(0) => \out_r_Din_A[0]_INST_0_n_7\,
      DI(7) => \out_r_Din_A[0]_INST_0_i_1_n_0\,
      DI(6) => \out_r_Din_A[0]_INST_0_i_2_n_0\,
      DI(5) => \out_r_Din_A[0]_INST_0_i_3_n_0\,
      DI(4) => \out_r_Din_A[0]_INST_0_i_4_n_0\,
      DI(3) => \out_r_Din_A[0]_INST_0_i_5_n_0\,
      DI(2) => \out_r_Din_A[0]_INST_0_i_6_n_0\,
      DI(1) => \out_r_Din_A[0]_INST_0_i_7_n_0\,
      DI(0) => '0',
      O(7 downto 0) => \^out_r_din_a\(7 downto 0),
      S(7) => \out_r_Din_A[0]_INST_0_i_8_n_0\,
      S(6) => \out_r_Din_A[0]_INST_0_i_9_n_0\,
      S(5) => \out_r_Din_A[0]_INST_0_i_10_n_0\,
      S(4) => \out_r_Din_A[0]_INST_0_i_11_n_0\,
      S(3) => \out_r_Din_A[0]_INST_0_i_12_n_0\,
      S(2) => \out_r_Din_A[0]_INST_0_i_13_n_0\,
      S(1) => \out_r_Din_A[0]_INST_0_i_14_n_0\,
      S(0) => \out_r_Din_A[0]_INST_0_i_15_n_0\
    );
\out_r_Din_A[0]_INST_0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(6),
      I1 => mul_ln14_1_reg_625(6),
      I2 => \sum6_fu_94_reg_n_0_[6]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[0]_INST_0_i_1_n_0\
    );
\out_r_Din_A[0]_INST_0_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[0]_INST_0_i_3_n_0\,
      I1 => mul_ln14_1_reg_625(5),
      I2 => mul_ln14_reg_620(5),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[5]\,
      O => \out_r_Din_A[0]_INST_0_i_10_n_0\
    );
\out_r_Din_A[0]_INST_0_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[0]_INST_0_i_4_n_0\,
      I1 => mul_ln14_1_reg_625(4),
      I2 => mul_ln14_reg_620(4),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[4]\,
      O => \out_r_Din_A[0]_INST_0_i_11_n_0\
    );
\out_r_Din_A[0]_INST_0_i_12\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[0]_INST_0_i_5_n_0\,
      I1 => mul_ln14_1_reg_625(3),
      I2 => mul_ln14_reg_620(3),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[3]\,
      O => \out_r_Din_A[0]_INST_0_i_12_n_0\
    );
\out_r_Din_A[0]_INST_0_i_13\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[0]_INST_0_i_6_n_0\,
      I1 => mul_ln14_1_reg_625(2),
      I2 => mul_ln14_reg_620(2),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[2]\,
      O => \out_r_Din_A[0]_INST_0_i_13_n_0\
    );
\out_r_Din_A[0]_INST_0_i_14\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[0]_INST_0_i_7_n_0\,
      I1 => mul_ln14_1_reg_625(1),
      I2 => mul_ln14_reg_620(1),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[1]\,
      O => \out_r_Din_A[0]_INST_0_i_14_n_0\
    );
\out_r_Din_A[0]_INST_0_i_15\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"66966666"
    )
        port map (
      I0 => mul_ln14_reg_620(0),
      I1 => mul_ln14_1_reg_625(0),
      I2 => \sum6_fu_94_reg_n_0_[0]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[0]_INST_0_i_15_n_0\
    );
\out_r_Din_A[0]_INST_0_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(5),
      I1 => mul_ln14_1_reg_625(5),
      I2 => \sum6_fu_94_reg_n_0_[5]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[0]_INST_0_i_2_n_0\
    );
\out_r_Din_A[0]_INST_0_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(4),
      I1 => mul_ln14_1_reg_625(4),
      I2 => \sum6_fu_94_reg_n_0_[4]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[0]_INST_0_i_3_n_0\
    );
\out_r_Din_A[0]_INST_0_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(3),
      I1 => mul_ln14_1_reg_625(3),
      I2 => \sum6_fu_94_reg_n_0_[3]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[0]_INST_0_i_4_n_0\
    );
\out_r_Din_A[0]_INST_0_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(2),
      I1 => mul_ln14_1_reg_625(2),
      I2 => \sum6_fu_94_reg_n_0_[2]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[0]_INST_0_i_5_n_0\
    );
\out_r_Din_A[0]_INST_0_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(1),
      I1 => mul_ln14_1_reg_625(1),
      I2 => \sum6_fu_94_reg_n_0_[1]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[0]_INST_0_i_6_n_0\
    );
\out_r_Din_A[0]_INST_0_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(0),
      I1 => mul_ln14_1_reg_625(0),
      I2 => \sum6_fu_94_reg_n_0_[0]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[0]_INST_0_i_7_n_0\
    );
\out_r_Din_A[0]_INST_0_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[0]_INST_0_i_1_n_0\,
      I1 => mul_ln14_1_reg_625(7),
      I2 => mul_ln14_reg_620(7),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[7]\,
      O => \out_r_Din_A[0]_INST_0_i_8_n_0\
    );
\out_r_Din_A[0]_INST_0_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[0]_INST_0_i_2_n_0\,
      I1 => mul_ln14_1_reg_625(6),
      I2 => mul_ln14_reg_620(6),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[6]\,
      O => \out_r_Din_A[0]_INST_0_i_9_n_0\
    );
\out_r_Din_A[16]_INST_0\: unisim.vcomponents.CARRY8
     port map (
      CI => \out_r_Din_A[8]_INST_0_n_0\,
      CI_TOP => '0',
      CO(7) => \out_r_Din_A[16]_INST_0_n_0\,
      CO(6) => \out_r_Din_A[16]_INST_0_n_1\,
      CO(5) => \out_r_Din_A[16]_INST_0_n_2\,
      CO(4) => \out_r_Din_A[16]_INST_0_n_3\,
      CO(3) => \out_r_Din_A[16]_INST_0_n_4\,
      CO(2) => \out_r_Din_A[16]_INST_0_n_5\,
      CO(1) => \out_r_Din_A[16]_INST_0_n_6\,
      CO(0) => \out_r_Din_A[16]_INST_0_n_7\,
      DI(7) => \out_r_Din_A[16]_INST_0_i_1_n_0\,
      DI(6) => \out_r_Din_A[16]_INST_0_i_2_n_0\,
      DI(5) => \out_r_Din_A[16]_INST_0_i_3_n_0\,
      DI(4) => \out_r_Din_A[16]_INST_0_i_4_n_0\,
      DI(3) => \out_r_Din_A[16]_INST_0_i_5_n_0\,
      DI(2) => \out_r_Din_A[16]_INST_0_i_6_n_0\,
      DI(1) => \out_r_Din_A[16]_INST_0_i_7_n_0\,
      DI(0) => \out_r_Din_A[16]_INST_0_i_8_n_0\,
      O(7 downto 0) => \^out_r_din_a\(23 downto 16),
      S(7) => \out_r_Din_A[16]_INST_0_i_9_n_0\,
      S(6) => \out_r_Din_A[16]_INST_0_i_10_n_0\,
      S(5) => \out_r_Din_A[16]_INST_0_i_11_n_0\,
      S(4) => \out_r_Din_A[16]_INST_0_i_12_n_0\,
      S(3) => \out_r_Din_A[16]_INST_0_i_13_n_0\,
      S(2) => \out_r_Din_A[16]_INST_0_i_14_n_0\,
      S(1) => \out_r_Din_A[16]_INST_0_i_15_n_0\,
      S(0) => \out_r_Din_A[16]_INST_0_i_16_n_0\
    );
\out_r_Din_A[16]_INST_0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(22),
      I1 => mul_ln14_1_reg_625(22),
      I2 => \sum6_fu_94_reg_n_0_[22]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[16]_INST_0_i_1_n_0\
    );
\out_r_Din_A[16]_INST_0_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[16]_INST_0_i_2_n_0\,
      I1 => mul_ln14_1_reg_625(22),
      I2 => mul_ln14_reg_620(22),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[22]\,
      O => \out_r_Din_A[16]_INST_0_i_10_n_0\
    );
\out_r_Din_A[16]_INST_0_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[16]_INST_0_i_3_n_0\,
      I1 => mul_ln14_1_reg_625(21),
      I2 => mul_ln14_reg_620(21),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[21]\,
      O => \out_r_Din_A[16]_INST_0_i_11_n_0\
    );
\out_r_Din_A[16]_INST_0_i_12\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[16]_INST_0_i_4_n_0\,
      I1 => mul_ln14_1_reg_625(20),
      I2 => mul_ln14_reg_620(20),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[20]\,
      O => \out_r_Din_A[16]_INST_0_i_12_n_0\
    );
\out_r_Din_A[16]_INST_0_i_13\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[16]_INST_0_i_5_n_0\,
      I1 => mul_ln14_1_reg_625(19),
      I2 => mul_ln14_reg_620(19),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[19]\,
      O => \out_r_Din_A[16]_INST_0_i_13_n_0\
    );
\out_r_Din_A[16]_INST_0_i_14\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[16]_INST_0_i_6_n_0\,
      I1 => mul_ln14_1_reg_625(18),
      I2 => mul_ln14_reg_620(18),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[18]\,
      O => \out_r_Din_A[16]_INST_0_i_14_n_0\
    );
\out_r_Din_A[16]_INST_0_i_15\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[16]_INST_0_i_7_n_0\,
      I1 => mul_ln14_1_reg_625(17),
      I2 => mul_ln14_reg_620(17),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[17]\,
      O => \out_r_Din_A[16]_INST_0_i_15_n_0\
    );
\out_r_Din_A[16]_INST_0_i_16\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[16]_INST_0_i_8_n_0\,
      I1 => mul_ln14_1_reg_625(16),
      I2 => mul_ln14_reg_620(16),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[16]\,
      O => \out_r_Din_A[16]_INST_0_i_16_n_0\
    );
\out_r_Din_A[16]_INST_0_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(21),
      I1 => mul_ln14_1_reg_625(21),
      I2 => \sum6_fu_94_reg_n_0_[21]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[16]_INST_0_i_2_n_0\
    );
\out_r_Din_A[16]_INST_0_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(20),
      I1 => mul_ln14_1_reg_625(20),
      I2 => \sum6_fu_94_reg_n_0_[20]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[16]_INST_0_i_3_n_0\
    );
\out_r_Din_A[16]_INST_0_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(19),
      I1 => mul_ln14_1_reg_625(19),
      I2 => \sum6_fu_94_reg_n_0_[19]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[16]_INST_0_i_4_n_0\
    );
\out_r_Din_A[16]_INST_0_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(18),
      I1 => mul_ln14_1_reg_625(18),
      I2 => \sum6_fu_94_reg_n_0_[18]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[16]_INST_0_i_5_n_0\
    );
\out_r_Din_A[16]_INST_0_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(17),
      I1 => mul_ln14_1_reg_625(17),
      I2 => \sum6_fu_94_reg_n_0_[17]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[16]_INST_0_i_6_n_0\
    );
\out_r_Din_A[16]_INST_0_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(16),
      I1 => mul_ln14_1_reg_625(16),
      I2 => \sum6_fu_94_reg_n_0_[16]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[16]_INST_0_i_7_n_0\
    );
\out_r_Din_A[16]_INST_0_i_8\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(15),
      I1 => mul_ln14_1_reg_625(15),
      I2 => \sum6_fu_94_reg_n_0_[15]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[16]_INST_0_i_8_n_0\
    );
\out_r_Din_A[16]_INST_0_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[16]_INST_0_i_1_n_0\,
      I1 => mul_ln14_1_reg_625(23),
      I2 => mul_ln14_reg_620(23),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[23]\,
      O => \out_r_Din_A[16]_INST_0_i_9_n_0\
    );
\out_r_Din_A[24]_INST_0\: unisim.vcomponents.CARRY8
     port map (
      CI => \out_r_Din_A[16]_INST_0_n_0\,
      CI_TOP => '0',
      CO(7) => \NLW_out_r_Din_A[24]_INST_0_CO_UNCONNECTED\(7),
      CO(6) => \out_r_Din_A[24]_INST_0_n_1\,
      CO(5) => \out_r_Din_A[24]_INST_0_n_2\,
      CO(4) => \out_r_Din_A[24]_INST_0_n_3\,
      CO(3) => \out_r_Din_A[24]_INST_0_n_4\,
      CO(2) => \out_r_Din_A[24]_INST_0_n_5\,
      CO(1) => \out_r_Din_A[24]_INST_0_n_6\,
      CO(0) => \out_r_Din_A[24]_INST_0_n_7\,
      DI(7) => '0',
      DI(6) => \out_r_Din_A[24]_INST_0_i_1_n_0\,
      DI(5) => \out_r_Din_A[24]_INST_0_i_2_n_0\,
      DI(4) => \out_r_Din_A[24]_INST_0_i_3_n_0\,
      DI(3) => \out_r_Din_A[24]_INST_0_i_4_n_0\,
      DI(2) => \out_r_Din_A[24]_INST_0_i_5_n_0\,
      DI(1) => \out_r_Din_A[24]_INST_0_i_6_n_0\,
      DI(0) => \out_r_Din_A[24]_INST_0_i_7_n_0\,
      O(7 downto 0) => \^out_r_din_a\(31 downto 24),
      S(7) => \out_r_Din_A[24]_INST_0_i_8_n_0\,
      S(6) => \out_r_Din_A[24]_INST_0_i_9_n_0\,
      S(5) => \out_r_Din_A[24]_INST_0_i_10_n_0\,
      S(4) => \out_r_Din_A[24]_INST_0_i_11_n_0\,
      S(3) => \out_r_Din_A[24]_INST_0_i_12_n_0\,
      S(2) => \out_r_Din_A[24]_INST_0_i_13_n_0\,
      S(1) => \out_r_Din_A[24]_INST_0_i_14_n_0\,
      S(0) => \out_r_Din_A[24]_INST_0_i_15_n_0\
    );
\out_r_Din_A[24]_INST_0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(29),
      I1 => mul_ln14_1_reg_625(29),
      I2 => \sum6_fu_94_reg_n_0_[29]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[24]_INST_0_i_1_n_0\
    );
\out_r_Din_A[24]_INST_0_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[24]_INST_0_i_2_n_0\,
      I1 => mul_ln14_1_reg_625(29),
      I2 => mul_ln14_reg_620(29),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[29]\,
      O => \out_r_Din_A[24]_INST_0_i_10_n_0\
    );
\out_r_Din_A[24]_INST_0_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[24]_INST_0_i_3_n_0\,
      I1 => mul_ln14_1_reg_625(28),
      I2 => mul_ln14_reg_620(28),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[28]\,
      O => \out_r_Din_A[24]_INST_0_i_11_n_0\
    );
\out_r_Din_A[24]_INST_0_i_12\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[24]_INST_0_i_4_n_0\,
      I1 => mul_ln14_1_reg_625(27),
      I2 => mul_ln14_reg_620(27),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[27]\,
      O => \out_r_Din_A[24]_INST_0_i_12_n_0\
    );
\out_r_Din_A[24]_INST_0_i_13\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[24]_INST_0_i_5_n_0\,
      I1 => mul_ln14_1_reg_625(26),
      I2 => mul_ln14_reg_620(26),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[26]\,
      O => \out_r_Din_A[24]_INST_0_i_13_n_0\
    );
\out_r_Din_A[24]_INST_0_i_14\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[24]_INST_0_i_6_n_0\,
      I1 => mul_ln14_1_reg_625(25),
      I2 => mul_ln14_reg_620(25),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[25]\,
      O => \out_r_Din_A[24]_INST_0_i_14_n_0\
    );
\out_r_Din_A[24]_INST_0_i_15\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[24]_INST_0_i_7_n_0\,
      I1 => mul_ln14_1_reg_625(24),
      I2 => mul_ln14_reg_620(24),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[24]\,
      O => \out_r_Din_A[24]_INST_0_i_15_n_0\
    );
\out_r_Din_A[24]_INST_0_i_16\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"20DFDF20"
    )
        port map (
      I0 => \sum6_fu_94_reg_n_0_[31]\,
      I1 => icmp_ln108_reg_161_pp0_iter3_reg,
      I2 => or_ln9_reg_552_pp0_iter3_reg,
      I3 => mul_ln14_reg_620(31),
      I4 => mul_ln14_1_reg_625(31),
      O => \out_r_Din_A[24]_INST_0_i_16_n_0\
    );
\out_r_Din_A[24]_INST_0_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(28),
      I1 => mul_ln14_1_reg_625(28),
      I2 => \sum6_fu_94_reg_n_0_[28]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[24]_INST_0_i_2_n_0\
    );
\out_r_Din_A[24]_INST_0_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(27),
      I1 => mul_ln14_1_reg_625(27),
      I2 => \sum6_fu_94_reg_n_0_[27]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[24]_INST_0_i_3_n_0\
    );
\out_r_Din_A[24]_INST_0_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(26),
      I1 => mul_ln14_1_reg_625(26),
      I2 => \sum6_fu_94_reg_n_0_[26]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[24]_INST_0_i_4_n_0\
    );
\out_r_Din_A[24]_INST_0_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(25),
      I1 => mul_ln14_1_reg_625(25),
      I2 => \sum6_fu_94_reg_n_0_[25]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[24]_INST_0_i_5_n_0\
    );
\out_r_Din_A[24]_INST_0_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(24),
      I1 => mul_ln14_1_reg_625(24),
      I2 => \sum6_fu_94_reg_n_0_[24]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[24]_INST_0_i_6_n_0\
    );
\out_r_Din_A[24]_INST_0_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(23),
      I1 => mul_ln14_1_reg_625(23),
      I2 => \sum6_fu_94_reg_n_0_[23]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[24]_INST_0_i_7_n_0\
    );
\out_r_Din_A[24]_INST_0_i_8\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00DFDFFFFF202000"
    )
        port map (
      I0 => or_ln9_reg_552_pp0_iter3_reg,
      I1 => icmp_ln108_reg_161_pp0_iter3_reg,
      I2 => \sum6_fu_94_reg_n_0_[30]\,
      I3 => mul_ln14_1_reg_625(30),
      I4 => mul_ln14_reg_620(30),
      I5 => \out_r_Din_A[24]_INST_0_i_16_n_0\,
      O => \out_r_Din_A[24]_INST_0_i_8_n_0\
    );
\out_r_Din_A[24]_INST_0_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[24]_INST_0_i_1_n_0\,
      I1 => mul_ln14_1_reg_625(30),
      I2 => mul_ln14_reg_620(30),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[30]\,
      O => \out_r_Din_A[24]_INST_0_i_9_n_0\
    );
\out_r_Din_A[8]_INST_0\: unisim.vcomponents.CARRY8
     port map (
      CI => \out_r_Din_A[0]_INST_0_n_0\,
      CI_TOP => '0',
      CO(7) => \out_r_Din_A[8]_INST_0_n_0\,
      CO(6) => \out_r_Din_A[8]_INST_0_n_1\,
      CO(5) => \out_r_Din_A[8]_INST_0_n_2\,
      CO(4) => \out_r_Din_A[8]_INST_0_n_3\,
      CO(3) => \out_r_Din_A[8]_INST_0_n_4\,
      CO(2) => \out_r_Din_A[8]_INST_0_n_5\,
      CO(1) => \out_r_Din_A[8]_INST_0_n_6\,
      CO(0) => \out_r_Din_A[8]_INST_0_n_7\,
      DI(7) => \out_r_Din_A[8]_INST_0_i_1_n_0\,
      DI(6) => \out_r_Din_A[8]_INST_0_i_2_n_0\,
      DI(5) => \out_r_Din_A[8]_INST_0_i_3_n_0\,
      DI(4) => \out_r_Din_A[8]_INST_0_i_4_n_0\,
      DI(3) => \out_r_Din_A[8]_INST_0_i_5_n_0\,
      DI(2) => \out_r_Din_A[8]_INST_0_i_6_n_0\,
      DI(1) => \out_r_Din_A[8]_INST_0_i_7_n_0\,
      DI(0) => \out_r_Din_A[8]_INST_0_i_8_n_0\,
      O(7 downto 0) => \^out_r_din_a\(15 downto 8),
      S(7) => \out_r_Din_A[8]_INST_0_i_9_n_0\,
      S(6) => \out_r_Din_A[8]_INST_0_i_10_n_0\,
      S(5) => \out_r_Din_A[8]_INST_0_i_11_n_0\,
      S(4) => \out_r_Din_A[8]_INST_0_i_12_n_0\,
      S(3) => \out_r_Din_A[8]_INST_0_i_13_n_0\,
      S(2) => \out_r_Din_A[8]_INST_0_i_14_n_0\,
      S(1) => \out_r_Din_A[8]_INST_0_i_15_n_0\,
      S(0) => \out_r_Din_A[8]_INST_0_i_16_n_0\
    );
\out_r_Din_A[8]_INST_0_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(14),
      I1 => mul_ln14_1_reg_625(14),
      I2 => \sum6_fu_94_reg_n_0_[14]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[8]_INST_0_i_1_n_0\
    );
\out_r_Din_A[8]_INST_0_i_10\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[8]_INST_0_i_2_n_0\,
      I1 => mul_ln14_1_reg_625(14),
      I2 => mul_ln14_reg_620(14),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[14]\,
      O => \out_r_Din_A[8]_INST_0_i_10_n_0\
    );
\out_r_Din_A[8]_INST_0_i_11\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[8]_INST_0_i_3_n_0\,
      I1 => mul_ln14_1_reg_625(13),
      I2 => mul_ln14_reg_620(13),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[13]\,
      O => \out_r_Din_A[8]_INST_0_i_11_n_0\
    );
\out_r_Din_A[8]_INST_0_i_12\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[8]_INST_0_i_4_n_0\,
      I1 => mul_ln14_1_reg_625(12),
      I2 => mul_ln14_reg_620(12),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[12]\,
      O => \out_r_Din_A[8]_INST_0_i_12_n_0\
    );
\out_r_Din_A[8]_INST_0_i_13\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[8]_INST_0_i_5_n_0\,
      I1 => mul_ln14_1_reg_625(11),
      I2 => mul_ln14_reg_620(11),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[11]\,
      O => \out_r_Din_A[8]_INST_0_i_13_n_0\
    );
\out_r_Din_A[8]_INST_0_i_14\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[8]_INST_0_i_6_n_0\,
      I1 => mul_ln14_1_reg_625(10),
      I2 => mul_ln14_reg_620(10),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[10]\,
      O => \out_r_Din_A[8]_INST_0_i_14_n_0\
    );
\out_r_Din_A[8]_INST_0_i_15\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[8]_INST_0_i_7_n_0\,
      I1 => mul_ln14_1_reg_625(9),
      I2 => mul_ln14_reg_620(9),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[9]\,
      O => \out_r_Din_A[8]_INST_0_i_15_n_0\
    );
\out_r_Din_A[8]_INST_0_i_16\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[8]_INST_0_i_8_n_0\,
      I1 => mul_ln14_1_reg_625(8),
      I2 => mul_ln14_reg_620(8),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[8]\,
      O => \out_r_Din_A[8]_INST_0_i_16_n_0\
    );
\out_r_Din_A[8]_INST_0_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(13),
      I1 => mul_ln14_1_reg_625(13),
      I2 => \sum6_fu_94_reg_n_0_[13]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[8]_INST_0_i_2_n_0\
    );
\out_r_Din_A[8]_INST_0_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(12),
      I1 => mul_ln14_1_reg_625(12),
      I2 => \sum6_fu_94_reg_n_0_[12]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[8]_INST_0_i_3_n_0\
    );
\out_r_Din_A[8]_INST_0_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(11),
      I1 => mul_ln14_1_reg_625(11),
      I2 => \sum6_fu_94_reg_n_0_[11]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[8]_INST_0_i_4_n_0\
    );
\out_r_Din_A[8]_INST_0_i_5\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(10),
      I1 => mul_ln14_1_reg_625(10),
      I2 => \sum6_fu_94_reg_n_0_[10]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[8]_INST_0_i_5_n_0\
    );
\out_r_Din_A[8]_INST_0_i_6\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(9),
      I1 => mul_ln14_1_reg_625(9),
      I2 => \sum6_fu_94_reg_n_0_[9]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[8]_INST_0_i_6_n_0\
    );
\out_r_Din_A[8]_INST_0_i_7\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(8),
      I1 => mul_ln14_1_reg_625(8),
      I2 => \sum6_fu_94_reg_n_0_[8]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[8]_INST_0_i_7_n_0\
    );
\out_r_Din_A[8]_INST_0_i_8\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88E88888"
    )
        port map (
      I0 => mul_ln14_reg_620(7),
      I1 => mul_ln14_1_reg_625(7),
      I2 => \sum6_fu_94_reg_n_0_[7]\,
      I3 => icmp_ln108_reg_161_pp0_iter3_reg,
      I4 => or_ln9_reg_552_pp0_iter3_reg,
      O => \out_r_Din_A[8]_INST_0_i_8_n_0\
    );
\out_r_Din_A[8]_INST_0_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"9696699696969696"
    )
        port map (
      I0 => \out_r_Din_A[8]_INST_0_i_1_n_0\,
      I1 => mul_ln14_1_reg_625(15),
      I2 => mul_ln14_reg_620(15),
      I3 => or_ln9_reg_552_pp0_iter3_reg,
      I4 => icmp_ln108_reg_161_pp0_iter3_reg,
      I5 => \sum6_fu_94_reg_n_0_[15]\,
      O => \out_r_Din_A[8]_INST_0_i_9_n_0\
    );
out_r_EN_A_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => ap_enable_reg_pp0_iter4,
      I1 => ap_block_pp0_stage0_subdone,
      O => \^out_r_en_a\
    );
\out_r_WEN_A[0]_INST_0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"80"
    )
        port map (
      I0 => tmp_5_reg_582_pp0_iter3_reg,
      I1 => ap_block_pp0_stage0_subdone,
      I2 => ap_enable_reg_pp0_iter4,
      O => \^out_r_wen_a\(0)
    );
\sum6_fu_94_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(0),
      Q => \sum6_fu_94_reg_n_0_[0]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[10]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(10),
      Q => \sum6_fu_94_reg_n_0_[10]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[11]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(11),
      Q => \sum6_fu_94_reg_n_0_[11]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[12]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(12),
      Q => \sum6_fu_94_reg_n_0_[12]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[13]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(13),
      Q => \sum6_fu_94_reg_n_0_[13]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[14]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(14),
      Q => \sum6_fu_94_reg_n_0_[14]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[15]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(15),
      Q => \sum6_fu_94_reg_n_0_[15]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[16]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(16),
      Q => \sum6_fu_94_reg_n_0_[16]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[17]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(17),
      Q => \sum6_fu_94_reg_n_0_[17]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[18]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(18),
      Q => \sum6_fu_94_reg_n_0_[18]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[19]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(19),
      Q => \sum6_fu_94_reg_n_0_[19]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(1),
      Q => \sum6_fu_94_reg_n_0_[1]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[20]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(20),
      Q => \sum6_fu_94_reg_n_0_[20]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[21]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(21),
      Q => \sum6_fu_94_reg_n_0_[21]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[22]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(22),
      Q => \sum6_fu_94_reg_n_0_[22]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[23]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(23),
      Q => \sum6_fu_94_reg_n_0_[23]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[24]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(24),
      Q => \sum6_fu_94_reg_n_0_[24]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[25]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(25),
      Q => \sum6_fu_94_reg_n_0_[25]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[26]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(26),
      Q => \sum6_fu_94_reg_n_0_[26]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[27]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(27),
      Q => \sum6_fu_94_reg_n_0_[27]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[28]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(28),
      Q => \sum6_fu_94_reg_n_0_[28]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[29]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(29),
      Q => \sum6_fu_94_reg_n_0_[29]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(2),
      Q => \sum6_fu_94_reg_n_0_[2]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[30]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(30),
      Q => \sum6_fu_94_reg_n_0_[30]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[31]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(31),
      Q => \sum6_fu_94_reg_n_0_[31]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[3]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(3),
      Q => \sum6_fu_94_reg_n_0_[3]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(4),
      Q => \sum6_fu_94_reg_n_0_[4]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(5),
      Q => \sum6_fu_94_reg_n_0_[5]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[6]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(6),
      Q => \sum6_fu_94_reg_n_0_[6]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[7]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(7),
      Q => \sum6_fu_94_reg_n_0_[7]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[8]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(8),
      Q => \sum6_fu_94_reg_n_0_[8]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\sum6_fu_94_reg[9]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => \^ap_clk\,
      CE => \^out_r_en_a\,
      D => \^out_r_din_a\(9),
      Q => \sum6_fu_94_reg_n_0_[9]\,
      R => flow_control_loop_delay_pipe_U_n_26
    );
\tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3\: unisim.vcomponents.SRL16E
     port map (
      A0 => '0',
      A1 => '1',
      A2 => '0',
      A3 => '0',
      CE => ap_block_pp0_stage0_subdone,
      CLK => \^ap_clk\,
      D => tmp_5_fu_401_p3,
      Q => \tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3_n_0\
    );
\tmp_5_reg_582_pp0_iter3_reg_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => ap_block_pp0_stage0_subdone,
      D => \tmp_5_reg_582_pp0_iter2_reg_reg[0]_srl3_n_0\,
      Q => tmp_5_reg_582_pp0_iter3_reg,
      R => '0'
    );
\xor_ln12_reg_586_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => \^ap_clk\,
      CE => \^in1_en_a\,
      D => flow_control_loop_delay_pipe_U_n_28,
      Q => xor_ln12_reg_586,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
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
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "bd_0_hls_inst_0,mat_mul,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "HLS";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "mat_mul,Vivado 2024.2";
  attribute hls_module : string;
  attribute hls_module of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  signal \<const0>\ : STD_LOGIC;
  signal \<const1>\ : STD_LOGIC;
  signal \^in1_addr_a\ : STD_LOGIC_VECTOR ( 5 downto 3 );
  signal \^in1_addr_b\ : STD_LOGIC_VECTOR ( 5 downto 3 );
  signal \^in2_addr_a\ : STD_LOGIC_VECTOR ( 5 downto 2 );
  signal \^in2_addr_b\ : STD_LOGIC_VECTOR ( 5 downto 2 );
  signal \^out_r_addr_a\ : STD_LOGIC_VECTOR ( 5 downto 2 );
  signal \^s_axi_control_rdata\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal NLW_inst_in1_Addr_A_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_inst_in1_Addr_B_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_inst_in1_Din_A_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_inst_in1_Din_B_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_inst_in1_WEN_A_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_inst_in1_WEN_B_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_inst_in2_Addr_A_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_inst_in2_Addr_B_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_inst_in2_Din_A_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_inst_in2_Din_B_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_inst_in2_WEN_A_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_inst_in2_WEN_B_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_inst_out_r_Addr_A_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_inst_s_axi_control_BRESP_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_inst_s_axi_control_RDATA_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 5 );
  signal NLW_inst_s_axi_control_RRESP_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  attribute C_S_AXI_CONTROL_ADDR_WIDTH : integer;
  attribute C_S_AXI_CONTROL_ADDR_WIDTH of inst : label is 4;
  attribute C_S_AXI_CONTROL_DATA_WIDTH : integer;
  attribute C_S_AXI_CONTROL_DATA_WIDTH of inst : label is 32;
  attribute C_S_AXI_CONTROL_WSTRB_WIDTH : integer;
  attribute C_S_AXI_CONTROL_WSTRB_WIDTH of inst : label is 4;
  attribute C_S_AXI_DATA_WIDTH : integer;
  attribute C_S_AXI_DATA_WIDTH of inst : label is 32;
  attribute C_S_AXI_WSTRB_WIDTH : integer;
  attribute C_S_AXI_WSTRB_WIDTH of inst : label is 4;
  attribute SDX_KERNEL : string;
  attribute SDX_KERNEL of inst : label is "true";
  attribute SDX_KERNEL_SYNTH_INST : string;
  attribute SDX_KERNEL_SYNTH_INST of inst : label is "inst";
  attribute SDX_KERNEL_TYPE : string;
  attribute SDX_KERNEL_TYPE of inst : label is "hls";
  attribute ap_ST_fsm_pp0_stage0 : string;
  attribute ap_ST_fsm_pp0_stage0 of inst : label is "1'b1";
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of ap_clk : signal is "xilinx.com:signal:clock:1.0 ap_clk CLK";
  attribute X_INTERFACE_MODE : string;
  attribute X_INTERFACE_MODE of ap_clk : signal is "slave";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of ap_clk : signal is "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF s_axi_control, ASSOCIATED_RESET ap_rst_n, FREQ_HZ 300000000.0, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of ap_rst_n : signal is "xilinx.com:signal:reset:1.0 ap_rst_n RST";
  attribute X_INTERFACE_MODE of ap_rst_n : signal is "slave";
  attribute X_INTERFACE_PARAMETER of ap_rst_n : signal is "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of in1_Clk_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA CLK";
  attribute X_INTERFACE_INFO of in1_Clk_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB CLK";
  attribute X_INTERFACE_INFO of in1_EN_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA EN";
  attribute X_INTERFACE_INFO of in1_EN_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB EN";
  attribute X_INTERFACE_INFO of in1_Rst_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA RST";
  attribute X_INTERFACE_INFO of in1_Rst_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB RST";
  attribute X_INTERFACE_INFO of in2_Clk_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA CLK";
  attribute X_INTERFACE_INFO of in2_Clk_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB CLK";
  attribute X_INTERFACE_INFO of in2_EN_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA EN";
  attribute X_INTERFACE_INFO of in2_EN_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB EN";
  attribute X_INTERFACE_INFO of in2_Rst_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA RST";
  attribute X_INTERFACE_INFO of in2_Rst_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB RST";
  attribute X_INTERFACE_INFO of interrupt : signal is "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT";
  attribute X_INTERFACE_MODE of interrupt : signal is "master";
  attribute X_INTERFACE_PARAMETER of interrupt : signal is "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, PortWidth 1";
  attribute X_INTERFACE_INFO of out_r_Clk_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA CLK";
  attribute X_INTERFACE_INFO of out_r_EN_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA EN";
  attribute X_INTERFACE_INFO of out_r_Rst_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA RST";
  attribute X_INTERFACE_INFO of s_axi_control_ARREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control ARREADY";
  attribute X_INTERFACE_INFO of s_axi_control_ARVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control ARVALID";
  attribute X_INTERFACE_INFO of s_axi_control_AWREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control AWREADY";
  attribute X_INTERFACE_INFO of s_axi_control_AWVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control AWVALID";
  attribute X_INTERFACE_INFO of s_axi_control_BREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control BREADY";
  attribute X_INTERFACE_INFO of s_axi_control_BVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control BVALID";
  attribute X_INTERFACE_INFO of s_axi_control_RREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control RREADY";
  attribute X_INTERFACE_INFO of s_axi_control_RVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control RVALID";
  attribute X_INTERFACE_INFO of s_axi_control_WREADY : signal is "xilinx.com:interface:aximm:1.0 s_axi_control WREADY";
  attribute X_INTERFACE_INFO of s_axi_control_WVALID : signal is "xilinx.com:interface:aximm:1.0 s_axi_control WVALID";
  attribute X_INTERFACE_INFO of in1_Addr_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA ADDR";
  attribute X_INTERFACE_MODE of in1_Addr_A : signal is "master";
  attribute X_INTERFACE_PARAMETER of in1_Addr_A : signal is "XIL_INTERFACENAME in1_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of in1_Addr_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB ADDR";
  attribute X_INTERFACE_MODE of in1_Addr_B : signal is "master";
  attribute X_INTERFACE_PARAMETER of in1_Addr_B : signal is "XIL_INTERFACENAME in1_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of in1_Din_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA DIN";
  attribute X_INTERFACE_INFO of in1_Din_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB DIN";
  attribute X_INTERFACE_INFO of in1_Dout_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA DOUT";
  attribute X_INTERFACE_INFO of in1_Dout_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB DOUT";
  attribute X_INTERFACE_INFO of in1_WEN_A : signal is "xilinx.com:interface:bram:1.0 in1_PORTA WE";
  attribute X_INTERFACE_INFO of in1_WEN_B : signal is "xilinx.com:interface:bram:1.0 in1_PORTB WE";
  attribute X_INTERFACE_INFO of in2_Addr_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA ADDR";
  attribute X_INTERFACE_MODE of in2_Addr_A : signal is "master";
  attribute X_INTERFACE_PARAMETER of in2_Addr_A : signal is "XIL_INTERFACENAME in2_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of in2_Addr_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB ADDR";
  attribute X_INTERFACE_MODE of in2_Addr_B : signal is "master";
  attribute X_INTERFACE_PARAMETER of in2_Addr_B : signal is "XIL_INTERFACENAME in2_PORTB, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of in2_Din_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA DIN";
  attribute X_INTERFACE_INFO of in2_Din_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB DIN";
  attribute X_INTERFACE_INFO of in2_Dout_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA DOUT";
  attribute X_INTERFACE_INFO of in2_Dout_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB DOUT";
  attribute X_INTERFACE_INFO of in2_WEN_A : signal is "xilinx.com:interface:bram:1.0 in2_PORTA WE";
  attribute X_INTERFACE_INFO of in2_WEN_B : signal is "xilinx.com:interface:bram:1.0 in2_PORTB WE";
  attribute X_INTERFACE_INFO of out_r_Addr_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA ADDR";
  attribute X_INTERFACE_MODE of out_r_Addr_A : signal is "master";
  attribute X_INTERFACE_PARAMETER of out_r_Addr_A : signal is "XIL_INTERFACENAME out_r_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 64, MEM_WIDTH 32, MEM_ADDRESS_MODE BYTE_ADDRESS, READ_LATENCY 1, MEM_ECC NONE";
  attribute X_INTERFACE_INFO of out_r_Din_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA DIN";
  attribute X_INTERFACE_INFO of out_r_Dout_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA DOUT";
  attribute X_INTERFACE_INFO of out_r_WEN_A : signal is "xilinx.com:interface:bram:1.0 out_r_PORTA WE";
  attribute X_INTERFACE_INFO of s_axi_control_ARADDR : signal is "xilinx.com:interface:aximm:1.0 s_axi_control ARADDR";
  attribute X_INTERFACE_MODE of s_axi_control_ARADDR : signal is "slave";
  attribute X_INTERFACE_PARAMETER of s_axi_control_ARADDR : signal is "XIL_INTERFACENAME s_axi_control, ADDR_WIDTH 4, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 300000000.0, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN bd_0_ap_clk_0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s_axi_control_AWADDR : signal is "xilinx.com:interface:aximm:1.0 s_axi_control AWADDR";
  attribute X_INTERFACE_INFO of s_axi_control_BRESP : signal is "xilinx.com:interface:aximm:1.0 s_axi_control BRESP";
  attribute X_INTERFACE_INFO of s_axi_control_RDATA : signal is "xilinx.com:interface:aximm:1.0 s_axi_control RDATA";
  attribute X_INTERFACE_INFO of s_axi_control_RRESP : signal is "xilinx.com:interface:aximm:1.0 s_axi_control RRESP";
  attribute X_INTERFACE_INFO of s_axi_control_WDATA : signal is "xilinx.com:interface:aximm:1.0 s_axi_control WDATA";
  attribute X_INTERFACE_INFO of s_axi_control_WSTRB : signal is "xilinx.com:interface:aximm:1.0 s_axi_control WSTRB";
begin
  in1_Addr_A(31) <= \<const0>\;
  in1_Addr_A(30) <= \<const0>\;
  in1_Addr_A(29) <= \<const0>\;
  in1_Addr_A(28) <= \<const0>\;
  in1_Addr_A(27) <= \<const0>\;
  in1_Addr_A(26) <= \<const0>\;
  in1_Addr_A(25) <= \<const0>\;
  in1_Addr_A(24) <= \<const0>\;
  in1_Addr_A(23) <= \<const0>\;
  in1_Addr_A(22) <= \<const0>\;
  in1_Addr_A(21) <= \<const0>\;
  in1_Addr_A(20) <= \<const0>\;
  in1_Addr_A(19) <= \<const0>\;
  in1_Addr_A(18) <= \<const0>\;
  in1_Addr_A(17) <= \<const0>\;
  in1_Addr_A(16) <= \<const0>\;
  in1_Addr_A(15) <= \<const0>\;
  in1_Addr_A(14) <= \<const0>\;
  in1_Addr_A(13) <= \<const0>\;
  in1_Addr_A(12) <= \<const0>\;
  in1_Addr_A(11) <= \<const0>\;
  in1_Addr_A(10) <= \<const0>\;
  in1_Addr_A(9) <= \<const0>\;
  in1_Addr_A(8) <= \<const0>\;
  in1_Addr_A(7) <= \<const0>\;
  in1_Addr_A(6) <= \<const0>\;
  in1_Addr_A(5 downto 3) <= \^in1_addr_a\(5 downto 3);
  in1_Addr_A(2) <= \<const1>\;
  in1_Addr_A(1) <= \<const0>\;
  in1_Addr_A(0) <= \<const0>\;
  in1_Addr_B(31) <= \<const0>\;
  in1_Addr_B(30) <= \<const0>\;
  in1_Addr_B(29) <= \<const0>\;
  in1_Addr_B(28) <= \<const0>\;
  in1_Addr_B(27) <= \<const0>\;
  in1_Addr_B(26) <= \<const0>\;
  in1_Addr_B(25) <= \<const0>\;
  in1_Addr_B(24) <= \<const0>\;
  in1_Addr_B(23) <= \<const0>\;
  in1_Addr_B(22) <= \<const0>\;
  in1_Addr_B(21) <= \<const0>\;
  in1_Addr_B(20) <= \<const0>\;
  in1_Addr_B(19) <= \<const0>\;
  in1_Addr_B(18) <= \<const0>\;
  in1_Addr_B(17) <= \<const0>\;
  in1_Addr_B(16) <= \<const0>\;
  in1_Addr_B(15) <= \<const0>\;
  in1_Addr_B(14) <= \<const0>\;
  in1_Addr_B(13) <= \<const0>\;
  in1_Addr_B(12) <= \<const0>\;
  in1_Addr_B(11) <= \<const0>\;
  in1_Addr_B(10) <= \<const0>\;
  in1_Addr_B(9) <= \<const0>\;
  in1_Addr_B(8) <= \<const0>\;
  in1_Addr_B(7) <= \<const0>\;
  in1_Addr_B(6) <= \<const0>\;
  in1_Addr_B(5 downto 3) <= \^in1_addr_b\(5 downto 3);
  in1_Addr_B(2) <= \<const0>\;
  in1_Addr_B(1) <= \<const0>\;
  in1_Addr_B(0) <= \<const0>\;
  in1_Din_A(31) <= \<const0>\;
  in1_Din_A(30) <= \<const0>\;
  in1_Din_A(29) <= \<const0>\;
  in1_Din_A(28) <= \<const0>\;
  in1_Din_A(27) <= \<const0>\;
  in1_Din_A(26) <= \<const0>\;
  in1_Din_A(25) <= \<const0>\;
  in1_Din_A(24) <= \<const0>\;
  in1_Din_A(23) <= \<const0>\;
  in1_Din_A(22) <= \<const0>\;
  in1_Din_A(21) <= \<const0>\;
  in1_Din_A(20) <= \<const0>\;
  in1_Din_A(19) <= \<const0>\;
  in1_Din_A(18) <= \<const0>\;
  in1_Din_A(17) <= \<const0>\;
  in1_Din_A(16) <= \<const0>\;
  in1_Din_A(15) <= \<const0>\;
  in1_Din_A(14) <= \<const0>\;
  in1_Din_A(13) <= \<const0>\;
  in1_Din_A(12) <= \<const0>\;
  in1_Din_A(11) <= \<const0>\;
  in1_Din_A(10) <= \<const0>\;
  in1_Din_A(9) <= \<const0>\;
  in1_Din_A(8) <= \<const0>\;
  in1_Din_A(7) <= \<const0>\;
  in1_Din_A(6) <= \<const0>\;
  in1_Din_A(5) <= \<const0>\;
  in1_Din_A(4) <= \<const0>\;
  in1_Din_A(3) <= \<const0>\;
  in1_Din_A(2) <= \<const0>\;
  in1_Din_A(1) <= \<const0>\;
  in1_Din_A(0) <= \<const0>\;
  in1_Din_B(31) <= \<const0>\;
  in1_Din_B(30) <= \<const0>\;
  in1_Din_B(29) <= \<const0>\;
  in1_Din_B(28) <= \<const0>\;
  in1_Din_B(27) <= \<const0>\;
  in1_Din_B(26) <= \<const0>\;
  in1_Din_B(25) <= \<const0>\;
  in1_Din_B(24) <= \<const0>\;
  in1_Din_B(23) <= \<const0>\;
  in1_Din_B(22) <= \<const0>\;
  in1_Din_B(21) <= \<const0>\;
  in1_Din_B(20) <= \<const0>\;
  in1_Din_B(19) <= \<const0>\;
  in1_Din_B(18) <= \<const0>\;
  in1_Din_B(17) <= \<const0>\;
  in1_Din_B(16) <= \<const0>\;
  in1_Din_B(15) <= \<const0>\;
  in1_Din_B(14) <= \<const0>\;
  in1_Din_B(13) <= \<const0>\;
  in1_Din_B(12) <= \<const0>\;
  in1_Din_B(11) <= \<const0>\;
  in1_Din_B(10) <= \<const0>\;
  in1_Din_B(9) <= \<const0>\;
  in1_Din_B(8) <= \<const0>\;
  in1_Din_B(7) <= \<const0>\;
  in1_Din_B(6) <= \<const0>\;
  in1_Din_B(5) <= \<const0>\;
  in1_Din_B(4) <= \<const0>\;
  in1_Din_B(3) <= \<const0>\;
  in1_Din_B(2) <= \<const0>\;
  in1_Din_B(1) <= \<const0>\;
  in1_Din_B(0) <= \<const0>\;
  in1_WEN_A(3) <= \<const0>\;
  in1_WEN_A(2) <= \<const0>\;
  in1_WEN_A(1) <= \<const0>\;
  in1_WEN_A(0) <= \<const0>\;
  in1_WEN_B(3) <= \<const0>\;
  in1_WEN_B(2) <= \<const0>\;
  in1_WEN_B(1) <= \<const0>\;
  in1_WEN_B(0) <= \<const0>\;
  in2_Addr_A(31) <= \<const0>\;
  in2_Addr_A(30) <= \<const0>\;
  in2_Addr_A(29) <= \<const0>\;
  in2_Addr_A(28) <= \<const0>\;
  in2_Addr_A(27) <= \<const0>\;
  in2_Addr_A(26) <= \<const0>\;
  in2_Addr_A(25) <= \<const0>\;
  in2_Addr_A(24) <= \<const0>\;
  in2_Addr_A(23) <= \<const0>\;
  in2_Addr_A(22) <= \<const0>\;
  in2_Addr_A(21) <= \<const0>\;
  in2_Addr_A(20) <= \<const0>\;
  in2_Addr_A(19) <= \<const0>\;
  in2_Addr_A(18) <= \<const0>\;
  in2_Addr_A(17) <= \<const0>\;
  in2_Addr_A(16) <= \<const0>\;
  in2_Addr_A(15) <= \<const0>\;
  in2_Addr_A(14) <= \<const0>\;
  in2_Addr_A(13) <= \<const0>\;
  in2_Addr_A(12) <= \<const0>\;
  in2_Addr_A(11) <= \<const0>\;
  in2_Addr_A(10) <= \<const0>\;
  in2_Addr_A(9) <= \<const0>\;
  in2_Addr_A(8) <= \<const0>\;
  in2_Addr_A(7) <= \<const0>\;
  in2_Addr_A(6) <= \<const0>\;
  in2_Addr_A(5 downto 2) <= \^in2_addr_a\(5 downto 2);
  in2_Addr_A(1) <= \<const0>\;
  in2_Addr_A(0) <= \<const0>\;
  in2_Addr_B(31) <= \<const0>\;
  in2_Addr_B(30) <= \<const0>\;
  in2_Addr_B(29) <= \<const0>\;
  in2_Addr_B(28) <= \<const0>\;
  in2_Addr_B(27) <= \<const0>\;
  in2_Addr_B(26) <= \<const0>\;
  in2_Addr_B(25) <= \<const0>\;
  in2_Addr_B(24) <= \<const0>\;
  in2_Addr_B(23) <= \<const0>\;
  in2_Addr_B(22) <= \<const0>\;
  in2_Addr_B(21) <= \<const0>\;
  in2_Addr_B(20) <= \<const0>\;
  in2_Addr_B(19) <= \<const0>\;
  in2_Addr_B(18) <= \<const0>\;
  in2_Addr_B(17) <= \<const0>\;
  in2_Addr_B(16) <= \<const0>\;
  in2_Addr_B(15) <= \<const0>\;
  in2_Addr_B(14) <= \<const0>\;
  in2_Addr_B(13) <= \<const0>\;
  in2_Addr_B(12) <= \<const0>\;
  in2_Addr_B(11) <= \<const0>\;
  in2_Addr_B(10) <= \<const0>\;
  in2_Addr_B(9) <= \<const0>\;
  in2_Addr_B(8) <= \<const0>\;
  in2_Addr_B(7) <= \<const0>\;
  in2_Addr_B(6) <= \<const0>\;
  in2_Addr_B(5 downto 2) <= \^in2_addr_b\(5 downto 2);
  in2_Addr_B(1) <= \<const0>\;
  in2_Addr_B(0) <= \<const0>\;
  in2_Din_A(31) <= \<const0>\;
  in2_Din_A(30) <= \<const0>\;
  in2_Din_A(29) <= \<const0>\;
  in2_Din_A(28) <= \<const0>\;
  in2_Din_A(27) <= \<const0>\;
  in2_Din_A(26) <= \<const0>\;
  in2_Din_A(25) <= \<const0>\;
  in2_Din_A(24) <= \<const0>\;
  in2_Din_A(23) <= \<const0>\;
  in2_Din_A(22) <= \<const0>\;
  in2_Din_A(21) <= \<const0>\;
  in2_Din_A(20) <= \<const0>\;
  in2_Din_A(19) <= \<const0>\;
  in2_Din_A(18) <= \<const0>\;
  in2_Din_A(17) <= \<const0>\;
  in2_Din_A(16) <= \<const0>\;
  in2_Din_A(15) <= \<const0>\;
  in2_Din_A(14) <= \<const0>\;
  in2_Din_A(13) <= \<const0>\;
  in2_Din_A(12) <= \<const0>\;
  in2_Din_A(11) <= \<const0>\;
  in2_Din_A(10) <= \<const0>\;
  in2_Din_A(9) <= \<const0>\;
  in2_Din_A(8) <= \<const0>\;
  in2_Din_A(7) <= \<const0>\;
  in2_Din_A(6) <= \<const0>\;
  in2_Din_A(5) <= \<const0>\;
  in2_Din_A(4) <= \<const0>\;
  in2_Din_A(3) <= \<const0>\;
  in2_Din_A(2) <= \<const0>\;
  in2_Din_A(1) <= \<const0>\;
  in2_Din_A(0) <= \<const0>\;
  in2_Din_B(31) <= \<const0>\;
  in2_Din_B(30) <= \<const0>\;
  in2_Din_B(29) <= \<const0>\;
  in2_Din_B(28) <= \<const0>\;
  in2_Din_B(27) <= \<const0>\;
  in2_Din_B(26) <= \<const0>\;
  in2_Din_B(25) <= \<const0>\;
  in2_Din_B(24) <= \<const0>\;
  in2_Din_B(23) <= \<const0>\;
  in2_Din_B(22) <= \<const0>\;
  in2_Din_B(21) <= \<const0>\;
  in2_Din_B(20) <= \<const0>\;
  in2_Din_B(19) <= \<const0>\;
  in2_Din_B(18) <= \<const0>\;
  in2_Din_B(17) <= \<const0>\;
  in2_Din_B(16) <= \<const0>\;
  in2_Din_B(15) <= \<const0>\;
  in2_Din_B(14) <= \<const0>\;
  in2_Din_B(13) <= \<const0>\;
  in2_Din_B(12) <= \<const0>\;
  in2_Din_B(11) <= \<const0>\;
  in2_Din_B(10) <= \<const0>\;
  in2_Din_B(9) <= \<const0>\;
  in2_Din_B(8) <= \<const0>\;
  in2_Din_B(7) <= \<const0>\;
  in2_Din_B(6) <= \<const0>\;
  in2_Din_B(5) <= \<const0>\;
  in2_Din_B(4) <= \<const0>\;
  in2_Din_B(3) <= \<const0>\;
  in2_Din_B(2) <= \<const0>\;
  in2_Din_B(1) <= \<const0>\;
  in2_Din_B(0) <= \<const0>\;
  in2_WEN_A(3) <= \<const0>\;
  in2_WEN_A(2) <= \<const0>\;
  in2_WEN_A(1) <= \<const0>\;
  in2_WEN_A(0) <= \<const0>\;
  in2_WEN_B(3) <= \<const0>\;
  in2_WEN_B(2) <= \<const0>\;
  in2_WEN_B(1) <= \<const0>\;
  in2_WEN_B(0) <= \<const0>\;
  out_r_Addr_A(31) <= \<const0>\;
  out_r_Addr_A(30) <= \<const0>\;
  out_r_Addr_A(29) <= \<const0>\;
  out_r_Addr_A(28) <= \<const0>\;
  out_r_Addr_A(27) <= \<const0>\;
  out_r_Addr_A(26) <= \<const0>\;
  out_r_Addr_A(25) <= \<const0>\;
  out_r_Addr_A(24) <= \<const0>\;
  out_r_Addr_A(23) <= \<const0>\;
  out_r_Addr_A(22) <= \<const0>\;
  out_r_Addr_A(21) <= \<const0>\;
  out_r_Addr_A(20) <= \<const0>\;
  out_r_Addr_A(19) <= \<const0>\;
  out_r_Addr_A(18) <= \<const0>\;
  out_r_Addr_A(17) <= \<const0>\;
  out_r_Addr_A(16) <= \<const0>\;
  out_r_Addr_A(15) <= \<const0>\;
  out_r_Addr_A(14) <= \<const0>\;
  out_r_Addr_A(13) <= \<const0>\;
  out_r_Addr_A(12) <= \<const0>\;
  out_r_Addr_A(11) <= \<const0>\;
  out_r_Addr_A(10) <= \<const0>\;
  out_r_Addr_A(9) <= \<const0>\;
  out_r_Addr_A(8) <= \<const0>\;
  out_r_Addr_A(7) <= \<const0>\;
  out_r_Addr_A(6) <= \<const0>\;
  out_r_Addr_A(5 downto 2) <= \^out_r_addr_a\(5 downto 2);
  out_r_Addr_A(1) <= \<const0>\;
  out_r_Addr_A(0) <= \<const0>\;
  s_axi_control_BRESP(1) <= \<const0>\;
  s_axi_control_BRESP(0) <= \<const0>\;
  s_axi_control_RDATA(31) <= \<const0>\;
  s_axi_control_RDATA(30) <= \<const0>\;
  s_axi_control_RDATA(29) <= \<const0>\;
  s_axi_control_RDATA(28) <= \<const0>\;
  s_axi_control_RDATA(27) <= \<const0>\;
  s_axi_control_RDATA(26) <= \<const0>\;
  s_axi_control_RDATA(25) <= \<const0>\;
  s_axi_control_RDATA(24) <= \<const0>\;
  s_axi_control_RDATA(23) <= \<const0>\;
  s_axi_control_RDATA(22) <= \<const0>\;
  s_axi_control_RDATA(21) <= \<const0>\;
  s_axi_control_RDATA(20) <= \<const0>\;
  s_axi_control_RDATA(19) <= \<const0>\;
  s_axi_control_RDATA(18) <= \<const0>\;
  s_axi_control_RDATA(17) <= \<const0>\;
  s_axi_control_RDATA(16) <= \<const0>\;
  s_axi_control_RDATA(15) <= \<const0>\;
  s_axi_control_RDATA(14) <= \<const0>\;
  s_axi_control_RDATA(13) <= \<const0>\;
  s_axi_control_RDATA(12) <= \<const0>\;
  s_axi_control_RDATA(11) <= \<const0>\;
  s_axi_control_RDATA(10) <= \<const0>\;
  s_axi_control_RDATA(9) <= \^s_axi_control_rdata\(9);
  s_axi_control_RDATA(8) <= \<const0>\;
  s_axi_control_RDATA(7) <= \^s_axi_control_rdata\(7);
  s_axi_control_RDATA(6) <= \<const0>\;
  s_axi_control_RDATA(5) <= \<const0>\;
  s_axi_control_RDATA(4 downto 0) <= \^s_axi_control_rdata\(4 downto 0);
  s_axi_control_RRESP(1) <= \<const0>\;
  s_axi_control_RRESP(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
VCC: unisim.vcomponents.VCC
     port map (
      P => \<const1>\
    );
inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_mat_mul
     port map (
      ap_clk => ap_clk,
      ap_rst_n => ap_rst_n,
      in1_Addr_A(31 downto 6) => NLW_inst_in1_Addr_A_UNCONNECTED(31 downto 6),
      in1_Addr_A(5 downto 3) => \^in1_addr_a\(5 downto 3),
      in1_Addr_A(2 downto 0) => NLW_inst_in1_Addr_A_UNCONNECTED(2 downto 0),
      in1_Addr_B(31 downto 6) => NLW_inst_in1_Addr_B_UNCONNECTED(31 downto 6),
      in1_Addr_B(5 downto 3) => \^in1_addr_b\(5 downto 3),
      in1_Addr_B(2 downto 0) => NLW_inst_in1_Addr_B_UNCONNECTED(2 downto 0),
      in1_Clk_A => in1_Clk_A,
      in1_Clk_B => in1_Clk_B,
      in1_Din_A(31 downto 0) => NLW_inst_in1_Din_A_UNCONNECTED(31 downto 0),
      in1_Din_B(31 downto 0) => NLW_inst_in1_Din_B_UNCONNECTED(31 downto 0),
      in1_Dout_A(31 downto 0) => in1_Dout_A(31 downto 0),
      in1_Dout_B(31 downto 0) => in1_Dout_B(31 downto 0),
      in1_EN_A => in1_EN_A,
      in1_EN_B => in1_EN_B,
      in1_Rst_A => in1_Rst_A,
      in1_Rst_B => in1_Rst_B,
      in1_WEN_A(3 downto 0) => NLW_inst_in1_WEN_A_UNCONNECTED(3 downto 0),
      in1_WEN_B(3 downto 0) => NLW_inst_in1_WEN_B_UNCONNECTED(3 downto 0),
      in2_Addr_A(31 downto 6) => NLW_inst_in2_Addr_A_UNCONNECTED(31 downto 6),
      in2_Addr_A(5 downto 2) => \^in2_addr_a\(5 downto 2),
      in2_Addr_A(1 downto 0) => NLW_inst_in2_Addr_A_UNCONNECTED(1 downto 0),
      in2_Addr_B(31 downto 6) => NLW_inst_in2_Addr_B_UNCONNECTED(31 downto 6),
      in2_Addr_B(5 downto 2) => \^in2_addr_b\(5 downto 2),
      in2_Addr_B(1 downto 0) => NLW_inst_in2_Addr_B_UNCONNECTED(1 downto 0),
      in2_Clk_A => in2_Clk_A,
      in2_Clk_B => in2_Clk_B,
      in2_Din_A(31 downto 0) => NLW_inst_in2_Din_A_UNCONNECTED(31 downto 0),
      in2_Din_B(31 downto 0) => NLW_inst_in2_Din_B_UNCONNECTED(31 downto 0),
      in2_Dout_A(31 downto 0) => in2_Dout_A(31 downto 0),
      in2_Dout_B(31 downto 0) => in2_Dout_B(31 downto 0),
      in2_EN_A => in2_EN_A,
      in2_EN_B => in2_EN_B,
      in2_Rst_A => in2_Rst_A,
      in2_Rst_B => in2_Rst_B,
      in2_WEN_A(3 downto 0) => NLW_inst_in2_WEN_A_UNCONNECTED(3 downto 0),
      in2_WEN_B(3 downto 0) => NLW_inst_in2_WEN_B_UNCONNECTED(3 downto 0),
      interrupt => interrupt,
      out_r_Addr_A(31 downto 6) => NLW_inst_out_r_Addr_A_UNCONNECTED(31 downto 6),
      out_r_Addr_A(5 downto 2) => \^out_r_addr_a\(5 downto 2),
      out_r_Addr_A(1 downto 0) => NLW_inst_out_r_Addr_A_UNCONNECTED(1 downto 0),
      out_r_Clk_A => out_r_Clk_A,
      out_r_Din_A(31 downto 0) => out_r_Din_A(31 downto 0),
      out_r_Dout_A(31 downto 0) => B"00000000000000000000000000000000",
      out_r_EN_A => out_r_EN_A,
      out_r_Rst_A => out_r_Rst_A,
      out_r_WEN_A(3 downto 0) => out_r_WEN_A(3 downto 0),
      s_axi_control_ARADDR(3 downto 0) => s_axi_control_ARADDR(3 downto 0),
      s_axi_control_ARREADY => s_axi_control_ARREADY,
      s_axi_control_ARVALID => s_axi_control_ARVALID,
      s_axi_control_AWADDR(3 downto 2) => s_axi_control_AWADDR(3 downto 2),
      s_axi_control_AWADDR(1 downto 0) => B"00",
      s_axi_control_AWREADY => s_axi_control_AWREADY,
      s_axi_control_AWVALID => s_axi_control_AWVALID,
      s_axi_control_BREADY => s_axi_control_BREADY,
      s_axi_control_BRESP(1 downto 0) => NLW_inst_s_axi_control_BRESP_UNCONNECTED(1 downto 0),
      s_axi_control_BVALID => s_axi_control_BVALID,
      s_axi_control_RDATA(31 downto 10) => NLW_inst_s_axi_control_RDATA_UNCONNECTED(31 downto 10),
      s_axi_control_RDATA(9) => \^s_axi_control_rdata\(9),
      s_axi_control_RDATA(8) => NLW_inst_s_axi_control_RDATA_UNCONNECTED(8),
      s_axi_control_RDATA(7) => \^s_axi_control_rdata\(7),
      s_axi_control_RDATA(6 downto 5) => NLW_inst_s_axi_control_RDATA_UNCONNECTED(6 downto 5),
      s_axi_control_RDATA(4 downto 0) => \^s_axi_control_rdata\(4 downto 0),
      s_axi_control_RREADY => s_axi_control_RREADY,
      s_axi_control_RRESP(1 downto 0) => NLW_inst_s_axi_control_RRESP_UNCONNECTED(1 downto 0),
      s_axi_control_RVALID => s_axi_control_RVALID,
      s_axi_control_WDATA(31 downto 8) => B"000000000000000000000000",
      s_axi_control_WDATA(7) => s_axi_control_WDATA(7),
      s_axi_control_WDATA(6 downto 5) => B"00",
      s_axi_control_WDATA(4) => s_axi_control_WDATA(4),
      s_axi_control_WDATA(3 downto 2) => B"00",
      s_axi_control_WDATA(1 downto 0) => s_axi_control_WDATA(1 downto 0),
      s_axi_control_WREADY => s_axi_control_WREADY,
      s_axi_control_WSTRB(3 downto 1) => B"000",
      s_axi_control_WSTRB(0) => s_axi_control_WSTRB(0),
      s_axi_control_WVALID => s_axi_control_WVALID
    );
end STRUCTURE;
