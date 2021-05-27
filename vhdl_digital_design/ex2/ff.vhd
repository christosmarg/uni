entity ff is port (
	d: in bit;
	clk: in bit;
	q: out bit
);
end ff;

architecture behav of ff is
begin
	process (clk) begin
		if (clk 'event and clk = '1') then
			q <= d;
		end if;
	end process;
end behav;
