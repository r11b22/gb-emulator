#include "../cpu/translator.h"
#include "../cpu/registers.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define LD_TESTS 3 

void test_ld()
{
    uint16_t pc = 0;
    uint8_t* registers = reg_init();

    uint8_t instructions[LD_TESTS] = {0x40, 0x53, 0x6b};
    uint8_t dest_registers[LD_TESTS] = {1, 3, 7};
    uint8_t source_registers[LD_TESTS] = {1, 4, 4};

    for(int i = 0; i < LD_TESTS; i++)
    {
        // put i in register the source_registers
        reg_store(i, source_registers[i], registers);

        // execute the instruction
        exec_1(instructions[i], registers, &pc);


        // test pc
        assert(pc == i+1);

        // test the dest_registers
        assert(reg_load(dest_registers[i], registers) == i);
    }
}

int main()
{
    test_ld();
}
