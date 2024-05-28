entity reg is port (
	d: in bit_vector(3 downto 0);
	clk: in bit;
	clr: in bit;
	q: out bit_vector(3 downto 0)
);
end reg;

architecture struct of reg is
component ffrst is port (
	d: in bit;
	clk: in bit;
	rst: in bit;
	q: out bit
);
end component;

begin
	u: for i in 0 to 3 generate
		f: ffrst port map (d(i), clk, clr, q(i));
	end generate;
end struct;
