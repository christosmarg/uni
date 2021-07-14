library ieee;
use ieee.std_logic_1164.all;

entity alu_ctrl is port (
	funct:		in std_logic_vector(5 downto 0);
	alu_op:		in std_logic_vector(1 downto 0);
	op:		out std_logic_vector(3 downto 0)
);
end alu_ctrl;

architecture dataflow of alu_ctrl is
begin
	op <= "0010" when (alu_op = "00" or (alu_op = "10" and funct = "100000")) else
	      "0110" when (alu_op = "01" or (alu_op = "10" and funct = "100010")) else
	      "0000" when (alu_op = "10" and funct = "100100") else
	      "0001" when (alu_op = "10" and funct = "100101") else
	      "0111" when (alu_op = "10" and funct = "101010") else
	      "1111";
end dataflow;
