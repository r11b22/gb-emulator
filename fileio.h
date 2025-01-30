// make sure filio is not included twice
#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>

// the size of an operation in bytes
#define INSTRUCTION unsigned char
#define INS_SIZE sizeof(unsigned char)

void print_contents(FILE* file, unsigned int size);


#endif
