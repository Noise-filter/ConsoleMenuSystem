#ifndef MENU_API_H
#define MENU_API_H

#include "Utility.h"
#include "InputEvent.h"

namespace MenuSystem
{
	struct MenuSystemOption
	{
		//Graphics
		std::string windowTitle;
		Utility::Pos windowSize;
		Utility::Color backgroundColor;

		//Input
		Utility::Pos cursorPos;
		int cursorSize;				//1-100, default = 25
		bool cursorVisible;
		bool blockingInput;
	};

	class API
	{
	public:
		static bool Init(const MenuSystemOption& option);

		static void Render();

		static InputEvent GetInput();

		static void Shutdown();
	};
}

#endif