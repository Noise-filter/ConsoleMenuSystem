#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

#include "Utility.h"
#include "InputEvent.h"

namespace MenuSystem
{
	namespace Input
	{
		/*
			This class only saves the cursorPosition it wont update it automatically.
			You have to manually Set the cursor position.

			By default the GetInput function will block the program until something is clicked.
		*/

		const int DEFAULT_CURSOR_SIZE = 25;	//Min = 1, Max = 100

		struct InputOption
		{
			HANDLE consoleHandle;

			Utility::Pos cursorPos;
			int cursorSize;	//1-100

			bool cursorVisible;
			bool blockingInput;
		};

		class Input
		{
		public:
			static bool Init(const InputOption& option);

			static void SetCursorPosition(const Utility::Pos& pos);
			static void SetCursorVisibility(const bool visible);
			static void SetCursorSize(const int size);

			static Utility::Pos& GetPosition();
			static bool GetCursorVisibility();
			static int GetCursorSize();

			static InputEvent GetInput();

		private:
			static bool PeekInputBuffer();
		};
	}
}

#endif