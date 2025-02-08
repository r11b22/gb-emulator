#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../cpu/registers.h"


int main()
{
    uint8_t* registers = reg_init();

    assert(registers != NULL);

    reg_store(6, 0, registers);
    assert(reg_load(0, registers) == 6);
    reg_store(38, 5, registers);
    assert(reg_load(5, registers) == 38);

    reg_store16(0xFDBC, 3, registers);
    assert(reg_load16(3, registers) == 0xFDBC);

    struct reg_flags flags = {0, 1, 1, 0};

    set_flags(flags, registers);

    struct reg_flags result_flags = get_flags(registers);

    assert(result_flags.zero == flags.zero);
    assert(result_flags.subtraction == flags.subtraction);
    assert(result_flags.half_carry == flags.half_carry);
    assert(result_flags.carry == flags.carry);




    set_zero(true, registers);
    set_subtract(false, registers);
    set_half_carry(false, registers);
    set_carry(true, registers);

    result_flags = get_flags(registers);

    assert(result_flags.zero == true);
    assert(result_flags.subtraction == false);
    assert(result_flags.half_carry == false);
    assert(result_flags.carry == true);

    free(registers);
}
