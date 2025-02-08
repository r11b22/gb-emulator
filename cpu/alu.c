#include "alu.h"
#include "registers.h"
#include <stdint.h>
#include <stdbool.h>
/*
 * uses a 16 bit value to store the result and casts it to an 8bit value when storing
 * the 16 bit value is used to get the carry flag
 */
void add(size_t target, uint8_t *registers)
{
    // calculate the sum and save it in a buffer with 16 bits instead of 8
    uint16_t result = registers[0] + registers[target];


    // set all of the flags
    struct reg_flags flags = {result == 0, false, result > 0xf, result > 0xff};
    
    set_flags(flags, registers);

    reg_store((uint8_t)result, 0, registers);   
}

/*
 * same details as add(size_t target, uint8_t* registers)
 */
void adc(size_t target, uint8_t *registers)
{
    // calculate the sum and save it in a buffer with 16 bits instead of 8
    uint16_t result = registers[0] + registers[target];

    if(get_flags(registers).carry)
    {
        ++result;
    }

    // set all of the flags
    struct reg_flags flags = {result == 0, false, result > 0xf, result > 0xff};
    
    set_flags(flags, registers);

    reg_store((uint8_t)result, 0, registers);   
}

void sub(size_t target, uint8_t *registers)
{
    uint16_t result = registers[0] + ((uint8_t)(-registers[target]));
    
    // set all of the flags
    struct reg_flags flags = {result == 0, false, result > 0xf, result > 0xff};
    
    set_flags(flags, registers);

    reg_store((uint8_t)result, 0, registers);
}
