#include <apostle.h>
#include <p_paging.h>
#include <stdint.h>
#include <panic.h>
#include <elf.h>

apostle_t apostles[APOSTLE_AMOUNT];
apostle_t *cur_apostle = NULL;

void
aps_init()
{
    uint32_t i;

    for (i = 0; i < APOSTLE_AMOUNT; ++i)
        memset(apostles + i, 0, sizeof(apostle_t));
}



apostle_t *
aps_get_by_id(aid_t id)
{
    uint32_t i;

    for (i = 0; i < APOSTLE_AMOUNT; ++i)
        if (apostles[i].apostle_id == id)
            return apostles + i;

    return NULL;
}

apostle_t *
aps_get_by_state(apostle_state_t state)
{
    uint32_t i;

    for (i = 0; i < APOSTLE_AMOUNT; ++i)
        if (apostles[i].state == state)
            return apostle + i;

    return NULL;
}
