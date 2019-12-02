#ifndef INC_HEAP_H
#define INC_HEAP_H

#include <stdint.h>

/* 1 MB for HEAP */
#define HEAP_PAGE_SIZE (512)
#define HEAP_PAGE_AMOUNT (2 * 1024) 

void heap_init(void);

void show_addr(void);

void *malloc(size_t size);

#endif
