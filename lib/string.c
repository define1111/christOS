#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int
strlen(const char *s)
{
    const char *p;

    for (p = s; *p; ++p)
        ;

    return p - s;
}

int
strnlen(const char *s, size_t size)
{
    const char *p;

    for (p = s; size > 0 && *p; ++p, --size)
        ;

    return p - s;
}

char *
strcpy(char *dst, const char *src)
{
    char *ret = dst;

    while ((*dst++ = *src++))
        ;

    return ret;
}

char *
strncpy(char *dst, const char *str, size_t size)
{
    size_t i;
    char *ret;

    for (i = 0, ret = dst; i < size; ++i)
    {
        *dst++ = *str;
            
        if (*str) str++;
    }

    return ret;
}

char *strcat(char *dst, const char *src)
{
    int len = strlen(dst);
    strcpy(dst + len, src);
    return dst;
}

int
strcmp(const char *p, const char *q)
{
    while (*p && *p == *q)
    p++, q++;
    return (int) ((unsigned char) *p - (unsigned char) *q);
}

int
strncmp(const char *p, const char *q, size_t n)
{
    while (n > 0 && *p && *p == *q)
        n--, p++, q++;
    if (n == 0)
        return 0;
    else
        return (int) ((unsigned char) *p - (unsigned char) *q);
}

char *
strchr(const char *s, char c)
{
    for (; *s; ++s)
        if (*s == c)
            return (char*) s;
    return NULL;
}

char *
strext(char *dst, const char *s, char c)
{
    while (*s)
    {
        *dst++ = *s++;
        *dst++ = c;
    }

    return dst;
}

void *
memset(void *v, int c, size_t n)
{
    char *p = (char*) v;
    char char_c = (char) c;

    while (--n >= 0)
        *p++ = char_c;

    return v;
}

void *
memcpy(void *dst, const void *src, size_t n)
{
    const char *s = src;
    char *d = dst;

    if (s < d && s + n > d)
    {
        s += n;
        d += n;
        while (n-- > 0)
            *--d = *--s;
    }
    else
        while (n-- > 0)
            *d++ = *s++;

    return dst;
}

long
strtol(const char *s, char **endptr, int base)
{
    int neg = 0;
    long val = 0;

    while (*s == ' ' || *s == '\t')
        s++;

    if (*s == '+')
        s++;
    else if (*s == '-')
        s++, neg = 1;

    if ((base == 0 || base == 16) && (s[0] == '0' && s[1] == 'x'))
        s += 2, base = 16;
    else if (base == 0 && s[0] == '0')
        s++, base = 8;
    else if (base == 0)
        base = 10;

    while (true) 
    {
        int dig;

        if (*s >= '0' && *s <= '9')
            dig = *s - '0';
        else if (*s >= 'a' && *s <= 'z')
            dig = *s - 'a' + 10;
        else if (*s >= 'A' && *s <= 'Z')
            dig = *s - 'A' + 10;
        else
            break;
        if (dig >= base)
            break;
        s++, val = (val * base) + dig;
    }

    if (endptr)
        *endptr = (char *) s;
    return (neg ? -val : val);
}

