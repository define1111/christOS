#ifndef INC_APOSTLE_H
#define INC_APOSTLE_H

#include <stdint.h>
#include <reg.h>

#define APOSTLE_AMOUNT 12

typedef uint32_t aid_t;

struct apostle_memory_t
{
    void *page_entry;
    uint32_t pages_count;
};

typedef struct apostle_memory_t apostle_memory_t;

enum apostle_state_t
{
    APS_FREE = 0,
    APS_DYING,
    APS_RUNNABLE,
    APS_RUNNING,
    APS_NOT_RUNNABLE
};

typedef enum apostle_state_t apostle_state_t;

enum apostle_type_t
{
    APS_TYPE_IDLE = 0,
    APS_TYPE_KERNEL,
    APS_TYPE_USER
};

typedef enum apostle_type_t apostle_type_t;

struct apostle_t
{
    ait_t apostle_id;
    ait_t apostle_parent_id;
    char apostle_name[16];
    gp_registers_t gp_registers;
    op_registers_t op_registers;
    flags_t flags;
    uint32_t runs;
    apostle_state_t state;
    apostle_type_t type;
    apostle_memory_t memory;
};

typedef struct apostle_t apostle_t;

#endif
