#ifndef INC_PHYS_PAGING_H
#define INC_PHYS_PAGING_H

#include <stdint.h>

/* 4 MB for phys pages */
#define PHYS_PAGE_SIZE (4096)
#define PHYS_PAGE_AMOUNT (1024) 

void p_paging_init(void);

void p_show_addr(void);
void p_show_bit_map(void);

void *get_phys_page(size_t size);
void free_phys_page(void *addr, size_t size);
#endif
