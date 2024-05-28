library ieee;
use ieee.std_logic_1164.all;

entity regfile_tb is
end regfile_tb;

architecture behav of regfile_tb is

component regfile is
generic (
	dw:	natural := 4;
	sz:	natural := 4;
	addrw:	natural := 2
);
port (
	a:	in std_logic_vector(dw-1 downto 0);
	addr:	in std_logic_vector(addrw-1 downto 0);
	we:	in std_logic;
	clk:	in std_logic;
	c:	out std_logic_vector(dw-1 downto 0)
);
end component;

signal s_dw:	natural := 4;
signal s_sz:	natural := 4;
signal s_addrw:	natural := 2;
signal s_a:	std_logic_vector(s_dw-1 downto 0);
signal s_addr:	std_logic_vector(s_addrw-1 downto 0);
signal s_we:	std_logic;
signal s_clk:	std_logic;
signal s_c:	std_logic_vector(s_dw-1 downto 0);

begin
	uut: regfile port map (
		a => s_a,
		addr => s_addr,
		we => s_we,
		clk => s_clk,
		c => s_c	
	);

	process begin
		s_we <= '1';
		s_clk <= '1';
		wait for 250 ns;

		s_we <= '1';
		s_clk <= '0';
		s_addr <= "00";
		s_a <= "0101";
		wait for 250 ns;

		s_we <= '1';
		s_clk <= '1';
		wait for 250 ns;

		s_we <= '1';
		s_clk <= '0';
		s_addr <= "01";
		s_a <= "1101";
		wait for 250 ns;

		s_we <= '1';
		s_clk <= '1';
		wait for 250 ns;

		s_we <= '1';
		s_clk <= '0';
		s_addr <= "10";
		s_a <= "0010";
		wait for 250 ns;

		s_we <= '1';
		s_clk <= '1';
		wait for 250 ns;

		s_we <= '1';
		s_clk <= '0';
		s_addr <= "11";
		s_a <= "1001";
		wait for 250 ns;
	end process;
end behav;
