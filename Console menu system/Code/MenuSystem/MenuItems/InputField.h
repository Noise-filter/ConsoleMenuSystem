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
		bool Update(char input);

		void ClearText();

	private:
		void HandleInput(char input);
		void JumpToEnd();

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

				int length = size.x - text.textString.size();
				if (length > 0)
				{
					std::string spaces;
					for (int i = 0; i < length; i++)
						spaces.push_back(' ');
					Text empty(spaces, selectedColor);
					Pos emptyPos(pos.x + size.x - length, pos.y);
					Graphics::GraphicsAPI::PrintText(empty, emptyPos);
				}
			}
			else
			{	
				Graphics::GraphicsAPI::PrintText(text, pos, size);

				int length = size.x - text.textString.size();
				if (length > 0)
				{
					std::string spaces;
					for (int i = 0; i < length; i++)
						spaces.push_back('_');
					Text empty(spaces, text.color);
					Pos emptyPos(pos.x + size.x - length, pos.y);
					Graphics::GraphicsAPI::PrintText(empty, emptyPos);
				}
			}
		}
	}

	template <class Owner>
	bool InputField<Owner>::Update(char input)
	{
		if (currentCursorIndex == -1)
		{
			if (input == 13) //Enter
			{
				Input::Input::SetCursorVisibility(true);
				currentCursorIndex = 0;
				Input::Input::SetCursorPosition(pos);
				return true;
			}
		}
		else
		{
			if (input == 27) //Escape
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
	void InputField<Owner>::HandleInput(char input)
	{
		if (input > 0 && input < 32)
		{
			if (input == 8)
			{
				if (currentCursorIndex > 0)
				{
					text.textString.erase(text.textString.begin() + currentCursorIndex - 1);
					currentCursorIndex--;
				}
			}
		}
		else if (input >= 32 && input < 127)
		{
			if (input == '1')
			{
				currentCursorIndex--;
				if (currentCursorIndex < 0)
					currentCursorIndex = 0;
			}
			else if (input == '2')
			{
				currentCursorIndex++;
				if (currentCursorIndex >(int)text.textString.size())
					currentCursorIndex = text.textString.size();
			}
			else
			{
				text.textString.insert(text.textString.begin() + currentCursorIndex, input);
				currentCursorIndex++;
			}
		}
		else
		{

		}
	}

	template <class Owner>
	void InputField<Owner>::ClearText()
	{
		text.textString.clear();
	}

	template <class Owner>
	void InputField<Owner>::JumpToEnd()
	{

	}
}

#endif