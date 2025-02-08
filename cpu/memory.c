#include "memory.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


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
    memory[address] = value;
}

/*
 *
 */
uint8_t mem_load(uint16_t address, uint8_t* memory)
{
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
