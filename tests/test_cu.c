#include "../cpu/cu.h"
#include <assert.h>
#include <stdint.h>


void test_inc()
{
    uint16_t pc = 0;
    inc(&pc);
    assert(pc == 1);
}

void test_jmp()
{
    uint16_t pc = 0;
    jmp(&pc, 25);
    assert(pc == 25);
}

int main()
{
    test_inc();
}
