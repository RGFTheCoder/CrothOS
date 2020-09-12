#include "TextPrint.cpp"
#include "IDT.cpp"

#include "./Keyboard.cpp"

extern "C" void _start()
{
	ClearScreen();
	SetCursorPosition(PositionFromCoords(0, 0));
	InitializeIDT();

	MainKeyboardHandler = KeyboardHandler;

	PrintString(IntegerToString(-123456789));
	PrintString("\r\n");
	PrintString(FloatToString(-672.938));
	return;
}