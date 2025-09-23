library ieee;
use ieee.std_logic_1164.all;

entity mux_triple_2to1_tb is
end mux_triple_2to1_tb;

architecture behav of mux_triple_2to1_tb is

signal a1, b1: std_logic_vector(2 downto 0);
signal s1: std_logic;
signal d1: std_logic_vector(2 downto 0);

component mux_triple_2to1 port (
        a, b: in std_logic_vector(2 downto 0);
        s: in std_logic;
        d: out std_logic_vector(2 downto 0)
);
end component;

begin
        uut: mux_triple_2to1 port map (
                a => a1,
                b => b1,
                s => s1,
                d => d1
        );

        process begin
                a1 <= "001";
                b1 <= "010";
                s1 <= '0';
                wait for 20 ps;

                a1 <= "010";
                b1 <= "100";
                s1 <= '0';
                wait for 20 ps;

                a1 <= "111";
                b1 <= "011";
                s1 <= '0';
                wait for 20 ps;

                a1 <= "101";
                b1 <= "111";
                s1 <= '0';
                wait for 20 ps;

                a1 <= "010";
                b1 <= "001";
                s1 <= '1';
                wait for 20 ps;

                a1 <= "000";
                b1 <= "101";
                s1 <= '1';
                wait for 20 ps;

                a1 <= "101";
                b1 <= "010";
                s1 <= '1';
                wait for 20 ps;

                a1 <= "111";
                b1 <= "101";
                s1 <= '1';
                wait for 20 ps;
        end process;
end behav;
