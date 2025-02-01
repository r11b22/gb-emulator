#include "alu.h"
#include "registers.h"
#include <stdint.h>

/*
 * 
 */
void add(size_t target, uint8_t *registers)
{
    // calculate the sum and save it in a buffer with 16 bist instead of 8
    uint16_t result = registers[0] + registers[target];


    // set all of the flags
    struct reg_flags flags = {result == 0, false, result > 0xff, result > 0xffff};
    
    set_flags(flags, registers);



    reg_store((uint8_t)result, 0, registers);   
}
