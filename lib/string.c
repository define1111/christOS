#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

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
    char *dst = (char*) v;
    size_t i;

    for (i = 0; i < n; ++i)
        *dst++ = (char) c;

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

int 
strspn(char *str, const char *accept)
{
    int len = strlen(accept);
    int i, j;

    for (i = 0; *str; ++i)
    {
        bool is_found = false;

        for (j = 0; j < len; ++j) 
        {
            if (accept[j] == str[i]) 
            {
                is_found = true;
                break;
            }
        }

        if (!is_found) break;
    }

    return i;
}

int 
strcspn(char *str, const char *rejected)
{
    int len = strlen(rejected);
    int i, j;

    for (i = 0; *str; ++i) 
    {
        bool is_not_found = true;

        for (j = 0; j < len; ++j) {
            if (rejected[j] == str[i]) 
            {
                is_not_found = false;
                break;
            }
        }

        if (!is_not_found) break;
    }

    return i;
}

char *
strtok_r(char *str, const char *delim, char **save_ptr)
{
    char *end;

    if (str == NULL) 
        str = *save_ptr;

    if (*str) 
    {
        *save_ptr = str;
        return NULL;
    }

    str += strspn(str, delim);
    if (*str) 
    {
        *save_ptr = str;
        return NULL;
    }

    end = str + strcspn(str, delim);
    if (*end) 
    {
        *save_ptr = end;
        return NULL;
    }

    *end = '\0';
    *save_ptr = end + 1;

    return str;
}

char * 
itoa(uint32_t value, char *str, uint32_t base)
{
    char *original = str;
    char digit;

    do {
        digit = value % base;
        value = value / base;
        if (digit < 10) 
        {
            *str++ = digit | 0x30; /* number */
        } 
        else if (digit < 16) 
        {
            *str++ = ((digit - 10) | 0x40) + 1; /* alpha */
        }
        else 
        {
            *str++ = '?';
        }
    } while (value > 0);

    if (base == 16) 
    {
        /* hexedecimal integer */
        *str++ = 'x';
        *str++ = '0';
    } 
    else if (base == 8) 
    {
        /* octal integer */
        *str++ = 'o';
        *str++ = '0';
    } 
    else if (base == 2) 
    {
        /* binary integer */
        *str++ = 'b';
        *str++ = '0';
    }
    *str++ = '\0';

    strinv(original);

    return str;
}

uint32_t 
atou(char *str)
{
    int k = 0;

    while (*str) 
    {
        k = (k << 3) + (k << 1) + (*str) - '0';
        str++;
    }

    return k;
}

char * 
strinv(char *str)
{
    int i;
    uint32_t n = strlen(str);
    char buf[n + 2];
    char* cur = buf;

    for (i = n - 1; i >= 0; --i) 
        *cur++ = str[i];
    *cur++ = '\0';

    strcpy(str, buf);

    return str;
}

uint32_t
sprintf(char *s1, const char *s2, ...)
{
    va_list list;
    va_start(list, s2);

    return vsprintf(s1, s2, list);
}

uint32_t
snprintf(char *s1, uint32_t n, const char *s2, ...)
{
    va_list list;
    va_start(list, s2);

    return vsnprintf(s1, n, s2, list);
}

uint32_t
vsprintf(char *s1, const char *s2, va_list list)
{
    return vsnprintf(s1, 4 * 1024, s2, list);
}

uint32_t
vsnprintf(char *s1, uint32_t n, const char *s2, va_list list)
{
    uint32_t j = 0;
    size_t count = 0;
    char number[32];
    char *cur = s1;
    char *str;

    while (s2[j] != '\0' && j < n) 
    {
        if (s2[j] != '%') 
        {
            /* text */
            *cur++ = s2[j++];
        } 
        else if (s2[j] == '%') 
        {
            /* control character */
            switch (s2[++j]) {
                case 'c':
                    /* character */
                    *cur++ = va_arg(list, char);
                    break;
                case 'u':
                     /* unsigned decimal */
                    itoa(va_arg(list, uint32_t), number, 10);
                    strcpy(cur, number);
                    cur += strlen(number);
                    break;
                case 'X':
                    /* unsigned hexedecimal */
                    itoa(va_arg(list, uint32_t), number, 16);
                    strcpy(cur, number);
                    cur += strlen(number);
                    break;
                case 's':
                    /* string */
                    str = va_arg(list, char*);
                    strcpy(cur, str);
                    cur += strlen(str);
                    break;
                }
            j++;
        }
    }

    count = ((size_t) cur - (size_t) s1);
    *cur++ = '\0';

    va_end(list);

    return count;
}
