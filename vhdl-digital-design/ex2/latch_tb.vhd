entity latch_tb is
end latch_tb;

architecture behav of latch_tb is

signal d1: bit;
signal en1: bit;
signal q1: bit;

component latch is port (
	d: in bit;
	en: in bit;
	q: out bit
);
end component;

begin
	uut: latch port map (
		d => d1,
		en => en1,
		q => q1
	);

	process begin
		en1 <= '1';
		wait for 150 ns;
		en1 <= '0';
		wait for 250 ns;
		en1 <= '1';
		wait for 150 ns;
		en1 <= '0';
		wait for 250 ns;
		en1 <= '1';
		wait for 150 ns;
		en1 <= '0';
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
