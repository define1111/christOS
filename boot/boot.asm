bits 16
org 0x7c00

jmp start16

revelation1 db "And BIOS said: Let there be bootloader. And the bootlodaer become.", 0xd, 0xa, 0x0
revelation2 db "And the bootloader saw protected mode. And separated it from the real mode.", 0xd, 0xa, 0x0

print_string_si:
    push ax                   

    mov ah, 0x0e              
    call print_next_char      

    pop ax                    
    ret                      

print_next_char:
    mov al, [si]              
    cmp al, 0                 

    jz if_zero                

    int 0x10                  
    inc si                    

    jmp print_next_char       

if_zero:
    ret

start16:
    cli
    cld

    mov ah, 0x0
    mov al, 0x3
    int 0x10

    xor     ax, ax
    mov     ds, ax
    mov     es, ax
    mov     ss, ax
    
    mov     sp, 0x7c00

    mov     si, revelation1 
    call    print_string_si

seta20.1:
    in      al, 0x64
    test    al, 0x2
    jnz     seta20.1

    mov     al, 0xd1
    out     0x64, al

seta20.2:
    in      al, 0x64
    test    al, 0x2
    jnz     seta20.2

    mov     al, 0xdf
    out     0x60, al

    mov     si, revelation2
    call    print_string_si

    lgdt    [gdtr32]
    mov     eax, cr0
    or      eax, 1
    mov     cr0, eax

    jmp     8:start32

bits 32
start32:
    mov     eax, 16
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    movzx   esp, sp

    jmp     $

    hlt

align 16
gdt32:
    dq 0                  
    dq 0x00CF9A000000FFFF 
    dq 0x00CF92000000FFFF 
gdtr32:
    dw $ - gdt32 - 1
    dd gdt32
