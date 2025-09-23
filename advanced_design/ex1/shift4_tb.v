module shift4_tb;
	reg tb_d;
	reg tb_clr;
	reg tb_clk;
	reg tb_shf;
	wire [3:0] tb_q;

	shift4 shift4_tb(
		.d (tb_d),
		.clr (tb_clr),
		.clk (tb_clk),
		.shf (tb_shf),
		.q (tb_q)
	);

	/* switch clock values every 20 time units */
	always #20 tb_clk = ~tb_clk;

	initial begin
		$dumpfile("shift4.vcd");
		$dumpvars(0, shift4_tb);

		$monitor("time=%3d, tb_d=%b, tb_clr=%b, tb_clk=%b, tb_shf=%b, tb_q=%b\n",
		    $time, tb_d, tb_clr, tb_clk, tb_shf, tb_q);

		tb_clk <= 1;	/* start clock */
		tb_shf <= 0;	/* shift to the left */
		tb_d <= 1;	/* data pin is 1 */

		/* initialize q to 0 */
		tb_clr <= 1;
		#20 tb_clr <= 0;

		/*
		 * q is currently 1, set the data pin to 0 so that we do not
		 * add 1 every time we shift
		 */
		#20 tb_d <= 0;

		/* shift 2 times to the left */
		repeat (2) @ (posedge tb_clk)
			;

		/* change shift direction */
		#20 tb_shf <= 1;

		/* shift 2 times to the right */
		repeat (2) @ (posedge tb_clk)
			;

		/* clear q */
		#20 tb_clr <= 1;
		#20 tb_clr <= 0;

		$finish;
	end
endmodule
