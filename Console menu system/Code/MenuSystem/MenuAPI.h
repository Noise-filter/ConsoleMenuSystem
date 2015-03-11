#ifndef MENU_API_H
#define MENU_API_H

#ifdef _DEBUG
#include <vld.h>
#endif

#include "Utility.h"

namespace MenuSystem
{
	struct MenuSystemOption
	{
		//Graphics
		std::string windowTitle;
		Utility::Pos windowSize;
		Utility::Color backgroundColor;

		//Input
		bool cursorVisible;
		Utility::Pos cursorPos;
		int cursorSize;				//1-100, default = 25
		bool blockingInput;
	};

	class API
	{
	public:
		static bool Init(const MenuSystemOption& option);

		static void Render();

		static char GetInput();

		static void Shutdown();
	};
}

#endif