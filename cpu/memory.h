#ifndef MEMORY_H
#define MEMORY_H


#define MEM_SIZE 65535


#define IU_ADDR 0xffff

#include <stdint.h>

/*
 * initialize the memory
 * needs to be freed
 */
uint8_t* mem_init();

/*
 * store an 8 bit value to address in memory
 */
void mem_store(uint8_t value, uint16_t address, uint8_t* memory);

/*
 * gets the 8 bit value at address from memory
 */
uint8_t mem_load(uint16_t address, uint8_t* memory);

/*
 * pops a singel 8bit value from the stack
 */
uint8_t stack_pop(uint16_t* stack_pointer, uint8_t* memory);

/*
 * pushes a single 8bit value to the stack
 */
void stack_push(uint8_t value, uint16_t* stack_pointer, uint8_t* memory);
#endif



