#pragma once
#include "IO.cpp"
#include "TypeDefs.cpp"
#include "TextModeColorCodes.cpp"
#define VGA_MEMORY (u8 *)0xb8000
#define VGA_WIDTH 80

u16 CursorPosition;

void ClearScreen(const u8 &ClearColor = BG_BLACK | FG_WHITE)
{
	u64 value = 0;
	value += (u64)ClearColor << 8;
	value += (u64)ClearColor << 24;
	value += (u64)ClearColor << 40;
	value += (u64)ClearColor << 56;
	for (u64 *i = (u64 *)VGA_MEMORY; i < (u64 *)(VGA_MEMORY + 4000); i++)
	{
		*i = value;
	}
}

void SetCursorPosition(const u16 &position)
{
	outb(0x3D4, 0x0F);
	outb(0x3D5, (u8)(position & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (u8)((position >> 8) & 0xFF));

	CursorPosition = position;
}

constexpr inline const u16 PositionFromCoords(const u8 &x, const u8 &y)
{
	return y * VGA_WIDTH + x;
}

void PrintString(const char *str, const u8 &color = BG_BLACK | FG_WHITE)
{
	u8 *charPtr = (u8 *)str;
	u16 index = CursorPosition;
	while (*charPtr != 0)
	{
		switch (*charPtr)
		{
		case '\n':
			index += VGA_WIDTH;
			break;
		case '\r':
			index -= index % VGA_WIDTH;
			break;

		default:
			*(VGA_MEMORY + index * 2) = *charPtr;
			*(VGA_MEMORY + index * 2 + 1) = color;
			index++;
			break;
		}
		charPtr++;
	}
	SetCursorPosition(index);
}

char hexToStringOutput[128];
template <class T>
const char *HexToString(T value)
{
	T *valPtr = &value;
	u8 *ptr;
	u8 temp;
	u8 size = ((sizeof(T)) * 2 - 1);
	u8 i;
	for (i = 0; i < size; i++)
	{
		ptr = ((u8 *)valPtr + i);
		temp = ((*ptr & 0xf0) >> 4);
		hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
		temp = ((*ptr & 0x0f));
		hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
	}
	hexToStringOutput[size + 1] = 0;
	return hexToStringOutput;
}
