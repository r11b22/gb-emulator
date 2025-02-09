#include "interrupt.h"
#include "memory.h"
#include "../libs/binary.h"
#include <stdint.h>


/*
 * stack pointer gets pushed in the following order
 * lo, hi
 */
void enter_interrupt(enum interrupts intr_type, uint16_t *program_counter, uint16_t *stack_pointer, uint8_t *memory)
{
    if(intr_type == VBLANK)
    {
        // push cpu state to the stack
        stack_push(LO_HALF(*program_counter), stack_pointer, memory);
        stack_push(HI_HALF(*program_counter), stack_pointer, memory);
        *program_counter = VBLANK_LOC;
    }
}


/*
 * stack pointer gets poped in the following order
 * hi, lo
 */
void exit_interrupt(uint16_t *program_counter, uint16_t *stack_pointer, uint8_t *memory)
{
    uint8_t hi = stack_pop(stack_pointer, memory);
    uint8_t lo = stack_pop(stack_pointer, memory);
    *stack_pointer = COMBINE_BYTES(hi, lo);
}
