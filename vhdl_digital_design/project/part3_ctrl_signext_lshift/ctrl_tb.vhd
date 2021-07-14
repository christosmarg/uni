library ieee;
use ieee.std_logic_1164.all;

entity ctrl_tb is
end ctrl_tb;

architecture behav of ctrl_tb is

signal s_funct:		std_logic_vector(5 downto 0);
signal s_reg_dst:	std_logic;
signal s_reg_wr:	std_logic;
signal s_alu_src:	std_logic;
signal s_branch:	std_logic;
signal s_mem_rd:	std_logic;
signal s_mem_wr:	std_logic;
signal s_mem_toreg:	std_logic;
signal s_alu_op:	std_logic_vector(1 downto 0);

component ctrl is port (
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
end component;

begin
	uut: ctrl port map (
		funct => s_funct,
		reg_dst => s_reg_dst,
		reg_wr => s_reg_wr,
		alu_src => s_alu_src,
		branch => s_branch,
		mem_rd => s_mem_rd,
		mem_wr => s_mem_wr,
		mem_toreg => s_mem_toreg,
		alu_op => s_alu_op
	);

	process begin
		s_funct <= "000000";
		wait for 250 ns;

		s_funct <= "100011";
		wait for 250 ns;

		s_funct <= "101011";
		wait for 250 ns;

		s_funct <= "000100";
		wait for 250 ns;
	end process;
end behav;
