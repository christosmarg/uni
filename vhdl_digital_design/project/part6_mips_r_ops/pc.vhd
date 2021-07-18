library ieee;
use ieee.std_logic_1164.all;

entity pc is port (
	clk:	in std_logic;
	rst:	in std_logic;
	ipc:	in std_logic_vector(3 downto 0);
	opc:	out std_logic_vector(3 downto 0)
);
end pc;

architecture behav of pc is
begin
	process (clk) begin
		if (rst = '1') then
			opc <= "0000";
		elsif (rising_edge(clk)) then
			opc <= ipc;
		end if;
	end process;
end behav;
