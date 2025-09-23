library ieee;
use ieee.std_logic_1164.all;

entity dec2to4en_tb is
end dec2to4en_tb;

architecture behav of dec2to4en_tb is

signal a1: std_logic_vector(1 downto 0);
signal en1: std_logic;
signal d1: std_logic_vector(3 downto 0);

component dec2to4en is port (
        a: in std_logic_vector(1 downto 0);
        en: in std_logic;
        d: out std_logic_vector(3 downto 0)
);
end component;

begin
        uut: dec2to4en port map (
                a => a1,
                en => en1,
                d => d1
        );

        process begin
                a1 <= "00";
                en1 <= '0';
                wait for 20 ps;

                a1 <= "01";
                en1 <= '0';
                wait for 20 ps;

                a1 <= "10";
                en1 <= '0';
                wait for 20 ps;

                a1 <= "11";
                en1 <= '0';
                wait for 20 ps;

                a1 <= "00";
                en1 <= '1';
                wait for 20 ps;

                a1 <= "01";
                en1 <= '1';
                wait for 20 ps;

                a1 <= "10";
                en1 <= '1';
                wait for 20 ps;

                a1 <= "11";
                en1 <= '1';
                wait for 20 ps;
        end process;
end behav;
