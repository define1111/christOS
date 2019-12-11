#
# Interrupt descriptor table handlers
#
.code32
.text
.globl asm_ih_double_fault, asm_ih_general_protect
.globl asm_ih_alignment_check
.globl asm_ih_keyboard


/*
 * Handle error double fault
 */
 asm_ih_double_fault:
    cli
    pushal
    call asm_load_data_kselectors
    call ih_double_fault
    call asm_load_data_uselectors
    popal
    sti
    iretl

/*
 * General protect
 */
 asm_ih_general_protect:
    cli
    pushal
    call asm_load_data_kselectors
    call ih_general_protect
    call asm_load_data_uselectors
    popal
    sti
    iretl

/*
 * Alignment check
 */
 asm_ih_alignment_check:
    cli
    pushal
    call asm_load_data_kselectors
    call ih_alignment_check
    call asm_load_data_uselectors
    popal
    sti
    iretl

/*
 * Handle IRQ1
 * void asm_ih_keyboard(unsigned int)
 */
asm_ih_keyboard:
    pushal
    call asm_load_data_kselectors
    call ih_keyboard
    call asm_load_data_uselectors
    popal
    iretl

/*
 * Handle IRQ0
 * void asm_ih_timer()
 */
asm_ih_timer:
    cli
    pushal
    call asm_load_data_kselectors
    mov %esp,%ebp
    mov %ebp,%ebx
    pushl %ebx # &reg
    add $32,%ebx
    pushl %ebx # &ret addr
    call ih_timer
    mov %ebp,%esp
    call asm_load_data_uselectors
    popal
    sti
    iretl

/*
 * Handle syscall interrupt
 * void asm_ih_syscall(unsigned int *function)
 */
asm_ih_syscall:
    pushal
    call asm_load_data_kselectors
    mov %esp,%ebp
    mov %ebp,%ebx
    add $32,%ebx
    add $12,%ebx
    pushl (%ebx) # &function
    call ih_syscall
    mov %ebp,%esp
    mov %eax,28(%esp)
    call asm_load_data_uselectors
    popal
    iretl
