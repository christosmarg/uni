library ieee;
use ieee.std_logic_1164.all;

entity shift4_tb is
end shift4_tb;

architecture behav of shift4_tb is

signal d1: 	std_logic_vector(3 downto 0);
signal en1:	std_logic;
signal load1:	std_logic;
signal sin1:	std_logic;
signal clk1:	std_logic;
signal q1:	std_logic_vector(3 downto 0);

component shift4 is port (
	d:	in std_logic_vector(3 downto 0);
	en:	in std_logic;
	load:	in std_logic;
	sin:	in std_logic;
	clk:	in std_logic;
	q:	out std_logic_vector(3 downto 0)
);
end component;

begin
	uut: shift4 port map (
		d => d1,
		en => en1,
		load => load1,
		sin => sin1,
		clk => clk1,
		q => q1
	);

	process begin
		d1 <= "1011";
		load1 <= '1';
		en1 <= '0';
		sin1 <= '1';
		clk1 <= '1';
		wait for 250 ns;

		d1 <= "1011";
		load1 <= '0';
		en1 <= '1';
		sin1 <= '0';
		clk1 <= '1';
		wait for 250 ns;
	end process;
end behav;
