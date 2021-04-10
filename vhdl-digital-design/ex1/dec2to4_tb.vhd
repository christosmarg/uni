library ieee;
use ieee.std_logic_1164.all;

entity dec2to4_tb is
end dec2to4_tb;

architecture behav of dec2to4_tb is

signal a1: std_logic_vector(1 downto 0);
signal d1: std_logic_vector(3 downto 0);

component dec2to4 is port (
        a: in std_logic_vector(1 downto 0);
        d: out std_logic_vector(3 downto 0)
);
end component;

begin
        uut: dec2to4 port map (
                a => a1,
                d => d1
        );

        process begin
                a1 <= "00";
                wait for 20 ps;

                a1 <= "01";
                wait for 20 ps;

                a1 <= "10";
                wait for 20 ps;

                a1 <= "11";
                wait for 20 ps;
        end process;
end behav;
