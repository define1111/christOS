#ifndef INC_STDARG_H
#define INC_STDARG_H


#include <stdint.h>

typedef size_t* va_list;

#define va_start(l, a) (l = (void*)((size_t)&a) + sizeof(a))
#define va_end(l) (l = (void*)0)
#define va_arg(l, s) (*(s*)(l++))

#endif
