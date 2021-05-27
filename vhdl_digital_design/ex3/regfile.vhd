library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity regfile is
generic (
	dw:	natural := 4;
	sz:	natural := 4;
	addrw:	natural := 2
);
port (
	a:	in std_logic_vector(dw-1 downto 0);
	addr:	in std_logic_vector(addrw-1 downto 0);
	we:	in std_logic;
	clk:	in std_logic;
	c:	out std_logic_vector(dw-1 downto 0)
);
end regfile;

architecture behav of regfile is

type regarr is array(sz-1 downto 0) of std_logic_vector(dw-1 downto 0);
signal regf: regarr;

begin
	process (clk) begin
		if (falling_edge(clk)) then
			if (we = '1') then
				regf(to_integer(unsigned(addr))) <= a;
			end if;
		end if;
	end process;
	c <= regf(to_integer(unsigned(addr)));
end behav;
