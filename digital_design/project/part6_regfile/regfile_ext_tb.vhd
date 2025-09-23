library ieee;
use ieee.std_logic_1164.all;

entity regfile_ext_tb is
end regfile_ext_tb;

architecture behav of regfile_ext_tb is

component regfile_ext is
generic (
	sz:		natural := 4;
	addrw:		natural := 2
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

signal s_sz:		natural := 4;
signal s_addrw:		natural := 2;
signal s_idata:		std_logic_vector(s_sz-1 downto 0);
signal s_raddr1:	std_logic_vector(s_addrw-1 downto 0);
signal s_raddr2:	std_logic_vector(s_addrw-1 downto 0);
signal s_waddr:		std_logic_vector(s_addrw-1 downto 0);
signal s_we:		std_logic;
signal s_clk:		std_logic;
signal s_rst:		std_logic;
signal s_odata1:	std_logic_vector(s_sz-1 downto 0);
signal s_odata2:	std_logic_vector(s_sz-1 downto 0);

begin
	uut: regfile_ext port map (
		idata => s_idata,
		raddr1 => s_raddr1,
		raddr2 => s_raddr2,
		waddr => s_waddr,
		we => s_we,
		clk => s_clk,
		rst => s_rst,
		odata1 => s_odata1,
		odata2 => s_odata2
	);

	process begin
		s_we <= '1';
		s_clk <= '0';
		s_rst <= '1';
		wait for 250 ns;

		s_clk <= '1';
		s_rst <= '0';
		s_waddr <= "00";
		s_idata <= "0101";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		s_waddr <= "01";
		s_idata <= "1101";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		s_rst <= '0';
		s_waddr <= "10";
		s_idata <= "0010";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		s_waddr <= "11";
		s_idata <= "1001";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_we <= '0';
		s_clk <= '1';
		s_raddr1 <= "00";
		s_raddr2 <= "10";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_we <= '0';
		s_clk <= '1';
		s_raddr1 <= "01";
		s_raddr2 <= "10";
		wait for 250 ns;
	end process;
end behav;
