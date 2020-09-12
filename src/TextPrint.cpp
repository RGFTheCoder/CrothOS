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

void printChar(i8 chr, u8 color = BG_BLACK | FG_WHITE)
{
	*(VGA_MEMORY + CursorPosition * 2) = chr;
	*(VGA_MEMORY + CursorPosition * 2 + 1) = color;

	SetCursorPosition(CursorPosition + 1);
}

template <class T>
const char *HexToString(T value)
{
	static char hexToStringOutput[128];
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

template <class T>
const char *IntegerToString(T value)
{

	u8 isNegative = 0;
	if (value < 0)
	{
		isNegative = 1;
		value *= -1;
	}

	static char integerToStringOutput[128];
	u8 size = 0;
	u64 sizeTester = (u64)value;
	u8 index = 0;

	while (sizeTester / 10 > 0)
	{
		sizeTester /= 10;
		size++;
	}

	if (isNegative)
		size++;

	u64 newValue = (u64)value;
	while (newValue / 10 > 0)
	{
		u8 remainder = newValue % 10;
		newValue /= 10;
		integerToStringOutput[size - index] = remainder + '0';
		index++;
	}

	u8 remainder = newValue % 10;
	integerToStringOutput[size - index] = remainder + '0';
	index++;

	if (isNegative == 1)
	{
		integerToStringOutput[size - index] = '-';
	}
	integerToStringOutput[size + 1] = 0;

	return integerToStringOutput;
}

template <class T>
const char *FloatToString(T value, u8 decimalPlaces = 3)
{
	static char floatToStringOutput[128];
	char *intPtr = (char *)IntegerToString((int)value);
	char *floatPtr = floatToStringOutput;

	if (value < 0)
	{
		value *= -1;
	}

	while (*intPtr != 0)
	{
		*floatPtr = *intPtr;

		floatPtr++;
		intPtr++;
	}

	*(floatPtr++) = '.';

	T newValue = value - (int)value;

	for (u8 i = 0; i < decimalPlaces; i++)
	{
		newValue *= 10;
		*(floatPtr++) = (char)newValue + '0';
		newValue = newValue - (int)newValue;
	}

	*floatPtr = 0;

	return floatToStringOutput;
}