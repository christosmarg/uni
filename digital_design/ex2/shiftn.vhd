library ieee;
use ieee.std_logic_1164.all;

entity shiftn is
	generic (n: integer := 8);
	port (
		d:	in std_logic_vector(n - 1 downto 0);
		en: 	in std_logic;
		load: 	in std_logic;
		sin:	in std_logic;
		clk: 	in std_logic;
		q:	out std_logic_vector(n - 1 downto 0)
);
end shiftn;

architecture behav of shiftn is

signal qq: std_logic_vector(n - 1 downto 0);

begin
	process (clk) begin
		if (rising_edge(clk)) then
			if (load = '1') then
				q <= d;
			elsif (en = '1') then
				u: for i in 0 to n - 2 loop
					qq(i) <= qq(i + 1);
				end loop;
				qq(n - 1) <= sin;
			end if;
		end if;
	end process;
	q <= qq;
end behav;