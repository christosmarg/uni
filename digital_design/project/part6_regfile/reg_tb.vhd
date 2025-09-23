library ieee;
use ieee.std_logic_1164.all;

entity reg_tb is
end reg_tb;

architecture behav of reg_tb is

signal s_sz:	natural := 4;
signal s_d:	std_logic_vector(s_sz-1 downto 0);
signal s_rst:	std_logic;
signal s_clk:	std_logic;
signal s_q:	std_logic_vector(s_sz-1 downto 0);

component reg is
generic (
	sz:	natural := 4
);
port (
	d:	in std_logic_vector(sz-1 downto 0);
	rst:	in std_logic;
	clk:	in std_logic;
	q:	out std_logic_vector(sz-1 downto 0)
);
end component;

begin
	uut: reg port map (
		d => s_d,
		rst => s_rst,
		clk => s_clk,
		q => s_q
	);

	process begin
		s_rst <= '1';
		s_clk <= '0';
		s_d <= "0010";
		wait for 250 ns;

		s_clk <= '1';
		wait for 250 ns;

		s_clk <= '0';
		s_d <= "1110";
		wait for 250 ns;

		s_clk <= '1';
		wait for 250 ns;

		s_clk <= '0';
		s_d <= "1010";
		wait for 250 ns;

		s_rst <= '0';
		s_clk <= '1';
		wait for 250 ns;
	end process;
end behav;
