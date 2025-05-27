set SynModuleInfo {
  {SRCNAME attention_Pipeline_VITIS_LOOP_7_1_VITIS_LOOP_8_2 MODELNAME attention_Pipeline_VITIS_LOOP_7_1_VITIS_LOOP_8_2 RTLNAME attention_attention_Pipeline_VITIS_LOOP_7_1_VITIS_LOOP_8_2
    SUBMODULES {
      {MODELNAME attention_flow_control_loop_pipe_sequential_init RTLNAME attention_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME attention_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3 MODELNAME attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3 RTLNAME attention_attention_Pipeline_VITIS_LOOP_8_1_VITIS_LOOP_9_2_VITIS_LOOP_11_3}
  {SRCNAME attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2 MODELNAME attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2 RTLNAME attention_attention_Pipeline_VITIS_LOOP_25_1_VITIS_LOOP_26_2
    SUBMODULES {
      {MODELNAME attention_sdiv_32ns_32ns_32_36_1 RTLNAME attention_sdiv_32ns_32ns_32_36_1 BINDTYPE op TYPE sdiv IMPL auto LATENCY 35 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4 MODELNAME attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4 RTLNAME attention_attention_Pipeline_VITIS_LOOP_31_3_VITIS_LOOP_32_4
    SUBMODULES {
      {MODELNAME attention_sitodp_32ns_64_4_no_dsp_1 RTLNAME attention_sitodp_32ns_64_4_no_dsp_1 BINDTYPE op TYPE sitodp IMPL auto LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME attention_dexp_64ns_64ns_64_20_full_dsp_1 RTLNAME attention_dexp_64ns_64ns_64_20_full_dsp_1 BINDTYPE op TYPE dexp IMPL fulldsp LATENCY 19 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME attention_Pipeline_VITIS_LOOP_8_1 MODELNAME attention_Pipeline_VITIS_LOOP_8_1 RTLNAME attention_attention_Pipeline_VITIS_LOOP_8_1}
  {SRCNAME attention MODELNAME attention RTLNAME attention IS_TOP 1
    SUBMODULES {
      {MODELNAME attention_mul_32s_32s_32_2_1 RTLNAME attention_mul_32s_32s_32_2_1 BINDTYPE op TYPE mul IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME attention_k_t_RAM_AUTO_1R1W RTLNAME attention_k_t_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME attention_control_s_axi RTLNAME attention_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
