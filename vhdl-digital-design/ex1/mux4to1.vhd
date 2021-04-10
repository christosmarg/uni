library ieee;
use ieee.std_logic_1164.all;

entity mux4to1 is port (
        a: in std_logic_vector(3 downto 0);
        s: in std_logic_vector(1 downto 0);
        d: out std_logic
);
end mux4to1;

architecture behav of mux4to1 is
begin
        process (a, s) begin
                case s is
                        when "00" => d <= a(0);
                        when "01" => d <= a(1);
                        when "10" => d <= a(2);
                        when "11" => d <= a(3);
                        when others => d <= 'X';
                end case;
        end process;
end behav;
