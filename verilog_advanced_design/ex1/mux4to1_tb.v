module mux4to1_tb;
	reg [3:0] tb_a;
	reg [1:0] tb_s;
	wire tb_y;

	mux4to1 mux4to1_tb (
		.a (tb_a),
		.s (tb_s),
		.y (tb_y)
	);

	initial begin
		/* used by gtkwave to display the testbench in waveforms */
		$dumpfile("mux4to1.vcd");
		$dumpvars(0, mux4to1_tb);

		/* print the results to the command line */
		$monitor("time=%3d, tb_a=%b, tb_s=%b, tb_y=%b\n",
		    $time, tb_a, tb_s, tb_y);

		/* set a random 4bit value */
		tb_a <= 4'b1101;

		/* wait for 20 time units after each assignment */
		tb_s <= 2'b00;
		#20 tb_s <= 2'b01;
		#20 tb_s <= 2'b10;
		#20 tb_s <= 2'b11;
	end
endmodule
