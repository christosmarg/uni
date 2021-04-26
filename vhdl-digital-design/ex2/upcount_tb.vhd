library ieee;
use ieee.std_logic_1164.all;

entity upcount_tb is
end upcount_tb;

architecture behav of upcount_tb is

signal clk1: std_logic := '1';
signal rst1: std_logic := '1';
signal q1: std_logic_vector(1 downto 0);

component upcount is port (
	clk: in std_logic;
	rst: in std_logic;
	q: inout std_logic_vector(1 downto 0)
);
end component;

begin
	uut: upcount port map (
		clk => clk1,
		rst => rst1,
		q => q1
	);
	
	process begin
		rst1 <= '0';
		clk1 <= '0';
		wait for 250 ns;

		clk1 <= '1';
		wait for 250 ns;
	end process;
end behav;
