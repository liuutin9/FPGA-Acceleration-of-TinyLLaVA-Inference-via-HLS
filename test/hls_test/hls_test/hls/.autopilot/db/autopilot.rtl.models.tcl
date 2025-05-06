set SynModuleInfo {
  {SRCNAME mat_mul MODELNAME mat_mul RTLNAME mat_mul IS_TOP 1
    SUBMODULES {
      {MODELNAME mat_mul_mul_32s_32s_32_2_1 RTLNAME mat_mul_mul_32s_32s_32_2_1 BINDTYPE op TYPE mul IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME mat_mul_control_s_axi RTLNAME mat_mul_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME mat_mul_flow_control_loop_delay_pipe RTLNAME mat_mul_flow_control_loop_delay_pipe BINDTYPE interface TYPE internal_upc_flow_control INSTNAME mat_mul_flow_control_loop_delay_pipe_U}
    }
  }
}
