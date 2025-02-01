#include "../alu.h"
#include "../registers.h"
#include <assert.h>
#include <stdbool.h>

void test_add()
{
    uint8_t* registers = reg_init();

    // set register a
    reg_store(15, 0, registers);

    // set traget register
    reg_store(36, 3, registers);

    // performare add
    add(3, registers);

    assert(reg_load(0, registers) == 51);
    struct reg_flags flags = get_flags(registers);

    assert(flags.zero == false);
    assert(flags.subraction == false);
    assert(flags.half_carry == true);
    assert(flags.carry == false);
}



int main()
{

}
