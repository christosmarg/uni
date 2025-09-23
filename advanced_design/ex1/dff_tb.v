module dff_tb;
	reg tb_d;
	reg tb_clk;
	reg tb_rst;
	wire q;

	dff dff_tb(
		.d (tb_d),
		.clk (tb_clk),
		.rst (tb_rst),
		.q (tb_q)
	);

	always #20 tb_clk = ~tb_clk;

	initial begin
		$dumpfile("dff.vcd");
		$dumpvars(0, dff_tb);

		$monitor("time=%3d, tb_d=%b, tb_clk=%b, tb_rst=%b, tb_q=%b\n",
		    $time, tb_d, tb_clk, tb_rst, tb_q);

		tb_clk <= 1;
		tb_rst <= 0;
		tb_d <= 1;
		#40

		tb_rst <= 1;
		$finish;
    end
endmodule
