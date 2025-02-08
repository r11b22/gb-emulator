#include <stddef.h>
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

void read_file_to_mem(FILE* file, uint8_t* memory)
{
    if(file == NULL)
    {
        fprintf(stderr, "Error: File pointer is NULL\n");
        return;
    }
    // get filesize
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    fread(memory, sizeof(uint8_t), size, file);
}



uint8_t read_byte(FILE* file, uint16_t program_counter)
{
    uint8_t byte;

    fseek(file, program_counter, SEEK_SET);
    fread(&byte, sizeof(uint8_t), 1, file);

    return byte;
}

