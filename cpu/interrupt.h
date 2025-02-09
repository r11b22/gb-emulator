#ifndef H_INTERRUPT
#define H_INTERRUPT

#include <stdint.h>
enum interrupts{
    VBLANK
};

#define VBLANK_LOC 0x0040

/*
 * Enter an interrupt
 */
void enter_interrupt(enum interrupts intr_type, uint16_t* program_counter, uint16_t* stack_pointer, uint8_t* memory);

/*
 * Exit the current interrupt
 */
void exit_interrupt(uint16_t* program_counter, uint16_t* stack_pointer, uint8_t* memory);




#endif
