library ieee;
use ieee.std_logic_1164.all;

entity regfile_tb is
end regfile_tb;

architecture behav of regfile_tb is

component regfile is
generic (
	sz:	natural := 4;
	addrw:	natural := 3
);
port (
	idata:	in std_logic_vector(sz-1 downto 0);
	addr:	in std_logic_vector(addrw-1 downto 0);
	we:	in std_logic;
	clk:	in std_logic;
	odata:	out std_logic_vector(sz-1 downto 0)
);
end component;

signal s_sz:	natural := 4;
signal s_addrw:	natural := 3;
signal s_idata:	std_logic_vector(s_sz-1 downto 0);
signal s_addr:	std_logic_vector(s_addrw-1 downto 0);
signal s_we:	std_logic;
signal s_clk:	std_logic;
signal s_odata:	std_logic_vector(s_sz-1 downto 0);

begin
	uut: regfile port map (
		idata => s_idata,
		addr => s_addr,
		we => s_we,
		clk => s_clk,
		odata => s_odata
	);

	process begin
		s_we <= '1';
		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		s_addr <= "000";
		s_idata <= "0101";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		s_addr <= "001";
		s_idata <= "1101";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		s_addr <= "010";
		s_idata <= "0010";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		s_addr <= "011";
		s_idata <= "1001";
		wait for 250 ns;
	end process;
end behav;

