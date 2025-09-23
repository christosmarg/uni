library ieee;
use ieee.std_logic_1164.all;

entity fa_tb is
end fa_tb;

architecture behav of fa_tb is

signal a1, b1, cin1: bit;
signal s1, cout1: bit;

component fa is port (
        a, b, cin: in bit;
        s, cout: out bit
);
end component;

begin
        uut: fa port map (
                a => a1,
                b => b1,
                cin => cin1,
                s => s1,
                cout => cout1
        );

        process begin
                a1 <= '0';
                b1 <= '0';
                cin1 <= '0';
                wait for 20 ps;

                a1 <= '0';
                b1 <= '0';
                cin1 <= '1';
                wait for 20 ps;

                a1 <= '0';
                b1 <= '1';
                cin1 <= '0';
                wait for 20 ps;

                a1 <= '0';
                b1 <= '1';
                cin1 <= '1';
                wait for 20 ps;

                a1 <= '1';
                b1 <= '0';
                cin1 <= '0';
                wait for 20 ps;

                a1 <= '1';
                b1 <= '0';
                cin1 <= '1';
                wait for 20 ps;

                a1 <= '1';
                b1 <= '1';
                cin1 <= '0';
                wait for 20 ps;

                a1 <= '1';
                b1 <= '1';
                cin1 <= '1';
                wait for 20 ps;
        end process;
end behav;
