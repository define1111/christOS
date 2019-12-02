#include <heap.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

extern size_t real_end[];

static size_t *heap_begin;
static size_t *heap_end;
static size_t heap_page_size;
static size_t heap_page_amount;

static uint32_t bit_map[HEAP_PAGE_AMOUNT / (8 * sizeof(uint32_t))];

static bool is_free(uint32_t i);
static bool check_bit(uint32_t values, uint32_t position);
static void set_up_bit(uint32_t i);

void
heap_init()
{
    heap_begin = (size_t*) real_end;
    heap_page_size = HEAP_PAGE_SIZE;
    heap_page_amount = HEAP_PAGE_AMOUNT;
    heap_end = heap_begin + (heap_page_size * heap_page_amount) / sizeof(size_t);

    memset(bit_map, 0, heap_page_amount / 8);
}

void *
malloc(size_t size)
{
    uint32_t pages; 
    uint32_t i, j;
    size_t *addr = NULL;

    if (size == 0) return NULL;

    pages = (size / heap_page_size) + 1;

    for (i = 0; i < heap_page_amount; i++)
        if (is_free(i)) break;

    addr = heap_begin + (i * heap_page_size) / sizeof(size_t);

    for (j = 0; j < pages; i++, j++)
        set_up_bit(i);

    return (void*) addr;
} 

void
heap_show_addr()
{
    printf("\nheap_begin = %X\nheap_end = %X\n", heap_begin, heap_end);
}

void
heap_show_bit_map()
{
    uint32_t i;

    for (i = 0; i < HEAP_PAGE_AMOUNT; ++i)
        printf("%u", is_free(i));
    printf("\n");
}       
static bool
is_free(uint32_t i)
{
    uint32_t bit_map_index = i / (8 * sizeof(uint32_t));
    uint32_t bit_map_offset = i % (8 * sizeof(uint32_t));

    return check_bit(bit_map[bit_map_index], bit_map_offset);
}

static bool 
check_bit(uint32_t value, uint32_t position)
{
    const uint32_t one_32bit = 1 << 31;
    return !(value & (one_32bit >> position));
}

static void
set_up_bit(uint32_t i)
{ 
    uint32_t bit_map_index = i / (8 * sizeof(uint32_t));
    uint32_t bit_map_offset = i % (8 * sizeof(uint32_t));
    const uint32_t one_32bit = 1 << 31;

    bit_map[bit_map_index] |= one_32bit >> bit_map_offset;
}
