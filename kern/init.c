#include <string.h>

/* test nulling bss section */
char screen_buffer[64];

void
i386_init(void)
{
    extern char edata[], end[];
    char *screen_addr = (char*) 0xB8000;
    char *msg = "And kernel become";
    int apostols_amount = 12;

    /* nulling bss section before doing anything */
    memset(edata, 0, end - edata);

    /* hello world */
    sprintf(screen_buffer, "%s. And %u apostols will be forked.", msg, apostols_amount);
    strext(screen_addr, screen_buffer, 0x7);
}
