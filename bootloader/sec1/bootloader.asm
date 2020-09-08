[org 0x7c00]

mov [BOOT_DISK], dl

mov bp, 0x7c00
mov sp, bp

call ReadDisk

jmp PROGRAM_SPACE

jmp $

%include "./bootloader/sec1/print.asm"
%include "./bootloader/sec1/DiskRead.asm"

times 510-($-$$) db 0

db 0x55, 0xaa