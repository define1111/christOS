#include <string.h>
#include <stdio.h>
#include <video.h>

void
i386_init(void)
{
    extern char edata[], end[];
    char *msg = "And kernel become";
    int apostols_amount = 12;

    /* nulling bss section before doing anything */
    memset(edata, 0, end - edata);

    /* init consol */    
    video_init(); 

    /* hello world */
    printf("%s. And %u apostols will be forked.", msg, apostols_amount);
}
