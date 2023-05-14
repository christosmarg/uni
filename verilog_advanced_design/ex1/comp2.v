module comp2(a, y);
	input [1:0] a;
	output reg signed [3:0] y;

	always @ (a) begin
		if (a[0] > a[1])
			y = 4'b0001;
		else if (a[0] == a[1])
			y = 4'b0000;
		else
			/* 2's complement */
			y = 4'b1111;
	end
endmodule
