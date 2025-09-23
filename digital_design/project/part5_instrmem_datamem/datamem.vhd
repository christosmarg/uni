library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity datamem is port (
	clk:	in std_logic;
	addr:	in std_logic_vector(5 downto 0);
	we:	in std_logic;
	re:	in std_logic;
	writed:	in std_logic_vector(31 downto 0);
	readd:	out std_logic_vector(31 downto 0)
);
end datamem;

architecture behav of datamem is

type data_arr is array(0 to 63) of std_logic_vector(31 downto 0);
signal memfile: data_arr;

begin
	process (clk) begin
		if (clk'event and clk = '0') then
			if we = '1' then
				memfile(to_integer(unsigned(addr))) <= writed;
			end if;
		end if;
		if re = '1' then
			readd <= memfile(to_integer(unsigned(addr)));
		end if;
	end process;
end behav;
