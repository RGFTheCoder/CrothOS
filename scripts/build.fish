#!/bin/env fish
rm -rf ./bin/
mkdir -p ./bin/src/sec1/
mkdir -p ./bin/src/sec2/
mkdir -p ./bin/src/bin/

nasm -f bin ./src/sec1/bootloader.asm -o ./bin/src/sec1/bootloader.bin
nasm -f elf64 ./src/sec2/ExtendedProgram.asm -o ./bin/src/sec2/ExtendedProgram.o

x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c ./src/Kernel.cpp -o ./bin/src/Kernel.o

x86_64-elf-ld -o ./bin/src/Kernel.tmp -Ttext 0x7e00 ./bin/src/sec2/ExtendedProgram.o ./bin/src/Kernel.o

objcopy -O binary ./bin/src/Kernel.tmp ./bin/src/Kernel.bin

cat ./bin/src/sec1/bootloader.bin >./bin/src/bin/combined.bin
cat ./bin/src/Kernel.bin >>./bin/src/bin/combined.bin