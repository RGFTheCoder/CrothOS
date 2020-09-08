#include "TextPrint.cpp"
#include "IDT.cpp"

extern const char Test[];
extern const char Test2[];

extern "C" void _start()
{
	ClearScreen();
	SetCursorPosition(PositionFromCoords(0, 0));
	PrintString("hello there\r\n");
	InitializeIDT();
	return;
}