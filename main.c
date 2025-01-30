#include <stdio.h>
#include "fileio.h"


int main()
{
    // file
    FILE *file;
    // open file
    file = fopen("../roms/Pokemon/rom.gb", "rb");

    
    print_contents(file, 300);

    // close file
    fclose(file);
    return 0;
}

