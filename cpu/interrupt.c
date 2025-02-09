#include "interrupt.h"
#include "memory.h"
#include "../libs/binary.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


/*
 * stack pointer gets pushed in the following order
 * lo, hi
 */
void enter_interrupt(enum interrupts intr_type, bool* IME, uint16_t *program_counter, uint16_t *stack_pointer, uint8_t *memory)
{
    if(intr_type == VBLANK)
    {
        // check for vblank enabled
        if((memory[0xffff] & 0b00000001) == 0x1)
        {   
            #ifndef NDEBUG
            printf("vblank enabled\n");
            #endif
            *IME = false;
            // push cpu state to the stack
            stack_push(LO_HALF((*program_counter) + 1), stack_pointer, memory);
            stack_push(HI_HALF((*program_counter) + 1), stack_pointer, memory);
            // set pc
            *program_counter = VBLANK_LOC;
        }

        
    }else if(intr_type == LCD)
    {
        //chekc for lcd enabled
        if(((memory[0xffff] >> 1) & 0b00000001) == 0x1)
        {
            *IME = false;

            // push cpu state to the stack
            stack_push(LO_HALF((*program_counter) + 1), stack_pointer, memory);
            stack_push(HI_HALF((*program_counter) + 1), stack_pointer, memory);
            // set pc
            *program_counter = LCD_LOC;


        }
    }
}


/*
 * stack pointer gets poped in the following order
 * hi, lo
 */
void exit_interrupt(bool* IME, uint16_t *program_counter, uint16_t *stack_pointer, uint8_t *memory)
{
    uint8_t hi = stack_pop(stack_pointer, memory);
    uint8_t lo = stack_pop(stack_pointer, memory);
    *stack_pointer = COMBINE_BYTES(hi, lo);
    *IME = true;
}
