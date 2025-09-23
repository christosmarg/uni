library ieee;
use ieee.std_logic_1164.all;

entity datamem_tb is
end datamem_tb;

architecture behav of datamem_tb is

signal s_clk:		std_logic;
signal s_addr:		std_logic_vector(5 downto 0);
signal s_we:		std_logic;
signal s_re:		std_logic;
signal s_writed:	std_logic_vector(31 downto 0);
signal s_readd:		std_logic_vector(31 downto 0);

component datamem is port (
	clk:		in std_logic;
	addr:		in std_logic_vector(5 downto 0);
	we:		in std_logic;
	re:		in std_logic;
	writed:		in std_logic_vector(31 downto 0);
	readd:		out std_logic_vector(31 downto 0)
);
end component;

begin
	uut: datamem port map (
		clk => s_clk,
		addr => s_addr,
		we => s_we,
		re => s_re,
		writed => s_writed,
		readd => s_readd
	);

	process begin
		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		wait for 250 ns;

		s_we <= '1';
		s_re <= '0';
		s_addr <= "000000";
		s_writed <= "01010101010101010101010101010101";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		wait for 250 ns;

		s_addr <= "000001";
		s_writed <= "11011101110111011101110111011101";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		wait for 250 ns;

		s_addr <= "000010";
		s_writed <= "00100010001000100010001000100010";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		wait for 250 ns;

		s_addr <= "000011";
		s_writed <= "10011001100110011001100110011001";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		wait for 250 ns;

		s_we <= '0';
		s_re <= '1';
		s_addr <= "000000";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		wait for 250 ns;

		s_addr <= "000001";
		wait for 250 ns;

		s_clk <= '0';
		wait for 250 ns;

		s_clk <= '1';
		wait for 250 ns;
	end process;
end behav;
