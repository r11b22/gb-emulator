#include <stdint.h>
#include "cu.h"


/*
 *
 */
void inc(uint16_t *program_counter)
{
    *program_counter += 1;
}

/*
 *
 */
void jmp(uint16_t* program_counter, uint16_t offset)
{
    *program_counter += offset;
}
