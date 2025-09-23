entity reg_tb is
end reg_tb;

architecture behav of reg_tb is

signal d1: bit_vector(3 downto 0);
signal clk1: bit;
signal clr1: bit;
signal q1: bit_vector(3 downto 0);

component reg is port (
	d: in bit_vector(3 downto 0);
	clk: in bit;
	clr: in bit;
	q: out bit_vector(3 downto 0)
);
end component;

begin
	uut: reg port map (
		d => d1,
		clk => clk1,
		clr => clr1,
		q => q1
	);

	process begin
		clr1 <= '0';
		clk1 <= '0';
		d1 <= "0001";
		wait for 250 ns;

		clr1 <= '1';
		clk1 <= '1';
		d1 <= "0001";
		wait for 250 ns;

		clr1 <= '1';
		clk1 <= '0';
		d1 <= "0011";
		wait for 250 ns;

		clr1 <= '1';
		clk1 <= '1';
		d1 <= "0101";
		wait for 250 ns;
	end process;
end behav;