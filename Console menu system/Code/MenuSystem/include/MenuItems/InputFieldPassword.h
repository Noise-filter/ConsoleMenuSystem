#ifndef INPUT_FIELD_PASSWORD_H
#define INPUT_FIELD_PASSWORD_H

namespace MenuSystem
{
	template <class Owner>
	class InputFieldPassword : public InputField<Owner>
	{
	public:
		InputFieldPassword(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
			const Utility::TextColor selectedColor = Utility::TextColor())
			: InputField(owner, callbackFunction, pos, text, size, selectedColor) {}
		virtual ~InputFieldPassword() = default;

		void Render();

		virtual MenuItemType GetType();

	private:
		std::string GetStarString();

	};

	template <class Owner>
	void InputFieldPassword<Owner>::Render()
	{
		if (visible)
		{
			std::string stars = GetStarString();
			if (active)
			{
				Graphics::GraphicsAPI::PrintText(Utility::Text(stars + GetRemainingCharacters(' '), selectedColor), pos, size);
			}
			else
			{
				Graphics::GraphicsAPI::PrintText(Utility::Text(stars + GetRemainingCharacters('_'), text.color), pos, size);
			}
		}
	}

	template <class Owner>
	std::string InputFieldPassword<Owner>::GetStarString()
	{
		return std::string(text.textString.size(), '*');
	}

	template <class Owner>
	MenuItemType InputFieldPassword<Owner>::GetType()
	{
		return MenuItemType_InputFieldPassword;
	}
}

#endif