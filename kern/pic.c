#include <pic.h>
#include <x86.h>

/*
 * Api - Init programmable interrupt controller
 */
void pic_init()
{
    outb(PIC1_CMD_PORT, PIC_IQW_CMD); /* init PIC1 */
    outb(PIC2_CMD_PORT, PIC_IQW_CMD); /* init PIC2 */

    outb(PIC1_DATA_PORT, 0x20); /* IQW2 offset */
    outb(PIC2_DATA_PORT, 0x28); /* IQW2 offset */

    outb(PIC1_DATA_PORT, 0x00); /* IQW3 no cascade */
    outb(PIC2_DATA_PORT, 0x00); /* IQW3 no cascade */

    outb(PIC1_DATA_PORT, 0x01); /* IQW4 no cascade */
    outb(PIC2_DATA_PORT, 0x01); /* IQW4 no cascade */

    outb(PIC1_DATA_PORT, 0xff); /* disable irq PIC1 */
    outb(PIC2_DATA_PORT, 0xff); /* disable irq PIC2 */
}

/*
 * Api - Enable programmable interrupt controller
 */
void pic_enable()
{
    outb(PIC1_DATA_PORT, 0xFC); /* Enable IRQ0, IRQ1 */
}
