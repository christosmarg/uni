library ieee;
use ieee.std_logic_1164.all;

entity shl2_tb is
end shl2_tb;

architecture behav of shl2_tb is

signal s_in1:	std_logic_vector(31 downto 0);
signal s_d:	std_logic_vector(31 downto 0);

component shl2 is port (
	in1:	in std_logic_vector(31 downto 0);
	d:	out std_logic_vector(31 downto 0)
);
end component;

begin
	uut: shl2 port map (
		in1 => s_in1,
		d => s_d
	);

	process begin
		s_in1 <= x"0000aaaf";
		wait for 250 ns;

		s_in1 <= x"ffffaaaf";
		wait for 250 ns;
	end process;
end behav;
