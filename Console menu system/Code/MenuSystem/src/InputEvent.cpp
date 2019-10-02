#include "InputEvent.h"

//Always determine what event type it is before trying to get values from the event.
bool InputEvent::IsKeyEvent() const noexcept
{
	return (EventType == KEY_EVENT);
}

bool InputEvent::IsMouseEvent() const noexcept
{
	return (EventType == MOUSE_EVENT);
}

bool InputEvent::IsWindowResizeEvent() const noexcept
{
	return (EventType == WINDOW_BUFFER_SIZE_EVENT);
}

char InputEvent::GetAsciiChar() const noexcept
{
	return Event.KeyEvent.uChar.AsciiChar;
}

wchar_t InputEvent::GetUnicodeChar() const noexcept
{
	return Event.KeyEvent.uChar.UnicodeChar;
}

unsigned short InputEvent::GetVirtualKeyCode() const noexcept
{
	return Event.KeyEvent.wVirtualKeyCode;
}

unsigned long InputEvent::GetControlKeyState() const noexcept
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
bool InputEvent::EnterPressed() const noexcept
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_RETURN);
	}
	return false;
}

bool InputEvent::ExitPressed() const noexcept
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_ESCAPE);
	}
	return false;
}

bool InputEvent::UpPressed() const noexcept
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_UP);
	}
	return false;
}

bool InputEvent::DownPressed() const noexcept
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_DOWN);
	}
	return false;
}

bool InputEvent::LeftPressed() const noexcept
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_LEFT);
	}
	return false;
}

bool InputEvent::RightPressed() const noexcept
{
	if (IsKeyEvent())
	{
		return (GetVirtualKeyCode() == VK_RIGHT);
	}
	return false;
}

bool InputEvent::LeftMouseButtonPressed() const noexcept
{
	if (IsMouseEvent())
	{
		return (Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED);
	}
	return false;
}

bool InputEvent::RightMouseButtonPressed() const noexcept
{
	if (IsMouseEvent())
	{
		return (Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED);
	}
	return false;
}