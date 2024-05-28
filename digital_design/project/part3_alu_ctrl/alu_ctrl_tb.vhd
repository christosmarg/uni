library ieee;
use ieee.std_logic_1164.all;

entity alu_ctrl_tb is
end alu_ctrl_tb;

architecture behav of alu_ctrl_tb is

signal s_funct:		std_logic_vector(5 downto 0);
signal s_alu_op:	std_logic_vector(1 downto 0);
signal s_op:		std_logic_vector(3 downto 0);

component alu_ctrl is port (
	funct:		in std_logic_vector(5 downto 0);
	alu_op:		in std_logic_vector(1 downto 0);
	op:		out std_logic_vector(3 downto 0)
);
end component;

begin
	uut: alu_ctrl port map (
		funct => s_funct,
		alu_op => s_alu_op,
		op => s_op
	);

	process begin
		s_alu_op <= "00";
		s_funct <= "001001";
		wait for 250 ns;

		s_alu_op <= "00";
		s_funct <= "001010";
		wait for 250 ns;

		s_alu_op <= "01";
		s_funct <= "100111";
		wait for 250 ns;

		s_alu_op <= "10";
		s_funct <= "100000";
		wait for 250 ns;

		s_alu_op <= "10";
		s_funct <= "100010";
		wait for 250 ns;

		s_alu_op <= "10";
		s_funct <= "100100";
		wait for 250 ns;

		s_alu_op <= "10";
		s_funct <= "100101";
		wait for 250 ns;

		s_alu_op <= "10";
		s_funct <= "101010";
		wait for 250 ns;
	end process;
end behav;
