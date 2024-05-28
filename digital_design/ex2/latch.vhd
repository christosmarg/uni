entity latch is port (
	d: in bit;
	en: in bit;
	q: out bit
);
end latch;

architecture behav of latch is
begin
	process (d, en) begin
		if (en = '1') then
			q <= d;
		end if;
	end process;
end behav;
