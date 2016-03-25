        org     00000h
start:
    ; output 0xFF on IO 0x55
        ld a, 0ffh
        out (055h), a
        out (055h), a
        jr start
