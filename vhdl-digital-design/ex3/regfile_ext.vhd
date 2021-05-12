library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity regfile_ext is
generic (
	dw:	natural := 4;
	sz:	natural := 4;
	addrw:	natural := 2
);
port (
	a:	in std_logic_vector(dw-1 downto 0);
	raddr1:	in std_logic_vector(addrw-1 downto 0);
	raddr2:	in std_logic_vector(addrw-1 downto 0);
	waddr:	in std_logic_vector(addrw-1 downto 0);
	we:	in std_logic;
	clk:	in std_logic;
	rst:	in std_logic;
	b:	out std_logic_vector(dw-1 downto 0);
	c:	out std_logic_vector(dw-1 downto 0)
);
end regfile_ext;

architecture behav of regfile_ext is

type regarr is array(sz-1 downto 0) of std_logic_vector(dw-1 downto 0);
signal regf: regarr;

begin
	process (clk) begin
		if (rst = '1') then
			regf(0) <= "0000";
			regf(1) <= "0000";
			regf(2) <= "0000";
			regf(3) <= "0000";
		elsif (falling_edge(clk)) then
			if (we = '1') then
				regf(to_integer(unsigned(waddr))) <= a;
			end if;
		end if;
	end process;
	b <= regf(to_integer(unsigned(raddr1)));
	c <= regf(to_integer(unsigned(raddr2)));
end behav;