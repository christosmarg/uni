library ieee;
use ieee.std_logic_1164.all;
use work.all;

entity adder4 is port (
        a, b: in std_logic_vector(3 downto 0);
        cin: in std_logic;
        s: out std_logic_vector(3 downto 0);
        cout: out std_logic
);
end adder4;

architecture struct of adder4 is

signal y: std_logic_vector(4 downto 0);

begin
        y(0) <= cin;
        cout <= y(4);
        u: for i in 0 to 3 generate
                p: entity work.fa(dataflow) port map (a(i), b(i), cin, s(i), cout => y(i+1));
        end generate;
end struct;
