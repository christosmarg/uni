library ieee;
use ieee.std_logic_1164.all;

entity instrmem_tb is
end instrmem_tb;

architecture behav of instrmem_tb is

signal s_addr:	std_logic_vector(3 downto 0);
signal s_c:	std_logic_vector(31 downto 0);

component instrmem is port (
	addr:	in std_logic_vector(3 downto 0);
	c:	out std_logic_vector(31 downto 0)
);
end component;

begin
	uut: instrmem port map (
		addr => s_addr,
		c => s_c
	);

	process begin
		s_addr <= "0001";
		wait for 250 ns;

		s_addr <= "0010";
		wait for 250 ns;

		s_addr <= "0110";
		wait for 250 ns;

		s_addr <= "1000";
		wait for 250 ns;

		s_addr <= "1010";
		wait for 250 ns;
	end process;
end behav;
