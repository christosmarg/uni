library ieee;
use ieee.std_logic_1164.all;

entity mux2to1gen_tb is
end mux2to1gen_tb;

architecture behav of mux2to1gen_tb is

signal s_dw: 	natural := 4;
signal s_a:	std_logic_vector(s_dw-1 downto 0);
signal s_b:	std_logic_vector(s_dw-1 downto 0);
signal s_s:	std_logic;
signal s_c:	std_logic_vector(s_dw-1 downto 0);

component mux2to1gen is
generic (
	dw:	natural := 4
);
port (
	a:	in std_logic_vector(dw-1 downto 0);
	b:	in std_logic_vector(dw-1 downto 0);
	s: 	in std_logic;
	c:	out std_logic_vector(dw-1 downto 0)
);
end component;

begin
	uut: mux2to1gen port map (
		a => s_a,
		b => s_b,
		s => s_s,
		c => s_c
	);

	process begin
		s_a <= "0000";
		s_b <= "1101";
		s_s <= '0';
		wait for 250 ns;

		s_a <= "0000";
		s_b <= "1101";
		s_s <= '1';
		wait for 250 ns;
	end process;
end behav;
