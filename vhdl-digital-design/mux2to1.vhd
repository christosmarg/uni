library ieee;
use ieee.std_logic_1164.all;

entity mux2to1 is
port (
        a, b, s: in bit;
        c: out bit
);
end mux2to1;

architecture dataflow of mux2to1 is
begin
        c <= a when s = '1' else b;
        --c <= (a and s) or (b and (not s)); -- logic form
end dataflow;
