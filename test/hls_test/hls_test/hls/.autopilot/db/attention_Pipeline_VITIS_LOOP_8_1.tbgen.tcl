set moduleName attention_Pipeline_VITIS_LOOP_8_1
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
set C_modelName {attention_Pipeline_VITIS_LOOP_8_1}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
dict set ap_memory_interface_dict out_r { MEM_WIDTH 32 MEM_SIZE 24 MASTER_TYPE BRAM_CTRL MEM_ADDRESS_MODE BYTE_ADDRESS PACKAGE_IO port READ_LATENCY 1 }
set C_modelArgList {
	{ out_r int 32 regular {bram 6 { 0 0 } 0 1 }  }
	{ qk_scaled_exp_2_reload int 32 regular  }
	{ qk_scaled_exp_reload int 32 regular  }
	{ qk_scaled_exp_3_reload int 32 regular  }
	{ qk_scaled_exp_1_reload int 32 regular  }
	{ v_load int 32 regular  }
	{ v_load_1 int 32 regular  }
	{ v_load_2 int 32 regular  }
	{ v_load_3 int 32 regular  }
	{ v_load_4 int 32 regular  }
	{ v_load_5 int 32 regular  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "out_r", "interface" : "bram", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_scaled_exp_2_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_scaled_exp_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_scaled_exp_3_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_scaled_exp_1_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "v_load", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "v_load_1", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "v_load_2", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "v_load_3", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "v_load_4", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "v_load_5", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 34
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ out_r_Addr_A sc_out sc_lv 32 signal 0 } 
	{ out_r_EN_A sc_out sc_logic 1 signal 0 } 
	{ out_r_WEN_A sc_out sc_lv 4 signal 0 } 
	{ out_r_Din_A sc_out sc_lv 32 signal 0 } 
	{ out_r_Dout_A sc_in sc_lv 32 signal 0 } 
	{ out_r_Addr_B sc_out sc_lv 32 signal 0 } 
	{ out_r_EN_B sc_out sc_logic 1 signal 0 } 
	{ out_r_WEN_B sc_out sc_lv 4 signal 0 } 
	{ out_r_Din_B sc_out sc_lv 32 signal 0 } 
	{ out_r_Dout_B sc_in sc_lv 32 signal 0 } 
	{ qk_scaled_exp_2_reload sc_in sc_lv 32 signal 1 } 
	{ qk_scaled_exp_reload sc_in sc_lv 32 signal 2 } 
	{ qk_scaled_exp_3_reload sc_in sc_lv 32 signal 3 } 
	{ qk_scaled_exp_1_reload sc_in sc_lv 32 signal 4 } 
	{ v_load sc_in sc_lv 32 signal 5 } 
	{ v_load_1 sc_in sc_lv 32 signal 6 } 
	{ v_load_2 sc_in sc_lv 32 signal 7 } 
	{ v_load_3 sc_in sc_lv 32 signal 8 } 
	{ v_load_4 sc_in sc_lv 32 signal 9 } 
	{ v_load_5 sc_in sc_lv 32 signal 10 } 
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
 	{ "name": "out_r_Addr_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Addr_A" }} , 
 	{ "name": "out_r_EN_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "EN_A" }} , 
 	{ "name": "out_r_WEN_A", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "out_r", "role": "WEN_A" }} , 
 	{ "name": "out_r_Din_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Din_A" }} , 
 	{ "name": "out_r_Dout_A", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Dout_A" }} , 
 	{ "name": "out_r_Addr_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Addr_B" }} , 
 	{ "name": "out_r_EN_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "EN_B" }} , 
 	{ "name": "out_r_WEN_B", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "out_r", "role": "WEN_B" }} , 
 	{ "name": "out_r_Din_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Din_B" }} , 
 	{ "name": "out_r_Dout_B", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Dout_B" }} , 
 	{ "name": "qk_scaled_exp_2_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_exp_2_reload", "role": "default" }} , 
 	{ "name": "qk_scaled_exp_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_exp_reload", "role": "default" }} , 
 	{ "name": "qk_scaled_exp_3_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_exp_3_reload", "role": "default" }} , 
 	{ "name": "qk_scaled_exp_1_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_exp_1_reload", "role": "default" }} , 
 	{ "name": "v_load", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v_load", "role": "default" }} , 
 	{ "name": "v_load_1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v_load_1", "role": "default" }} , 
 	{ "name": "v_load_2", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v_load_2", "role": "default" }} , 
 	{ "name": "v_load_3", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v_load_3", "role": "default" }} , 
 	{ "name": "v_load_4", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v_load_4", "role": "default" }} , 
 	{ "name": "v_load_5", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v_load_5", "role": "default" }} , 
 	{ "name": "grp_fu_465_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_465_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_465_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_465_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_465_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_465_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_465_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_465_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_469_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_469_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_469_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_469_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_469_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "grp_fu_469_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_469_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_469_p_ce", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2"],
		"CDFG" : "attention_Pipeline_VITIS_LOOP_8_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "8", "EstimateLatencyMax" : "8",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "out_r", "Type" : "Bram", "Direction" : "O"},
			{"Name" : "qk_scaled_exp_2_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_scaled_exp_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_scaled_exp_3_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_scaled_exp_1_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "v_load", "Type" : "None", "Direction" : "I"},
			{"Name" : "v_load_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "v_load_2", "Type" : "None", "Direction" : "I"},
			{"Name" : "v_load_3", "Type" : "None", "Direction" : "I"},
			{"Name" : "v_load_4", "Type" : "None", "Direction" : "I"},
			{"Name" : "v_load_5", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_8_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "2", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter2", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U34", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	attention_Pipeline_VITIS_LOOP_8_1 {
		out_r {Type O LastRead -1 FirstWrite 3}
		qk_scaled_exp_2_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_exp_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_exp_3_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_exp_1_reload {Type I LastRead 0 FirstWrite -1}
		v_load {Type I LastRead 0 FirstWrite -1}
		v_load_1 {Type I LastRead 0 FirstWrite -1}
		v_load_2 {Type I LastRead 0 FirstWrite -1}
		v_load_3 {Type I LastRead 0 FirstWrite -1}
		v_load_4 {Type I LastRead 0 FirstWrite -1}
		v_load_5 {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "8", "Max" : "8"}
	, {"Name" : "Interval", "Min" : "8", "Max" : "8"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	out_r { bram {  { out_r_Addr_A MemPortADDR2 1 32 }  { out_r_EN_A MemPortCE2 1 1 }  { out_r_WEN_A MemPortWE2 1 4 }  { out_r_Din_A MemPortDIN2 1 32 }  { out_r_Dout_A MemPortDOUT2 0 32 }  { out_r_Addr_B MemPortADDR2 1 32 }  { out_r_EN_B MemPortCE2 1 1 }  { out_r_WEN_B MemPortWE2 1 4 }  { out_r_Din_B MemPortDIN2 1 32 }  { out_r_Dout_B MemPortDOUT2 0 32 } } }
	qk_scaled_exp_2_reload { ap_none {  { qk_scaled_exp_2_reload in_data 0 32 } } }
	qk_scaled_exp_reload { ap_none {  { qk_scaled_exp_reload in_data 0 32 } } }
	qk_scaled_exp_3_reload { ap_none {  { qk_scaled_exp_3_reload in_data 0 32 } } }
	qk_scaled_exp_1_reload { ap_none {  { qk_scaled_exp_1_reload in_data 0 32 } } }
	v_load { ap_none {  { v_load in_data 0 32 } } }
	v_load_1 { ap_none {  { v_load_1 in_data 0 32 } } }
	v_load_2 { ap_none {  { v_load_2 in_data 0 32 } } }
	v_load_3 { ap_none {  { v_load_3 in_data 0 32 } } }
	v_load_4 { ap_none {  { v_load_4 in_data 0 32 } } }
	v_load_5 { ap_none {  { v_load_5 in_data 0 32 } } }
}
