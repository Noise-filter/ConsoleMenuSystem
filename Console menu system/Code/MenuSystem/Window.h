#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <string>

#include "Utility.h"

namespace MenuSystem
{
	namespace Window
	{
		const int DEFAULT_CONSOLE_SIZE_WIDTH = 80;
		const int DEFAULT_CONSOLE_SIZE_HEIGHT = 30;

		const std::string DEFUALT_CONSOLE_TITLE("Console");

		struct WindowOption
		{
			WindowOption(std::string title = DEFUALT_CONSOLE_TITLE, Utility::Pos size = Utility::Pos(DEFAULT_CONSOLE_SIZE_WIDTH, DEFAULT_CONSOLE_SIZE_HEIGHT))
				: windowTitle(title), windowSize(size)
			{}

			std::string windowTitle;
			Utility::Pos windowSize;
		};

		class Window
		{
		public:
			Window();

			bool Init(const WindowOption& option);

			bool SetWindowTitle(std::string text);
			bool SetWindowSize(const Utility::Pos& size);
			
			HANDLE GetConsoleHandle();
			std::string GetWindowTitle();
			Utility::Pos& GetWindowSize();
			Utility::Pos GetMaximumWindowSize();

		private:
			std::string windowTitle;
			Utility::Pos windowSize;
			Utility::Pos maxWindowSize;

			HANDLE consoleHandle;
			HWND consoleWindow;

		};
	}
}

#endif