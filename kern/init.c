#include <string.h>
#include <stdio.h>
#include <video.h>

int 
factorial(int x)
{
    if (x == 1)
        return 1;
    return x * factorial(x - 1);
}

void
test_console_scroll()
{
    int i;

    for (i = 0; i < 19; ++i)
    {
        printf("test_console_scroll\n");
    }
}

void
i386_init(void)
{
    extern char edata[], end[];
    char *msg = "And kernel become";
    int apostols_amount = 12;
    int x = 5;

    /* nulling bss section before doing anything */
    memset(edata, 0, end - edata);

    /* init console */    
    console_init(); 

    /* hello world */
    printf("%s. And %u apostols will be forked.\n", msg, apostols_amount);
    printf("\n");
    printf("test\nconsole\n\n");
    printf("factorial(%u) = %u\n", x, factorial(x));


    test_console_scroll();
}
