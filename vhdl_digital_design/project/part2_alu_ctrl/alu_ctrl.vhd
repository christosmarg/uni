library ieee;
use ieee.std_logic_1164.all;

entity alu_ctrl is port (
	op_5to0:	in std_logic_vector(5 downto 0);
	op_alu:		in std_logic_vector(1 downto 0);
	op:		out std_logic_vector(3 downto 0)
);
end alu_ctrl;

architecture dataflow of alu_ctrl is
begin
end behav;
