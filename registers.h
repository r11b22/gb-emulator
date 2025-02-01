#ifndef REGISTERS_H
#define REGISTERS_H

#include <stddef.h>
#include <stdint.h>

#define REG_AMOUNT 8

/*
 * intitializes the register array and returns its pointer
 * doesn't set registers to any values
 * (needs free)
 */
uint8_t* reg_init();

/*
 * gets the current value in the given register
 */
uint8_t reg_load(size_t reg_ind, uint8_t* registers);

/*
 * loades a 16 bit value value from the registers only half the indecies are supported (uses 2 registers for each value)
 */
uint16_t reg_load16(size_t reg_ind, uint8_t* registers);

/*
 * stores value in the given register
 */
void reg_store(uint8_t value, size_t reg_ind, uint8_t* registers);

/*
 * stores a 16 bit value in the registers only half the indecies are supported(uses 2 registers per value)
 */
void reg_store16(uint16_t value, size_t reg_ind, uint8_t* registers);


#endif
