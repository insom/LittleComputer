all:
	sdcc -mz80 --code-loc 0 --no-std-crt0 helloc.c
	objcopy -I ihex -O binary helloc.ihx helloc.raw
.PHONY: all
