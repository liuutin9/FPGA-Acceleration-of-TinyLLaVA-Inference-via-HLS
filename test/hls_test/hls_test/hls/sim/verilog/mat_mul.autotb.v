// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
 `timescale 1ns/1ps


`define AUTOTB_DUT      mat_mul
`define AUTOTB_DUT_INST AESL_inst_mat_mul
`define AUTOTB_TOP      apatb_mat_mul_top
`define AUTOTB_LAT_RESULT_FILE "mat_mul.result.lat.rb"
`define AUTOTB_PER_RESULT_TRANS_FILE "mat_mul.performance.result.transaction.xml"
`define AUTOTB_TOP_INST AESL_inst_apatb_mat_mul_top
`define AUTOTB_MAX_ALLOW_LATENCY  15000000
`define AUTOTB_CLOCK_PERIOD_DIV2 1.67

`define AESL_BRAM_in1 AESL_autobram_in1
`define AESL_BRAM_INST_in1 bram_inst_in1
`define AESL_BRAM_in2 AESL_autobram_in2
`define AESL_BRAM_INST_in2 bram_inst_in2
`define AESL_BRAM_out_r AESL_autobram_out_r
`define AESL_BRAM_INST_out_r bram_inst_out_r
`define AUTOTB_TVIN_in1  "../tv/cdatafile/c.mat_mul.autotvin_in1.dat"
`define AUTOTB_TVIN_in2  "../tv/cdatafile/c.mat_mul.autotvin_in2.dat"
`define AUTOTB_TVIN_out_r  "../tv/cdatafile/c.mat_mul.autotvin_out_r.dat"
`define AUTOTB_TVIN_in1_out_wrapc  "../tv/rtldatafile/rtl.mat_mul.autotvin_in1.dat"
`define AUTOTB_TVIN_in2_out_wrapc  "../tv/rtldatafile/rtl.mat_mul.autotvin_in2.dat"
`define AUTOTB_TVIN_out_r_out_wrapc  "../tv/rtldatafile/rtl.mat_mul.autotvin_out_r.dat"
`define AUTOTB_TVOUT_out_r  "../tv/cdatafile/c.mat_mul.autotvout_out_r.dat"
`define AUTOTB_TVOUT_out_r_out_wrapc  "../tv/rtldatafile/rtl.mat_mul.autotvout_out_r.dat"
module `AUTOTB_TOP;

parameter AUTOTB_TRANSACTION_NUM = 1;
parameter PROGRESS_TIMEOUT = 10000000;
parameter LATENCY_ESTIMATION = 37;
parameter LENGTH_in1 = 16;
parameter LENGTH_in2 = 16;
parameter LENGTH_out_r = 16;

task read_token;
    input integer fp;
    output reg [191 : 0] token;
    integer ret;
    begin
        token = "";
        ret = 0;
        ret = $fscanf(fp,"%s",token);
    end
endtask

reg AESL_clock;
reg rst;
reg dut_rst;
reg start;
reg ce;
reg tb_continue;
wire AESL_start;
wire AESL_reset;
wire AESL_ce;
wire AESL_ready;
wire AESL_idle;
wire AESL_continue;
wire AESL_done;
reg AESL_done_delay = 0;
reg AESL_done_delay2 = 0;
reg AESL_ready_delay = 0;
wire ready;
wire ready_wire;
wire [3 : 0] control_AWADDR;
wire  control_AWVALID;
wire  control_AWREADY;
wire  control_WVALID;
wire  control_WREADY;
wire [31 : 0] control_WDATA;
wire [3 : 0] control_WSTRB;
wire [3 : 0] control_ARADDR;
wire  control_ARVALID;
wire  control_ARREADY;
wire  control_RVALID;
wire  control_RREADY;
wire [31 : 0] control_RDATA;
wire [1 : 0] control_RRESP;
wire  control_BVALID;
wire  control_BREADY;
wire [1 : 0] control_BRESP;
wire  control_INTERRUPT;
wire [31 : 0] in1_ADDR_A;
wire  in1_EN_A;
wire [3 : 0] in1_WEN_A;
wire [31 : 0] in1_DIN_A;
wire [31 : 0] in1_DOUT_A;
wire  in1_CLK_A;
wire  in1_RST_A;
wire [31 : 0] in1_ADDR_B;
wire  in1_EN_B;
wire [3 : 0] in1_WEN_B;
wire [31 : 0] in1_DIN_B;
wire [31 : 0] in1_DOUT_B;
wire  in1_CLK_B;
wire  in1_RST_B;
wire [31 : 0] in2_ADDR_A;
wire  in2_EN_A;
wire [3 : 0] in2_WEN_A;
wire [31 : 0] in2_DIN_A;
wire [31 : 0] in2_DOUT_A;
wire  in2_CLK_A;
wire  in2_RST_A;
wire [31 : 0] in2_ADDR_B;
wire  in2_EN_B;
wire [3 : 0] in2_WEN_B;
wire [31 : 0] in2_DIN_B;
wire [31 : 0] in2_DOUT_B;
wire  in2_CLK_B;
wire  in2_RST_B;
wire [31 : 0] out_r_ADDR_A;
wire  out_r_EN_A;
wire [3 : 0] out_r_WEN_A;
wire [31 : 0] out_r_DIN_A;
wire [31 : 0] out_r_DOUT_A;
wire  out_r_CLK_A;
wire  out_r_RST_A;
integer done_cnt = 0;
integer AESL_ready_cnt = 0;
integer ready_cnt = 0;
reg ready_initial;
reg ready_initial_n;
reg ready_last_n;
reg ready_delay_last_n;
reg done_delay_last_n;
reg interface_done = 0;
wire AESL_slave_start;
reg AESL_slave_start_lock = 0;
wire AESL_slave_write_start_in;
wire AESL_slave_write_start_finish;
reg AESL_slave_ready;
wire AESL_slave_output_done;
wire AESL_slave_done;
reg ready_rise = 0;
reg start_rise = 0;
reg slave_start_status = 0;
reg slave_done_status = 0;
reg ap_done_lock = 0;


wire ap_clk;
wire ap_rst_n;
wire ap_rst_n_n;

`AUTOTB_DUT `AUTOTB_DUT_INST(
    .s_axi_control_AWADDR(control_AWADDR),
    .s_axi_control_AWVALID(control_AWVALID),
    .s_axi_control_AWREADY(control_AWREADY),
    .s_axi_control_WVALID(control_WVALID),
    .s_axi_control_WREADY(control_WREADY),
    .s_axi_control_WDATA(control_WDATA),
    .s_axi_control_WSTRB(control_WSTRB),
    .s_axi_control_ARADDR(control_ARADDR),
    .s_axi_control_ARVALID(control_ARVALID),
    .s_axi_control_ARREADY(control_ARREADY),
    .s_axi_control_RVALID(control_RVALID),
    .s_axi_control_RREADY(control_RREADY),
    .s_axi_control_RDATA(control_RDATA),
    .s_axi_control_RRESP(control_RRESP),
    .s_axi_control_BVALID(control_BVALID),
    .s_axi_control_BREADY(control_BREADY),
    .s_axi_control_BRESP(control_BRESP),
    .interrupt(control_INTERRUPT),
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .in1_Addr_A(in1_ADDR_A),
    .in1_EN_A(in1_EN_A),
    .in1_WEN_A(in1_WEN_A),
    .in1_Din_A(in1_DIN_A),
    .in1_Dout_A(in1_DOUT_A),
    .in1_Clk_A(in1_CLK_A),
    .in1_Rst_A(in1_RST_A),
    .in1_Addr_B(in1_ADDR_B),
    .in1_EN_B(in1_EN_B),
    .in1_WEN_B(in1_WEN_B),
    .in1_Din_B(in1_DIN_B),
    .in1_Dout_B(in1_DOUT_B),
    .in1_Clk_B(in1_CLK_B),
    .in1_Rst_B(in1_RST_B),
    .in2_Addr_A(in2_ADDR_A),
    .in2_EN_A(in2_EN_A),
    .in2_WEN_A(in2_WEN_A),
    .in2_Din_A(in2_DIN_A),
    .in2_Dout_A(in2_DOUT_A),
    .in2_Clk_A(in2_CLK_A),
    .in2_Rst_A(in2_RST_A),
    .in2_Addr_B(in2_ADDR_B),
    .in2_EN_B(in2_EN_B),
    .in2_WEN_B(in2_WEN_B),
    .in2_Din_B(in2_DIN_B),
    .in2_Dout_B(in2_DOUT_B),
    .in2_Clk_B(in2_CLK_B),
    .in2_Rst_B(in2_RST_B),
    .out_r_Addr_A(out_r_ADDR_A),
    .out_r_EN_A(out_r_EN_A),
    .out_r_WEN_A(out_r_WEN_A),
    .out_r_Din_A(out_r_DIN_A),
    .out_r_Dout_A(out_r_DOUT_A),
    .out_r_Clk_A(out_r_CLK_A),
    .out_r_Rst_A(out_r_RST_A));

// Assignment for control signal
assign ap_clk = AESL_clock;
assign ap_rst_n = dut_rst;
assign ap_rst_n_n = ~dut_rst;
assign AESL_reset = rst;
assign AESL_start = start;
assign AESL_ce = ce;
assign AESL_continue = tb_continue;
  assign AESL_slave_write_start_in = slave_start_status ;
  assign AESL_slave_start = AESL_slave_write_start_finish;
  assign AESL_done = slave_done_status ;

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
    begin
        slave_start_status <= 1;
    end
    else begin
        if (AESL_start == 1 ) begin
            start_rise = 1;
        end
        if (start_rise == 1 && AESL_done == 1 ) begin
            slave_start_status <= 1;
        end
        if (AESL_slave_write_start_in == 1 && AESL_done == 0) begin 
            slave_start_status <= 0;
            start_rise = 0;
        end
    end
end

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
    begin
        AESL_slave_ready <= 0;
        ready_rise = 0;
    end
    else begin
        if (AESL_ready == 1 ) begin
            ready_rise = 1;
        end
        if (ready_rise == 1 && AESL_done_delay == 1 ) begin
            AESL_slave_ready <= 1;
        end
        if (AESL_slave_ready == 1) begin 
            AESL_slave_ready <= 0;
            ready_rise = 0;
        end
    end
end

always @ (posedge AESL_clock)
begin
    if (AESL_done == 1) begin
        slave_done_status <= 0;
    end
    else if (AESL_slave_output_done == 1 ) begin
        slave_done_status <= 1;
    end
end
//------------------------bramin1 Instantiation--------------

// The input and output of bramin1
wire  bramin1_Clk_A, bramin1_Clk_B;
wire  bramin1_EN_A, bramin1_EN_B;
wire  [4 - 1 : 0] bramin1_WEN_A, bramin1_WEN_B;
wire    [31 : 0]    bramin1_Addr_A, bramin1_Addr_B;
wire    [31 : 0]    bramin1_Din_A, bramin1_Din_B;
wire    [31 : 0]    bramin1_Dout_A, bramin1_Dout_B;
wire    bramin1_ready;
wire    bramin1_done;

`AESL_BRAM_in1 `AESL_BRAM_INST_in1(
    .Clk_A    (bramin1_Clk_A),
    .Rst_A    (bramin1_Rst_A),
    .EN_A     (bramin1_EN_A),
    .WEN_A    (bramin1_WEN_A),
    .Addr_A   (bramin1_Addr_A),
    .Din_A    (bramin1_Din_A),
    .Dout_A   (bramin1_Dout_A),
    .Clk_B    (bramin1_Clk_B),
    .Rst_B    (bramin1_Rst_B),
    .EN_B     (bramin1_EN_B),
    .WEN_B    (bramin1_WEN_B),
    .Addr_B   (bramin1_Addr_B),
    .Din_B    (bramin1_Din_B),
    .Dout_B   (bramin1_Dout_B),
    .ready    (bramin1_ready),
    .done        (bramin1_done)
);

// Assignment between dut and bramin1
assign bramin1_Clk_A = in1_CLK_A;
assign bramin1_Rst_A = in1_RST_A;
assign bramin1_Addr_A = in1_ADDR_A;
assign bramin1_EN_A = in1_EN_A;
assign in1_DOUT_A = bramin1_Dout_A;
assign bramin1_WEN_A = 0;
assign bramin1_Din_A = 0;
assign bramin1_Clk_B = in1_CLK_B;
assign bramin1_Rst_B = in1_RST_B;
assign bramin1_Addr_B = in1_ADDR_B;
assign bramin1_EN_B = in1_EN_B;
assign in1_DOUT_B = bramin1_Dout_B;
assign bramin1_WEN_B = 0;
assign bramin1_Din_B = 0;
assign bramin1_ready=    ready;
assign bramin1_done = 0;


//------------------------bramin2 Instantiation--------------

// The input and output of bramin2
wire  bramin2_Clk_A, bramin2_Clk_B;
wire  bramin2_EN_A, bramin2_EN_B;
wire  [4 - 1 : 0] bramin2_WEN_A, bramin2_WEN_B;
wire    [31 : 0]    bramin2_Addr_A, bramin2_Addr_B;
wire    [31 : 0]    bramin2_Din_A, bramin2_Din_B;
wire    [31 : 0]    bramin2_Dout_A, bramin2_Dout_B;
wire    bramin2_ready;
wire    bramin2_done;

`AESL_BRAM_in2 `AESL_BRAM_INST_in2(
    .Clk_A    (bramin2_Clk_A),
    .Rst_A    (bramin2_Rst_A),
    .EN_A     (bramin2_EN_A),
    .WEN_A    (bramin2_WEN_A),
    .Addr_A   (bramin2_Addr_A),
    .Din_A    (bramin2_Din_A),
    .Dout_A   (bramin2_Dout_A),
    .Clk_B    (bramin2_Clk_B),
    .Rst_B    (bramin2_Rst_B),
    .EN_B     (bramin2_EN_B),
    .WEN_B    (bramin2_WEN_B),
    .Addr_B   (bramin2_Addr_B),
    .Din_B    (bramin2_Din_B),
    .Dout_B   (bramin2_Dout_B),
    .ready    (bramin2_ready),
    .done        (bramin2_done)
);

// Assignment between dut and bramin2
assign bramin2_Clk_A = in2_CLK_A;
assign bramin2_Rst_A = in2_RST_A;
assign bramin2_Addr_A = in2_ADDR_A;
assign bramin2_EN_A = in2_EN_A;
assign in2_DOUT_A = bramin2_Dout_A;
assign bramin2_WEN_A = 0;
assign bramin2_Din_A = 0;
assign bramin2_Clk_B = in2_CLK_B;
assign bramin2_Rst_B = in2_RST_B;
assign bramin2_Addr_B = in2_ADDR_B;
assign bramin2_EN_B = in2_EN_B;
assign in2_DOUT_B = bramin2_Dout_B;
assign bramin2_WEN_B = 0;
assign bramin2_Din_B = 0;
assign bramin2_ready=    ready;
assign bramin2_done = 0;


//------------------------bramout_r Instantiation--------------

// The input and output of bramout_r
wire  bramout_r_Clk_A, bramout_r_Clk_B;
wire  bramout_r_EN_A, bramout_r_EN_B;
wire  [4 - 1 : 0] bramout_r_WEN_A, bramout_r_WEN_B;
wire    [31 : 0]    bramout_r_Addr_A, bramout_r_Addr_B;
wire    [31 : 0]    bramout_r_Din_A, bramout_r_Din_B;
wire    [31 : 0]    bramout_r_Dout_A, bramout_r_Dout_B;
wire    bramout_r_ready;
wire    bramout_r_done;

`AESL_BRAM_out_r `AESL_BRAM_INST_out_r(
    .Clk_A    (bramout_r_Clk_A),
    .Rst_A    (bramout_r_Rst_A),
    .EN_A     (bramout_r_EN_A),
    .WEN_A    (bramout_r_WEN_A),
    .Addr_A   (bramout_r_Addr_A),
    .Din_A    (bramout_r_Din_A),
    .Dout_A   (bramout_r_Dout_A),
    .Clk_B    (bramout_r_Clk_B),
    .Rst_B    (bramout_r_Rst_B),
    .EN_B     (bramout_r_EN_B),
    .WEN_B    (bramout_r_WEN_B),
    .Addr_B   (bramout_r_Addr_B),
    .Din_B    (bramout_r_Din_B),
    .Dout_B   (bramout_r_Dout_B),
    .ready    (bramout_r_ready),
    .done        (bramout_r_done)
);

// Assignment between dut and bramout_r
assign bramout_r_Clk_A = out_r_CLK_A;
assign bramout_r_Rst_A = out_r_RST_A;
assign bramout_r_Addr_A = out_r_ADDR_A;
assign bramout_r_EN_A = out_r_EN_A;
assign bramout_r_WEN_A = out_r_WEN_A;
assign bramout_r_Din_A = out_r_DIN_A;
assign bramout_r_WEN_B = 0;
assign bramout_r_Din_B = 0;
assign bramout_r_ready= ready_initial | bramout_r_done;
assign bramout_r_done =    AESL_done_delay;


AESL_axi_slave_control AESL_AXI_SLAVE_control(
    .clk   (AESL_clock),
    .reset (AESL_reset),
    .TRAN_s_axi_control_AWADDR (control_AWADDR),
    .TRAN_s_axi_control_AWVALID (control_AWVALID),
    .TRAN_s_axi_control_AWREADY (control_AWREADY),
    .TRAN_s_axi_control_WVALID (control_WVALID),
    .TRAN_s_axi_control_WREADY (control_WREADY),
    .TRAN_s_axi_control_WDATA (control_WDATA),
    .TRAN_s_axi_control_WSTRB (control_WSTRB),
    .TRAN_s_axi_control_ARADDR (control_ARADDR),
    .TRAN_s_axi_control_ARVALID (control_ARVALID),
    .TRAN_s_axi_control_ARREADY (control_ARREADY),
    .TRAN_s_axi_control_RVALID (control_RVALID),
    .TRAN_s_axi_control_RREADY (control_RREADY),
    .TRAN_s_axi_control_RDATA (control_RDATA),
    .TRAN_s_axi_control_RRESP (control_RRESP),
    .TRAN_s_axi_control_BVALID (control_BVALID),
    .TRAN_s_axi_control_BREADY (control_BREADY),
    .TRAN_s_axi_control_BRESP (control_BRESP),
    .TRAN_control_interrupt (control_INTERRUPT),
    .TRAN_control_ready_out (AESL_ready),
    .TRAN_control_ready_in (AESL_slave_ready),
    .TRAN_control_done_out (AESL_slave_output_done),
    .TRAN_control_idle_out (AESL_idle),
    .TRAN_control_write_start_in     (AESL_slave_write_start_in),
    .TRAN_control_write_start_finish (AESL_slave_write_start_finish),
    .TRAN_control_transaction_done_in (AESL_done_delay),
    .TRAN_control_start_in  (AESL_slave_start)
);

initial begin : generate_AESL_ready_cnt_proc
    AESL_ready_cnt = 0;
    wait(AESL_reset === 1);
    while(AESL_ready_cnt != AUTOTB_TRANSACTION_NUM) begin
        while(AESL_ready !== 1) begin
            @(posedge AESL_clock);
            # 0.4;
        end
        @(negedge AESL_clock);
        AESL_ready_cnt = AESL_ready_cnt + 1;
        @(posedge AESL_clock);
        # 0.4;
    end
end

    event next_trigger_ready_cnt;
    
    initial begin : gen_ready_cnt
        ready_cnt = 0;
        wait (AESL_reset === 1);
        forever begin
            @ (posedge AESL_clock);
            if (ready == 1) begin
                if (ready_cnt < AUTOTB_TRANSACTION_NUM) begin
                    ready_cnt = ready_cnt + 1;
                end
            end
            -> next_trigger_ready_cnt;
        end
    end
    
    wire all_finish = (done_cnt == AUTOTB_TRANSACTION_NUM);
    
    // done_cnt
    always @ (posedge AESL_clock) begin
        if (~AESL_reset) begin
            done_cnt <= 0;
        end else begin
            if (AESL_done == 1) begin
                if (done_cnt < AUTOTB_TRANSACTION_NUM) begin
                    done_cnt <= done_cnt + 1;
                end
            end
        end
    end
    
    initial begin : finish_simulation
        wait (all_finish == 1);
        // last transaction is saved at negedge right after last done
        repeat(6) @ (posedge AESL_clock);
        $finish;
    end
    
initial begin
    AESL_clock = 0;
    forever #`AUTOTB_CLOCK_PERIOD_DIV2 AESL_clock = ~AESL_clock;
end


reg end_in1;
reg [31:0] size_in1;
reg [31:0] size_in1_backup;
reg end_in2;
reg [31:0] size_in2;
reg [31:0] size_in2_backup;
reg end_out_r;
reg [31:0] size_out_r;
reg [31:0] size_out_r_backup;

initial begin : initial_process
    integer proc_rand;
    rst = 0;
    # 100;
    repeat(3+3) @ (posedge AESL_clock);
    # 0.1;
    rst = 1;
end
initial begin : initial_process_for_dut_rst
    integer proc_rand;
    dut_rst = 0;
    # 100;
    repeat(3) @ (posedge AESL_clock);
    # 0.1;
    dut_rst = 1;
end
initial begin : start_process
    integer proc_rand;
    reg [31:0] start_cnt;
    ce = 1;
    start = 0;
    start_cnt = 0;
    wait (AESL_reset === 1);
    @ (posedge AESL_clock);
    #0 start = 1;
    start_cnt = start_cnt + 1;
    forever begin
        if (start_cnt >= AUTOTB_TRANSACTION_NUM + 1) begin
            #0 start = 0;
        end
        @ (posedge AESL_clock);
        if (AESL_ready) begin
            start_cnt = start_cnt + 1;
        end
    end
end

always @(AESL_done)
begin
    tb_continue = AESL_done;
end

initial begin : ready_initial_process
    ready_initial = 0;
    wait (AESL_start === 1);
    ready_initial = 1;
    @(posedge AESL_clock);
    ready_initial = 0;
end

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
      AESL_ready_delay = 0;
  else
      AESL_ready_delay = AESL_ready;
end
initial begin : ready_last_n_process
  ready_last_n = 1;
  wait(ready_cnt == AUTOTB_TRANSACTION_NUM)
  @(posedge AESL_clock);
  ready_last_n <= 0;
end

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
      ready_delay_last_n = 0;
  else
      ready_delay_last_n <= ready_last_n;
end
assign ready = (ready_initial | AESL_ready_delay);
assign ready_wire = ready_initial | AESL_ready_delay;
initial begin : done_delay_last_n_process
  done_delay_last_n = 1;
  while(done_cnt < AUTOTB_TRANSACTION_NUM)
      @(posedge AESL_clock);
  # 0.1;
  done_delay_last_n = 0;
end

always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
  begin
      AESL_done_delay <= 0;
      AESL_done_delay2 <= 0;
  end
  else begin
      AESL_done_delay <= AESL_done & done_delay_last_n;
      AESL_done_delay2 <= AESL_done_delay;
  end
end
always @(posedge AESL_clock)
begin
    if(AESL_reset === 0)
      interface_done = 0;
  else begin
      # 0.01;
      if(ready === 1 && ready_cnt > 0 && ready_cnt < AUTOTB_TRANSACTION_NUM)
          interface_done = 1;
      else if(AESL_done_delay === 1 && done_cnt == AUTOTB_TRANSACTION_NUM)
          interface_done = 1;
      else
          interface_done = 0;
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

reg dump_tvout_finish_out_r;

initial begin : dump_tvout_runtime_sign_out_r
    integer fp;
    dump_tvout_finish_out_r = 0;
    fp = $fopen(`AUTOTB_TVOUT_out_r_out_wrapc, "wb");
    if (fp == 0) begin
        $display("Failed to open file \"%s\"!", `AUTOTB_TVOUT_out_r_out_wrapc);
        $display("ERROR: Simulation using HLS TB failed.");
        $finish;
    end
    $fclose(fp);
    wait (done_cnt == AUTOTB_TRANSACTION_NUM);
    repeat(5) @ (posedge AESL_clock);
    fp = $fopen(`AUTOTB_TVOUT_out_r_out_wrapc, "ab");
    if (fp == 0) begin
        $display("Failed to open file \"%s\"!", `AUTOTB_TVOUT_out_r_out_wrapc);
        $display("ERROR: Simulation using HLS TB failed.");
        $finish;
    end
    write_binary(fp,64'h5a5aa5a50f0ff0f0,64);
    $fclose(fp);
    repeat(5) @ (posedge AESL_clock);
    dump_tvout_finish_out_r = 1;
end


////////////////////////////////////////////
// progress and performance
////////////////////////////////////////////

task wait_start();
    while (~AESL_start) begin
        @ (posedge AESL_clock);
    end
endtask

reg [31:0] clk_cnt = 0;
reg AESL_ready_p1;
reg AESL_start_p1;

always @ (posedge AESL_clock) begin
    if (AESL_reset == 0) begin
        clk_cnt <= 32'h0;
        AESL_ready_p1 <= 1'b0;
        AESL_start_p1 <= 1'b0;
    end
    else begin
        clk_cnt <= clk_cnt + 1;
        AESL_ready_p1 <= AESL_ready;
        AESL_start_p1 <= AESL_start;
    end
end

reg [31:0] start_timestamp [0:AUTOTB_TRANSACTION_NUM - 1];
reg [31:0] start_cnt;
reg [31:0] ready_timestamp [0:AUTOTB_TRANSACTION_NUM - 1];
reg [31:0] ap_ready_cnt;
reg [31:0] finish_timestamp [0:AUTOTB_TRANSACTION_NUM - 1];
reg [31:0] finish_cnt;
reg [31:0] lat_total;
event report_progress;

always @(posedge AESL_clock)
begin
    if (finish_cnt == AUTOTB_TRANSACTION_NUM - 1 && AESL_done == 1'b1)
        lat_total = clk_cnt - start_timestamp[0];
end

initial begin
    start_cnt = 0;
    finish_cnt = 0;
    ap_ready_cnt = 0;
    wait (AESL_reset == 1);
    wait_start();
    start_timestamp[start_cnt] = clk_cnt;
    start_cnt = start_cnt + 1;
    if (AESL_done) begin
        finish_timestamp[finish_cnt] = clk_cnt;
        finish_cnt = finish_cnt + 1;
    end
    -> report_progress;
    forever begin
        @ (posedge AESL_clock);
        if (start_cnt < AUTOTB_TRANSACTION_NUM) begin
            if ((AESL_start && AESL_ready_p1)||(AESL_start && ~AESL_start_p1)) begin
                start_timestamp[start_cnt] = clk_cnt;
                start_cnt = start_cnt + 1;
            end
        end
        if (ap_ready_cnt < AUTOTB_TRANSACTION_NUM) begin
            if (AESL_start_p1 && AESL_ready_p1) begin
                ready_timestamp[ap_ready_cnt] = clk_cnt;
                ap_ready_cnt = ap_ready_cnt + 1;
            end
        end
        if (finish_cnt < AUTOTB_TRANSACTION_NUM) begin
            if (AESL_done) begin
                finish_timestamp[finish_cnt] = clk_cnt;
                finish_cnt = finish_cnt + 1;
            end
        end
        -> report_progress;
    end
end

reg [31:0] progress_timeout;

initial begin : simulation_progress
    real intra_progress;
    wait (AESL_reset == 1);
    progress_timeout = PROGRESS_TIMEOUT;
    $display("////////////////////////////////////////////////////////////////////////////////////");
    $display("// Inter-Transaction Progress: Completed Transaction / Total Transaction");
    $display("// Intra-Transaction Progress: Measured Latency / Latency Estimation * 100%%");
    $display("//");
    $display("// RTL Simulation : \"Inter-Transaction Progress\" [\"Intra-Transaction Progress\"] @ \"Simulation Time\"");
    $display("////////////////////////////////////////////////////////////////////////////////////");
    print_progress();
    while (finish_cnt < AUTOTB_TRANSACTION_NUM) begin
        @ (report_progress);
        if (finish_cnt < AUTOTB_TRANSACTION_NUM) begin
            if (AESL_done) begin
                print_progress();
                progress_timeout = PROGRESS_TIMEOUT;
            end else begin
                if (progress_timeout == 0) begin
                    print_progress();
                    progress_timeout = PROGRESS_TIMEOUT;
                end else begin
                    progress_timeout = progress_timeout - 1;
                end
            end
        end
    end
    print_progress();
    $display("////////////////////////////////////////////////////////////////////////////////////");
    calculate_performance();
end

task get_intra_progress(output real intra_progress);
    begin
        if (start_cnt > finish_cnt) begin
            intra_progress = clk_cnt - start_timestamp[finish_cnt];
        end else if(finish_cnt > 0) begin
            intra_progress = LATENCY_ESTIMATION;
        end else begin
            intra_progress = 0;
        end
        intra_progress = intra_progress / LATENCY_ESTIMATION;
    end
endtask

task print_progress();
    real intra_progress;
    begin
        if (LATENCY_ESTIMATION > 0) begin
            get_intra_progress(intra_progress);
            $display("// RTL Simulation : %0d / %0d [%2.2f%%] @ \"%0t\"", finish_cnt, AUTOTB_TRANSACTION_NUM, intra_progress * 100, $time);
        end else begin
            $display("// RTL Simulation : %0d / %0d [n/a] @ \"%0t\"", finish_cnt, AUTOTB_TRANSACTION_NUM, $time);
        end
    end
endtask

task calculate_performance();
    integer i;
    integer fp;
    reg [31:0] latency [0:AUTOTB_TRANSACTION_NUM - 1];
    reg [31:0] latency_min;
    reg [31:0] latency_max;
    reg [31:0] latency_total;
    reg [31:0] latency_average;
    reg [31:0] interval [0:AUTOTB_TRANSACTION_NUM - 2];
    reg [31:0] interval_min;
    reg [31:0] interval_max;
    reg [31:0] interval_total;
    reg [31:0] interval_average;
    reg [31:0] total_execute_time;
    begin
        latency_min = -1;
        latency_max = 0;
        latency_total = 0;
        interval_min = -1;
        interval_max = 0;
        interval_total = 0;
        total_execute_time = lat_total;

        for (i = 0; i < AUTOTB_TRANSACTION_NUM; i = i + 1) begin
            // calculate latency
            latency[i] = finish_timestamp[i] - start_timestamp[i];
            if (latency[i] > latency_max) latency_max = latency[i];
            if (latency[i] < latency_min) latency_min = latency[i];
            latency_total = latency_total + latency[i];
            // calculate interval
            if (AUTOTB_TRANSACTION_NUM == 1) begin
                interval[i] = 0;
                interval_max = 0;
                interval_min = 0;
                interval_total = 0;
            end else if (i < AUTOTB_TRANSACTION_NUM - 1) begin
                interval[i] = start_timestamp[i + 1] - start_timestamp[i];
                if (interval[i] > interval_max) interval_max = interval[i];
                if (interval[i] < interval_min) interval_min = interval[i];
                interval_total = interval_total + interval[i];
            end
        end

        latency_average = latency_total / AUTOTB_TRANSACTION_NUM;
        if (AUTOTB_TRANSACTION_NUM == 1) begin
            interval_average = 0;
        end else begin
            interval_average = interval_total / (AUTOTB_TRANSACTION_NUM - 1);
        end

        fp = $fopen(`AUTOTB_LAT_RESULT_FILE, "w");

        $fdisplay(fp, "$MAX_LATENCY = \"%0d\"", latency_max);
        $fdisplay(fp, "$MIN_LATENCY = \"%0d\"", latency_min);
        $fdisplay(fp, "$AVER_LATENCY = \"%0d\"", latency_average);
        $fdisplay(fp, "$MAX_THROUGHPUT = \"%0d\"", interval_max);
        $fdisplay(fp, "$MIN_THROUGHPUT = \"%0d\"", interval_min);
        $fdisplay(fp, "$AVER_THROUGHPUT = \"%0d\"", interval_average);
        $fdisplay(fp, "$TOTAL_EXECUTE_TIME = \"%0d\"", total_execute_time);

        $fclose(fp);

        fp = $fopen(`AUTOTB_PER_RESULT_TRANS_FILE, "w");

        $fdisplay(fp, "%20s%16s%16s", "", "latency", "interval");
        if (AUTOTB_TRANSACTION_NUM == 1) begin
            i = 0;
            $fdisplay(fp, "transaction%8d:%16d%16d", i, latency[i], interval[i]);
        end else begin
            for (i = 0; i < AUTOTB_TRANSACTION_NUM; i = i + 1) begin
                if (i < AUTOTB_TRANSACTION_NUM - 1) begin
                    $fdisplay(fp, "transaction%8d:%16d%16d", i, latency[i], interval[i]);
                end else begin
                    $fdisplay(fp, "transaction%8d:%16d               x", i, latency[i]);
                end
            end
        end

        $fclose(fp);
    end
endtask


////////////////////////////////////////////
// Dependence Check
////////////////////////////////////////////

`ifndef POST_SYN

`endif
///////////////////////////////////////////////////////
// dataflow status monitor
///////////////////////////////////////////////////////
dataflow_monitor U_dataflow_monitor(
    .clock(AESL_clock),
    .reset(~rst),
    .finish(all_finish));

`include "fifo_para.vh"

endmodule
