entity ffrst_tb is
end ffrst_tb;

architecture behav of ffrst_tb is

signal d1: bit;
signal clk1: bit;
signal rst1: bit;
signal q1: bit;

component ffrst is port (
	d: in bit;
	clk: in bit;
	rst: in bit;
	q: out bit
);
end component;

begin
	uut: ffrst port map (
		d => d1,
		clk => clk1,
		rst => rst1,
		q => q1
	);

	process begin
		rst1 <= '1';
		clk1 <= '1';
		wait for 150 ns;
		clk1 <= '0';
		wait for 250 ns;
		rst1 <= '0';	-- reset now is 0 so q is always 0 now
		clk1 <= '1';
		wait for 150 ns;
		clk1 <= '0';
		wait for 250 ns;
		rst1 <= '1';
		clk1 <= '1';
		wait for 150 ns;
		clk1 <= '0';
		wait for 250 ns;
	end process;

	process begin
		d1 <= '1';
		wait for 280 ns;
		d1 <= '0';
		wait for 300 ns;
		d1 <= '1';
		wait for 250 ns;
		d1 <= '0';
		wait for 150 ns;
		d1 <= '1';
		wait for 75 ns;
		d1 <= '0';
		wait for 150 ns;
	end process;
end behav;
