library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity alu_tb is
end alu_tb;

architecture behav of alu_tb is

signal s_dw:	natural := 4;
signal s_alu_in1:	std_logic_vector(s_dw-1 downto 0);
signal s_alu_in2:	std_logic_vector(s_dw-1 downto 0);
signal s_alu_ctrl:	std_logic_vector(3 downto 0);
signal s_alu_out:	std_logic_vector(s_dw-1 downto 0);
signal s_alu_zero:	std_logic;

component alu is
generic (
	dw:	natural := 4
);
port (
	alu_in1:	in std_logic_vector(dw-1 downto 0);
	alu_in2:	in std_logic_vector(dw-1 downto 0);
	alu_ctrl:	in std_logic_vector(3 downto 0);
	alu_out:	out std_logic_vector(dw-1 downto 0);
	alu_zero:	out std_logic
);
end component;

begin
	uut: alu port map (
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
	end process;
end behav;
