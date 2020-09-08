#pragma once
#include "TypeDefs.cpp"
#include "TextPrint.cpp"

struct IDT64
{
	u16 offset_low;
	u16 selector;
	u8 ist;
	u8 types_attr;
	u16 offset_mid;
	u32 offset_high;
	u32 zero;
};

extern IDT64 _idt[256];
extern u64 isr1;
extern "C" void LoadIDT();

void InitializeIDT()
{
	for (u8 t = 0; t < 256; t++)
	{
		_idt[t].zero = 0;
		_idt[t].offset_low = (u16)(((u64)&isr1 & 0x000000000000ffff));
		_idt[t].offset_mid = (u16)(((u64)&isr1 & 0x00000000ffff0000) >> 16);
		_idt[t].offset_high = (u32)(((u64)&isr1 & 0xffffffff00000000) >> 32);
		_idt[t].ist = 0;
		_idt[t].selector = 0x08;
		_idt[t].types_attr = 0x8e;
	}

	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	LoadIDT();
}

extern "C" void isr1_handler()
{
	PrintString("hello there\r\n");
	PrintString(HexToString(inb(0x60)));

	outb(0x20, 0x20);
	outb(0xa0, 0x20);
}