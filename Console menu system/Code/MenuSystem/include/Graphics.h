#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Windows.h>

#include "Utility.h"
#include "Window.h"

namespace MenuSystem
{
	namespace Graphics
	{
		struct GraphicsOption
		{
			GraphicsOption(std::string title = Window::DEFUALT_CONSOLE_TITLE, Utility::Pos size = Utility::Pos(Window::DEFAULT_CONSOLE_SIZE_WIDTH, Window::DEFAULT_CONSOLE_SIZE_HEIGHT))
				: windowTitle(title), windowSize(size)
			{}

			std::string windowTitle;
			Utility::Pos windowSize;
			Utility::Color backgroundColor;
		};

		class GraphicsAPI
		{
		public:
			static bool Init(const GraphicsOption& option);

			//Only use force if you have set the color manually else where.
			static bool UseColor(Utility::TextColor& color);

			static void PrintBuffer(const CHAR_INFO buffer[], const Utility::Pos& pos, const Utility::Pos& size);

			static void PrintCharacter(const Utility::Pos& renderPos, const char character);

			static void PrintText(Utility::Text& text, const Utility::Pos& pos, const Utility::Pos& size = Utility::Pos());

			static void ClearScreen(const Utility::Pos& start, const Utility::Pos& size);

			static void Present();

			static void MoveCursor(const Utility::Pos& pos);
			
			static HANDLE GetConsoleHandle();

			static MenuSystem::Window::Window* GetWindow();

			static void Shutdown();

		};
	}
}

#endif