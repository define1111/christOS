#ifndef INC_REG_H
#define INC_REG_H

#include <stdint.h>
#include <stddef.h>

/*
 * i80386 general purpose registers
 */
struct gp_registers_t 
{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp; /* current stack */
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
} attribute(packed);

typedef struct gp_registers_t gp_registers_t;

/*
 * i80386 other purpose registers
 */
struct op_registers_t 
{
    uint32_t eip;
    uint32_t cr3; /* page directory */
    uint32_t k_esp; /* kernel stack */
    uint32_t u_esp; /* user stack */
    uint16_t cs;
    uint16_t ds;
    uint16_t ss;
};

typedef struct op_registers_t op_registers_t;

/*
 * i80386 flags
 */
struct flags_t 
{
    uint8_t cflag : 1; /* carry flag */
    uint8_t res1 : 1; /* reserved */
    uint8_t pflag : 1; /* parity flag */
    uint8_t res2 : 1; /* reserved */
    uint8_t aflag : 1; /* auxiliary carry flag */
    uint8_t res3 : 1; /* reserved */
    uint8_t zflag : 1; /* zero flag */
    uint8_t sflag : 1; /* sign flag */
    uint8_t tflag : 1; /* trap flag */
    uint8_t iflag : 1; /* interrupt enable flag */
    uint8_t dflag : 1; /* direction flag */
    uint8_t oflag : 1; /* overflow flag */
    uint8_t iopl : 2; /* io privilege level */
    uint8_t nt : 1; /* nested task */
    uint8_t res4 : 1; /* reserved */

    uint8_t rflag : 1; /* resume flag */
    uint8_t vmflag : 1; /* virtual mode flag */
    uint8_t acflag : 1; /* alignment check flag */
    uint8_t viflag : 1; /* virtual interrupt flag */
    uint8_t vipflag : 1; /* virtual interrupt pending flag */
    uint8_t idflag : 1; /* id flag */
    uint16_t res5 : 10; /* reserved */
} attribute(packed);

typedef struct flags_t flags_t;

/*
 * Api
 */
uint16_t asm_get_cs(void);
uint16_t asm_get_ds(void);
uint16_t asm_get_ss(void);
uint32_t asm_get_esp(void);
uint32_t asm_get_eflags(void);
uint32_t asm_get_cr0(void);
uint32_t asm_get_cr2(void);
uint32_t asm_get_cr3(void);
void asm_lock(void);
void asm_unlock(void);
void asm_hlt(void);

#endif
