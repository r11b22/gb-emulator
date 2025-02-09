#ifndef H_INTERRUPT
#define H_INTERRUPT

#include <stdint.h>
#include <stdbool.h>
enum interrupts{
    VBLANK,
    LCD
};

#define VBLANK_LOC 0x0040
#define LCD_LOC 0x0048

/*
 * Enter an interrupt
 */
void enter_interrupt(enum interrupts intr_type, bool* IME, uint16_t* program_counter, uint16_t* stack_pointer, uint8_t* memory);

/*
 * Exit the current interrupt
 */
void exit_interrupt(bool* IME, uint16_t* program_counter, uint16_t* stack_pointer, uint8_t* memory);




#endif
