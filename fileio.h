// make sure filio is not included twice
#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdint.h>
#include <stdio.h>

/*
 * prints {size} bytes from the file
 */
void print_contents(FILE* file, unsigned int size);

/*
 * reads one byte from a file and moves the file pointer
 */
uint8_t read_byte(FILE* file, uint16_t program_counter);

/*
 * reads a file into the rom section of the gb memory
 */
void read_file_to_mem(FILE* file, uint8_t* memory);

#endif
