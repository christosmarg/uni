module lfsr_tb;
	reg tb_clk;
	reg tb_rst;
	wire [2:0] tb_out;

	lfsr lfsr_tb(
		.clk (tb_clk),
		.rst (tb_rst),
		.out (tb_out)
	);

	always #20 tb_clk = ~tb_clk;

	initial begin
		$dumpfile("lfsr.vcd");
		$dumpvars(0, lfsr_tb);

		$monitor("time=%3d, clk=%b, rst=%b, out=%b\n",
		    $time, tb_clk, tb_rst, tb_out);

		tb_clk <= 0;
		tb_rst <= 1;
		#20

		tb_rst <= 0;

		repeat (4) @ (posedge tb_clk)
			;

		$finish;
	end
endmodule
