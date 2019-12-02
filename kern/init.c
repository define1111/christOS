#include <string.h>
#include <stdio.h>
#include <video.h>
#include <heap.h>

void
i386_init(void)
{
    extern char edata[], end[];
    char *msg = "And kernel become";
    int apostols_amount = 12;
    
    char *str = NULL;
    int *arr = NULL;

    /* nulling bss section before doing anything */
    memset(edata, 0, end - edata);

    console_init(); 

    heap_init();

    /* hello world */
    printf("%s. And %u apostols will be forked.\n", msg, apostols_amount);

    show_addr();

    str = (char*) malloc(4 * sizeof(char));
    str[0] = 'A';
    str[1] = 'B';
    str[2] = 'C';
    str[3] = '\0';

    arr = (int*) malloc(3 * sizeof(int));

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    printf("%s\n%X\n%u %u %u\n%X\n", str, str, arr[0], arr[1], arr[2], arr);
    
}
