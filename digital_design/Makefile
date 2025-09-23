all:
	ghdl -a -fsynopsys ${IN}.vhd
	ghdl -e -fsynopsys ${IN}
	ghdl -r ${IN} --vcd=${IN}.vcd

sim:
	gtkwave ${IN}.vcd

clean:
	rm -f *.o *.cf *.vcd ${IN}
