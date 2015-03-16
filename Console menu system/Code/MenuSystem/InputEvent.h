#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

#include <Windows.h>

class InputEvent : public INPUT_RECORD
{
public:
	InputEvent();
	virtual ~InputEvent();

	//Always determine what event type it is before trying to get values from the event.
	bool IsKeyEvent();
	bool IsMouseEvent();
	bool IsWindowResizeEvent();

	char GetAsciiChar();
	wchar_t GetUnicodeChar();

	unsigned short GetVirtualKeyCode();
	unsigned long GetControlKeyState();

	/*Helpful functions which checks the key bindings*/
	bool EnterPressed();
	bool ExitPressed();
	bool UpPressed();
	bool DownPressed();
	bool LeftPressed();
	bool RightPressed();

	bool LeftMouseButtonPressed();
	bool RightMouseButtonPressed();

private:
	

};

#endif