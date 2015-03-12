#include "Window.h"

using namespace MenuSystem::Window;
using namespace MenuSystem::Utility;

using namespace std;

Window::Window()
	: windowTitle(""), windowSize(Pos(0, 0)), consoleHandle(NULL)
{}

bool Window::Init(const WindowOption& option)
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if(consoleHandle == INVALID_HANDLE_VALUE)
	{
		consoleHandle = NULL;
		int error = GetLastError();
		return false;
	}

	if(!SetWindowTitle(option.windowTitle))
	{
		return false;
	}

	if(!SetWindowSize(option.windowSize))
	{
		return false;
	}

	return true;
}

bool Window::SetWindowTitle(std::string text)
{
	if(!SetConsoleTitle(text.c_str()))
	{
		int error = GetLastError();

		if(!SetConsoleTitle(DEFUALT_CONSOLE_TITLE.c_str()))
		{
			int error = GetLastError();
			return false;
		}
	}

	//Get console title
	char tempTitle[1024];
	int titleLength = 0;

	titleLength = GetConsoleTitle(tempTitle, 1024);
	if(!titleLength && text.size() > 0)
	{
		int error = GetLastError();
		return false;
	}
	else
	{
		this->windowTitle.assign(&tempTitle[0], &tempTitle[titleLength]);
	}

	return true;
}

bool Window::SetWindowSize(const Pos& size)
{
	if(maxWindowSize == Pos(0, 0))
	{
		Pos maxWindowSize = GetMaximumWindowSize();
		if(maxWindowSize.x == 0 || maxWindowSize.y == 0)
		{
			return false;
		}
	}

	COORD coord;
	coord.X = size.x;
	coord.Y = size.y;
	
	if (!SetConsoleScreenBufferSize(consoleHandle, coord))
	{
		return false;
	}
	
	/*
	if(size.x > maxWindowSize.x)
		return false;

	if(size.y > maxWindowSize.y)
		return false;
	*/

	SMALL_RECT rect = {0, 0, size.x-1, size.y-1};
	if(!SetConsoleWindowInfo(consoleHandle, true, &rect))
	{
		return false;
	}

	this->windowSize = size;

	return true;
}

HANDLE Window::GetConsoleHandle()
{
	return consoleHandle;
}

std::string Window::GetWindowTitle()
{
	return windowTitle;
}

Pos& Window::GetWindowSize()
{
	return windowSize;
}

Pos Window::GetMaximumWindowSize()
{
	if(maxWindowSize == Pos(0, 0))
	{
		_CONSOLE_SCREEN_BUFFER_INFO info;
		if(!GetConsoleScreenBufferInfo(consoleHandle, &info))
		{
			maxWindowSize.x = 0;
			maxWindowSize.y = 0;
			return maxWindowSize;
		}
		maxWindowSize = Pos(info.dwMaximumWindowSize.X, info.dwMaximumWindowSize.Y);
	}

	return maxWindowSize;
}