#include "registers.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BOOL_TO_INT(x) ((x) == true ? 1 : 0)
#define INT_TO_BOOL(x) ((x) == 1)

/*
 * the gameboy has the following registers:
 * a
 * b
 * c
 * d
 * e
 * f
 * g
 * h
 * l
 *
 * can be combined to save 16 bit values in
 * af
 * bc
 * de
 * hl
 */


/*
 * allocates registers via malloc
 * prints a warning if the register allocation fails
 */
uint8_t* reg_init()
{
    uint8_t* reg_list = malloc(sizeof(uint8_t) * REG_AMOUNT);

    if (reg_list == NULL)
    {
        printf("The register list could not be allocated\n");
    }
    
    return reg_list;
}


/*
 * flags are stored in the upper 4 bits of register f
 */
void set_flags(struct reg_flags flags, uint8_t *registers)
{
    // calculate flag values individually
    uint8_t zero = (BOOL_TO_INT(flags.zero) << 7) & 0b10000000;
    uint8_t subtraction = (BOOL_TO_INT(flags.subtraction) << 6) & 0b01000000;
    uint8_t half_carry = (BOOL_TO_INT(flags.half_carry) << 5) & 0b00100000;
    uint8_t carry = (BOOL_TO_INT(flags.carry) << 4) & 0b00010000;

    // combine all flags
    uint8_t value = zero | subtraction | half_carry | carry;
    reg_store(value, 5, registers);
}

void set_zero(bool flag, uint8_t* registers)
{
    uint8_t flags = registers[5];

    uint8_t zero = (BOOL_TO_INT(flag) << 7) & 0b10000000;

    // put the zero bit to 0 so we can overwrite it
    flags &= 0b01110000;

    // set the zero bit
    flags |= zero;

    reg_store(flags, 5, registers);
}


void set_subtract(bool flag, uint8_t* registers)
{
    uint8_t flags = registers[5];
 
    uint8_t subtract = (BOOL_TO_INT(flag) << 6) & 0b01000000;

    // put the zero bit to 0 so we can overwrite it
    flags &= 0b10110000;

    // set the zero bit
    flags |= subtract;

    reg_store(flags, 5, registers);
}


void set_half_carry(bool flag, uint8_t* registers)
{
    uint8_t flags = registers[5];
 
    uint8_t half_carry = (BOOL_TO_INT(flag) << 5) & 0b00100000;

    // put the zero bit to 0 so we can overwrite it
    flags &= 0b11010000;

    // set the zero bit
    flags |= half_carry;

    reg_store(flags, 5, registers);
}



void set_carry(bool flag, uint8_t* registers)
{
    uint8_t flags = registers[5];

    uint8_t carry = (BOOL_TO_INT(flag) << 4) & 0b00010000;

    // put the zero bit to 0 so we can overwrite it
    flags &= 0b11100000;

    // set the zero bit
    flags |= carry;

    reg_store(flags, 5, registers);
}

/*
 *
 */
struct reg_flags get_flags(uint8_t *registers)
{
    uint8_t value = reg_load(5, registers);

    struct reg_flags flags = {false, false, false, false};

    flags.zero = INT_TO_BOOL((value >> 7) &0x1);
    flags.subtraction = INT_TO_BOOL((value >> 6) & 0x1);
    flags.half_carry = INT_TO_BOOL((value >> 5) & 0x1);
    flags.carry = INT_TO_BOOL((value >> 4) & 0x1);

    return flags;
}

/*
 *
 */
uint8_t reg_load(size_t reg_ind, uint8_t* registers)
{
    if (reg_ind >= REG_AMOUNT)
    {printf("reg_ind: %zd, is not a valid register.\n", reg_ind);}
    return registers[reg_ind];
}



/* 
 * registers are combined for 16 bit storage in the follwing way
 * "af" ("a" and "f" combined), 
 * "bc" ("b" and "c" combined), 
 * "de" ("d" and "e" combinded), 
 * "hl" ("h" and "l" combined),
 *
 * these pairs are hardcoded for now
 * TODO: find a faster way to map this
 */
uint16_t reg_load16(size_t reg_ind, uint8_t *registers)
{

    if (reg_ind >= 4)
    {printf("reg_ind: %zd, is not a valid 16 bit register address.\n", reg_ind);}

    uint8_t reg1;
    uint8_t reg2;

    switch (reg_ind) {
        case 0:
            reg1 = registers[0];
            reg2 = registers[5];
            break;
        case 1:
            reg1 = registers[1];
            reg2 = registers[2];
            break;
        case 2:
            reg1 = registers[3];
            reg2 = registers[4];
            break;
        case 3:
            reg1 = registers[6];
            reg2 = registers[7];
            break;
    }
    // convert both registers to 16 bits
    uint16_t value1 = (uint16_t) reg1;
    uint16_t value2 = (uint16_t) ((reg2 << 8) & 0xff00);

    // combine the values and return
    return value1 | value2;
}

/*
 * 
 */
void reg_store(uint8_t value, size_t reg_ind, uint8_t *registers)
{
   registers[reg_ind] = value; 
}

/* 
 * registers are combined for 16 bit storage in the follwing way
 * "af" ("a" and "f" combined), 
 * "bc" ("b" and "c" combined), 
 * "de" ("d" and "e" combinded), 
 * "hl" ("h" and "l" combined),
 *
 * these pairs are hardcoded for now
 * TODO: find a faster way to map this
 */
void reg_store16(uint16_t value, size_t reg_ind, uint8_t *registers)
{
    if (reg_ind >= 4)
    {printf("reg_ind: %zd, is not a valid 16 bit register address.\n", reg_ind);}


    uint8_t reg1 = (uint8_t)(value & 0xff); // get the first 8 bits
    uint8_t reg2 = (uint8_t)(value >> 8) & 0xff; // get the last 8 bits
    
    switch (reg_ind) {
    case 0:
        registers[0] = reg1;
        registers[5] = reg2;
        break;
    case 1:
        registers[1] = reg1;
        registers[2] = reg2;
        break;
    case 2:
        registers[3] = reg1;
        registers[4] = reg2;
        break;
    case 3:
        registers[6] = reg1;
        registers[7] = reg2;
        break;
    }
}
