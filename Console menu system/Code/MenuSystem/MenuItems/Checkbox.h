#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Button.h"
namespace MenuSystem
{
	template <class Owner>
	class Checkbox : public Button<Owner>
	{
	public:
		Checkbox(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
			const Utility::TextColor selectedColor = Utility::TextColor(), bool checked = false);
		virtual ~Checkbox();

		void Render();
		bool Update(InputEvent input);

		void SetChecked(bool checked);
	
		bool IsChecked();
		virtual MenuItemType GetType();

	private:
		bool checked;

	};

	template <class Owner>
	Checkbox<Owner>::Checkbox(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos, const Utility::Text& text, const Utility::Pos& size,
			const Utility::TextColor selectedColor, bool checked)
			: Button(owner, callbackFunction, pos, text, size, selectedColor), checked(checked)
	{}

	template <class Owner>
	Checkbox<Owner>::~Checkbox()
	{}

	template <class Owner>
	void Checkbox<Owner>::Render()
	{
		if(visible)
		{
			if(active)
			{
				if(checked)
					Graphics::GraphicsAPI::PrintText(Utility::Text("[X] " + text.textString, selectedColor), pos, size);
				else
					Graphics::GraphicsAPI::PrintText(Utility::Text("[ ] " + text.textString, selectedColor), pos, size);
			}
			else
			{
				if(checked)
					Graphics::GraphicsAPI::PrintText(Utility::Text("[X] " + text.textString, text.color), pos, size);
				else
					Graphics::GraphicsAPI::PrintText(Utility::Text("[ ] " + text.textString, text.color), pos, size);
			}
		}
	}

	template <class Owner>
	bool Checkbox<Owner>::Update(InputEvent input)
	{
		if (input.EnterPressed())
		{
			checked = !checked;

			SendEventCallback(ButtonState_Pressed);

			return true;
		}
		return false;
	}

	template <class Owner>
	void Checkbox<Owner>::SetChecked(bool checked) { this->checked = checked; }

	template <class Owner>
	bool Checkbox<Owner>::IsChecked() { return checked; }

	template <class Owner>
	MenuItemType Checkbox<Owner>::GetType() { return MenuItemType_Checkbox; }
}

#endif