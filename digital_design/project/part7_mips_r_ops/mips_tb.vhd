library ieee;
use ieee.std_logic_1164.all;

entity mips_tb is
end mips_tb;

architecture behav of mips_tb is

signal s_m_clk:		std_logic;
signal s_m_rst:		std_logic;

component mips is port (
	m_clk:		in std_logic;
	m_rst:		in std_logic
);
end component;

begin
	uut: mips port map (
		m_clk => s_m_clk,
		m_rst => s_m_rst
	);

	process begin
		-- Reset everything.
		s_m_rst <= '1';
		s_m_clk <= '0';
		wait for 250 ns;

		s_m_clk <= '1';
		wait for 250 ns;

		-- 1st cycle.
		s_m_rst <= '0';
		s_m_clk <= '0';
		wait for 250 ns;

		s_m_clk <= '1';
		wait for 250 ns;

		-- 2nd cycle.
		s_m_clk <= '0';
		wait for 250 ns;

		s_m_clk <= '1';
		wait for 250 ns;

		-- 3rd cycle.
		s_m_clk <= '0';
		wait for 250 ns;

		s_m_clk <= '1';
		wait for 250 ns;
	end process;
end behav;
