#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"


void print_contents(FILE* file, unsigned int size)
{
    uint8_t* buffer = malloc(sizeof(uint8_t)*size);

    fread(buffer, sizeof(uint8_t), size, file);

    for (int i = 0; i < size; ++i)
    {
        printf("0x%02x ", buffer[i]);
    }
    printf("\n");
    free(buffer);
}


uint8_t read_byte(FILE* file)
{
    uint8_t byte;

    fread(&byte, sizeof(uint8_t), 1, file);

    return byte;
}

