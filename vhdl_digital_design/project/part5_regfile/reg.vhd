library ieee;
use ieee.std_logic_1164.all;

entity reg is
generic (
	sz:	natural := 4
);
port (
	d:	in std_logic_vector(sz-1 downto 0);
	rst:	in std_logic;
	clk:	in std_logic;
	q:	out std_logic_vector(sz-1 downto 0)
);
end reg;

architecture behav of reg is

-- We want to automatically initialize the vector no matter its size.
signal s_init:	std_logic_vector(sz-1 downto 0) := (others => '0');

begin
	process (rst, clk) begin
		if (rst = '0') then
			q <= s_init;
		elsif (rising_edge(clk)) then
			q <= d;
		end if;
	end process;
end behav;
