#include "InputEvent.h"

InputEvent::InputEvent()
{}

InputEvent::~InputEvent()
{}

//Always determine what event type it is before trying to get values from the event.
bool InputEvent::IsKeyEvent()
{
	return (EventType == KEY_EVENT);
}

bool InputEvent::IsMouseEvent()
{
	return (EventType == MOUSE_EVENT);
}

bool InputEvent::IsWindowResizeEvent()
{
	return (EventType == WINDOW_BUFFER_SIZE_EVENT);
}

char InputEvent::GetAsciiChar()
{
	return Event.KeyEvent.uChar.AsciiChar;
}

wchar_t InputEvent::GetUnicodeChar()
{
	return Event.KeyEvent.uChar.UnicodeChar;
}

unsigned short InputEvent::GetVirtualKeyCode()
{
	return Event.KeyEvent.wVirtualKeyCode;
}

unsigned long InputEvent::GetControlKeyState()
{
	if (IsKeyEvent())
	{
		return Event.KeyEvent.dwControlKeyState;
	}
	else if (IsMouseEvent())
	{
		return Event.MouseEvent.dwControlKeyState;
	}
	
	return 0;
}

/*Helpful functions which checks the key bindings*/
bool InputEvent::EnterPressed()
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_RETURN);
	}
	return false;
}

bool InputEvent::ExitPressed()
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_ESCAPE);
	}
	return false;
}

bool InputEvent::UpPressed()
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_UP);
	}
	return false;
}

bool InputEvent::DownPressed()
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_DOWN);
	}
	return false;
}

bool InputEvent::LeftPressed()
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_LEFT);
	}
	return false;
}

bool InputEvent::RightPressed()
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_RIGHT);
	}
	return false;
}

bool InputEvent::LeftMouseButtonPressed()
{
	if (IsMouseEvent())
	{
		return (Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED);
	}
	return false;
}

bool InputEvent::RightMouseButtonPressed()
{
	if (IsMouseEvent())
	{
		return (Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED);
	}
	return false;
}