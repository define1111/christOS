#include <string.h>

/* test nulling bss section */
int arr[50];

void
i386_init(void)
{
    extern char edata[], end[];
    char *screen_addr = (char*) 0xB8000;
    char *msg = "*nd kernel become";

    /* nulling bss section before doing anything */
    memset(edata, 0, end - edata);

    /* hello world */
    memset(msg, 'A', 1);
    strext(screen_addr, msg, 0x7);
}
