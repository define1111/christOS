#ifndef INC_STRING_H
#define INC_STRING_H

#include <stdint.h>
#include <stdarg.h>

int strlen(const char *s);
int strnlen(const char *s, size_t size);

char *strcpy(char *dsr, const char *src);
char *strncpy(char *dst, const char *str, size_t size);
char *strcat(char *dst, const char *src);

int strcmp(const char *p, const char *q);
int strncmp(const char *p, const char *q, size_t n);

char *strchr(const char *s, char c);
char *strext(char *dst, const char *s, char c);

void *memext(void *dst, size_t n, const void *src, char sym);
void *memset(void *v, int c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);

int strspn(char *str, const char *accept);
int strcspn(char *str, const char *rejected);
char *strtok_r(char *str, const char *delim, char **save_ptr);

char *itoa(uint32_t value, char *str, uint32_t base);
uint32_t atou(char *str);

char *strinv(char *str);

uint32_t sprintf(char *s1, const char *s2, ...);
uint32_t snprintf(char *s1, uint32_t n, const char *s2, ...);
uint32_t vsprintf(char *s1, const char *s2, va_list list);
uint32_t vsnprintf(char *s1, uint32_t n, const char *s2, va_list list);
#endif
