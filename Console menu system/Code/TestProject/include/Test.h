#ifndef TEST_H
#define TEST_H

#include "Menu.h"
#include "Utility.h"
#include "MenuFactory.h"

class Test
{
public:
	~Test()
	{
		jsonMenu.DeleteAll();
	}

	void Init()
	{
		jsonMenu = MenuSystem::MenuFactory::Create("json/test.txt", this);

		jsonMenu.SetCallbackFunction<Test*>(Test::callbackFunction);
		
		//Labels
		selected = (MenuSystem::TextLabel*)jsonMenu.GetMenuItem("selectedLabel");
		lastDeselected = (MenuSystem::TextLabel*)jsonMenu.GetMenuItem("lastDeselectedLabel");
		lastPressed = (MenuSystem::TextLabel*)jsonMenu.GetMenuItem("lastPressedLabel");
		checkbox = (MenuSystem::TextLabel*)jsonMenu.GetMenuItem("checkboxLabel");
		fpsLabel = (MenuSystem::TextLabel*)jsonMenu.GetMenuItem("fpsLabel");

		for (int i = 0; i < 5; i++)
		{
			std::string barName = "ProgressBar " + std::to_string(i+1);
			std::string labelName = "ProgressBarLabel " + std::to_string(i + 1);
			progressBars[i] = (MenuSystem::ProgressBar*)(jsonMenu.GetMenuItem(barName));
			valueLabels[i] = (MenuSystem::TextLabel*)jsonMenu.GetMenuItem(labelName);
		}

		drawArea = (MenuSystem::DrawArea*)jsonMenu.GetMenuItem("DrawArea");
		drawArea->Fill(' ', MenuSystem::Utility::TextColor());

		sprite = (MenuSystem::Sprite*)jsonMenu.GetMenuItem("Sprite");

		jsonMenu.Render();
	}

	bool Update(float fps)
	{
		InputEvent input = MenuSystem::API::GetInput();
		if (!jsonMenu.Update(input))
		{
			if(input.ExitPressed())
				return false;
		}

		if (fps < 0)
			fps = 0;
		fpsLabel->SetText("Fps: " + std::to_string((int)fps));

		UpdateProgressBars();

		updateDrawArea();

		jsonMenu.Render();

		return true;
	} 

	static void callbackFunction(MenuSystem::ButtonEvent<Test*>& e)
	{
		if(e.state == MenuSystem::ButtonState_Selected)
			e.owner->selected->SetText("Selected: " + e.sender->GetText());
		else if(e.state == MenuSystem::ButtonState_None)
			e.owner->lastDeselected->SetText("Last deselected: " + e.sender->GetText());
		else if(e.state == MenuSystem::ButtonState_Pressed)
			e.owner->lastPressed->SetText("Last pressed: " + e.sender->GetText()); 
		
		if(e.sender->GetType() == MenuSystem::MenuItemType_Checkbox)
		{
			if(((MenuSystem::Checkbox<Test*>*)e.sender)->IsChecked())
				e.owner->checkbox->SetText("Checkbox is checked!");
			else
				e.owner->checkbox->SetText("Checkbox is not checked!");
		}
	}

	void UpdateProgressBars()
	{
		for (int i = 0; i < 5; i++)
		{
			if (progressBars[i]->IsFull())
			{
				progressBars[i]->Reset();
			}
			else
			{
				progressBars[i]->AddProgressValue(0.0001f * (i+1));
			}

			std::string valueText = std::to_string(progressBars[i]->GetProgressValue());
			valueLabels[i]->SetText(valueText);
		}
	}

	void updateDrawArea()
	{
		MenuSystem::Utility::Pos pos(rand() % drawArea->GetSize().x, rand() % drawArea->GetSize().y);
		if (rand() % 2 == 0)
		{
			drawArea->SetCharacter('X', pos);
		}
		else
		{
			drawArea->SetCharacter(' ', pos);
		}
	}

public:
	MenuSystem::Menu jsonMenu;

	MenuSystem::TextLabel* selected;
	MenuSystem::TextLabel* lastDeselected;
	MenuSystem::TextLabel* lastPressed;

	MenuSystem::TextLabel* checkbox;
	MenuSystem::TextLabel* fpsLabel;

	MenuSystem::ProgressBar* progressBars[5];
	MenuSystem::TextLabel* valueLabels[5];

	MenuSystem::DrawArea* drawArea;
	MenuSystem::Sprite* sprite;
};

#endif