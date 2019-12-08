#ifndef INC_STDDEF_H
#define INC_STDDEF_H

#define HIGH_WORD(addr) ((addr & 0xffff0000) >> 16)
#define LOW_WORD(addr) ((addr & 0xffff))
#define LOW_BYTE(addr) ((addr & 0x00ff))
#define HIGH_BYTE(addr) ((addr & 0xff00) >> 8)

#define attribute(value) __attribute__((value))

#endif
