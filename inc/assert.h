#ifndef INC_ASSERT_H
#define INC_ASSERT_H

#include <stdint.h>
#include <stdbool.h>

void assert(const char *file, uint32_t line, bool expr);
void unreachable(const char *file, uint32_t line);

#endif
