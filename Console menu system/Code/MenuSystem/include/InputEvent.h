#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

#include <Windows.h>

class InputEvent : public INPUT_RECORD
{
public:
	virtual ~InputEvent() = default;

	//Always determine what event type it is before trying to get values from the event.
	bool IsKeyEvent() const noexcept;
	bool IsMouseEvent() const noexcept;
	bool IsWindowResizeEvent() const noexcept;

	char GetAsciiChar() const noexcept;
	wchar_t GetUnicodeChar() const noexcept;

	unsigned short GetVirtualKeyCode() const noexcept;
	unsigned long GetControlKeyState() const noexcept;

	/*Helpful functions which checks the key bindings*/
	bool EnterPressed() const noexcept;
	bool ExitPressed() const noexcept;
	bool UpPressed() const noexcept;
	bool DownPressed() const noexcept;
	bool LeftPressed() const noexcept;
	bool RightPressed() const noexcept;

	bool LeftMouseButtonPressed() const noexcept;
	bool RightMouseButtonPressed() const noexcept;

private:
	

};

#endif