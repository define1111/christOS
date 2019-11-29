#include <panic.h>
#include <stdio.h>

void
panic(char *msg, ...)
{
    va_list list;

    va_start(list, msg);

    vprintf(msg, list);
    printf("kernel panic");
}
