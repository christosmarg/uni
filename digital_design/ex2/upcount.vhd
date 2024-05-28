library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity upcount is port (
	clk: in std_logic;
	rst: in std_logic;
	q: inout std_logic_vector(1 downto 0)
);
end upcount;

architecture behav of upcount is
begin
	process (clk, rst) begin
		if (rst = '1') then
			q <= "00";
		elsif (rising_edge(clk)) then
			q <= q + 1;
		end if;
	end process;
end behav;
