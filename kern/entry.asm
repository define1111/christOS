bits 32

global _start
extern i386_init

section .text

_start:
    cli

    mov ebp, 0x0
    mov esp, bootstack

    call i386_init

    hlt
    

section .data
bootstack:   

