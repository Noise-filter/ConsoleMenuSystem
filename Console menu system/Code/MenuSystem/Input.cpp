#include "Input.h"

#include <Windows.h>
#include <conio.h>

using namespace MenuSystem::Utility;
using namespace MenuSystem::Input;

namespace
{
	HANDLE consoleHandle;
	Pos cursorPos;
	bool cursorVisible;
	int cursorSize;

	bool blockingInput;
}

bool Input::Init(const InputOption& option)
{
	consoleHandle = option.consoleHandle;
	cursorPos = option.cursorPos;
	cursorVisible = option.cursorVisible;
	cursorSize = option.cursorSize;
	blockingInput = option.blockingInput;

	if(cursorSize > 100) cursorSize = 100;
	if(cursorSize < 1) cursorSize = 1;

	Input::SetCursorPosition(cursorPos);
	Input::SetCursorVisibility(cursorVisible);

	return true;
}

void Input::SetCursorPosition(const Pos& pos)
{
	cursorPos = pos;

	COORD coord;
	coord.X = cursorPos.x;
	coord.Y = cursorPos.y;

	SetConsoleCursorPosition(consoleHandle, coord);
}

void Input::SetCursorVisibility(const bool visible)
{
	cursorVisible = visible;

	CONSOLE_CURSOR_INFO info;

	info.bVisible = cursorVisible;
	info.dwSize = cursorSize;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void Input::SetCursorSize(const int size)
{
	cursorSize = size;

	//Clamp the values to 1-100
	if(cursorSize > 100)
		cursorSize = 100;
	if(cursorSize < 1)
		cursorSize = 1;

	CONSOLE_CURSOR_INFO info;

	info.bVisible = cursorVisible;
	info.dwSize = cursorSize;
	SetConsoleCursorInfo(consoleHandle, &info);
}

Pos& Input::GetPosition()
{
	return cursorPos;
}

bool Input::GetCursorVisibility()
{
	return cursorVisible;
}

int Input::GetCursorSize()
{
	return cursorSize;
}

char Input::GetInput()
{
	if(!blockingInput)
	{
		if(_kbhit())
		{
			return _getch();
		}
	}
	else
	{
		return _getch();
	}
	return 0;
}