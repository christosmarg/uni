library ieee;
use ieee.std_logic_1164.all;

entity dec4to16_tb is
end dec4to16_tb;

architecture behav of dec4to16_tb is

signal a1: std_logic_vector(3 downto 0);
signal d1: std_logic_vector(15 downto 0);

component dec4to16 is port (
        a: in std_logic_vector(3 downto 0);
        d: out std_logic_vector(15 downto 0)
);
end component;

begin
        uut: dec4to16 port map (
                a => a1,
                d => d1
        );

        process begin
                a1 <= "0000";
                wait for 20 ps;

                a1 <= "0001";
                wait for 20 ps;

                a1 <= "0010";
                wait for 20 ps;

                a1 <= "0011";
                wait for 20 ps;

                a1 <= "0100";
                wait for 20 ps;

                a1 <= "0101";
                wait for 20 ps;

                a1 <= "0110";
                wait for 20 ps;

                a1 <= "0111";
                wait for 20 ps;

                a1 <= "1000";
                wait for 20 ps;

                a1 <= "1001";
                wait for 20 ps;

                a1 <= "1010";
                wait for 20 ps;

                a1 <= "1011";
                wait for 20 ps;

                a1 <= "1100";
                wait for 20 ps;

                a1 <= "1101";
                wait for 20 ps;

                a1 <= "1110";
                wait for 20 ps;

                a1 <= "1111";
                wait for 20 ps;
        end process;
end behav;
