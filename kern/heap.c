#include <heap.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

extern size_t real_end[];

static size_t *heap_begin;
static size_t *heap_end;
static size_t heap_page_size;
static size_t heap_page_amount;

static bool is_free[HEAP_PAGE_AMOUNT];

void
heap_init()
{
    heap_begin = (size_t*) real_end;
    heap_page_size = HEAP_PAGE_SIZE;
    heap_page_amount = HEAP_PAGE_AMOUNT;
    heap_end = heap_begin + (heap_page_size * heap_page_amount) / 4;

    memset(is_free, true, HEAP_PAGE_AMOUNT * sizeof(bool));
}

void *
malloc(size_t size)
{
    uint32_t pages; 
    int i;
    size_t *addr = NULL;

    if (size == 0) return NULL;

    pages = (size / heap_page_size) + 1;

    for (i = 0; i < heap_page_amount; i++)
        if (is_free[i]) break;

    addr = heap_begin + (i * heap_page_size) / 4;

    for (; i < pages; i++)
        is_free[i] = false;

    return (void*) addr;
} 

void
show_addr()
{
    printf("\nheap_begin = %X\nheap_end = %X\n", heap_begin, heap_end);
}



