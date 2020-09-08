PrintStringRaw:
	mov ah, 0x0e
	.Loop:
	cmp [bx], byte 0x00
	je .Exit
		mov al, [bx]
		int 0x10
		inc bx
		jmp .Loop
	.Exit:
	ret


PrintString:
	call PrintStringRaw
	mov al, 10
	int 0x10
	mov al, 13
	int 0x10
	ret