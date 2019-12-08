#include <gdt_idt_table.h>
#include <interrupts.h>
#include <pic.h>
#include <x86.h>
#include <stdio.h>
#include <panic.h>

/*
 * Api - Double fault
 */
void ih_double_fault()
{
    panic("[IH]: double fault\n");
}

/*
 * Api - General protect
 */
void ih_general_protect()
{
    panic("[IH]: general protect\n");
}

/*
 * Api - Alignment check
 */
void ih_alignment_check()
{
    panic("[IH]: alignment check\n");
}

/*
 * Api - Keyboard interrupt handler
 */
void ih_keyboard()
{
    char keycode;
    unsigned char status;

    printf("[IH]: irq %u\n", 1);

    status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);

        if (keycode < 1) {
            goto end;
        }

        /* call low half (bottom) interrupt handler */
    }

end:
    outb(PIC1_CMD_PORT, 0x20); /* end of interrupt */
}
