library ieee;
use ieee.std_logic_1164.all;

entity mux_triple_2to1 is port (
        a, b: in std_logic_vector(2 downto 0);
        s: in std_logic;
        d: out std_logic_vector(2 downto 0)
);
end mux_triple_2to1;

architecture dataflow of mux_triple_2to1 is
begin
        d <= a when s = '1' else b;
end dataflow;
