#ifndef MEMORY_H
#define MEMORY_H


#define MEM_SIZE 65535


#define SWRAM_START 0xa000
#define SWRAM_END 0xdfff

#define IRAM_START 0xc000
#define IRAM_END 0xdfff

#define HRAM_START 0xff80
#define HRAM_END 0xfffe

#define IU_ADDR 0xffff

#include <stdint.h>
#include <stdbool.h>

struct i_flags{
    bool vblank;
    bool lcd;
    bool time;
    bool serial;
    bool joypad;
};
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


/*
 * get the interrupt flags
 */
struct i_flags get_i_flags(uint8_t* memory);

#endif



