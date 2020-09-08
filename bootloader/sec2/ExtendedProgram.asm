[org 0x7e00]

jmp EnterProtectedMode

%include "./bootloader/sec2/gdt.asm"
%include "./bootloader/sec1/print.asm"
%include "./bootloader/sec2/CPUID.asm"
%include "./bootloader/sec2/SimplePaging.asm"

EnterProtectedMode:
	call EnableA20
	cli
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp codeseg:StartProtectedMode

EnableA20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

[bits 32]

StartProtectedMode:

	mov ax, dataseg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call DetectCPUID
	call DetectLongMode
	call SetUpIdentityPaging
	
	jmp $

times 0x0400-($-$$) db 0