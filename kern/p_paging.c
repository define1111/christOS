#include <p_paging.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <panic.h>

extern size_t real_end[];

static size_t *pa_begin;
static size_t *pa_end;
static size_t page_size;
static size_t page_amount;

static uint32_t bit_map[PHYS_PAGE_AMOUNT / (8 * sizeof(uint32_t))];

static bool is_free(uint32_t i);
static bool is_free_diap(uint32_t begin, uint32_t end);
static bool check_bit(uint32_t values, uint32_t position);
static void set_up_bit(uint32_t i);
static void set_down_bit(uint32_t i);

void
p_paging_init()
{
    pa_begin = (size_t*) real_end;
    page_size = PHYS_PAGE_SIZE;
    page_amount = PHYS_PAGE_AMOUNT;
    pa_end = pa_begin + (page_size * page_amount) / sizeof(size_t);

    memset(bit_map, 0, page_amount / 8);
}

void *
get_phys_page(size_t size)
{
    uint32_t pages; 
    uint32_t i, j;
    size_t *addr = NULL;
    bool flag = false;

    if (size == 0) return NULL;

    pages = (size / page_size) + 1;

    for (i = 0; i < page_amount; i++)
        if (is_free_diap(i, i + pages))
        {
            flag = true;        
            break;
        }

    if (!flag) return NULL;

    addr = pa_begin + (i * page_size) / sizeof(size_t);

    for (j = 0; j < pages; i++, j++)
        set_up_bit(i);

    return (void*) addr;
} 

void
free_phys_page(void *addr, size_t size)
{
    size_t *a = (size_t*) addr;
    uint32_t i, j;
    uint32_t pages;

    if (a < pa_begin || a > pa_end)
        panic("can't free pointer from no-heap space\n");

    pages = (size / page_size) + 1;

    for (i = 0; i < page_amount; ++i)
        if (a == pa_begin + (i * page_size) / sizeof(size_t)) break;
    
    for (j = 0; j < pages; i++, j++)
        set_down_bit(i);
}

void
p_show_addr()
{
    printf("\npa_begin = %X\npa_end = %X\n", pa_begin, pa_end);
}

void
p_show_bit_map()
{
    uint32_t i;

    for (i = 0; i < page_amount; ++i)
        printf("%u", is_free(i));
    printf("\n");
}       

static bool
is_free_diap(uint32_t begin, uint32_t end)
{
    uint32_t i;
    bool flag = true;

    for (i = begin; i <= end; ++i)
        if (!is_free(i))
        {
            flag = false;
            break;
        }

    return flag;
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

static void
set_down_bit(uint32_t i)
{
    uint32_t bit_map_index = i / (8 * sizeof(uint32_t));
    uint32_t bit_map_offset = i % (8 * sizeof(uint32_t));
    const uint32_t one_32bit = 1 << 31;

    bit_map[bit_map_index] ^= one_32bit >> bit_map_offset;
}
