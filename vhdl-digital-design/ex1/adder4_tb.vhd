library ieee;
use ieee.std_logic_1164.all;

entity adder4_tb is
end adder4_tb;

architecture behav of adder4_tb is

signal a1, b1: std_logic_vector(3 downto 0);
signal cin1: std_logic;
signal s1: std_logic_vector(3 downto 0);
signal cout1: std_logic;

component adder4 is port (
        a, b: in std_logic_vector(3 downto 0);
        cin: in std_logic;
        s: out std_logic_vector(3 downto 0);
        cout: out std_logic
);
end component;

begin
        uut: adder4 port map (
                a => a1,
                b => b1,
                cin => cin1,
                s => s1,
                cout => cout1
        );

        process begin
                a1 <= "0000";
                b1 <= "0000";
                cin1 <= '0';
                wait for 20 ps;

                a1 <= "1111";
                b1 <= "1111";
                cin1 <= '0';
                wait for 20 ps;

                a1 <= "1111";
                b1 <= "1111";
                cin1 <= '1';
                wait for 20 ps;
                
                -- 3 + 5 (overflow)
                a1 <= "0011";
                b1 <= "0101";
                cin1 <= '0';
                wait for 20 ps;

                -- -2 + 3
                -- 2 -> 0010 -> (2's complement) -> ~0010 | 0001 ->
                -- 1101 | 0001 -> 1101 (+ cin)
                a1 <= not "0010" or "0001";
                b1 <= "0011";
                cin1 <= '1';
                wait for 20 ps;

                -- -8 + 7 (~1000 | 0001 + cin)
                a1 <= not "1000" or "0001";
                b1 <= "0111";
                cin1 <= '1';
                wait for 20 ps;
        end process;
end behav;
