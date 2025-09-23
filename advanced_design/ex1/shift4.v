module shift4(d, clr, clk, shf, q);
	input d;
	input clr;
	input clk;
	input shf;
	output reg [3:0] q;

	/* run on a rising clock signal */
	always @ (posedge clk) begin
		if (clr)
			q = 0;
		else if (shf == 0)
			q = (q << 1) | d;
		else if (shf == 1)
			q = (q >> 1) | d;
		else
			q = q;
	end
endmodule
