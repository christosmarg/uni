library ieee;
use ieee.std_logic_1164.all;

entity alu4_tb is
end alu4_tb;

architecture behav of alu4_tb is
component alu4 is port (
	alu_in1:	in std_logic_vector(3 downto 0);
	alu_in2:	in std_logic_vector(3 downto 0);
	alu_ctrl:	in std_logic_vector(3 downto 0);
	alu_out:	out std_logic_vector(3 downto 0);
	alu_zero:	out std_logic
);
end component;

signal	s_alu_in1:	std_logic_vector(3 downto 0);
signal	s_alu_in2:	std_logic_vector(3 downto 0);
signal	s_alu_ctrl:	std_logic_vector(3 downto 0);
signal	s_alu_out:	std_logic_vector(3 downto 0);
signal	s_alu_zero:	std_logic;

begin
	uut: alu4 port map (
		alu_in1 => s_alu_in1,
		alu_in2 => s_alu_in2,
		alu_ctrl => s_alu_ctrl,
		alu_out => s_alu_out,
		alu_zero => s_alu_zero
	);
	
	process begin
		s_alu_in1 <= "0010";
		s_alu_in2 <= "0100";
		s_alu_ctrl <= "0010";
		wait for 250 ns;

		s_alu_in1 <= "0100";
		s_alu_in2 <= "1111";
		s_alu_ctrl <= "0000";
		wait for 250 ns;

		s_alu_in1 <= "0100";
		s_alu_in2 <= "1111";
		s_alu_ctrl <= "0001";
		wait for 250 ns;

		s_alu_in1 <= "0100";
		s_alu_in2 <= "0010";
		s_alu_ctrl <= "0110";
		wait for 250 ns;

		s_alu_in1 <= "0100";
		s_alu_in2 <= "0110";
		s_alu_ctrl <= "0110";
		wait for 250 ns;

		s_alu_in1 <= "0100";
		s_alu_in2 <= "0110";
		s_alu_ctrl <= "0111";
		wait for 250 ns;
	end process;
end behav;