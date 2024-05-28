module lfsr(clk, rst, out);
	input clk;
	input rst;
	output reg [2:0] out;

	always @ (posedge clk) begin
		if (rst)
			out = 4'b101;
		else
			out = {out[1:0],(out[2] ^ out[1])};
	end
endmodule
