library ieee;
use ieee.std_logic_1164.all;

entity mips is port (
);
end mips;

architecture struct of mips is

component alu is
generic (
	sz:		natural := 32
);
port (
	alu_in1:	in std_logic_vector(sz-1 downto 0);
	alu_in2:	in std_logic_vector(sz-1 downto 0);
	alu_ctrl:	in std_logic_vector(3 downto 0);
	alu_out:	out std_logic_vector(sz-1 downto 0);
	alu_zero:	out std_logic
);
end component;

component regfile_ext is
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
end component;

component instrmem is port (
	addr:		in std_logic_vector(3 downto 0);
	c:		out std_logic_vector(31 downto 0)
);
end component;

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

component alu_ctrl is port (
	funct:		in std_logic_vector(5 downto 0);
	alu_op:		in std_logic_vector(1 downto 0);
	op:		out std_logic_vector(3 downto 0)
);
end component;

component pc is port (
);
end component;

component adder32 is port (
);
end component;

begin
end struct;
