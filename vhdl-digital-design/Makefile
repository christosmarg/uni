all:
	ghdl -a --ieee=synopsys ${IN}.vhd
	ghdl -e --ieee=synopsys ${IN}
	ghdl -r ${IN} --vcd=${IN}.vcd

sim:
	gtkwave ${IN}.vcd

clean:
	rm -f *.o *.cf *.vcd ${IN}
