library ieee;
use ieee.std_logic_1164.all;

entity mips is port (
	m_clk:		in std_logic;
	m_rst:		in std_logic
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
	addr:		in std_logic_vector(31 downto 0);
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

component adder32 is port (
	x:		in std_logic_vector(31 downto 0);
	y:		in std_logic_vector(31 downto 0);
	z:		out std_logic_vector(31 downto 0)
);
end component;

component pc is port (
	clk:		in std_logic;
	rst:		in std_logic;
	ipc:		in std_logic_vector(31 downto 0);
	opc:		out std_logic_vector(31 downto 0)
);
end component;

constant c_pc_add_val:	std_logic_vector(31 downto 0) := x"00000004";
signal s_adder_out:	std_logic_vector(31 downto 0);
signal s_pc_out:	std_logic_vector(31 downto 0);
signal s_alu_out:	std_logic_vector(31 downto 0);
signal s_reg_dst:	std_logic;
signal s_reg_wr:	std_logic;
signal s_alu_src:	std_logic;
signal s_branch:	std_logic;
signal s_mem_rd:	std_logic;
signal s_mem_wr:	std_logic;
signal s_mem_toreg:	std_logic;
signal s_alu_op:	std_logic_vector(1 downto 0);
signal s_op:		std_logic_vector(3 downto 0);
signal s_reg_out1:	std_logic_vector(31 downto 0);
signal s_reg_out2:	std_logic_vector(31 downto 0);
signal s_alu_zero:	std_logic;
signal s_instr:		std_logic_vector(31 downto 0);

begin
	alu_map: alu port map (
		alu_in1 => s_reg_out1,
		alu_in2 => s_reg_out2,
		alu_ctrl => s_op,
		alu_out => s_alu_out,
		alu_zero => s_alu_zero
	);

	regfile_ext_map: regfile_ext port map (
		idata => s_alu_out,
		raddr1 => s_instr(25 downto 21),
		raddr2 => s_instr(20 downto 16),
		waddr => s_instr(15 downto 11),
		we => s_reg_wr,
		clk => m_clk,
		rst => m_rst,
		odata1 => s_reg_out1,
		odata2 => s_reg_out2
	);

	instrmem_map: instrmem port map (
		addr => s_pc_out,
		c => s_instr
	);
	
	ctrl_map: ctrl port map (
		funct => s_instr(31 downto 26),
		reg_dst => s_reg_dst,
		reg_wr => s_reg_wr,
		alu_src => s_alu_src,
		branch => s_branch,
		mem_rd => s_mem_rd,
		mem_wr => s_mem_wr,
		mem_toreg => s_mem_toreg,
		alu_op => s_alu_op
	);

	alu_ctrl_map: alu_ctrl port map (
		funct => s_instr(5 downto 0),
		alu_op => s_alu_op,
		op => s_op
	);

	adder32_map: adder32 port map (
		x => s_pc_out,
		y => c_pc_add_val,
		z => s_adder_out
	);

	pc_map: pc port map (
		clk => m_clk,
		rst => m_rst,
		ipc => s_adder_out,
		opc => s_pc_out
	);
end struct;
