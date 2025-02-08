# A GB-EMULATOR WRITEN IN C

## Data
16 bit values in instructions are in little endian: (lo hi)

## managing registers (registers.c, registers.h)
registers are kept in an array

create the registers via `uint8_t* reg_init()`

load from register via `uint8_t reg_load(size_t reg_ind, uint8_t* registers)`
store to register via `void reg_store(uint8_t value, size_t reg_ind, uint8_t* registers)`
store to a virtual 16bit register via `void reg_store16(uint16_t value, size_t reg_ind, uint8_t* registers)`

## instructions

Instructions are split up into micro instructions.
Each micro instruction can take any argument from the original instruction.
Micro instructions are directly implemented in c


## micro instructions 

### ALU (alu.c alu.h)
#### ADD target
adds the registers A and traget into A
#### ADC target
adds the regsiters A, target and carry into A
#### SUB target
subtracts the registers A and target into A

### CU (cu.c cu.h)
#### INC
increments the program counter
#### JMP
add a specific amount to the program counter


## instruction translation (translator.c translator.h)
translates each instruction into micro instructions and executes them
there are 3 types of instructions
1 len
2 len
3 len




## memory (memory.c memory.h)
memory can be accesd via the mem_load() and mem_store() functions


memory is divided in sectors

* 0xc000-0xDFFF : Internal ram 8 kB
* 0xff0-0xff4B : I(nput)/O(utput)  
* 0xff80-0xfffe : High (speed) ram 127 bytes
* 0xffff : interupt register 1 byte (stores interupt type)
