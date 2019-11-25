#ifndef INC_STRING_H
#define INC_STRING_H

#include <stdint.h>

int strlen(const char *s);
int strnlen(const char *s, size_t size);

char *strcpy(char *dsr, const char *src);
char *strncpy(char *dst, const char *str, size_t size);
char *strcat(char *dst, const char *src);

int strcmp(const char *p, const char *q);
int strncmp(const char *p, const char *q, size_t n);

char *strchr(const char *s, char c);
char *strext(char *dst, const char *s, char c);

void *memset(void *v, int c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);

long strtil(const char *s, char **endptr, int base);

#endif
