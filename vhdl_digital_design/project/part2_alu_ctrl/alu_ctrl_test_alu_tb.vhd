library ieee;
use ieee.std_logic_1164.all;

entity alu_ctrl_test_alu_tb is
end alu_ctrl_test_alu_tb;

architecture behav of alu_ctrl_test_alu_tb is

signal s_dw:		natural := 4;
signal s_t_funct:	std_logic_vector(5 downto 0);
signal s_t_alu_op:	std_logic_vector(1 downto 0);
signal s_t_alu_in1:	std_logic_vector(s_dw-1 downto 0);
signal s_t_alu_in2:	std_logic_vector(s_dw-1 downto 0);
signal s_t_alu_out:	std_logic_vector(s_dw-1 downto 0);
signal s_t_alu_zero:	std_logic;

component alu_ctrl_test_alu is generic (
	t_dw:		natural := 4
);
port (
	t_funct:	in std_logic_vector(5 downto 0);
	t_alu_op:	in std_logic_vector(1 downto 0);
	t_alu_in1:	in std_logic_vector(t_dw-1 downto 0);
	t_alu_in2:	in std_logic_vector(t_dw-1 downto 0);
	t_alu_out:	out std_logic_vector(t_dw-1 downto 0);
	t_alu_zero:	out std_logic
);
end component;

begin
	uut: alu_ctrl_test_alu port map (
		t_funct => s_t_funct,
		t_alu_op => s_t_alu_op,
		t_alu_in1 => s_t_alu_in1,
		t_alu_in2 => s_t_alu_in2,
		t_alu_out => s_t_alu_out,
		t_alu_zero => s_t_alu_zero
	);

	process begin
		s_t_alu_in1 <= "1100";
		s_t_alu_in2 <= "1100";

		s_t_alu_op <= "00";
		s_t_funct <= "001001";
		wait for 250 ns;

		s_t_alu_op <= "00";
		s_t_funct <= "001010";
		wait for 250 ns;

		s_t_alu_op <= "01";
		s_t_funct <= "100111";
		wait for 250 ns;

		s_t_alu_op <= "10";
		s_t_funct <= "100000";
		wait for 250 ns;

		s_t_alu_op <= "10";
		s_t_funct <= "100010";
		wait for 250 ns;

		s_t_alu_op <= "10";
		s_t_funct <= "100100";
		wait for 250 ns;

		s_t_alu_op <= "10";
		s_t_funct <= "100101";
		wait for 250 ns;

		s_t_alu_op <= "10";
		s_t_funct <= "101010";
		wait for 250 ns;
	end process;
end behav;
