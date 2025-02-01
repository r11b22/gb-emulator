#include "../cpu/alu.h"
#include "../cpu/registers.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

void test_add()
{
    uint8_t* registers = reg_init();

    
    /* Test simple addidtion
     */
    // set register a
    reg_store(15, 0, registers);

    // set traget register
    reg_store(36, 3, registers);

    // performare add
    add(3, registers);

    assert(reg_load(0, registers) == 51);
    struct reg_flags flags = get_flags(registers);

    assert(flags.zero == false);
    assert(flags.subtraction == false);
    assert(flags.half_carry == true);
    assert(flags.carry == false);

    /* test overflow
     */
    // put 0xff in a
    reg_store(255, 0, registers);

    // put 3 in register c
    reg_store(3, 2, registers);


    // add a and c
    add(2, registers);


    // test result
    assert(reg_load(0, registers) == 2);

    // test flags
    flags = get_flags(registers);

    assert(flags.zero == false);
    assert(flags.subtraction == false);
    assert(flags.half_carry == true);
    assert(flags.carry == true);

    /* test 0
     */
    // store 0 in reg a
    reg_store(0, 0, registers);

    // store 0 in reg d
    reg_store(0, 3, registers);

    // add a and d
    add(3, registers);

    //test result
    assert(reg_load(0, registers) == 0);

    // test flags
    flags = get_flags(registers);

    assert(flags.zero == true);
    assert(flags.subtraction == false);
    assert(flags.half_carry == false);
    assert(flags.carry == false);

    free(registers);
}



int main()
{
    test_add();
}
