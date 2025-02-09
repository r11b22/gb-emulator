#include "memory.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define IN_RANGE(x, upper, lower) (x <= upper && x >= lower)


/*
 * Initializes memory via malloc
 */
uint8_t* mem_init()
{
    uint8_t* memory = malloc(sizeof(uint8_t) * MEM_SIZE);

    if(memory == NULL)
    {
        perror("Could not create memory, returning NULL\n");
        return NULL;
    }
    return memory;
}


/*
 *
 */
void mem_store(uint8_t value, uint16_t address, uint8_t *memory)
{
    if(IN_RANGE(address, SWRAM_END, SWRAM_START) || IN_RANGE(address, IRAM_END, IRAM_START) || IN_RANGE(address, HRAM_END, HRAM_START))
    {
        memory[address] = value;
        #ifndef NDEBUG
            printf("Memory write:\n");
            if(address != 0x0)
            {
                printf("0x%x-0x%x\n", address-1, memory[address-1]);
            }
            printf("0x%x-0x%x\n", address, memory[address]);
            if (address != 0xffff)
            {
                printf("0x%x-0x%x\n", address+1, memory[address+1]);
            }
        #endif
    }else
    {
        printf("Memory write in a read only segment: address: 0x%x\n", address);
    }
}

/*
 *
 */
uint8_t mem_load(uint16_t address, uint8_t* memory)
{
    
    #ifndef NDEBUG
        printf("Memory read:\n");
        if(address != 0x0)
        {
            printf("0x%x-0x%x\n", address-1, memory[address-1]);
        }
        printf("0x%x-0x%x\n", address, memory[address]);
        if (address != 0xffff)
        {
            printf("0x%x-0x%x\n", address+1, memory[address+1]);
        }
    #endif
    return memory[address];
}

/*
 * the stack climbs down
 * this function increments the sp(until out of bounds)
 */
uint8_t stack_pop(uint16_t *stack_pointer, uint8_t *memory)
{
    uint8_t value = memory[*stack_pointer];
    if (*stack_pointer < MEM_SIZE)
    {
        (*stack_pointer)++;
    }
    return value;
}

/*
 * the stack climbs down
 * this function decrements the sp (until out of bounds)
 */
void stack_push(uint8_t value, uint16_t *stack_pointer, uint8_t *memory)
{
    // make space on stack
    if(*stack_pointer > 0)
    {
        (*stack_pointer)--;
    }

    // put value on stack
    memory[*stack_pointer] = value;
}


/*
 *
 */
struct i_flags get_i_flags(uint8_t *memory)
{
    bool vblank = memory[0xff0f] & 0b00000001;
    bool lcd = (memory[0xff0f] >> 1) & 0b00000001;
    bool time = (memory[0xff0f] >> 2) & 0b00000001;
    bool serial = (memory[0xff0f] >> 3) & 0b00000001;
    bool joypad = (memory[0xff0f] >> 4) & 0b00000001;

    struct i_flags flags = {vblank, lcd, time, serial, joypad};
    return flags;

}
