#include <assert.h>
#include <stdlib.h>
#include "../registers.h"


int main()
{
    uint8_t* registers = reg_init();

    assert(registers != NULL);

    reg_store(6, 0, registers);
    assert(reg_load(0, registers) == 6);

    reg_store16(1256, 3, registers);
    assert(reg_load16(3, registers) == 1256);




    free(registers);
}
