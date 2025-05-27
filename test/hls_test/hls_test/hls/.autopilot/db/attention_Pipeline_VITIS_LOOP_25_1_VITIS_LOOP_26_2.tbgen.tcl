set moduleName attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2
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
set C_modelName {attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ qk_102_reload int 32 regular  }
	{ qk_91_reload int 32 regular  }
	{ qk_124_reload int 32 regular  }
	{ qk_113_reload int 32 regular  }
	{ d_k int 32 regular  }
	{ qk_scaled_3_out int 32 regular {pointer 1}  }
	{ qk_scaled_2_out int 32 regular {pointer 1}  }
	{ qk_scaled_1_out int 32 regular {pointer 1}  }
	{ qk_scaled_out int 32 regular {pointer 1}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "qk_102_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_91_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_124_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_113_reload", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "d_k", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "qk_scaled_3_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_scaled_2_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_scaled_1_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "qk_scaled_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 19
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ qk_102_reload sc_in sc_lv 32 signal 0 } 
	{ qk_91_reload sc_in sc_lv 32 signal 1 } 
	{ qk_124_reload sc_in sc_lv 32 signal 2 } 
	{ qk_113_reload sc_in sc_lv 32 signal 3 } 
	{ d_k sc_in sc_lv 32 signal 4 } 
	{ qk_scaled_3_out sc_out sc_lv 32 signal 5 } 
	{ qk_scaled_3_out_ap_vld sc_out sc_logic 1 outvld 5 } 
	{ qk_scaled_2_out sc_out sc_lv 32 signal 6 } 
	{ qk_scaled_2_out_ap_vld sc_out sc_logic 1 outvld 6 } 
	{ qk_scaled_1_out sc_out sc_lv 32 signal 7 } 
	{ qk_scaled_1_out_ap_vld sc_out sc_logic 1 outvld 7 } 
	{ qk_scaled_out sc_out sc_lv 32 signal 8 } 
	{ qk_scaled_out_ap_vld sc_out sc_logic 1 outvld 8 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "qk_102_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_102_reload", "role": "default" }} , 
 	{ "name": "qk_91_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_91_reload", "role": "default" }} , 
 	{ "name": "qk_124_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_124_reload", "role": "default" }} , 
 	{ "name": "qk_113_reload", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_113_reload", "role": "default" }} , 
 	{ "name": "d_k", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "d_k", "role": "default" }} , 
 	{ "name": "qk_scaled_3_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_3_out", "role": "default" }} , 
 	{ "name": "qk_scaled_3_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_scaled_3_out", "role": "ap_vld" }} , 
 	{ "name": "qk_scaled_2_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_2_out", "role": "default" }} , 
 	{ "name": "qk_scaled_2_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_scaled_2_out", "role": "ap_vld" }} , 
 	{ "name": "qk_scaled_1_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_1_out", "role": "default" }} , 
 	{ "name": "qk_scaled_1_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_scaled_1_out", "role": "ap_vld" }} , 
 	{ "name": "qk_scaled_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "qk_scaled_out", "role": "default" }} , 
 	{ "name": "qk_scaled_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "qk_scaled_out", "role": "ap_vld" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2"],
		"CDFG" : "attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "40", "EstimateLatencyMax" : "40",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "qk_102_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_91_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_124_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_113_reload", "Type" : "None", "Direction" : "I"},
			{"Name" : "d_k", "Type" : "None", "Direction" : "I"},
			{"Name" : "qk_scaled_3_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "qk_scaled_2_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "qk_scaled_1_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "qk_scaled_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_25_1_VITIS_LOOP_26_2", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter35", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter35", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sdiv_32ns_32ns_32_36_1_U9", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2 {
		qk_102_reload {Type I LastRead 0 FirstWrite -1}
		qk_91_reload {Type I LastRead 0 FirstWrite -1}
		qk_124_reload {Type I LastRead 0 FirstWrite -1}
		qk_113_reload {Type I LastRead 0 FirstWrite -1}
		d_k {Type I LastRead 0 FirstWrite -1}
		qk_scaled_3_out {Type O LastRead -1 FirstWrite 34}
		qk_scaled_2_out {Type O LastRead -1 FirstWrite 34}
		qk_scaled_1_out {Type O LastRead -1 FirstWrite 34}
		qk_scaled_out {Type O LastRead -1 FirstWrite 34}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "40", "Max" : "40"}
	, {"Name" : "Interval", "Min" : "40", "Max" : "40"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	qk_102_reload { ap_none {  { qk_102_reload in_data 0 32 } } }
	qk_91_reload { ap_none {  { qk_91_reload in_data 0 32 } } }
	qk_124_reload { ap_none {  { qk_124_reload in_data 0 32 } } }
	qk_113_reload { ap_none {  { qk_113_reload in_data 0 32 } } }
	d_k { ap_none {  { d_k in_data 0 32 } } }
	qk_scaled_3_out { ap_vld {  { qk_scaled_3_out out_data 1 32 }  { qk_scaled_3_out_ap_vld out_vld 1 1 } } }
	qk_scaled_2_out { ap_vld {  { qk_scaled_2_out out_data 1 32 }  { qk_scaled_2_out_ap_vld out_vld 1 1 } } }
	qk_scaled_1_out { ap_vld {  { qk_scaled_1_out out_data 1 32 }  { qk_scaled_1_out_ap_vld out_vld 1 1 } } }
	qk_scaled_out { ap_vld {  { qk_scaled_out out_data 1 32 }  { qk_scaled_out_ap_vld out_vld 1 1 } } }
}
