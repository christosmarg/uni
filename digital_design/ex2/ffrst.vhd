entity ffrst is port (
	d: in bit;
	clk: in bit;
	rst: in bit;
	q: out bit
);
end ffrst;

architecture behav of ffrst is
begin
	process (clk, rst) begin
		if (rst = '0') then
		       q <= '0';
		elsif (clk 'event and clk = '1') then
		       q <= d;
		end if; 
	end process;
end behav;
