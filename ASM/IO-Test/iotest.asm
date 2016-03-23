        org     00000h
start:
        ld d, 064h
loop:
    ; store d in (d)
        ld l, d  
        ld h, 0
        ld (hl), d       

    ; output d on IO 0x55
        ld a, d  
        out (055h), a

    ; increment d
        inc d   

    ; check if d > 200
        ld a, d  
        sub 200
        jr c, loop
        jr start
