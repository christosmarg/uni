library ieee;
use ieee.std_logic_1164.all;

entity sign_ext_tb is
end sign_ext_tb;

architecture behav of sign_ext_tb is

signal s_instr:		std_logic_vector(15 downto 0);
signal s_sign_ex:	std_logic_vector(31 downto 0);

component sign_ext is port (
	instr:		in std_logic_vector(15 downto 0);
	sign_ex:	out std_logic_vector(31 downto 0)
);
end component;

begin
	uut: sign_ext port map (
		instr => s_instr,
		sign_ex => s_sign_ex
	);

	process begin
		s_instr <= x"0010";
		wait for 250 ns;

		s_instr <= x"1001";
		wait for 250 ns;

		s_instr <= x"80a0";
		wait for 250 ns;
	end process;
end behav;
