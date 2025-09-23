all:
	sdcc --use-non-free -mpic14 -p16f877a main.c
	pk2cmd -P PIC16F877A -E
	pk2cmd -P PIC16F877A -X -M -F main.hex

clean:
	rm -f *.asm *.cod *.hex *.lst *.o
