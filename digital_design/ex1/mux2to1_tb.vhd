entity mux2to1_tb is
end mux2to1_tb;

architecture tb of mux2to1_tb is

signal a1, b1, s1, c1: bit;

component mux2to1
port (
        a, b, s: in bit;
        c: out bit
);
end component;

begin
        m1: mux2to1 port map (
                a => a1,
                b => b1,
                s => s1,
                c => c1
        );
        process begin
                a1 <= '1';
                b1 <= '0';
                s1 <= '1';
                wait for 20 ps;

                a1 <= '1';
                b1 <= '0';
                s1 <= '0';
                wait for 20 ps;
        end process;
end tb;
