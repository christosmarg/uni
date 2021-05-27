library ieee;
use ieee.std_logic_1164.all;

entity dec2to4en is port (
        a: in std_logic_vector(1 downto 0);
        en: in std_logic;
        d: out std_logic_vector(3 downto 0)
);
end dec2to4en;

architecture dataflow of dec2to4en is
begin
        d(0) <= not a(0) and not a(1) and en;
        d(1) <= a(0) and not a(1) and en;
        d(2) <= not a(0) and a(1) and en;
        d(3) <= a(0) and a(1) and en;
end dataflow;
