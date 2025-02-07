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
