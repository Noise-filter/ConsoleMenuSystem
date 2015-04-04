#ifndef INPUT_FIELD_H
#define INPUT_FIELD_H

#include "Button.h"
#include "../Input.h"

namespace MenuSystem
{
	template <class Owner>
	class InputField : public Button<Owner>
	{
	public:
		InputField(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
			const Utility::TextColor selectedColor = Utility::TextColor());
		virtual ~InputField();

		void Render();
		bool Update(InputEvent input);

		void ClearText();

		virtual MenuItemType GetType();

	protected:
		void FillRestOfField(char character);

	private:
		void HandleInput(InputEvent input);
		bool IsAnInputKey(InputEvent input);

	protected:
		int currentCursorIndex;
	};

	template <class Owner>
	InputField<Owner>::InputField(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos, const Utility::Text& text, const Utility::Pos& size, const Utility::TextColor selectedColor)
		: Button(owner, callbackFunction, pos, text, size, selectedColor)
	{
		currentCursorIndex = -1;
	}

	template <class Owner>
	InputField<Owner>::~InputField()
	{

	}

	template <class Owner>
	void InputField<Owner>::Render()
	{
		if (visible)
		{
			if (active)
			{
				if (currentCursorIndex >= 0 && currentCursorIndex > size.x)
				{
					Graphics::GraphicsAPI::PrintText(Text(text.textString.substr(currentCursorIndex - size.x), selectedColor), pos, size);
				}
				else
				{
					Graphics::GraphicsAPI::PrintText(Text(text.textString, selectedColor), pos, size);
				}

				FillRestOfField(' ');
			}
			else
			{	
				Graphics::GraphicsAPI::PrintText(text, pos, size);

				FillRestOfField('_');
			}
		}
	}

	template <class Owner>
	bool InputField<Owner>::Update(InputEvent input)
	{
		if (currentCursorIndex == -1)
		{
			if (input.EnterPressed())
			{
				Input::Input::SetCursorVisibility(true);
				currentCursorIndex = (int)text.textString.size();
				Pos cursorPos = pos;
				cursorPos.x += currentCursorIndex;
				if (cursorPos.x > size.x + pos.x)
					cursorPos.x = size.x + pos.x;
				Input::Input::SetCursorPosition(cursorPos);
				return true;
			}
		}
		else
		{
			if (input.ExitPressed())
			{
				currentCursorIndex = -1;
				Input::Input::SetCursorVisibility(false);
			}

			HandleInput(input);

			if (currentCursorIndex > size.x)
				Input::Input::SetCursorPosition(Pos(pos.x + size.x, pos.y));
			else
				Input::Input::SetCursorPosition(Pos(pos.x + currentCursorIndex, pos.y));

			return true;
		}

		return false;
	}

	template <class Owner>
	void InputField<Owner>::HandleInput(InputEvent input)
	{
		if (input.LeftPressed())
		{
			currentCursorIndex--;
			if (currentCursorIndex < 0)
				currentCursorIndex = 0;
		}
		else if (input.RightPressed())
		{
			currentCursorIndex++;
			if (currentCursorIndex >(int)text.textString.size())
				currentCursorIndex = (int)text.textString.size();
		}
		else if (input.GetVirtualKeyCode() == VK_BACK)
		{
			if (currentCursorIndex > 0)
			{
				text.textString.erase(text.textString.begin() + currentCursorIndex - 1);
				currentCursorIndex--;
			}
		}
		else if (input.GetVirtualKeyCode() == VK_DELETE)
		{
			if (currentCursorIndex < (int)text.textString.size())
			{
				text.textString.erase(text.textString.begin() + currentCursorIndex);
			}
		}
		else if (input.GetVirtualKeyCode() == VK_HOME)
		{
			currentCursorIndex = 0;
		}
		else if (input.GetVirtualKeyCode() == VK_END)
		{
			currentCursorIndex = (int)text.textString.size();
		}
		else if (IsAnInputKey(input))
		{
			text.textString.insert(text.textString.begin() + currentCursorIndex, input.GetAsciiChar());
			currentCursorIndex++;
		}
	}

	//Checks if the key pressed is an key you want to get the ascii code from.
	template <class Owner>
	bool InputField<Owner>::IsAnInputKey(InputEvent input)
	{
		if (input.GetVirtualKeyCode() == VK_SPACE ||
			(input.GetVirtualKeyCode() >= 0x30 && input.GetVirtualKeyCode() <= 0x39) || //top number keys
			(input.GetVirtualKeyCode() >= 0x41 && input.GetVirtualKeyCode() <= 0x5A) || //Letters
			(input.GetVirtualKeyCode() >= VK_NUMPAD0 && input.GetVirtualKeyCode() <= VK_DIVIDE) || //Numpad
			(input.GetVirtualKeyCode() >= VK_OEM_1 && input.GetVirtualKeyCode() <= VK_OEM_3) ||	//Miscellaneous keys
			(input.GetVirtualKeyCode() >= VK_OEM_4 && input.GetVirtualKeyCode() <= VK_OEM_8) ||	//Miscellaneous keys
			(input.GetVirtualKeyCode() == VK_OEM_102))
		{
			return true;
		}
		return false;

	}

	template <class Owner>
	void InputField<Owner>::FillRestOfField(char character)
	{
		int length = size.x - (int)text.textString.size();
		if (length > 0)
		{
			std::string spaces;
			for (int i = 0; i < length; i++)
				spaces.push_back(character);

			Text empty;
			if (active)
				empty = Text(spaces, selectedColor);
			else
				empty = Text(spaces, text.color);
			Pos emptyPos(pos.x + size.x - length, pos.y);
			Graphics::GraphicsAPI::PrintText(empty, emptyPos);
		}
	}

	template <class Owner>
	void InputField<Owner>::ClearText()
	{
		text.textString.clear();
	}

	template <class Owner>
	MenuItemType InputField<Owner>::GetType()
	{
		return MenuItemType_InputField;
	}
}

#endif