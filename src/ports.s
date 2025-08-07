section .text
global out_byte
global in_byte

out_byte:
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret

in_byte:
    mov dx, [esp + 4]
    in al, dx
    ret