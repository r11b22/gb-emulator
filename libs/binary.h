#ifndef BINARY_H
#define BINARY_H

#include <stdint.h>

#define COMBINE_BYTES(hi, lo) (((uint16_t)lo) & 0x00ff) | ((((uint16_t)hi ) << 8) & 0xff00)
#define GET_END_BIT(x) (x >> 7) & 1
#define GET_START_BIT(x) x & 1
/*
 * calculates the lo half of 2 bytes (little endian)
 */
#define LO_HALF(x) ((uint8_t)((x) & 0x00ff))
/*
 * calculates the hi half of 2 bytes (little endian)
 */
#define HI_HALF(x) ((uint8_t)(((x) >> 8) & 0xff00))

#endif
