library ieee;
use ieee.std_logic_1164.all;

entity fa is port (
        a:	in std_logic;
	b:	in std_logic;
	cin:	in std_logic;
        s:	out std_logic;
	cout:	out std_logic
);
end fa;

architecture dataflow of fa is
begin
        s <= a xor b xor cin;
        cout <= (a and b) or (cin and (a xor b));
end dataflow;
