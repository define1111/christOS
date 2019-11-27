#include <string.h>

void
i386_init(void)
{
//  extern char *edata, *end;
    char *screen_addr = (char*) 0xB8000;
    char *msg = "And kernel become";

    strext(screen_addr, msg, 0x7);

//  memset(edata, 0, end - edata);
}
