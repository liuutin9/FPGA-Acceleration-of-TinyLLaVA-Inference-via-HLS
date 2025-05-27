set ModuleHierarchy {[{
"Name" : "attention","ID" : "0","Type" : "sequential",
"SubInsts" : [
	{"Name" : "grp_attention_Pipeline_VITIS_LOOP_7_1_VITIS_LOOP_8_2_fu_181","ID" : "1","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_7_1_VITIS_LOOP_8_2","ID" : "2","Type" : "pipeline"},]},
	{"Name" : "grp_attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3_fu_189","ID" : "3","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3","ID" : "4","Type" : "pipeline"},]},
	{"Name" : "grp_attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2_fu_200","ID" : "5","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_25_1_VITIS_LOOP_26_2","ID" : "6","Type" : "pipeline"},]},
	{"Name" : "grp_attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4_fu_214","ID" : "7","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_31_3_VITIS_LOOP_32_4","ID" : "8","Type" : "pipeline"},]},
	{"Name" : "grp_attention_Pipeline_VITIS_LOOP_8_1_fu_226","ID" : "9","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_8_1","ID" : "10","Type" : "pipeline"},]},]
}]}