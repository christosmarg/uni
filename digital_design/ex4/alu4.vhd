library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity alu4 is port (
	alu_in1:	in std_logic_vector(3 downto 0);
	alu_in2:	in std_logic_vector(3 downto 0);
	alu_ctrl:	in std_logic_vector(3 downto 0);
	alu_out:	out std_logic_vector(3 downto 0);
	alu_zero:	out std_logic
);
end alu4;

architecture behav of alu4 is
signal sig:		std_logic_vector(3 downto 0);

begin
	process (alu_ctrl) begin
		case alu_ctrl is
		when "0000" => sig <= alu_in1 and alu_in2;
		when "0001" => sig <= alu_in1 or alu_in2;
		when "0010" =>
			sig <= std_logic_vector(signed(alu_in1) + signed(alu_in2));
		when "0110" =>
			sig <= std_logic_vector(signed(alu_in1) - signed(alu_in2));
		when "0111" =>
			if (alu_in1 < alu_in2) then
				sig <= "0001";
			else
				sig <= "0000";
			end if;
		when others => sig <= (others => 'X');
		end case;
	end process;
	alu_zero <= '1' when sig = "0000" else '0';
	alu_out <= sig;
end behav;
