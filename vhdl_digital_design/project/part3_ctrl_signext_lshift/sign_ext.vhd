library ieee;
use ieee.std_logic_1164.all;

entity sign_ext is port (
	instr:		in std_logic_vector(15 downto 0);
	sign_ex:	out std_logic_vector(31 downto 0)
);
end sign_ext;

architecture dataflow of sign_ext is
begin
	-- Check the MSB to determine the sign.
	sign_ex <= x"0000" & instr when instr(15) = '0' else
		   x"ffff" & instr when instr(15) = '1';
end dataflow;
