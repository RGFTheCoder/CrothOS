#!/bin/env fish
rm -rf ./bin/
mkdir -p ./bin/src/sec1/
mkdir -p ./bin/src/sec2/
mkdir -p ./bin/src/bin/
mkdir -p ./bin/src/assets/

nasm -f bin ./src/sec1/bootloader.asm -o ./bin/src/sec1/bootloader.bin
nasm -f bin ./src/sec2/empty.asm -o ./bin/src/sec2/empty.bin
nasm -f elf64 ./src/sec2/ExtendedProgram.asm -o ./bin/src/sec2/ExtendedProgram.o
nasm -f elf64 ./src/sec2/Binaries.asm -o ./bin/src/sec2/Binaries.o

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c ./src/Kernel.cpp -o ./bin/src/Kernel.o -std=c++2a

x86_64-elf-ld -T"./scripts/link.ld"


cat ./bin/src/sec1/bootloader.bin >./bin/src/bin/combined.bin
cat ./bin/src/Kernel.bin >>./bin/src/bin/combined.bin
cat ./bin/src/sec2/empty.bin >>./bin/src/bin/combined.bin

echo mov al, (math floor"("(wc -c < ./bin/src/bin/combined.bin)/512")") >./src/sec1/DiskReadSegments.asm