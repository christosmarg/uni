library ieee;
use ieee.std_logic_1164.all;

entity alu_ctrl_test_alu is generic (
	t_dw:		natural := 4
);
port (
	t_op_5to0:	in std_logic_vector(5 downto 0);
	t_op_alu:	in std_logic_vector(1 downto 0);
	t_op:		in std_logic_vector(3 downto 0);
	t_alu_in1:	in std_logic_vector(dw-1 downto 0);
	t_alu_in2:	in std_logic_vector(dw-1 downto 0);
	t_alu_ctrl:	out std_logic_vector(3 downto 0);
	t_alu_out:	out std_logic_vector(dw-1 downto 0);
	t_alu_zero:	out std_logic
);
end alu_ctrl_test_alu;

architecture struct of alu_ctrl_test_alu is

component alu_ctrl is port (
	op_5to0:	in std_logic_vector(5 downto 0);
	op_alu:		in std_logic_vector(1 downto 0);
	op:		in std_logic_vector(3 downto 0)
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
		op_5to0 => t_op_5to0,
		op_alu => t_op_alu,
		op => t_op
	);

	uut_alu: alu port map (
		alu_in1 => t_alu_in1,
		alu_in2 => t_alu_in2,
		alu_ctrl => t_alu_ctrl,
		alu_out => t_alu_out,
		alu_zero => t_alu_zero
	);
end struct;
