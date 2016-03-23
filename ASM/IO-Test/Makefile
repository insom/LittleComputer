all:
	z80asm iotest.asm
	objcopy -I binary -O ihex a.bin a.ihx
sim: all
	sz80 a.ihx
.PHONY: all
