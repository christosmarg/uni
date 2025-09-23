library ieee;
use ieee.std_logic_1164.all;

entity alu_ctrl_test_alu is generic (
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
end alu_ctrl_test_alu;

architecture struct of alu_ctrl_test_alu is

signal s_ctrl:		std_logic_vector(3 downto 0);

component alu_ctrl is port (
	funct:		in std_logic_vector(5 downto 0);
	alu_op:		in std_logic_vector(1 downto 0);
	op:		out std_logic_vector(3 downto 0)
);
end component;

component alu is generic (
	dw:		natural := 4
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
	uut_alu_ctrl: alu_ctrl port map (
		funct => t_funct,
		alu_op => t_alu_op,
		op => s_ctrl
	);

	uut_alu: alu port map (
		alu_in1 => t_alu_in1,
		alu_in2 => t_alu_in2,
		alu_ctrl => s_ctrl,
		alu_out => t_alu_out,
		alu_zero => t_alu_zero
	);
end struct;
