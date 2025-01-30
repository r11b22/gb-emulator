#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"


void print_contents(FILE* file, unsigned int size)
{
    INSTRUCTION* buffer = malloc(INS_SIZE*size);

    fread(buffer, INS_SIZE, size, file);

    for (int i = 0; i < size; ++i)
    {
        printf("0x%02x ", buffer[i]);
    }
    printf("\n");
    free(buffer);
}

