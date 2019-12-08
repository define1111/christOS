#ifndef INC_INTERRUPTS_H
#define INC_INTERRUPTS_H

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

/*
 * Api - IDT
 */
void ih_double_fault(void);
void ih_general_protect(void);
void ih_page_fault(void);
void ih_alignment_check(void);
void asm_ih_double_fault(void);
void asm_ih_general_protect(void);
void asm_ih_page_fault(void);
void asm_ih_alignment_check(void);

/*
 * Api - IRQ
 */
void ih_keyboard(void);
void asm_ih_keyboard(void);

#endif
