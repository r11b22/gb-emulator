# A GB-EMULATOR WRITEN IN C


## managing registers (registers.c, registers.h)
registers are kept in an array

create the registers via `uint8_t* reg_init()`

load from register via `uint8_t reg_load(size_t reg_ind, uint8_t* registers)`
store to register via `void reg_store(uint8_t value, size_t reg_ind, uint8_t* registers)`
store to a virtual 16bit register via `void reg_store16(uint16_t value, size_t reg_ind, uint8_t* registers)`


