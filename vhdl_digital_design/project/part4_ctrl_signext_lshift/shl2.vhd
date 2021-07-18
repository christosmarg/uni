library ieee;
use ieee.std_logic_1164.all;

entity shl2 is port (
	in1:	in std_logic_vector(31 downto 0);
	d:	out std_logic_vector(31 downto 0)
);
end shl2;

architecture dataflow of shl2 is
begin
	d <= in1(29 downto 0) & "00";	
end dataflow;
