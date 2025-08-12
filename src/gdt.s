global gdt_flush
global gdt_get

gdt_flush:
    cli

    mov eax, [esp+4]
    lgdt [eax]

    mov ax, 0x18
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush

.flush:
    ;sti ;remove for now

    ret

gdt_get:
    push ebp
    mov ebp, esp

    mov eax, [ebp+8]
    sgdt [eax]

    pop ebp
    ret