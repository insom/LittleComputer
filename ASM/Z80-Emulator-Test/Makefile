all:
	z80asm hello.asm
	objcopy -I binary -O ihex a.bin a.ihx
sim: all
	sz80 a.ihx
.PHONY: all
