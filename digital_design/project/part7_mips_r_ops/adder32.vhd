library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

entity adder32 is port (
	x:	in std_logic_vector(31 downto 0);
	y:	in std_logic_vector(31 downto 0);
	z:	out std_logic_vector(31 downto 0)
);
end adder32;

architecture dataflow of adder32 is
begin
	z <= std_logic_vector(unsigned(x) + unsigned(y));
end dataflow;
