#ifndef CU_H
#define CU_H

#include <stdint.h>


/*
 * increments the porgramm counter
 */
void inc(uint16_t* program_counter);

/*
 * icnrements the programm counter with offset
 */
void jmp(uint16_t* program_counter, uint16_t offset);

#endif
