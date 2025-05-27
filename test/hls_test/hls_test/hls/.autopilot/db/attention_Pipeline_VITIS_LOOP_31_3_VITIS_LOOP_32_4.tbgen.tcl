set moduleName attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4
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
set C_modelName {attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ qk_scaled_1_reload int 32 regular  }
	{ qk_scaled_reload int 32 regular  }
	{ qk_scaled_3_reload int 32 regular  }
	{ qk_scaled_2_reload int 32 regular  }
	{ qk_scaled_exp_3_out int 32 regular {pointer 1}  }
	{ qk_scaled_exp_2_out int 32 regular {pointer 1}  }
	{ qk_scaled_exp_1_out int 32 regular {pointer 1}  }
	{ qk_scaled_exp_out int 32 regular {pointer 1}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "qk_scaled_1_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_scaled_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_scaled_3_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_scaled_2_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_scaled_exp_3_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_scaled_exp_2_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_scaled_exp_1_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_scaled_exp_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 18
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ qk_scaled_1_reload sc_in sc_lv 32 signal 0 } 
	{ qk_scaled_reload sc_in sc_lv 32 signal 1 } 
	{ qk_scaled_3_reload sc_in sc_lv 32 signal 2 } 
	{ qk_scaled_2_reload sc_in sc_lv 32 signal 3 } 
	{ qk_scaled_exp_3_out sc_out sc_lv 32 signal 4 } 
	{ qk_scaled_exp_3_out_ap_vld sc_out sc_logic 1 outvld 4 } 
	{ qk_scaled_exp_2_out sc_out sc_lv 32 signal 5 } 
	{ qk_scaled_exp_2_out_ap_vld sc_out sc_logic 1 outvld 5 } 
	{ qk_scaled_exp_1_out sc_out sc_lv 32 signal 6 } 
	{ qk_scaled_exp_1_out_ap_vld sc_out sc_logic 1 outvld 6 } 
	{ qk_scaled_exp_out sc_out sc_lv 32 signal 7 } 
	{ qk_scaled_exp_out_ap_vld sc_out sc_logic 1 outvld 7 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "qk_scaled_1_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_1_reload", "role": "default" }} , 
 	{ "name": "qk_scaled_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_reload", "role": "default" }} , 
 	{ "name": "qk_scaled_3_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_3_reload", "role": "default" }} , 
 	{ "name": "qk_scaled_2_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_2_reload", "role": "default" }} , 
 	{ "name": "qk_scaled_exp_3_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_exp_3_out", "role": "default" }} , 
 	{ "name": "qk_scaled_exp_3_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_scaled_exp_3_out", "role": "ap_vld" }} , 
 	{ "name": "qk_scaled_exp_2_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_exp_2_out", "role": "default" }} , 
 	{ "name": "qk_scaled_exp_2_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_scaled_exp_2_out", "role": "ap_vld" }} , 
 	{ "name": "qk_scaled_exp_1_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_exp_1_out", "role": "default" }} , 
 	{ "name": "qk_scaled_exp_1_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_scaled_exp_1_out", "role": "ap_vld" }} , 
 	{ "name": "qk_scaled_exp_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_exp_out", "role": "default" }} , 
 	{ "name": "qk_scaled_exp_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_scaled_exp_out", "role": "ap_vld" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3"],
		"CDFG" : "attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "31", "EstimateLatencyMax" : "31",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "qk_scaled_1_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_scaled_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_scaled_3_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_scaled_2_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_scaled_exp_3_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "qk_scaled_exp_2_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "qk_scaled_exp_1_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "qk_scaled_exp_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_31_3_VITIS_LOOP_32_4", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter26", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter26", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sitodp_32ns_64_4_no_dsp_1_U20", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dexp_64ns_64ns_64_20_full_dsp_1_U21", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4 {
		qk_scaled_1_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_3_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_2_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_exp_3_out {Type O LastRead -1 FirstWrite 25}
		qk_scaled_exp_2_out {Type O LastRead -1 FirstWrite 25}
		qk_scaled_exp_1_out {Type O LastRead -1 FirstWrite 25}
		qk_scaled_exp_out {Type O LastRead -1 FirstWrite 25}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "31", "Max" : "31"}
	, {"Name" : "Interval", "Min" : "31", "Max" : "31"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	qk_scaled_1_reload { ap_none {  { qk_scaled_1_reload in_data 0 32 } } }
	qk_scaled_reload { ap_none {  { qk_scaled_reload in_data 0 32 } } }
	qk_scaled_3_reload { ap_none {  { qk_scaled_3_reload in_data 0 32 } } }
	qk_scaled_2_reload { ap_none {  { qk_scaled_2_reload in_data 0 32 } } }
	qk_scaled_exp_3_out { ap_vld {  { qk_scaled_exp_3_out out_data 1 32 }  { qk_scaled_exp_3_out_ap_vld out_vld 1 1 } } }
	qk_scaled_exp_2_out { ap_vld {  { qk_scaled_exp_2_out out_data 1 32 }  { qk_scaled_exp_2_out_ap_vld out_vld 1 1 } } }
	qk_scaled_exp_1_out { ap_vld {  { qk_scaled_exp_1_out out_data 1 32 }  { qk_scaled_exp_1_out_ap_vld out_vld 1 1 } } }
	qk_scaled_exp_out { ap_vld {  { qk_scaled_exp_out out_data 1 32 }  { qk_scaled_exp_out_ap_vld out_vld 1 1 } } }
}
