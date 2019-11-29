#include <assert.h>
#include <panic.h>
#include <stdio.h>

void
assert(const char *file, uint32_t line, bool expr)
{
    if (!expr)
        panic("%s line %u", file, line);
}

void
unreachable(const char *file, uint32_t line)
{
    printf("code unreachable");
    panic("%s line %u");
}
