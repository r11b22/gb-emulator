#include "registers.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>



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
