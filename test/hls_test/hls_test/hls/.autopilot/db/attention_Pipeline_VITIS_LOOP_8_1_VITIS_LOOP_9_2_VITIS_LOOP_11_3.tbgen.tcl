set moduleName attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type loop_auto_rewind
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set svuvm_can_support 1
set cdfgNum 8
set C_modelName {attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
dict set ap_memory_interface_dict q { MEM_WIDTH 32 MEM_SIZE 24 MASTER_TYPE BRAM_CTRL MEM_ADDRESS_MODE BYTE_ADDRESS PACKAGE_IO port READ_LATENCY 1 }
dict set ap_memory_interface_dict k_t { MEM_WIDTH 32 MEM_SIZE 24 MASTER_TYPE BRAM_CTRL MEM_ADDRESS_MODE WORD_ADDRESS PACKAGE_IO port READ_LATENCY 1 }
set C_modelArgList {
	{ q int 32 regular {bram 6 { 1 1 } 1 1 }  }
	{ k_t int 32 regular {array 6 { 1 1 } 1 1 }  }
	{ qk_124_out int 32 regular {pointer 1}  }
	{ qk_113_out int 32 regular {pointer 1}  }
	{ qk_102_out int 32 regular {pointer 1}  }
	{ qk_91_out int 32 regular {pointer 1}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "q", "interface" : "bram", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k_t", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_124_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_113_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_102_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_91_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 38
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ q_Addr_A sc_out sc_lv 32 signal 0 } 
	{ q_EN_A sc_out sc_logic 1 signal 0 } 
	{ q_WEN_A sc_out sc_lv 4 signal 0 } 
	{ q_Din_A sc_out sc_lv 32 signal 0 } 
	{ q_Dout_A sc_in sc_lv 32 signal 0 } 
	{ q_Addr_B sc_out sc_lv 32 signal 0 } 
	{ q_EN_B sc_out sc_logic 1 signal 0 } 
	{ q_WEN_B sc_out sc_lv 4 signal 0 } 
	{ q_Din_B sc_out sc_lv 32 signal 0 } 
	{ q_Dout_B sc_in sc_lv 32 signal 0 } 
	{ k_t_address0 sc_out sc_lv 3 signal 1 } 
	{ k_t_ce0 sc_out sc_logic 1 signal 1 } 
	{ k_t_q0 sc_in sc_lv 32 signal 1 } 
	{ k_t_address1 sc_out sc_lv 3 signal 1 } 
	{ k_t_ce1 sc_out sc_logic 1 signal 1 } 
	{ k_t_q1 sc_in sc_lv 32 signal 1 } 
	{ qk_124_out sc_out sc_lv 32 signal 2 } 
	{ qk_124_out_ap_vld sc_out sc_logic 1 outvld 2 } 
	{ qk_113_out sc_out sc_lv 32 signal 3 } 
	{ qk_113_out_ap_vld sc_out sc_logic 1 outvld 3 } 
	{ qk_102_out sc_out sc_lv 32 signal 4 } 
	{ qk_102_out_ap_vld sc_out sc_logic 1 outvld 4 } 
	{ qk_91_out sc_out sc_lv 32 signal 5 } 
	{ qk_91_out_ap_vld sc_out sc_logic 1 outvld 5 } 
	{ grp_fu_465_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_465_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_465_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_465_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_469_p_din0 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_469_p_din1 sc_out sc_lv 32 signal -1 } 
	{ grp_fu_469_p_dout0 sc_in sc_lv 32 signal -1 } 
	{ grp_fu_469_p_ce sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "q_Addr_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Addr_A" }} , 
 	{ "name": "q_EN_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "q", "role": "EN_A" }} , 
 	{ "name": "q_WEN_A", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "q", "role": "WEN_A" }} , 
 	{ "name": "q_Din_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Din_A" }} , 
 	{ "name": "q_Dout_A", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Dout_A" }} , 
 	{ "name": "q_Addr_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Addr_B" }} , 
 	{ "name": "q_EN_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "q", "role": "EN_B" }} , 
 	{ "name": "q_WEN_B", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "q", "role": "WEN_B" }} , 
 	{ "name": "q_Din_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Din_B" }} , 
 	{ "name": "q_Dout_B", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Dout_B" }} , 
 	{ "name": "k_t_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "k_t", "role": "address0" }} , 
 	{ "name": "k_t_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "k_t", "role": "ce0" }} , 
 	{ "name": "k_t_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k_t", "role": "q0" }} , 
 	{ "name": "k_t_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "k_t", "role": "address1" }} , 
 	{ "name": "k_t_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "k_t", "role": "ce1" }} , 
 	{ "name": "k_t_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k_t", "role": "q1" }} , 
 	{ "name": "qk_124_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_124_out", "role": "default" }} , 
 	{ "name": "qk_124_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_124_out", "role": "ap_vld" }} , 
 	{ "name": "qk_113_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_113_out", "role": "default" }} , 
 	{ "name": "qk_113_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_113_out", "role": "ap_vld" }} , 
 	{ "name": "qk_102_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_102_out", "role": "default" }} , 
 	{ "name": "qk_102_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_102_out", "role": "ap_vld" }} , 
 	{ "name": "qk_91_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_91_out", "role": "default" }} , 
 	{ "name": "qk_91_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_91_out", "role": "ap_vld" }} , 
 	{ "name": "grp_fu_465_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_465_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_465_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_465_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_465_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_465_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_465_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_465_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_469_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_469_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_469_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_469_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_469_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_469_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_469_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_469_p_ce", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "14", "EstimateLatencyMax" : "14",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "q", "Type" : "Bram", "Direction" : "I"},
			{"Name" : "k_t", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "qk_124_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "qk_113_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "qk_102_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "qk_91_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter5", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter5", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3 {
		q {Type I LastRead 2 FirstWrite -1}
		k_t {Type I LastRead 2 FirstWrite -1}
		qk_124_out {Type O LastRead -1 FirstWrite 4}
		qk_113_out {Type O LastRead -1 FirstWrite 4}
		qk_102_out {Type O LastRead -1 FirstWrite 4}
		qk_91_out {Type O LastRead -1 FirstWrite 4}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "14", "Max" : "14"}
	, {"Name" : "Interval", "Min" : "14", "Max" : "14"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	q { bram {  { q_Addr_A MemPortADDR2 1 32 }  { q_EN_A MemPortCE2 1 1 }  { q_WEN_A MemPortWE2 1 4 }  { q_Din_A MemPortDIN2 1 32 }  { q_Dout_A MemPortDOUT2 0 32 }  { q_Addr_B MemPortADDR2 1 32 }  { q_EN_B MemPortCE2 1 1 }  { q_WEN_B MemPortWE2 1 4 }  { q_Din_B MemPortDIN2 1 32 }  { q_Dout_B MemPortDOUT2 0 32 } } }
	k_t { ap_memory {  { k_t_address0 mem_address 1 3 }  { k_t_ce0 mem_ce 1 1 }  { k_t_q0 mem_dout 0 32 }  { k_t_address1 MemPortADDR2 1 3 }  { k_t_ce1 MemPortCE2 1 1 }  { k_t_q1 MemPortDOUT2 0 32 } } }
	qk_124_out { ap_vld {  { qk_124_out out_data 1 32 }  { qk_124_out_ap_vld out_vld 1 1 } } }
	qk_113_out { ap_vld {  { qk_113_out out_data 1 32 }  { qk_113_out_ap_vld out_vld 1 1 } } }
	qk_102_out { ap_vld {  { qk_102_out out_data 1 32 }  { qk_102_out_ap_vld out_vld 1 1 } } }
	qk_91_out { ap_vld {  { qk_91_out out_data 1 32 }  { qk_91_out_ap_vld out_vld 1 1 } } }
}
