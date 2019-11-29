#ifndef INC_STDIO_H
#define INC_STDIO_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

void printf(const char *format, ...);
void vprintf(const char *format, va_list list);

void clear(void);
void mode(bool is_early);
void log(char *buf, uint32_t n);

#endif
