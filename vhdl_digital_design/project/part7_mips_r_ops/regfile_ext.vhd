library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity regfile_ext is
generic (
	sz:		natural := 32;
	addrw:		natural := 5
);
port (
	idata:		in std_logic_vector(sz-1 downto 0);
	raddr1:		in std_logic_vector(addrw-1 downto 0);
	raddr2:		in std_logic_vector(addrw-1 downto 0);
	waddr:		in std_logic_vector(addrw-1 downto 0);
	we:		in std_logic;
	clk:		in std_logic;
	rst:		in std_logic;
	odata1:		out std_logic_vector(sz-1 downto 0);
	odata2:		out std_logic_vector(sz-1 downto 0)
);
end regfile_ext;

architecture behav of regfile_ext is

signal arrsz:		natural := 32;
type regarr		is array(0 to arrsz-1) of std_logic_vector(sz-1 downto 0);
-- Array used for initialization when rst = 1.
signal s_init:		regarr := (others => x"ffffffff");
signal regf:		regarr;

begin
	process (clk) begin
		if (rst = '1') then
			regf <= s_init;
		elsif (clk'event and clk = '0') then
			if (we = '1') then
				regf(to_integer(unsigned(waddr))) <= idata;
			end if;
		end if;
	end process;
	odata1 <= regf(to_integer(unsigned(raddr1)));
	odata2 <= regf(to_integer(unsigned(raddr2)));
end behav;
