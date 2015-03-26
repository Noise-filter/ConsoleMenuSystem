#ifndef TEST_H
#define TEST_H

#include "Menu.h"
#include "Utility.h"

class Test
{
public:
	Test(){}

	~Test()
	{
		menu.DeleteAll();
	}

	void Init()
	{
		//Username
		menu.AddMenuItem(new MenuSystem::TextLabel(MenuSystem::Utility::Pos(80, 0), MenuSystem::Utility::Text("Username:", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(0, 0)));
		menu.AddMenuItem(new MenuSystem::InputField<Test*>(this, Test::asd, MenuSystem::Utility::Pos(80, 1), MenuSystem::Utility::Text("", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(20, 1), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		
		//Password
		menu.AddMenuItem(new MenuSystem::TextLabel(MenuSystem::Utility::Pos(80, 3), MenuSystem::Utility::Text("Password:", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(0, 0)));
		menu.AddMenuItem(new MenuSystem::InputFieldPassword<Test*>(this, Test::asd, MenuSystem::Utility::Pos(80, 4), MenuSystem::Utility::Text("", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(20, 1), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));

		//9 buttons
		menu.AddMenuItem(new MenuSystem::Button<Test*>(this, Test::asd, MenuSystem::Utility::Pos(5, 5), MenuSystem::Utility::Text("Test button", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(11,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		menu.AddMenuItem(new MenuSystem::Button<Test*>(this, Test::asd, MenuSystem::Utility::Pos(20, 10), MenuSystem::Utility::Text("Test button2", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(12,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		menu.AddMenuItem(new MenuSystem::Button<Test*>(this, Test::asd, MenuSystem::Utility::Pos(20, 5), MenuSystem::Utility::Text("Test button3", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(12,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		menu.AddMenuItem(new MenuSystem::Button<Test*>(this, Test::asd, MenuSystem::Utility::Pos(5, 10), MenuSystem::Utility::Text("Test button4", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(12,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		menu.AddMenuItem(new MenuSystem::Button<Test*>(this, Test::asd, MenuSystem::Utility::Pos(5, 15), MenuSystem::Utility::Text("Test button5", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(12,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		menu.AddMenuItem(new MenuSystem::Button<Test*>(this, Test::asd, MenuSystem::Utility::Pos(20, 15), MenuSystem::Utility::Text("Test button6", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(12,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		menu.AddMenuItem(new MenuSystem::Button<Test*>(this, Test::asd, MenuSystem::Utility::Pos(35, 5), MenuSystem::Utility::Text("Test button7", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(12,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		menu.AddMenuItem(new MenuSystem::Button<Test*>(this, Test::asd, MenuSystem::Utility::Pos(35, 10), MenuSystem::Utility::Text("Test button8", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(12,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		menu.AddMenuItem(new MenuSystem::Button<Test*>(this, Test::asd, MenuSystem::Utility::Pos(35, 15), MenuSystem::Utility::Text("Test button9", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(12,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		
		//Checkbox
		menu.AddMenuItem(new MenuSystem::Checkbox<Test*>(this, Test::asd, MenuSystem::Utility::Pos(0, 0), MenuSystem::Utility::Text("Checkbox", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(12,0), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red)));
		
		//Checkbox list
		std::vector<std::string> checkboxes;
		checkboxes.push_back("Checkbox 1");
		checkboxes.push_back("Checkbox 2");
		checkboxes.push_back("Checkbox 3");
		checkboxes.push_back("Checkbox 4");
		checkboxes.push_back("Checkbox 5");
		checkboxes.push_back("Hej");
		for (int i = 0; i < 255; i++)
		{
			checkboxes.push_back("Hej" + (char)i);
		}

		MenuSystem::CheckboxList<Test*>* asd = new MenuSystem::CheckboxList<Test*>(this, Test::asd, MenuSystem::Utility::Pos(0, 20), MenuSystem::Utility::Text("Checkbox List", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(20,5), MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_Green, MenuSystem::Utility::COLOR_Red));
		asd->SetItems(checkboxes);
		asd->AddItem("Hej", 2);
		asd->AddItem("Checkbox 5", 2);
		menu.AddMenuItem(asd);

		//Labels
		selected = new MenuSystem::TextLabel(MenuSystem::Utility::Pos(20, 20), MenuSystem::Utility::Text("", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos());
		lastDeselected = new MenuSystem::TextLabel(MenuSystem::Utility::Pos(20, 21), MenuSystem::Utility::Text("", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos());
		lastPressed = new MenuSystem::TextLabel(MenuSystem::Utility::Pos(20, 22), MenuSystem::Utility::Text("", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos());
		checkbox = new MenuSystem::TextLabel(MenuSystem::Utility::Pos(20, 23), MenuSystem::Utility::Text("Checkbox is not checked!", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos());
		fpsLabel = new MenuSystem::TextLabel(MenuSystem::Utility::Pos(20, 24), MenuSystem::Utility::Text("Fps: 0", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos());
		menu.AddMenuItem(selected);
		menu.AddMenuItem(lastDeselected);
		menu.AddMenuItem(lastPressed);
		menu.AddMenuItem(checkbox);
		menu.AddMenuItem(fpsLabel);

		for (int i = 0; i < 5; i++)
		{
			progressBars[i] = new MenuSystem::ProgressBar(MenuSystem::Utility::Pos(50, 20+(i*3)), MenuSystem::Utility::Text("", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(10 + i*3, 0));
			menu.AddMenuItem(progressBars[i]);
			valueLabels[i] = new MenuSystem::TextLabel(MenuSystem::Utility::Pos(50, 21+(i*3)), MenuSystem::Utility::Text("", MenuSystem::Utility::TextColor(MenuSystem::Utility::COLOR_White, MenuSystem::Utility::COLOR_Black)), MenuSystem::Utility::Pos(10, 1));
			menu.AddMenuItem(valueLabels[i]);
		}

		menu.Render();
	}

	bool Update(float fps)
	{
		InputEvent input = MenuSystem::API::GetInput();
		if(!menu.Update(input))
		{
			if(input.ExitPressed())
				return false;
		}

		char fpsText[15];
		_itoa_s((int)fps, fpsText, 10);
		fpsLabel->SetText(std::string("Fps: ") + fpsText);

		menu.Render();

		UpdateProgressBars();

		return true;
	} 

	static void asd(MenuSystem::ButtonEvent<Test*>& e)
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

public:
	MenuSystem::Menu menu;
	MenuSystem::TextLabel* selected;
	MenuSystem::TextLabel* lastDeselected;
	MenuSystem::TextLabel* lastPressed;

	MenuSystem::TextLabel* checkbox;
	MenuSystem::TextLabel* fpsLabel;

	MenuSystem::ProgressBar* progressBars[5];
	MenuSystem::TextLabel* valueLabels[5];

};

#endif