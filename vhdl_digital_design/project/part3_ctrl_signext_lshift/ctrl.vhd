library ieee;
use ieee.std_logic_1164.all;

entity ctrl is port (
	funct:		in std_logic_vector(5 downto 0);
	reg_dst:	out std_logic;
	reg_wr:		out std_logic;
	alu_src:	out std_logic;
	branch:		out std_logic;
	mem_rd:		out std_logic;
	mem_wr:		out std_logic;
	mem_toreg:	out std_logic;
	alu_op:		out std_logic_vector(1 downto 0)
);
end ctrl;

architecture dataflow of ctrl is
begin
	reg_dst		<= '1' when funct = "000000" else '0';
	reg_wr		<= '1' when funct = "000000" or funct = "100011" else '0';
	alu_src		<= '1' when funct = "100011" or funct = "101011" else '0';
	branch		<= '1' when funct = "000100" else '0';
	mem_rd		<= '1' when funct = "100011" else '0';
	mem_wr		<= '1' when funct = "101011" else '0';
	mem_toreg	<= '1' when funct = "100011" else '0';
	with funct select
		alu_op <= "10" when "000000",
			  "01" when "000100",
			  "00" when others;
end dataflow;
