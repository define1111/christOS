#ifndef INC_GDT_IDT_H
#define INC_GDT_IDT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define GDT_NULL_SEGMENT 0
#define GDT_KCODE_SEGMENT 1
#define GDT_KDATA_SEGMENT 2
#define GDT_KSTACK_SEGMENT 3
#define GDT_UCODE_SEGMENT 4
#define GDT_UDATA_SEGMENT 5
#define GDT_USTACK_SEGMENT 6
#define GDT_TSS_SEGMENT 7
#define GDT_ENTRIES_COUNT 8

#define GDT_NULL_SELECTOR 0x00
#define GDT_KCODE_SELECTOR 0x08
#define GDT_KDATA_SELECTOR 0x10
#define GDT_KSTACK_SELECTOR 0x18
#define GDT_KTSS_SELECTOR 0x38
#define GDT_UCODE_SELECTOR 0x23
#define GDT_UDATA_SELECTOR 0x2b
#define GDT_USTACK_SELECTOR 0x33
#define GDT_UTSS_SELECTOR 0x3b

#define IDT_SIZE 256
#define INT_ZERO 0x0
#define INT_OPCODE 0x6
#define INT_DOUBLE_FAULT 0x8
#define INT_GENERAL_PROTECT 0xD
#define INT_PAGE_FAULT 0xE
#define INT_ALIGNMENT_CHECK 0x11
#define INT_TIMER 0x20
#define INT_KEYBOARD 0x21
#define INT_SYSCALL 0x80
#define INTERRUPT_GATE 0x8e


struct GDT_entry_t 
{
    uint16_t limit_low: 16;
    uint16_t base_low: 16;
    uint8_t base_middle: 8;
    uint8_t type: 4; /* whether code (0b1010), data (0b0010), stack (0b0110) or tss (0b1001) */
    uint8_t s: 1; /* whether system descriptor */
    uint8_t dpl: 2; /* privilege level */
    uint8_t p: 1; /* whether segment prensent */
    uint8_t limit_high: 4;
    uint8_t a: 1; /* reserved for operation system */
    uint8_t zero: 1; /* zero */
    uint8_t db: 1; /* whether 16 or 32 segment */
    uint8_t g: 1; /* granularity */
    uint8_t base_high: 8;
} attribute(packed);

typedef struct GDT_entry_t GDT_entry_t;

struct GDT_pointer_t 
{
    uint16_t limit;
    uint32_t base;
} attribute(packed);

typedef struct GDT_pointer_t GDT_pointer_t;

struct IDT_entry_t 
{
    uint16_t offset_lowerbits;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higherbits;
};

typedef struct IDT_entry_t IDT_entry_t;

void gdt_init(void);
void idt_init(void);

#endif
