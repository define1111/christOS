#ifndef INC_HEAP_H
#define INC_HEAP_H

#include <stdint.h>

/* 1 MB for HEAP */
#define HEAP_PAGE_SIZE (512)
#define HEAP_PAGE_AMOUNT (2 * 1024) 

void heap_init(void);

void heap_show_addr(void);
void heap_show_bit_map(void);

void *malloc(size_t size);
void free(void *addr, size_t size);
#endif
