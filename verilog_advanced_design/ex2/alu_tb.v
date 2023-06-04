module alu_tb;
	reg tb_clk;
	reg [31:0] tb_in_a;
	reg [31:0] tb_in_b;
	reg [1:0] tb_alu_op;
	reg tb_mux_sel;
	wire [31:0] tb_alu_out;
	wire [31:0] tb_mux_out;

	alu alu_tb(
		.clk (tb_clk),
		.in_a (tb_in_a),
		.in_b (tb_in_b),
		.alu_op (tb_alu_op),
		.mux_sel (tb_mux_sel),
		.alu_out (tb_alu_out),
		.mux_out (tb_mux_out)
	);

	always #20 tb_clk = ~tb_clk;

	initial begin
		$dumpfile("alu.vcd");
		$dumpvars(0, alu_tb);

		$monitor("time=%3d, clk=%b, in_a=%b, in_b=%b, alu_op=%b, mux_sel=%b, alu_out=%b, mux_out=%b\n",
		    $time, tb_clk, tb_in_a, tb_in_b, tb_alu_op, tb_mux_sel,
		    tb_alu_out, tb_mux_out);

		tb_clk <= 0;
	
		tb_in_a <= 16'hffff;
		tb_in_b <= 16'hc23a;
		tb_alu_op <= 2'b01;
		tb_mux_sel <= 0;
		#40

		tb_in_a <= 16'hab12;
		tb_in_b <= 16'h12ba;
		tb_alu_op <= 2'b10;
		tb_mux_sel <= 0;
		#40

		tb_in_a <= 16'h12c5;
		tb_in_b <= 16'hd145;
		tb_alu_op <= 2'b11;
		tb_mux_sel <= 1;
		#40

		$finish;
	end
endmodule
