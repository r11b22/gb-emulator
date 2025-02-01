#include <stdio.h>
#include "registers.h"
#include <stdint.h>

int main()
{
    uint8_t* reg_list = reg_init();

    if (reg_list == NULL)
    {return -1;}


    reg_store(15, 5, reg_list);

    uint8_t value = reg_load(5, reg_list);

    printf("%d\n", value);

    return 0;
}

