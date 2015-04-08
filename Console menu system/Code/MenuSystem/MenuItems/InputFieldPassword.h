#ifndef INPUT_FIELD_PASSWORD_H
#define INPUT_FIELD_PASSWORD_H

namespace MenuSystem
{
	template <class Owner>
	class InputFieldPassword : public InputField<Owner>
	{
	public:
		InputFieldPassword(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
			const Utility::TextColor selectedColor = Utility::TextColor());
		virtual ~InputFieldPassword();

		void Render();

		virtual MenuItemType GetType();

	private:
		std::string GetStarString();

	};

	template <class Owner>
	InputFieldPassword<Owner>::InputFieldPassword(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos, const Utility::Text& text, const Utility::Pos& size, const Utility::TextColor selectedColor)
		: InputField(owner, callbackFunction, pos, text, size, selectedColor)
	{
		currentCursorIndex = -1;
	}

	template <class Owner>
	InputFieldPassword<Owner>::~InputFieldPassword()
	{

	}

	template <class Owner>
	void InputFieldPassword<Owner>::Render()
	{
		if (visible)
		{
			std::string stars = GetStarString();

			if (active)
			{
				if (currentCursorIndex >= 0 && currentCursorIndex > size.x)
				{
					Graphics::GraphicsAPI::PrintText(Text(stars, selectedColor), pos, size);
				}
				else
				{
					Graphics::GraphicsAPI::PrintText(Text(stars, selectedColor), pos, size);
				}

				FillRestOfField(' ');
			}
			else
			{
				Graphics::GraphicsAPI::PrintText(Text(stars, text.color), pos, size);

				FillRestOfField('_');
			}
		}
	}

	template <class Owner>
	std::string InputFieldPassword<Owner>::GetStarString()
	{
		std::string str;
		for (int i = 0; i < (int)text.textString.size(); i++)
		{
			str += '*';
		}
		return str;
	}

	template <class Owner>
	MenuItemType InputFieldPassword<Owner>::GetType()
	{
		return MenuItemType_InputFieldPassword;
	}
}

#endif