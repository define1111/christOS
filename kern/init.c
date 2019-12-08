#include <string.h>
#include <stdio.h>
#include <video.h>
#include <p_paging.h>
#include <gdt_idt_table.h>

void
i386_init(void)
{
    extern char edata[], end[];
    char *msg = "And kernel become";
    int apostols_amount = 12;

    /* nulling bss section before doing anything */
    memset(edata, 0, end - edata);

    gdt_init();
    idt_init();
    console_init(); 
    p_paging_init();

    /* hello world */
    printf("%s. And %u apostols will be forked.\n", msg, apostols_amount);
}
