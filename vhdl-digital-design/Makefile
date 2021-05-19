all:
	ghdl -a ${IN}.vhd
	ghdl -e ${IN}
	ghdl -r ${IN} --vcd=${IN}.vcd

sim:
	gtkwave ${IN}.vcd

clean:
	rm -f *.o *.cf *.vcd ${IN}
