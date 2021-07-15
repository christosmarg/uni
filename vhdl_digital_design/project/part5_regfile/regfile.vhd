library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity regfile is
generic (
	sz:	natural := 4;
	addrw:	natural := 3
);
port (
	idata:	in std_logic_vector(sz-1 downto 0);
	addr:	in std_logic_vector(addrw-1 downto 0);
	we:	in std_logic;
	clk:	in std_logic;
	odata:	out std_logic_vector(sz-1 downto 0)
);
end regfile;

architecture behav of regfile is

signal arrsz:	natural := 4;
type regarr	is array(arrsz-1 downto 0) of std_logic_vector(sz-1 downto 0);
signal regf:	regarr;

begin
	process (clk) begin
		if (clk'event and clk = '0') then
			if (we = '1') then
				regf(to_integer(unsigned(addr))) <= idata;
			end if;
		end if;
	end process;
	odata <= regf(to_integer(unsigned(addr)));
end behav;
