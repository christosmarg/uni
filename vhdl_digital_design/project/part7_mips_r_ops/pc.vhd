library ieee;
use ieee.std_logic_1164.all;

entity pc is port (
	clk:	in std_logic;
	rst:	in std_logic;
	ipc:	in std_logic_vector(31 downto 0);
	opc:	out std_logic_vector(31 downto 0)
);
end pc;

architecture behav of pc is
begin
	process (clk, rst) begin
		if (rst = '1') then
			opc <= x"00000000";
		elsif (clk'event and clk = '0') then
			opc <= ipc;
		end if;
	end process;
end behav;
