bits 32

global _start
extern i386_init

section .text

_start:
    cli

    mov ebp, 0x0
    mov esp, bootstacktop 

    call i386_init

    hlt

section .data
align 4 
global bootstack
bootstack:
resb 8 * 4 * 1024
global bootstacktop
bootstacktop:
