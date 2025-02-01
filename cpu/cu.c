#include <stdint.h>
#include "cu.h"


/*
 *
 */
void inc(uint16_t *programm_counter)
{
    *programm_counter += 1;
}

/*
 *
 */
void jmp(uint16_t* programm_counter, uint16_t offset)
{
    *programm_counter += offset;
}
