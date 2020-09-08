#!/bin/env fish
rm -rf ./bin/
mkdir -p ./bin/bootloader/sec1/
mkdir -p ./bin/bootloader/sec2/
mkdir -p ./bin/bootloader/bin/

nasm -f bin ./bootloader/sec1/bootloader.asm -o ./bin/bootloader/sec1/bootloader.bin
nasm -f bin ./bootloader/sec2/ExtendedProgram.asm -o ./bin/bootloader/sec2/ExtendedProgram.bin

cat ./bin/bootloader/sec1/bootloader.bin >./bin/bootloader/bin/combined.bin
cat ./bin/bootloader/sec2/ExtendedProgram.bin >>./bin/bootloader/bin/combined.bin