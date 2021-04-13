entity ff_tb is
end ff_tb;

architecture behav of ff_tb is

signal d1: bit;
signal clk1: bit;
signal q1: bit;

component ff is port (
        d: in bit;
        clk: in bit;
        q: out bit
);
end component;

begin
        uut: ff port map (
                d => d1,
                clk => clk1,
                q => q1
        );

        process begin
                clk1 <= '1';
                wait for 150 ns;

                clk1 <= '0';
                wait for 250 ns;

                clk1 <= '1';
                wait for 150 ns;

                clk1 <= '0';
                wait for 250 ns;

                clk1 <= '1';
                wait for 150 ns;

                clk1 <= '0';
                wait for 250 ns;
        end process;

        process begin
                d1 <= '1';
                wait for 280 ns;

                d1 <= '0';
                wait for 300 ns;

                d1 <= '1';
                wait for 250 ns;

                d1 <= '0';
                wait for 150 ns;

                d1 <= '1';
                wait for 75 ns;

                d1 <= '0';
                wait for 150 ns;
        end process;
end behav;
