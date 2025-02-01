#ifndef REGISTERS_H
#define REGISTERS_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define REG_AMOUNT 8




struct reg_flags{
    bool zero;
    bool subtraction;
    bool half_carry;
    bool carry;
};




/*
 * intitializes the register array and returns its pointer
 * doesn't set registers to any values
 * (needs free)
 */
uint8_t* reg_init();


/*
 * sets the flags in flag register f (zshc0000)
 */
void set_flags(struct reg_flags flags, uint8_t* registers);


/*
 * sets the zero flag 
 */
void set_zero(bool flag, uint8_t* registers);

/*
 * sets the zero flag 
 */
void set_subtract(bool flag, uint8_t* registers);

/*
 * sets the zero flag 
 */
void set_half_carry(bool flag, uint8_t* registers);

/*
 * sets the zero flag 
 */
void set_carry(bool flag, uint8_t* registers);

/*
 * gets the flags in flag register f (zshc0000)
 */
struct reg_flags get_flags(uint8_t* registers);

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
