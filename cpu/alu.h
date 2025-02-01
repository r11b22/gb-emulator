#ifndef ALU_H
#define ALU_H


#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

/*
 * adds the values in register a and target into a
 * sets flags Z, N, H, C
 */
void add(size_t target, uint8_t* registers);

/*
 * adds the values in register a, target and the carry flag into a
 * sets flags Z, N, H, C
 */
void adc(size_t target, uint8_t* registers);


#endif
