        org     00000h
        ld c, 0
start:
    ; fetch data+c into a
        ld h, 0
        ld a, data
        add c
        ld l, a
        ld a, (hl)

    ; print a
        ld l, a
        ld a, 1
        rst 8

    ; increment c
        ld a, c
        inc a
        ld c, a

    ; check if c > 13
        sub 13
        jr c, start
end:
        jr end
data:
        dm "Hello, world"
        db 10
