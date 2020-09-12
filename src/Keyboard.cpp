#pragma once

#include "./TypeDefs.cpp"
#include "./TextPrint.cpp"

struct
{
	bool leftShift = false;
	bool rightShift = false;
} pressedKeys;

u8 lastScancode = 0;

void StandardKeyboardHandler(u8 scancode, u8 chr)
{
	if (chr != 0)
		if (pressedKeys.leftShift)
		{
			printChar(chr - 32);
		}
		else
		{
			printChar(chr);
		}
	else
		switch (scancode)
		{
		case 0x8e:
			SetCursorPosition(CursorPosition - 1);
			printChar(' ');
			SetCursorPosition(CursorPosition - 1);
			break;
		case 0x2a:
			pressedKeys.leftShift = true;
			break;
		case 0xaa:
			pressedKeys.leftShift = false;
			break;
		case 0x36:
			pressedKeys.rightShift = true;
			break;
		case 0xb6:
			pressedKeys.rightShift = false;
			break;
		case 0x9c:
			PrintString("\r\n");
			break;

		default:
			break;
		}
}

void KeyboardHandler0xe0(u8 scancode)
{
	switch (scancode)
	{
	case 0x50:
		SetCursorPosition(CursorPosition + VGA_WIDTH);
		break;
	case 0x48:
		SetCursorPosition(CursorPosition - VGA_WIDTH);
		break;

	default:
		break;
	}
}

void KeyboardHandler(u8 scancode, u8 chr)
{
	switch (lastScancode)
	{
	case 0xe0:
		KeyboardHandler0xe0(scancode);

	default:
		StandardKeyboardHandler(scancode, chr);
		break;
	}
	lastScancode = scancode;
}
