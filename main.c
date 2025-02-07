#include <stdio.h>
#include "cpu/registers.h"
#include "cpu/translator.h"
#include "fileio.h"
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "cpu/memory.h"


#define LEN_2_OPCODES_LEN 4
#define LEN_3_OPCODES_LEN 0

size_t get_exectution_len(uint8_t opcode)
{
    uint8_t len_2_opcodes[LEN_2_OPCODES_LEN] = {0x20, 0x30, 0xf0, 0xe0};
    for (int i = 0; i < LEN_2_OPCODES_LEN; i++)
    {
        if (opcode == len_2_opcodes[i])
        {
            return 2;
        }
    }

    uint8_t len_3_opcodes[LEN_3_OPCODES_LEN] = {};
    for (int i = 0; i < LEN_3_OPCODES_LEN; i++)
    {
        if (opcode == len_3_opcodes[i])
        {
            return 3;
        }
    }

    return 1;
}



int main()
{

    char cwd[100];
    getcwd(cwd, sizeof(cwd));

    printf("Working directory is %s\n", cwd);
    FILE* file = fopen("../roms/Tetris/rom.gb", "rb");

    uint8_t* registers = reg_init();
    uint16_t program_counter = 0;
    uint8_t* memory = mem_init();

    while (!feof(file)) {
        uint8_t byte = read_byte(file, program_counter);
        if(get_exectution_len(byte) == 1)
        {
            //printf("test\n");
            exec_1(byte, registers, &program_counter);
        }else if(get_exectution_len(byte) == 2)
        {
            exec_2(byte, read_byte(file, program_counter + 1), registers, &program_counter, memory);
        }
        
        
    }

    fclose(file);

    free(memory);
    free(registers);

    return 0;
}

