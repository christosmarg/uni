library ieee;
use ieee.std_logic_1164.all;

entity mux4to1_tb is
end mux4to1_tb;

architecture behav of mux4to1_tb is

signal a1: std_logic_vector(3 downto 0);
signal s1: std_logic_vector(1 downto 0);
signal d1: std_logic;

component mux4to1 port (
        a: in std_logic_vector(3 downto 0);
        s: in std_logic_vector(1 downto 0);
        d: out std_logic
);
end component;

begin
        uut: mux4to1 port map (
                a => a1,
                s => s1,
                d => d1
        );

        process begin
                a1 <= "0000";
                s1 <= "00";
                wait for 20 ps;

                a1 <= "0101";
                s1 <= "01";
                wait for 20 ps;

                a1 <= "1010";
                s1 <= "10";
                wait for 20 ps;

                a1 <= "1100";
                s1 <= "11";
                wait for 20 ps;
        end process;
end behav;
