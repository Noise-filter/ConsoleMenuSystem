#ifndef BUTTON_H
#define BUTTON_H

#include "TextLabel.h"
#include "Utility.h"
#include "Graphics.h"

namespace MenuSystem
{
	enum ButtonState
	{
		ButtonState_None,
		ButtonState_Selected,
		ButtonState_Pressed,

		ButtonState_Count,
		ButtonState_Unknown = -1
	};

	template <typename Owner>
	struct ButtonEvent
	{
		ButtonState state;
		TextLabel* sender;
		Owner owner;
		void* userData;
	};

	template <class Owner>
	class Button : public TextLabel
	{
	public:
		typedef void (*EventFunc)(MenuSystem::ButtonEvent<Owner>& e);
		Button(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
			const Utility::TextColor selectedColor = Utility::TextColor());
		~Button();

		virtual void Render();
		virtual bool Update(InputEvent input);

		virtual void SendEventCallback(const ButtonState state);

		virtual void SetActive(const bool active);
		void SetSelectedColor(const Utility::TextColor selectedColor);
		void SetButtonState(ButtonState state);
		virtual void SetEventCallback(EventFunc func);
		void SetOwner(Owner owner);
		void SetUserData(void* userData);

		Utility::TextColor GetSelectedColor();
		ButtonState GetButtonState();
		//EventFunc GetEventCallback();
		Owner GetOwner();
		void* GetUserData();
		virtual MenuItemType GetType();
		virtual bool IsInteractive() const;

	protected:
		Utility::TextColor selectedColor;

		ButtonState currentState;
		EventFunc eventCallback;
		Owner owner;
		void* userData;

	};
	
	template <class Owner>
	Button<Owner>::Button(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos, const Utility::Text& text, const Utility::Pos& size,
			const Utility::TextColor selectedColor)
			: owner(owner), eventCallback(callbackFunction), TextLabel(pos, text, size), selectedColor(selectedColor)
	{

	}
	
	template <class Owner>
	Button<Owner>::~Button()
	{}

	template <class Owner>
	void Button<Owner>::Render()
	{
		if(visible)
		{
			if(active)
			{
				Graphics::GraphicsAPI::PrintText(Utility::Text(text.textString, selectedColor), pos, size);
			}
			else
			{
				Graphics::GraphicsAPI::PrintText(text, pos, size);
			}
		}
	}
	
	template <class Owner>
	bool Button<Owner>::Update(InputEvent input)
	{
		if(input.EnterPressed())
		{
			//Send event
			SendEventCallback(ButtonState_Pressed);
			return true;
		}
		return false;
	}
		
	template <class Owner>
	void Button<Owner>::SendEventCallback(const ButtonState state)
	{
		if(eventCallback)
		{
			ButtonEvent<Owner> e;
			e.userData = userData;
			e.owner = owner;
			e.sender = this;
			e.state = state;

			eventCallback(e);
		}
	}

	/****************************
				Set
	****************************/
	template <class Owner>
	void Button<Owner>::SetActive(const bool active)
	{
		this->active = active;

		if(this->active) SendEventCallback(ButtonState_Selected);
		else SendEventCallback(ButtonState_None);
	}

	template <class Owner>
	void Button<Owner>::SetSelectedColor(const Utility::TextColor color) { this->selectedColor = color; }

	template <class Owner>
	void Button<Owner>::SetButtonState(ButtonState state) { this->currentState = state; }

	template <class Owner>
	void Button<Owner>::SetEventCallback(EventFunc func) { this->eventCallback = func; }

	template <class Owner>
	void Button<Owner>::SetOwner(Owner owner) { this->owner = owner; }

	template <class Owner>
	void Button<Owner>::SetUserData(void* userData) { this->userData = userData; }

	/****************************
				Get
	****************************/
	template <class Owner>
	Utility::TextColor Button<Owner>::GetSelectedColor() { return selectedColor; }

	template <class Owner>
	ButtonState Button<Owner>::GetButtonState() { return currentState; }

	//template <class Owner>
	//EventFunc Button<Owner>::GetEventCallback() { return eventCallback; }

	template <class Owner>
	Owner Button<Owner>::GetOwner() { return owner; }

	template <class Owner>
	void* Button<Owner>::GetUserData() { return userData; }
	
	template <class Owner>
	MenuItemType Button<Owner>::GetType() { return MenuItemType_Button; }
	
	template <class Owner>
	bool Button<Owner>::IsInteractive() const { return true; }
}

#endif