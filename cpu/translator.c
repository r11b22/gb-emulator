#include "translator.h"
#include "memory.h"
#include "registers.h"
#include "cu.h"
#include "alu.h"
#include "../libs/binary.h"
#include <stddef.h>
#include <stdint.h>

/*returns true if x is in [lower, upper]*/
#define IN_RANGE(x, lower, upper) x <= upper && x >= lower


void exec_1(uint8_t opcode, uint8_t *registers, uint16_t *program_counter)
{
    size_t LD_REG_TRANSLATION[6] = {1, 2, 3, 4, 6, 7};


    if(opcode == 0x00) // NOP
    {
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x40, 0x45)) // LD B, reg
    {
        uint8_t value = reg_load(LD_REG_TRANSLATION[opcode-0x40], registers);
        reg_store(value, 1, registers);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x50, 0x55)) // LD D, reg
    {
        uint8_t value = reg_load(LD_REG_TRANSLATION[opcode-0x50], registers);
        reg_store(value, 3, registers);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x60, 0x65)) // LD H, reg
    {
        uint8_t value = reg_load(LD_REG_TRANSLATION[opcode-0x60], registers);
        reg_store(value, 6, registers);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x48, 0x4d)) // LD C, reg
    {
        uint8_t value = reg_load(LD_REG_TRANSLATION[opcode-0x48], registers);
        reg_store(value, 2, registers);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x58, 0x5d)) // LD E, reg
    {
        uint8_t value = reg_load(LD_REG_TRANSLATION[opcode-0x58], registers);
        reg_store(value, 4, registers);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x68, 0x6d)) // LD L, reg
    {
        uint8_t value = reg_load(LD_REG_TRANSLATION[opcode-0x68], registers);
        reg_store(value, 7, registers);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x78, 0x7d)) // LD A, reg
    {
        uint8_t value = reg_load(LD_REG_TRANSLATION[opcode-0x78], registers);
        reg_store(value, 0, registers);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x70, 0x75)) // LD HL, reg
    {
        uint8_t value = reg_load(LD_REG_TRANSLATION[opcode-0x70], registers);
        reg_store16(value, 3, registers);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x80, 0x85)) // ADD A, reg
    {
        add(LD_REG_TRANSLATION[opcode-0x80], registers);

        // after instruction execution increment program counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x88, 0x8d)) // adc A, reg
    {
        adc(LD_REG_TRANSLATION[opcode-0x88], registers);

        // after instruction execution increment program counter
        inc(program_counter);
    }else if (IN_RANGE(opcode, 0xb8, 0xbd)) // CP reg
    {
        uint8_t value_a = reg_load(0, registers);
        uint8_t value_reg = reg_load(LD_REG_TRANSLATION[opcode-0xb8], registers);
        int16_t diff = value_a - value_reg;

        struct reg_flags flags = {diff == 0, true, !(IN_RANGE(diff, 0, 0xf)), diff < 0};
        set_flags(flags, registers);

        // go to next instruction
        inc(program_counter);

    }else
    {
        printf("insturction: 0x%x not implemented for oplength of 1 byte, executing nop\n", opcode);
        inc(program_counter);
    }






}

/*
 *
 */
void exec_2(uint8_t opcode, uint8_t param, uint8_t* registers, uint16_t* program_counter, uint8_t* memory)
{
    if(opcode == 0x20) // JR NZ, r8
    {
        // test for Z flag
        struct reg_flags flags = get_flags(registers);
        if (!flags.zero)
        {
            jmp(program_counter, param);
        }else 
        {
            // next instruction
            jmp(program_counter, 2);    
        }
        
    }else if(opcode == 0x30) // JR NC, r8
    {
        struct reg_flags flags = get_flags(registers);
        // test for CY flag
        if (!flags.carry)
        {
            jmp(program_counter, param);
        }else
        {
            // next instruction
            jmp(program_counter, 2);
        }
    }else if(opcode == 0xe0) // LD (a8), A
    {
        mem_store(reg_load(0, registers), COMBINE_BYTES(0xff, param), memory);
        jmp(program_counter, 2);
    }else
    {
        printf("insturction: 0x%x param: 0x%x not implemented for oplength of 2 bytes, executing nop\n", opcode, param);
        jmp(program_counter, 2);
    }
}
