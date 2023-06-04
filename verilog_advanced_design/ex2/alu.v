module alu(clk, in_a, in_b, alu_op, mux_sel, alu_out, mux_out);
	input clk;
	input [31:0] in_a;
	input [31:0] in_b;
	input [1:0] alu_op;
	input mux_sel;
	output reg [31:0] alu_out;
	output reg [31:0] mux_out;

	always @ (posedge clk) begin
		case (alu_op)
			2'b00: alu_out = in_a & in_b;
			2'b01: alu_out = in_a | in_b;
			2'b10: alu_out = in_a + in_b;
			2'b11: alu_out = in_a - in_b;
			default: alu_out = 0;
		endcase
		if (mux_sel == 0)
			mux_out = alu_out;
		else
			mux_out = in_b;
	end
endmodule
