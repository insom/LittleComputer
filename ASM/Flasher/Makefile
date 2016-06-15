all:
	z80asm flasher.asm
	objcopy -I binary -O ihex a.bin a.ihx
sim: all
	sz80 a.ihx
.PHONY: all
