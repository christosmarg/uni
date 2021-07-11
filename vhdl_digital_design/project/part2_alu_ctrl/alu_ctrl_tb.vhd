library ieee;
use ieee.std_logic_1164.all;

entity alu_ctrl_tb is
end alu_ctrl_tb;

architecture behav of alu_ctrl_tb is

signal s_op_5to0:	std_logic_vector(5 downto 0);
signal s_op_alu:	std_logic_vector(1 downto 0);
signal s_op:		std_logic_vector(3 downto 0);

component alu_ctrl is port (
	op_5to0:	in std_logic_vector(5 downto 0);
	op_alu:		in std_logic_vector(1 downto 0);
	op:		out std_logic_vector(3 downto 0)
);
end component;

begin
	uut: alu_ctrl port map (
		op_5to0 => s_op_5to0,
		op_alu => s_op_alu,
		op => s_op
	);

	process begin;
		s_op_alu <= "00";
		s_op_5to0 <= "001001";
		wait for 250 ns;

		s_op_alu <= "00";
		s_op_5to0 <= "001010";
		wait for 250 ns;

		s_op_alu <= "01";
		s_op_5to0 <= "100111";
		wait for 250 ns;

		s_op_alu <= "10";
		s_op_5to0 <= "100000";
		wait for 250 ns;

		s_op_alu <= "10";
		s_op_5to0 <= "100010";
		wait for 250 ns;

		s_op_alu <= "10";
		s_op_5to0 <= "100100";
		wait for 250 ns;

		s_op_alu <= "10";
		s_op_5to0 <= "100101";
		wait for 250 ns;

		s_op_alu <= "10";
		s_op_5to0 <= "101010";
		wait for 250 ns;
	end process;
end behav;
