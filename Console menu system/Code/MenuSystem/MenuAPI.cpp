#include "MenuAPI.h"

#include "Input.h"
#include "Graphics.h"

using namespace MenuSystem;
using namespace MenuSystem::Input;
using namespace MenuSystem::Graphics;

bool API::Init(const MenuSystemOption& option)
{
	GraphicsOption gOption;
	gOption.backgroundColor = option.backgroundColor;
	gOption.windowSize = option.windowSize;
	gOption.windowTitle = option.windowTitle;

	if(!GraphicsAPI::Init(gOption))
	{
		return false;
	}
	API::Render();

	InputOption iOption;
	iOption.blockingInput = option.blockingInput;
	iOption.consoleHandle = GraphicsAPI::GetConsoleHandle();
	iOption.cursorPos = option.cursorPos;
	iOption.cursorSize = option.cursorSize;
	iOption.cursorVisible = option.cursorVisible;

	Input::Input::Init(iOption);

	return true;
}

void API::Render()
{
	//Render all the active menus.

	//Show backbuffer
	GraphicsAPI::Present();
}

char API::GetInput()
{
	return Input::Input::GetInput();
}

void API::Shutdown()
{
	Input::Input::SetCursorPosition((0, 0));
	GraphicsAPI::Shutdown();
}