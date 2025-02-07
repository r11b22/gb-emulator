#include "../libs/binary.h"
#include <assert.h>
#include <stdint.h>


void test_concat()
{
    uint16_t bytes = COMBINE_BYTES(0x0f, 0xce);
    assert(bytes == 0x0fce);
}

int main()
{
    test_concat();
}
