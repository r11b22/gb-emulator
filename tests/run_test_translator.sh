gcc -o test test_translator.c ../cpu/cu.c ../cpu/cu.h ../cpu/registers.c ../cpu/registers.h ../cpu/alu.h ../cpu/alu.c ../cpu/translator.h ../cpu/translator.c

./test
