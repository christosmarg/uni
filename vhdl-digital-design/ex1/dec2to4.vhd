library ieee;
use ieee.std_logic_1164.all;

entity dec2to4 is port (
        a: in std_logic_vector(1 downto 0);
        d: out std_logic_vector(3 downto 0)
);
end dec2to4;

architecture dataflow of dec2to4 is
begin
        d(0) <= not a(0) and not a(1);
        d(1) <= not a(0) and a(1);
        d(2) <= a(0) and not a(1);
        d(3) <= a(0) and a(1);
end dataflow;
