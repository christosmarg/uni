library ieee;
use ieee.std_logic_1164.all;

entity shift4 is port (
	d:	in std_logic_vector(3 downto 0);
	en:	in std_logic;
	load:	in std_logic;
	sin:	in std_logic;
	clk:	in std_logic;
	q:	out std_logic_vector(3 downto 0)
);
end shift4;

architecture behav of shift4 is

signal qq: std_logic_vector(3 downto 0);

begin
	process (clk) begin
		if (rising_edge(clk)) then
			if (load = '1') then
				q <= d;
			elsif (en = '1') then
				qq(0) <= qq(1);
				qq(1) <= qq(2);
				qq(2) <= qq(3);
				qq(3) <= sin;
			end if;
		end if;
	end process;
	q <= qq;
end behav;
