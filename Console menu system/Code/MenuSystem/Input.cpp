#include "Input.h"

#include <Windows.h>
#include <conio.h>

using namespace MenuSystem::Utility;
using namespace MenuSystem::Input;

//TODO: Set mouse support ENABLE_EXTENDED_FLAGS maybe
/*
fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
if (!SetConsoleMode(hStdin, fdwMode))
ErrorExit("SetConsoleMode");
*/
namespace
{
	Input input;

	HANDLE inputHandle;
	HANDLE consoleHandle;
	Pos cursorPos;
	bool cursorVisible;
	int cursorSize;

	bool blockingInput;
}

bool Input::Init(const InputOption& option)
{
	inputHandle = GetStdHandle(STD_INPUT_HANDLE);

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

InputEvent Input::GetInput()
{
	InputEvent inputEvent;
	DWORD dwEventsRead = 0;
	bool readInput = true;

	if (!blockingInput)
	{
		readInput = input.PeekInputBuffer();
	}

	if (readInput)
	{
		do
		{
			ReadConsoleInput(inputHandle, &inputEvent, 1, &dwEventsRead);
		} while (inputEvent.EventType != KEY_EVENT || inputEvent.Event.KeyEvent.bKeyDown == false);
	}

	return inputEvent;
}

bool Input::PeekInputBuffer()
{
	InputEvent inputEvent[10];
	DWORD dwEventsRead = 0;
	PeekConsoleInput(inputHandle, inputEvent, 10, &dwEventsRead);

	for (int i = 0; i < dwEventsRead; i++)
	{
		if (inputEvent[i].EventType == KEY_EVENT)
			return true;
	}

	return false;
}