#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <stdint.h>

/*
 * executes all instructions with a length of 1 byte
 */

void exec_1(uint8_t opcode, uint8_t* registers, uint16_t* program_counter, uint16_t* stack_pointer, uint8_t* memory);

/*
 * executes all instructions with a length of 2 bytes
 */
void exec_2(uint8_t opcode, uint8_t param, uint8_t* registers, uint16_t* program_counter, uint8_t* memory);

/*
 * executes all instructions with a length of 3 bytes
 */
void exec_3(uint8_t opcode, uint8_t param1, uint8_t param2, uint8_t* registers, uint16_t* program_counter, uint16_t *stack_pointer, uint8_t* memory);
#endif
