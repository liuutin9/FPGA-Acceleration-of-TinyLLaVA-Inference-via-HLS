// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
`timescale 1 ns / 1 ps

module AESL_autobram_out_r (
    Clk_A,
    Rst_A,
    EN_A,
    WEN_A,
    Addr_A,
    Din_A,
    Dout_A,
    Clk_B,
    Rst_B,
    EN_B,
    WEN_B,
    Addr_B,
    Din_B,
    Dout_B,
    ready,
    done
);

//------------------------Parameter----------------------
localparam
    TV_IN  = "../tv/cdatafile/c.mat_mul.autotvin_out_r.dat", 
    TV_OUT = "../tv/rtldatafile/rtl.mat_mul.autotvout_out_r.dat"; 
//------------------------Local signal-------------------
parameter DATA_WIDTH = 32'd 32;
parameter ADDR_WIDTH = 32'd 32;
parameter DEPTH = 32'd 16;

// Input and Output
input Clk_A,Clk_B;
input Rst_A,Rst_B;
input EN_A, EN_B;
input [DATA_WIDTH/8 -1 : 0] WEN_A, WEN_B;
input [ADDR_WIDTH - 1 : 0] Addr_A, Addr_B;
input [DATA_WIDTH - 1 : 0] Din_A, Din_B;
output reg [DATA_WIDTH - 1 : 0] Dout_A, Dout_B;
input ready;
input done;
event initialed;
event dut2tb_ap_ready;
event dut2tb_ap_done;
event finished;

// Inner signals
reg [DATA_WIDTH - 1 : 0] mem [0 : DEPTH - 1];
initial begin : initialize_mem
  integer i;
  for (i = 0; i < DEPTH; i = i + 1) begin
      mem[i] = 0;
  end
end
reg written_flag;
event write_process_done;
//------------------------Task and function--------------
task read_token;
	input integer fp;
	output reg [127 :0] token;
  integer ret;
  begin
      token = "";
      ret = 0;
      ret = $fscanf(fp,"%s",token);
	end
endtask

//------------------------Read array-------------------

// Read data form file to array
initial begin : read_file_process
  integer fp;
  integer err;
  integer ret;
  reg [127 : 0] token;
  reg [ 8*5 : 1] str;
  reg [ DATA_WIDTH - 1 : 0] mem_tmp;
    reg [63:0] trans_depth;
    reg [32 -1:0] bin_data;
  integer transaction_idx;
  integer i;
  transaction_idx = 0;

  wait(Rst_A === 0);
  fp = $fopen(TV_IN,"rb");
  if(fp == 0) begin       // Failed to open file
	    $display("Failed to open file \"%s\"!", TV_IN);
	    $finish;
  end
  $fread(trans_depth,fp);
  while (trans_depth != 64'h5a5aa5a50f0ff0f0)  begin
      # 0.2;
	    while(ready !== 1) begin
	        @(posedge Clk_A);
          # 0.2;
      end
	    for(i = 0; i < DEPTH; i = i + 1) begin
          $fread(bin_data,fp);
		    mem[i] = bin_data;
	    end
      $fread(trans_depth,fp);
      transaction_idx = transaction_idx + 1;
      @(posedge Clk_A);
  end
  $fclose(fp);
end

// Read data from array to RTL
initial begin : read_array_A
  while(1) begin
      @(posedge Clk_A);
      # 0.3;
      if(EN_A)
          Dout_A = mem[Addr_A*8/32];
  end
end
initial begin : read_array_B
  while(1) begin
      @(posedge Clk_B);
      # 0.3;
      if(EN_B)
          Dout_B = mem[Addr_B*8/32];
  end
end

//------------------------Write array-------------------

// Write data from RTL to array
initial begin : write_array_A
  while(1) begin
      @(negedge Clk_A);
      if(EN_A) begin
          if(WEN_A[0]) begin
              mem[Addr_A*8/DATA_WIDTH][0*8+7 : 0*8] <= Din_A[0*8+7 : 0*8];
          end
          if(WEN_A[1]) begin
              mem[Addr_A*8/DATA_WIDTH][1*8+7 : 1*8] <= Din_A[1*8+7 : 1*8];
          end
          if(WEN_A[2]) begin
              mem[Addr_A*8/DATA_WIDTH][2*8+7 : 2*8] <= Din_A[2*8+7 : 2*8];
          end
          if(WEN_A[3]) begin
              mem[Addr_A*8/DATA_WIDTH][3*8+7 : 3*8] <= Din_A[3*8+7 : 3*8];
          end
      end
  end
end
initial begin : write_array_B
  while(1) begin
      @(negedge Clk_B);
      if(EN_B) begin
          if(WEN_B[0]) begin
              mem[Addr_B*8/DATA_WIDTH][0*8+7 : 0*8] <= Din_B[0*8+7 : 0*8];
          end
          if(WEN_B[1]) begin
              mem[Addr_B*8/DATA_WIDTH][1*8+7 : 1*8] <= Din_B[1*8+7 : 1*8];
          end
          if(WEN_B[2]) begin
              mem[Addr_B*8/DATA_WIDTH][2*8+7 : 2*8] <= Din_B[2*8+7 : 2*8];
          end
          if(WEN_B[3]) begin
              mem[Addr_B*8/DATA_WIDTH][3*8+7 : 3*8] <= Din_B[3*8+7 : 3*8];
          end
      end
  end
end

task write_binary;
    input integer fp;
    input reg[64-1:0] in;
    input integer in_bw;
    reg [63:0] tmp_long;
    reg[64-1:0] local_in;
    integer char_num;
    integer long_num;
    integer i;
    integer j;
    begin
        long_num = (in_bw + 63) / 64;
        char_num = ((in_bw - 1) % 64 + 7) / 8;
        for(i=long_num;i>0;i=i-1) begin
             local_in = in;
             tmp_long = local_in >> ((i-1)*64);
             for(j=0;j<64;j=j+1)
                 if (tmp_long[j] === 1'bx)
                     tmp_long[j] = 1'b0;
             if (i == long_num) begin
                 case(char_num)
                     1: $fwrite(fp,"%c",tmp_long[7:0]);
                     2: $fwrite(fp,"%c%c",tmp_long[15:8],tmp_long[7:0]);
                     3: $fwrite(fp,"%c%c%c",tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     4: $fwrite(fp,"%c%c%c%c",tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     5: $fwrite(fp,"%c%c%c%c%c",tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     6: $fwrite(fp,"%c%c%c%c%c%c",tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     7: $fwrite(fp,"%c%c%c%c%c%c%c",tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     8: $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
                     default: ;
                 endcase
             end
             else begin
                 $fwrite(fp,"%c%c%c%c%c%c%c%c",tmp_long[63:56],tmp_long[55:48],tmp_long[47:40],tmp_long[39:32],tmp_long[31:24],tmp_long[23:16],tmp_long[15:8],tmp_long[7:0]);
             end
        end
    end
endtask;
// Write data from array to file
initial begin : write_file_proc
	integer fp;
	integer transaction_num;
  reg [ 8*5 : 1] str;
  reg [63:0] bin_data;
	integer i;
	transaction_num = 0;
  written_flag = 0;
  wait(Rst_A === 0);
	while(transaction_num < 1) begin
      # 0.1;
	    while(done !== 1) begin
	        @(posedge Clk_A);
          # 0.1;
      end
        fp = $fopen(TV_OUT, "ab");
        if (fp == 0) begin       // Failed to open file
            $display("Failed to open file \"%s\"!", TV_OUT);
            $finish;
        end
        bin_data = DEPTH;
        write_binary(fp,bin_data,64);
	      for (i = 0; i < DEPTH; i = i + 1) begin
            bin_data = mem[i];
            write_binary(fp,bin_data,32);
        end
	    transaction_num = transaction_num + 1;
	    $fclose(fp);
      written_flag = 1;
      -> write_process_done;
      @(posedge Clk_A);
	end
end

endmodule
