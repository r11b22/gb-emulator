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
#define IN_VERTICAL_RANGE(x, col, lower, upper) ((x-col)&0b00001111) == 0 && (x-col)/16 <= upper && (x-col)/16 >= lower
#define VERTICAL_INDEX(x, col) ((x-col)/16) 

void exec_1(uint8_t opcode, uint8_t *registers, uint16_t *program_counter, uint16_t *stack_pointer, uint8_t* memory)
{
    size_t LD_REG_TRANSLATION[6] = {1, 2, 3, 4, 6, 7};
    size_t LD_IM_TRANSLATION[6] = {1, 3, 6, 2, 4, 7};

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
        mem_store(value, reg_load16(3, registers), memory);

        // after instruction execution increment programm counter
        inc(program_counter);
    }else if(IN_VERTICAL_RANGE(opcode, 0x07, 0x4, 0x6)) // LD reg, A
    {
        size_t reg = ((((opcode-0x07)/16)-0x4)*2)+1;
        reg_store(reg_load(0, registers), reg, registers);
        inc(program_counter);

    }else if(IN_VERTICAL_RANGE(opcode, 0x6, 0x4, 0x6)) // LD reg, mem
    {
        reg_store(mem_load(reg_load16(3, registers), memory), LD_IM_TRANSLATION[VERTICAL_INDEX(opcode, 0x6)], registers);
        inc(program_counter);

    }else if(IN_VERTICAL_RANGE(opcode, 0xe, 0x4, 0x6)) // LD reg, mem
    {    
        reg_store(mem_load(reg_load16(3, registers), memory), LD_IM_TRANSLATION[VERTICAL_INDEX(opcode, 0xe) + 3], registers);
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
    }else if (IN_RANGE(opcode, 0x90, 0x95)) // SUB, A, reg 
    {
        sub(LD_REG_TRANSLATION[opcode-0x90], registers);

        inc(program_counter);
    }else if(IN_VERTICAL_RANGE(opcode, 0x4, 0x0, 0x2)) // inc reg
    {
        size_t reg = LD_IM_TRANSLATION[VERTICAL_INDEX(opcode, 0x4)];
        uint8_t value = reg_load(reg, registers) + 1;
        
        set_zero(value == 0, registers);
        set_subtract(false, registers);
        set_half_carry(value > 0xf, registers);

        reg_store(value, reg, registers);
        inc(program_counter);

    }else if(IN_VERTICAL_RANGE(opcode, 0xc, 0x0, 0x2)) // inc reg
    {
        size_t reg = LD_IM_TRANSLATION[VERTICAL_INDEX(opcode, 0xc)+3];
        uint8_t value = reg_load(reg, registers) + 1;
        
        set_zero(value == 0, registers);
        set_subtract(false, registers);
        set_half_carry(value > 0xf, registers);

        reg_store(value, reg, registers);
        inc(program_counter);

    }else if(IN_VERTICAL_RANGE(opcode, 0x5, 0x0, 0x2)) // dec reg
    {
        size_t reg = LD_IM_TRANSLATION[VERTICAL_INDEX(opcode, 0x5)];
        uint8_t value = reg_load(reg, registers) - 1;
        
        set_zero(value == 0, registers);
        set_subtract(true, registers);
        set_half_carry(value > 0xf, registers);

        reg_store(value, reg, registers);
        inc(program_counter);

    }else if(IN_VERTICAL_RANGE(opcode, 0xd, 0x0, 0x2)) // dec reg
    {
        size_t reg = LD_IM_TRANSLATION[VERTICAL_INDEX(opcode, 0xd)+3];
        uint8_t value = reg_load(reg, registers) - 1;
        
        set_zero(value == 0, registers);
        set_subtract(true, registers);
        set_half_carry(value > 0xf, registers);

        reg_store(value, reg, registers);
        inc(program_counter);

    }else if(opcode == 0x1f) // RRA
    {
        uint8_t value = reg_load(0, registers);
        bool new_carry = value & 1;
        value >>= 1;
        value = (value & 0b01111111) | ((get_flags(registers).carry << 7) & 0b10000000);
        reg_store(value, 0, registers);
        set_carry(new_carry, registers);
        inc(program_counter);
    }else if(opcode == 0xAf) // xor a
    {
        reg_store(0, 0, registers);
        set_zero(true, registers);
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

    }else if(opcode == 0xc1 || opcode == 0xd1 || opcode == 0xe1 || opcode == 0xf1) // POP reg
    {
        // each pop does 2 8 bit pops
        if(opcode == 0xf1)
        {
            reg_store(stack_pop(stack_pointer, memory), 0, registers);
            reg_store(stack_pop(stack_pointer, memory), 5, registers);
        }else
        {
            size_t reg = (opcode-0x01)/16;
            reg_store(stack_pop(stack_pointer, memory), (reg*2)+1, registers);
            reg_store(stack_pop(stack_pointer, memory), (reg*2)+2, registers);
        }

        inc(program_counter);
    }else if(opcode == 0xc5 || opcode == 0xd5 || opcode == 0xe5 || opcode == 0xf5) // PUSH reg
    {
        if(opcode == 0xf5)
        {
            stack_push(reg_load(0, registers), stack_pointer, memory);
            stack_push(reg_load(5, registers), stack_pointer, memory);
        }else
        {
            size_t reg = (opcode-0x05)/16;
            stack_push(reg_load((reg*2) + 1, registers), stack_pointer, memory);
            stack_push(reg_load((reg*2) + 2, registers), stack_pointer, memory);
        }
        inc(program_counter);

    }else if(opcode == 0x22) // LD (HL+), A
    {
        mem_store(reg_load(0, registers), reg_load16(3, registers), memory);
        reg_store16(reg_load16(3, registers)+1, 3, registers);
        inc(program_counter);

    }else if(opcode == 0x32) // LD (HL-), A
    {
        mem_store(reg_load(0, registers), reg_load16(3, registers), memory);
        reg_store16(reg_load16(3, registers)-1, 3, registers);
        inc(program_counter);

    }else if(opcode == 0xc0) // ret NZ
    {
        struct reg_flags flags = get_flags(registers);

        if(!flags.zero)
        {
            uint8_t lo = stack_pop(stack_pointer, memory);
            uint8_t hi = stack_pop(stack_pointer, memory);
            *program_counter = COMBINE_BYTES(hi, lo);
        }
    }else if(opcode == 0xd0) // ret NZ
    {
        struct reg_flags flags = get_flags(registers);

        if(!flags.carry)
        {
            uint8_t lo = stack_pop(stack_pointer, memory);
            uint8_t hi = stack_pop(stack_pointer, memory);
            *program_counter = COMBINE_BYTES(hi, lo);
        }
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

    size_t LD_IM_TRANSLATION[6] = {1, 3, 6, 2, 4, 7};
    if (opcode == 0x18) // JR r8
    {
        jmp(program_counter, param);

    }else if(opcode == 0x20) // JR NZ r8
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
    }else if(opcode == 0x28) // JR Z, r8
    {
        // test for Z flag
        struct reg_flags flags = get_flags(registers);
        if (flags.zero)
        {
            jmp(program_counter, param);
        }else 
        {
            // next instruction
            jmp(program_counter, 2);    
        }
        
    }else if(opcode == 0x38) // JR C, r8
    {
        struct reg_flags flags = get_flags(registers);
        // test for CY flag
        if (flags.carry)
        {
            jmp(program_counter, param);
        }else
        {
            // next instruction
            jmp(program_counter, 2);
        }
    }else if(opcode == 0x06 || opcode == 0x16 || opcode == 0x26) // LD reg, d8
    {
        reg_store(param, LD_IM_TRANSLATION[(opcode - 0x06)/16], registers);
        jmp(program_counter, 2);

    }else if(opcode == 0x0e || opcode == 0x1e || opcode == 0x2e) // LD reg, d8
    {
        reg_store(param, LD_IM_TRANSLATION[((opcode - 0x0e)/16)+3], registers);
        jmp(program_counter, 2);

    }else if(opcode == 0x36)
    {
        mem_store(COMBINE_BYTES(0x00, param), reg_load16(3, registers), memory);
        jmp(program_counter, 2);
    }else if(opcode == 0x3e)
    {
        reg_store(param, 0, registers);
        jmp(program_counter, 2);
    }else if(opcode == 0xe0) // LD (a8), A
    {
        mem_store(reg_load(0, registers), COMBINE_BYTES(0xff, param), memory);
        jmp(program_counter, 2);
    }else if (opcode == 0xf0) // LD A, (a8)
    {
        reg_store(mem_load(param, memory), 0, registers);
        jmp(program_counter, 2);
    }else if (opcode == 0xfe) // CP reg
    {
        uint8_t value_a = reg_load(0, registers);
        int16_t diff = value_a - param;

        struct reg_flags flags = {diff == 0, true, !(IN_RANGE(diff, 0, 0xf)), diff < 0};
        set_flags(flags, registers);

        // go to next instruction
        inc(program_counter);

    }else
    {
        printf("insturction: 0x%x param: 0x%x not implemented for oplength of 2 bytes, executing nop\n", opcode, param);
        jmp(program_counter, 2);
    }
}

void exec_3(uint8_t opcode, uint8_t param1, uint8_t param2, uint8_t *registers, uint16_t *program_counter, uint8_t *memory)
{
    uint16_t param = COMBINE_BYTES(param2, param1);
    if(opcode == 0xc2) //JP NZ, a16 
    {
        // test for Z flag
        struct reg_flags flags = get_flags(registers);
        if (!flags.zero)
        {
            *program_counter = param;
        }else 
        {
            // next instruction
            jmp(program_counter, 3);    
        }

    }else if(opcode == 0xd2) // JP NC, a16
    {
        // test for CY flag
        struct reg_flags flags = get_flags(registers);
        if (!flags.carry)
        {
            *program_counter = param;
        }else 
        {
            // next instruction
            jmp(program_counter, 3);    
        }

    }else if(IN_VERTICAL_RANGE(opcode, 0x1, 0x0, 0x2)) // LD reg, 16bit
    {
        reg_store16(param, VERTICAL_INDEX(opcode, 0x1) + 1, registers);
        jmp(program_counter, 3);
    }else if(opcode == 0xc3)
    {
        *program_counter = param;
    }else
    { 
        printf("insturction: 0x%x params: 0x%x, 0x%x not implemented for oplength of 2 bytes, executing nop\n", opcode, param1, param2);
    }
}
