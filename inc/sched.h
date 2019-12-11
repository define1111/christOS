#ifndef INC_SCHED_H
#define INC_SCHED_H

#include <stdint.h>
#include <apostle.h>

void sched_init(void);
void sched_schedule(void);
void sched_yield(void);

#endif
