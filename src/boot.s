MBOOT_PAGE_ALIGN    equ 1<<0
MBOOT_MEM_INFO      equ 1<<1
MBOOT_HEADER_MAGIC  equ 0x1BADB002
MBOOT_HEADER_CHECKSUM equ -(MBOOT_HEADER_MAGIC + (MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO))

section .multiboot
align 4
    dd MBOOT_HEADER_MAGIC
    dd MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
    dd MBOOT_HEADER_CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

section .text
global _start
extern kernel_main

_start:
    mov esp, stack_top

    push eax
    push ebx

    call kernel_main

    cli
.hang:
    hlt
    jmp .hang