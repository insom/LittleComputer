        org     00000h
start:
        ld a, 055h ;; 01010101
        out (0h), a ;; Address doesn't matter

        ld d, 0
loop: ;; FOR d = 0 to 200 : NEXT
        inc d
        ld a, d
        sub 200
        jr c, loop

        ;; again but different

        ld a, 0AAh ;; 10101010
        out (0h), a ;; Address _still_ doesn't matter

        ld d, 0
loop2: ;; FOR d = 0 to 200 : NEXT
        inc d
        ld a, d
        sub 200
        jr c, loop2

        ;; back to the start

        jr start
