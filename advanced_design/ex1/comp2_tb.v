module comp2_tb;
	reg [1:0] tb_a;
	wire signed [3:0] tb_y;

	comp2 comp2_tb(
		.a (tb_a),
		.y (tb_y)
	);

	initial begin
		$dumpfile("comp2.vcd");
		$dumpvars(0, comp2_tb);

		$monitor("time=%3d, tb_a=%b, tb_y=%d\n", $time, tb_a, tb_y);

		tb_a <= 2'b01;
		#20 tb_a <= 2'b00;
		#20 tb_a <= 2'b10;
	end
endmodule

