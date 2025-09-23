library ieee;
use ieee.std_logic_1164.all;

entity adder32 is port (
	a:	in std_logic_vector(31 downto 0);
	b:	in std_logic_vector(31 downto 0);
	cin:	in std_logic;
	s:	out std_logic_vector(31 downto 0);
	cout:	out std_logic
);
end adder32;

architecture struct of adder32 is

component fa is port (
	a:	in std_logic;
	b:	in std_logic;
	cin:	in std_logic;
	s:	out std_logic;
	cout:	out std_logic
);
end component;

signal y:	std_logic_vector(32 downto 0);

begin
	y(0) <= cin;
	cout <= y(32);
	adder_gen: for i in 0 to 31 generate
		adder_map: fa port map (a(i), b(i), cin, s(i), cout => y(i+1));
	end generate;
end struct;
