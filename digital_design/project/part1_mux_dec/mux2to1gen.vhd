library ieee;
use ieee.std_logic_1164.all;

entity mux2to1gen is
generic (
	sz: 	natural := 4
);
port (
	a: 	in std_logic_vector(sz-1 downto 0);
	b: 	in std_logic_vector(sz-1 downto 0);
	s: 	in std_logic;
	c: 	out std_logic_vector(sz-1 downto 0)
);
end mux2to1gen;

architecture dataflow of mux2to1gen is
begin
	c <= a when s = '1' else b;
end dataflow;
