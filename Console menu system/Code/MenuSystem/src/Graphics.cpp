#include "Graphics.h"

#include <iostream>
#include <Windows.h>

#include "Window.h"
#include "Input.h"

using namespace MenuSystem::Graphics;
using namespace MenuSystem::Utility;
using namespace MenuSystem::Window;
using namespace MenuSystem::Input;

using namespace std;

//Variables used by the GraphicsAPI
namespace
{
	Window* window;
	CHAR_INFO* backbuffer;

	TextColor backgroundColor;
	short backgroundColorAttr;
	
	TextColor lastColor;
	short lastColorAttr;
}

bool GraphicsAPI::Init(const GraphicsOption& option)
{
	backbuffer = NULL;

	WindowOption wOption;
	wOption.windowSize = option.windowSize;
	wOption.windowTitle = option.windowTitle;

	window = new ::Window();
	if(!window->Init(wOption))
	{
		Shutdown();
		return false;
	}

	backgroundColor = TextColor(option.backgroundColor, option.backgroundColor);
	backgroundColorAttr = backgroundColor.GetColor();

	backbuffer = new CHAR_INFO[option.windowSize.x * option.windowSize.y];

	for(int x = 0; x < option.windowSize.x; x++)
	{
		for(int y = 0; y < option.windowSize.y; y++)
		{
			backbuffer[x + option.windowSize.x * y].Char.UnicodeChar = ' ';
			backbuffer[x + option.windowSize.x * y].Attributes = backgroundColorAttr;
		}
	}

	//Set first color
	if(!UseColor(backgroundColor, true))
	{
		Shutdown();
		return false;
	}

	return true;
}

void GraphicsAPI::Shutdown()
{
	UseColor(backgroundColor);

	delete[] backbuffer;
	backbuffer = NULL;

	delete window;
	window = NULL;
}

bool GraphicsAPI::UseColor(TextColor& color, bool force)
{
	if(lastColor != color)
	{
		lastColor = color;
		lastColorAttr = lastColor.GetColor();
		//if(!SetConsoleTextAttribute(window->GetConsoleHandle(), lastColorAttr))
		{
		//	return false;
		}
	}
	return true;
}

void GraphicsAPI::PrintBuffer(const CHAR_INFO buffer[], const Pos& pos, const Pos& size)
{
	for (int x = pos.x; x < size.x + pos.x; x++)
	{
		for (int y = pos.y; y < size.y + pos.y; y++)
		{
			int index = x + window->GetWindowSize().x * y;
			int index2 = (x - pos.x) + (y - pos.y) * size.x;

			backbuffer[index].Attributes = buffer[index2].Attributes;
			backbuffer[index].Char.AsciiChar = buffer[index2].Char.AsciiChar;
		}
	}
}

void GraphicsAPI::PrintCharacter(const Pos& renderPos, const char character)
{
	int index = renderPos.x + window->GetWindowSize().x * renderPos.y;

	backbuffer[index].Attributes = lastColorAttr;
	backbuffer[index].Char.AsciiChar = character;
}

void GraphicsAPI::PrintText(Text& text, const Pos& pos, const Pos& size)
{
	GraphicsAPI::UseColor(text.color);

	Pos tempSize = size;
	Pos windowSize = window->GetWindowSize();

	if(tempSize.x == 0) tempSize.x = windowSize.x;
	if(tempSize.y == 0) tempSize.y = windowSize.y;

	if(tempSize.x + pos.x >= windowSize.x)
		tempSize.x -= (tempSize.x + pos.x - windowSize.x);

	if(tempSize.y + pos.y >= windowSize.y)
		tempSize.y -= (tempSize.y + pos.y - windowSize.y);

	Pos renderPos = pos;
	int textIndex = 0;
	std::string tempString;
	int textStringLength = (int)text.textString.size();

	int yLimit = pos.y + tempSize.y;
	for(; renderPos.y < yLimit && (textIndex < textStringLength || (int)tempString.size() > 0); renderPos.y++)
	{
		int xLimit = pos.x + tempSize.x;
		for(; renderPos.x < xLimit && (textIndex < textStringLength || (int)tempString.size() > 0); renderPos.x++)
		{
			if(tempString.size() > 0)
			{
				GraphicsAPI::PrintCharacter(renderPos, tempString[0]);
				tempString.erase(tempString.begin());
			}
			else
			{
				renderPos.x--;
				if(text.textString[textIndex] == '\t')
				{
					tempString += "        ";
				}
				else if(text.textString[textIndex] == '\n')
				{
					for(int i = 1; i < pos.x + size.x - renderPos.x; i++)
						tempString += ' ';
				}
				else
				{
					renderPos.x++;
					GraphicsAPI::PrintCharacter(renderPos, text.textString[textIndex]);
				}

				++textIndex;
			}
		}
		renderPos.x = pos.x;
	}
}

void GraphicsAPI::ClearScreen(const Pos& start, const Pos& size)
{
	Pos maxWindowSize = window->GetWindowSize();
	
	Pos tempStart = start;
	if(tempStart.x < 0) tempStart.x = 0;
	if(tempStart.y < 0) tempStart.y = 0;
	
	if(tempStart.x > maxWindowSize.x) tempStart.x = maxWindowSize.x;
	if(tempStart.y > maxWindowSize.y) tempStart.y = maxWindowSize.y;
	
	Pos tempSize = size;

	if(tempSize.x == 0) tempSize.x = maxWindowSize.x;
	if(tempSize.y == 0) tempSize.y = maxWindowSize.y;

	if(tempSize.x + tempStart.x > maxWindowSize.x) tempSize.x = maxWindowSize.x;
	else tempSize.x += tempStart.x;

	if(tempSize.y + tempStart.x > maxWindowSize.y) tempSize.y = maxWindowSize.y;
	else tempSize.y += tempStart.y;

	UseColor(backgroundColor);
	int yStart = tempStart.y;

	for(; tempStart.x < tempSize.x; tempStart.x++)
	{
		tempStart.y = yStart;
		for(; tempStart.y < tempSize.y; tempStart.y++)
		{
			PrintCharacter(tempStart, ' ');
		}
	}
}

void GraphicsAPI::Present()
{
	COORD backbufferSize = {window->GetWindowSize().x, window->GetWindowSize().y};
	COORD zeroZero = {0, 0};
	SMALL_RECT rect = {zeroZero.X, zeroZero.Y, backbufferSize.X-1, backbufferSize.Y-1};

	WriteConsoleOutput(window->GetConsoleHandle(), backbuffer, backbufferSize, zeroZero, &rect);
}

HANDLE GraphicsAPI::GetConsoleHandle()
{
	return window->GetConsoleHandle();
}

Window* GraphicsAPI::GetWindow()
{
	return window;
}