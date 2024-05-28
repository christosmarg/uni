library ieee;
use ieee.std_logic_1164.all;

entity ha_tb is
end ha_tb;

architecture behav of ha_tb is

signal a1, b1: bit;
signal s1, c1: bit;

component ha is port (
        a, b: in bit;
        s, c: out bit
);
end component;

begin
        uut: ha port map (
                a => a1,
                b => b1,
                s => s1,
                c => c1
        );

        process begin
                a1 <= '0';
                b1 <= '0';
                wait for 20 ps;

                a1 <= '0';
                b1 <= '1';
                wait for 20 ps;

                a1 <= '1';
                b1 <= '0';
                wait for 20 ps;

                a1 <= '1';
                b1 <= '1';
                wait for 20 ps;
        end process;
end behav;
