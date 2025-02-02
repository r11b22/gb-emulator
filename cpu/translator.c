#include "translator.h"
#include "registers.h"
#include "cu.h"
#include "alu.h"
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
    }else if(IN_RANGE(opcode, 0x70, 0x75))
    {
        uint8_t value = reg_load(LD_REG_TRANSLATION[opcode-0x70], registers);
        reg_store16(value, 4, registers);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_RANGE(opcode, 0x80, 0x85))
    {
        add(LD_REG_TRANSLATION[opcode-0x80], registers);

        // after instruction execution increment program counter
        inc(program_counter);
    }






}
