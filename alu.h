#ifndef ALU_H
#define ALU_H


#include <stdio.h>
#include <stdint.h>

/*
 * adds the values in register a and target into a
 * sets flags Z, C
 */
void add(size_t target, uint8_t* registers);


#endif
