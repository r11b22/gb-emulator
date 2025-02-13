#include <bits/time.h>
#include <stddef.h>
#include <stdio.h>
#include "cpu/registers.h"
#include "cpu/translator.h"
#include "fileio.h"
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "cpu/memory.h"
#include "cpu/interrupt.h"


//#define STEPWISE 0x214 

#define LEN_2_OPCODES_LEN 16
#define LEN_3_OPCODES_LEN 8

#define FRAME_RATE 60.0

size_t get_exectution_len(uint8_t opcode)
{
    uint8_t len_2_opcodes[LEN_2_OPCODES_LEN] = {0x18, 0x20, 0x30, 0x28, 0x38, 0xf0, 0xe0, 0x06, 0x0e, 0x16, 0x1e, 0x26, 0x2e, 0x36, 0x3e, 0xfe};
    for (int i = 0; i < LEN_2_OPCODES_LEN; i++)
    {
        if (opcode == len_2_opcodes[i])
        {
            return 2;
        }
    }

    uint8_t len_3_opcodes[LEN_3_OPCODES_LEN] = {0xc2, 0xd2, 0xc3, 0x01, 0x11, 0x21, 0x08, 0x31};
    for (int i = 0; i < LEN_3_OPCODES_LEN; i++)
    {
        if (opcode == len_3_opcodes[i])
        {
            return 3;
        }
    }

    return 1;
}

void vblank_check(const double s_per_frame, struct timespec *last_time, struct timespec *current_time, uint16_t *program_counter, uint16_t *stack_pointer, uint8_t *memory)
{
    clock_gettime(CLOCK_MONOTONIC, current_time);

    // calculate elapes time in seconds
    double elapsed_time = (current_time->tv_sec - last_time->tv_sec) + ((current_time->tv_nsec - last_time->tv_nsec)/1e9);

    if(elapsed_time >= s_per_frame)
    {
        #ifdef STEPWISE
        getchar();
        #endif
        // set vblank in IF
        memory[0xff0f] = (memory[0xff0f] & 0b11111110) | 1;
        *last_time = *current_time;
    }
}




void execute_interrupts(bool *IME, uint16_t *program_counter, uint16_t *stack_pointer, uint8_t *memory)
{
    if(*IME)
    {
        struct i_flags flags = get_i_flags(memory);
        if(flags.vblank)
        {
            enter_interrupt(VBLANK, IME, program_counter, stack_pointer, memory);
        }
    }
}

int main(int argc, char** argv)
{
    const double s_per_frame = 1.0/FRAME_RATE;

    char cwd[100];
    getcwd(cwd, sizeof(cwd));

    printf("Working directory is %s\n", cwd);
    const char* path = "roms/Pokemon/rom.gb";
    if(argc > 1)
    {
        path = argv[1];
    }
    FILE* file = fopen(path, "rb");

    uint8_t* registers = reg_init();
    uint16_t program_counter = 0x100;
    uint16_t stack_pointer = 0xfffe;
    uint8_t* memory = mem_init();
    bool IME = true;

    read_file_to_mem(file, memory);
    #ifdef STEPWISE
    bool breaked = false;
    #endif

    struct timespec last_time, current_time;
    clock_gettime(CLOCK_MONOTONIC, &last_time);

    #ifdef STEPWISE
    if(program_counter == STEPWISE)
    {
        breaked = true;
    }
    #endif

    // loop until 0x10 (stop)
    while (memory[program_counter] != 0x10 && file != NULL) {
        


        uint8_t byte = memory[program_counter];
        #ifdef STEPWISE
        if(breaked)
        {

            printf("executing instruction: 0x%x, 0x%x, 0x%x at: 0x%x\n", byte, memory[program_counter + 1], memory[program_counter + 2], program_counter);




            // wait for confirmation
            getchar();
        }else if(program_counter == STEPWISE)
        {
            breaked = true;
        }
        #endif



        size_t len = get_exectution_len(byte);    
        if(len == 1)
        {
            //printf("test\n");
            exec_1(byte, registers, &program_counter, &stack_pointer, memory, &IME);
        }else if(len == 2)
        {
            exec_2(byte, memory[program_counter + 1], registers, &program_counter, memory);
        }else if (len == 3) 
        {
            exec_3(byte, memory[program_counter + 1], memory[program_counter + 2], registers, &program_counter, &stack_pointer, memory);
        }
        
        #ifdef STEPWISE
        if(breaked)
        {
        // print registers
        printf("REGISTERS:\n");
        printf("\treg a: 0x%x\n", registers[0]);
        printf("\treg b: 0x%x\n", registers[1]);
        printf("\treg c: 0x%x\n", registers[2]);
        printf("\treg d: 0x%x\n", registers[3]);
        printf("\treg e: 0x%x\n", registers[4]);
        printf("\treg f: 0x%x\n", registers[5]);
        printf("\treg h: 0x%x\n", registers[6]);
        printf("\treg l: 0x%x\n", registers[7]);
        printf("\tStack pointer: 0x%x\n", stack_pointer);
        }
        #endif

        /*handle interrupts*/
        vblank_check(s_per_frame, &last_time, &current_time, &program_counter, &stack_pointer, memory);
        execute_interrupts(&IME, &program_counter, &stack_pointer, memory);
    }
    if(file != NULL)
    {
        fclose(file);
    }

    free(memory);
    free(registers);

    return 0;
}

