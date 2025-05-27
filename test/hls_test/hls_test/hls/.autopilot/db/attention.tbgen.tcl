set moduleName attention
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_chain
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set svuvm_can_support 1
set cdfgNum 8
set C_modelName {attention}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
dict set ap_memory_interface_dict out_r { MEM_WIDTH 32 MEM_SIZE 24 MASTER_TYPE BRAM_CTRL MEM_ADDRESS_MODE BYTE_ADDRESS PACKAGE_IO port READ_LATENCY 1 }
dict set ap_memory_interface_dict q { MEM_WIDTH 32 MEM_SIZE 24 MASTER_TYPE BRAM_CTRL MEM_ADDRESS_MODE BYTE_ADDRESS PACKAGE_IO port READ_LATENCY 1 }
dict set ap_memory_interface_dict k { MEM_WIDTH 32 MEM_SIZE 24 MASTER_TYPE BRAM_CTRL MEM_ADDRESS_MODE BYTE_ADDRESS PACKAGE_IO port READ_LATENCY 1 }
dict set ap_memory_interface_dict v { MEM_WIDTH 32 MEM_SIZE 24 MASTER_TYPE BRAM_CTRL MEM_ADDRESS_MODE BYTE_ADDRESS PACKAGE_IO port READ_LATENCY 1 }
set C_modelArgList {
	{ out_r int 32 regular {bram 6 { 0 0 } 0 1 }  }
	{ q int 32 regular {bram 6 { 1 1 } 1 1 }  }
	{ k int 32 regular {bram 6 { 1 3 } 1 1 }  }
	{ v int 32 regular {bram 6 { 1 1 } 1 1 }  }
	{ d_k int 32 regular {axi_slave 0}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "out_r", "interface" : "bram", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "q", "interface" : "bram", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "k", "interface" : "bram", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "v", "interface" : "bram", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "d_k", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":16}, "offset_end" : {"in":23}} ]}
# RTL Port declarations: 
set portNum 69
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ out_r_Addr_A sc_out sc_lv 32 signal 0 } 
	{ out_r_EN_A sc_out sc_logic 1 signal 0 } 
	{ out_r_WEN_A sc_out sc_lv 4 signal 0 } 
	{ out_r_Din_A sc_out sc_lv 32 signal 0 } 
	{ out_r_Dout_A sc_in sc_lv 32 signal 0 } 
	{ out_r_Clk_A sc_out sc_logic 1 signal 0 } 
	{ out_r_Rst_A sc_out sc_logic 1 signal 0 } 
	{ out_r_Addr_B sc_out sc_lv 32 signal 0 } 
	{ out_r_EN_B sc_out sc_logic 1 signal 0 } 
	{ out_r_WEN_B sc_out sc_lv 4 signal 0 } 
	{ out_r_Din_B sc_out sc_lv 32 signal 0 } 
	{ out_r_Dout_B sc_in sc_lv 32 signal 0 } 
	{ out_r_Clk_B sc_out sc_logic 1 signal 0 } 
	{ out_r_Rst_B sc_out sc_logic 1 signal 0 } 
	{ q_Addr_A sc_out sc_lv 32 signal 1 } 
	{ q_EN_A sc_out sc_logic 1 signal 1 } 
	{ q_WEN_A sc_out sc_lv 4 signal 1 } 
	{ q_Din_A sc_out sc_lv 32 signal 1 } 
	{ q_Dout_A sc_in sc_lv 32 signal 1 } 
	{ q_Clk_A sc_out sc_logic 1 signal 1 } 
	{ q_Rst_A sc_out sc_logic 1 signal 1 } 
	{ q_Addr_B sc_out sc_lv 32 signal 1 } 
	{ q_EN_B sc_out sc_logic 1 signal 1 } 
	{ q_WEN_B sc_out sc_lv 4 signal 1 } 
	{ q_Din_B sc_out sc_lv 32 signal 1 } 
	{ q_Dout_B sc_in sc_lv 32 signal 1 } 
	{ q_Clk_B sc_out sc_logic 1 signal 1 } 
	{ q_Rst_B sc_out sc_logic 1 signal 1 } 
	{ k_Addr_A sc_out sc_lv 32 signal 2 } 
	{ k_EN_A sc_out sc_logic 1 signal 2 } 
	{ k_WEN_A sc_out sc_lv 4 signal 2 } 
	{ k_Din_A sc_out sc_lv 32 signal 2 } 
	{ k_Dout_A sc_in sc_lv 32 signal 2 } 
	{ k_Clk_A sc_out sc_logic 1 signal 2 } 
	{ k_Rst_A sc_out sc_logic 1 signal 2 } 
	{ v_Addr_A sc_out sc_lv 32 signal 3 } 
	{ v_EN_A sc_out sc_logic 1 signal 3 } 
	{ v_WEN_A sc_out sc_lv 4 signal 3 } 
	{ v_Din_A sc_out sc_lv 32 signal 3 } 
	{ v_Dout_A sc_in sc_lv 32 signal 3 } 
	{ v_Clk_A sc_out sc_logic 1 signal 3 } 
	{ v_Rst_A sc_out sc_logic 1 signal 3 } 
	{ v_Addr_B sc_out sc_lv 32 signal 3 } 
	{ v_EN_B sc_out sc_logic 1 signal 3 } 
	{ v_WEN_B sc_out sc_lv 4 signal 3 } 
	{ v_Din_B sc_out sc_lv 32 signal 3 } 
	{ v_Dout_B sc_in sc_lv 32 signal 3 } 
	{ v_Clk_B sc_out sc_logic 1 signal 3 } 
	{ v_Rst_B sc_out sc_logic 1 signal 3 } 
	{ s_axi_control_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_AWADDR sc_in sc_lv 5 signal -1 } 
	{ s_axi_control_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_control_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_control_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_ARADDR sc_in sc_lv 5 signal -1 } 
	{ s_axi_control_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_control_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_control_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_BRESP sc_out sc_lv 2 signal -1 } 
	{ interrupt sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "s_axi_control_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "control", "role": "AWADDR" },"address":[{"name":"attention","role":"start","value":"0","valid_bit":"0"},{"name":"attention","role":"continue","value":"0","valid_bit":"4"},{"name":"attention","role":"auto_start","value":"0","valid_bit":"7"},{"name":"d_k","role":"data","value":"16"}] },
	{ "name": "s_axi_control_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWVALID" } },
	{ "name": "s_axi_control_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWREADY" } },
	{ "name": "s_axi_control_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WVALID" } },
	{ "name": "s_axi_control_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WREADY" } },
	{ "name": "s_axi_control_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "WDATA" } },
	{ "name": "s_axi_control_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "control", "role": "WSTRB" } },
	{ "name": "s_axi_control_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "control", "role": "ARADDR" },"address":[{"name":"attention","role":"start","value":"0","valid_bit":"0"},{"name":"attention","role":"done","value":"0","valid_bit":"1"},{"name":"attention","role":"idle","value":"0","valid_bit":"2"},{"name":"attention","role":"ready","value":"0","valid_bit":"3"},{"name":"attention","role":"auto_start","value":"0","valid_bit":"7"}] },
	{ "name": "s_axi_control_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARVALID" } },
	{ "name": "s_axi_control_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARREADY" } },
	{ "name": "s_axi_control_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RVALID" } },
	{ "name": "s_axi_control_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RREADY" } },
	{ "name": "s_axi_control_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "RDATA" } },
	{ "name": "s_axi_control_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "RRESP" } },
	{ "name": "s_axi_control_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BVALID" } },
	{ "name": "s_axi_control_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BREADY" } },
	{ "name": "s_axi_control_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "BRESP" } },
	{ "name": "interrupt", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "interrupt" } }, 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "out_r_Addr_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Addr_A" }} , 
 	{ "name": "out_r_EN_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "EN_A" }} , 
 	{ "name": "out_r_WEN_A", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "out_r", "role": "WEN_A" }} , 
 	{ "name": "out_r_Din_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Din_A" }} , 
 	{ "name": "out_r_Dout_A", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Dout_A" }} , 
 	{ "name": "out_r_Clk_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "Clk_A" }} , 
 	{ "name": "out_r_Rst_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "Rst_A" }} , 
 	{ "name": "out_r_Addr_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Addr_B" }} , 
 	{ "name": "out_r_EN_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "EN_B" }} , 
 	{ "name": "out_r_WEN_B", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "out_r", "role": "WEN_B" }} , 
 	{ "name": "out_r_Din_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Din_B" }} , 
 	{ "name": "out_r_Dout_B", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "Dout_B" }} , 
 	{ "name": "out_r_Clk_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "Clk_B" }} , 
 	{ "name": "out_r_Rst_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "Rst_B" }} , 
 	{ "name": "q_Addr_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Addr_A" }} , 
 	{ "name": "q_EN_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "q", "role": "EN_A" }} , 
 	{ "name": "q_WEN_A", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "q", "role": "WEN_A" }} , 
 	{ "name": "q_Din_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Din_A" }} , 
 	{ "name": "q_Dout_A", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Dout_A" }} , 
 	{ "name": "q_Clk_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "q", "role": "Clk_A" }} , 
 	{ "name": "q_Rst_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "q", "role": "Rst_A" }} , 
 	{ "name": "q_Addr_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Addr_B" }} , 
 	{ "name": "q_EN_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "q", "role": "EN_B" }} , 
 	{ "name": "q_WEN_B", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "q", "role": "WEN_B" }} , 
 	{ "name": "q_Din_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Din_B" }} , 
 	{ "name": "q_Dout_B", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "q", "role": "Dout_B" }} , 
 	{ "name": "q_Clk_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "q", "role": "Clk_B" }} , 
 	{ "name": "q_Rst_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "q", "role": "Rst_B" }} , 
 	{ "name": "k_Addr_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k", "role": "Addr_A" }} , 
 	{ "name": "k_EN_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "k", "role": "EN_A" }} , 
 	{ "name": "k_WEN_A", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "k", "role": "WEN_A" }} , 
 	{ "name": "k_Din_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k", "role": "Din_A" }} , 
 	{ "name": "k_Dout_A", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k", "role": "Dout_A" }} , 
 	{ "name": "k_Clk_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "k", "role": "Clk_A" }} , 
 	{ "name": "k_Rst_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "k", "role": "Rst_A" }} , 
 	{ "name": "v_Addr_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v", "role": "Addr_A" }} , 
 	{ "name": "v_EN_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "v", "role": "EN_A" }} , 
 	{ "name": "v_WEN_A", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "v", "role": "WEN_A" }} , 
 	{ "name": "v_Din_A", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v", "role": "Din_A" }} , 
 	{ "name": "v_Dout_A", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v", "role": "Dout_A" }} , 
 	{ "name": "v_Clk_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "v", "role": "Clk_A" }} , 
 	{ "name": "v_Rst_A", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "v", "role": "Rst_A" }} , 
 	{ "name": "v_Addr_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v", "role": "Addr_B" }} , 
 	{ "name": "v_EN_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "v", "role": "EN_B" }} , 
 	{ "name": "v_WEN_B", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "v", "role": "WEN_B" }} , 
 	{ "name": "v_Din_B", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v", "role": "Din_B" }} , 
 	{ "name": "v_Dout_B", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "v", "role": "Dout_B" }} , 
 	{ "name": "v_Clk_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "v", "role": "Clk_B" }} , 
 	{ "name": "v_Rst_B", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "v", "role": "Rst_B" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "4", "6", "9", "13", "16", "17", "18"],
		"CDFG" : "attention",
		"Protocol" : "ap_ctrl_chain",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "110", "EstimateLatencyMax" : "110",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "out_r", "Type" : "Bram", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "13", "SubInstance" : "grp_attention_Pipeline_VITIS_LOOP_8_1_fu_226", "Port" : "out_r", "Inst_start_state" : "9", "Inst_end_state" : "10"}]},
			{"Name" : "q", "Type" : "Bram", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "4", "SubInstance" : "grp_attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3_fu_189", "Port" : "q", "Inst_start_state" : "3", "Inst_end_state" : "4"}]},
			{"Name" : "k", "Type" : "Bram", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_attention_Pipeline_VITIS_LOOP_7_1_VITIS_LOOP_8_2_fu_181", "Port" : "k", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "v", "Type" : "Bram", "Direction" : "I"},
			{"Name" : "d_k", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.k_t_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_7_1_VITIS_LOOP_8_2_fu_181", "Parent" : "0", "Child" : ["3"],
		"CDFG" : "attention_Pipeline_VITIS_LOOP_7_1_VITIS_LOOP_8_2",
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
			{"Name" : "k", "Type" : "Bram", "Direction" : "I"},
			{"Name" : "k_t", "Type" : "Memory", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_7_1_VITIS_LOOP_8_2", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter1", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "3", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_7_1_VITIS_LOOP_8_2_fu_181.flow_control_loop_pipe_sequential_init_U", "Parent" : "2"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3_fu_189", "Parent" : "0", "Child" : ["5"],
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
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3_fu_189.flow_control_loop_pipe_sequential_init_U", "Parent" : "4"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2_fu_200", "Parent" : "0", "Child" : ["7", "8"],
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
	{"ID" : "7", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2_fu_200.sdiv_32ns_32ns_32_36_1_U9", "Parent" : "6"},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2_fu_200.flow_control_loop_pipe_sequential_init_U", "Parent" : "6"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4_fu_214", "Parent" : "0", "Child" : ["10", "11", "12"],
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
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4_fu_214.sitodp_32ns_64_4_no_dsp_1_U20", "Parent" : "9"},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4_fu_214.dexp_64ns_64ns_64_20_full_dsp_1_U21", "Parent" : "9"},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4_fu_214.flow_control_loop_pipe_sequential_init_U", "Parent" : "9"},
	{"ID" : "13", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_8_1_fu_226", "Parent" : "0", "Child" : ["14", "15"],
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
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_8_1_fu_226.mul_32s_32s_32_2_1_U34", "Parent" : "13"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_attention_Pipeline_VITIS_LOOP_8_1_fu_226.flow_control_loop_pipe_sequential_init_U", "Parent" : "13"},
	{"ID" : "16", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.control_s_axi_U", "Parent" : "0"},
	{"ID" : "17", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U45", "Parent" : "0"},
	{"ID" : "18", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_32s_32_2_1_U46", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	attention {
		out_r {Type O LastRead -1 FirstWrite 3}
		q {Type I LastRead 2 FirstWrite -1}
		k {Type I LastRead 0 FirstWrite -1}
		v {Type I LastRead 8 FirstWrite -1}
		d_k {Type I LastRead 4 FirstWrite -1}}
	attention_Pipeline_VITIS_LOOP_7_1_VITIS_LOOP_8_2 {
		k {Type I LastRead 0 FirstWrite -1}
		k_t {Type O LastRead -1 FirstWrite 1}}
	attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3 {
		q {Type I LastRead 2 FirstWrite -1}
		k_t {Type I LastRead 2 FirstWrite -1}
		qk_124_out {Type O LastRead -1 FirstWrite 4}
		qk_113_out {Type O LastRead -1 FirstWrite 4}
		qk_102_out {Type O LastRead -1 FirstWrite 4}
		qk_91_out {Type O LastRead -1 FirstWrite 4}}
	attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2 {
		qk_102_reload {Type I LastRead 0 FirstWrite -1}
		qk_91_reload {Type I LastRead 0 FirstWrite -1}
		qk_124_reload {Type I LastRead 0 FirstWrite -1}
		qk_113_reload {Type I LastRead 0 FirstWrite -1}
		d_k {Type I LastRead 0 FirstWrite -1}
		qk_scaled_3_out {Type O LastRead -1 FirstWrite 34}
		qk_scaled_2_out {Type O LastRead -1 FirstWrite 34}
		qk_scaled_1_out {Type O LastRead -1 FirstWrite 34}
		qk_scaled_out {Type O LastRead -1 FirstWrite 34}}
	attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4 {
		qk_scaled_1_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_3_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_2_reload {Type I LastRead 0 FirstWrite -1}
		qk_scaled_exp_3_out {Type O LastRead -1 FirstWrite 25}
		qk_scaled_exp_2_out {Type O LastRead -1 FirstWrite 25}
		qk_scaled_exp_1_out {Type O LastRead -1 FirstWrite 25}
		qk_scaled_exp_out {Type O LastRead -1 FirstWrite 25}}
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
	{"Name" : "Latency", "Min" : "110", "Max" : "110"}
	, {"Name" : "Interval", "Min" : "111", "Max" : "111"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	out_r { bram {  { out_r_Addr_A MemPortADDR2 1 32 }  { out_r_EN_A MemPortCE2 1 1 }  { out_r_WEN_A MemPortWE2 1 4 }  { out_r_Din_A MemPortDIN2 1 32 }  { out_r_Dout_A MemPortDOUT2 0 32 }  { out_r_Clk_A mem_clk 1 1 }  { out_r_Rst_A mem_rst 1 1 }  { out_r_Addr_B MemPortADDR2 1 32 }  { out_r_EN_B MemPortCE2 1 1 }  { out_r_WEN_B MemPortWE2 1 4 }  { out_r_Din_B MemPortDIN2 1 32 }  { out_r_Dout_B MemPortDOUT2 0 32 }  { out_r_Clk_B mem_clk 1 1 }  { out_r_Rst_B mem_rst 1 1 } } }
	q { bram {  { q_Addr_A MemPortADDR2 1 32 }  { q_EN_A MemPortCE2 1 1 }  { q_WEN_A MemPortWE2 1 4 }  { q_Din_A MemPortDIN2 1 32 }  { q_Dout_A MemPortDOUT2 0 32 }  { q_Clk_A mem_clk 1 1 }  { q_Rst_A mem_rst 1 1 }  { q_Addr_B MemPortADDR2 1 32 }  { q_EN_B MemPortCE2 1 1 }  { q_WEN_B MemPortWE2 1 4 }  { q_Din_B MemPortDIN2 1 32 }  { q_Dout_B MemPortDOUT2 0 32 }  { q_Clk_B mem_clk 1 1 }  { q_Rst_B mem_rst 1 1 } } }
	k { bram {  { k_Addr_A MemPortADDR2 1 32 }  { k_EN_A MemPortCE2 1 1 }  { k_WEN_A MemPortWE2 1 4 }  { k_Din_A MemPortDIN2 1 32 }  { k_Dout_A MemPortDOUT2 0 32 }  { k_Clk_A mem_clk 1 1 }  { k_Rst_A mem_rst 1 1 } } }
	v { bram {  { v_Addr_A MemPortADDR2 1 32 }  { v_EN_A MemPortCE2 1 1 }  { v_WEN_A MemPortWE2 1 4 }  { v_Din_A MemPortDIN2 1 32 }  { v_Dout_A MemPortDOUT2 0 32 }  { v_Clk_A mem_clk 1 1 }  { v_Rst_A mem_rst 1 1 }  { v_Addr_B MemPortADDR2 1 32 }  { v_EN_B MemPortCE2 1 1 }  { v_WEN_B MemPortWE2 1 4 }  { v_Din_B MemPortDIN2 1 32 }  { v_Dout_B MemPortDOUT2 0 32 }  { v_Clk_B mem_clk 1 1 }  { v_Rst_B mem_rst 1 1 } } }
}

set maxi_interface_dict [dict create]

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
