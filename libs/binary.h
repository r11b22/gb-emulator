#ifndef BINARY_H
#define BINARY_H

#include <stdint.h>

#define COMBINE_BYTES(hi, lo) (((uint16_t)lo) & 0x00ff) | ((((uint16_t)hi ) << 8) & 0xff00)
#define GET_END_BIT(x) (x >> 7) & 1
#define GET_START_BIT(x) x & 1

#endif
