library ieee;
use ieee.std_logic_1164.all;

entity dec4to16 is port (
        a: in std_logic_vector(3 downto 0);
        d: out std_logic_vector(15 downto 0)
);
end dec4to16;

architecture dataflow of dec4to16 is
begin
        d(0)  <= not a(3) and not a(2) and not a(1) and not a(0);
        d(1)  <= not a(3) and not a(2) and not a(1) and     a(0);
        d(2)  <= not a(3) and not a(2) and     a(1) and not a(0);
        d(3)  <= not a(3) and not a(2) and     a(1) and     a(0);
        d(4)  <= not a(3) and     a(2) and not a(1) and not a(0);
        d(5)  <= not a(3) and     a(2) and not a(1) and     a(0);
        d(6)  <= not a(3) and     a(2) and     a(1) and not a(0);
        d(7)  <= not a(3) and     a(2) and     a(1) and     a(0);
        d(8)  <=     a(3) and not a(2) and not a(1) and not a(0);
        d(9)  <=     a(3) and not a(2) and not a(1) and     a(0);
        d(10) <=     a(3) and not a(2) and     a(1) and not a(0);
        d(11) <=     a(3) and not a(2) and     a(1) and     a(0);
        d(12) <=     a(3) and     a(2) and not a(1) and not a(0);
        d(13) <=     a(3) and     a(2) and not a(1) and     a(0);
        d(14) <=     a(3) and     a(2) and     a(1) and not a(0);
        d(15) <=     a(3) and     a(2) and     a(1) and     a(0);
end dataflow;
