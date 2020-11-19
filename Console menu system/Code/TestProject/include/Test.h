#ifndef TEST_H
#define TEST_H

#include "Menu.h"
#include "Utility.h"
#include "MenuFactory.h"

#include <filesystem>
namespace fs = std::filesystem;

class Test
{
public:
	void Init()
	{
		jsonMenu = MenuSystem::MenuFactory::Create("json/test.txt", this);
		jsonMenu.SetCallbackFunction<Test*>(Test::callbackFunction);

		//Labels
		selected = std::static_pointer_cast<MenuSystem::TextLabel>(jsonMenu.GetMenuItem("selectedLabel"));
		lastDeselected = std::static_pointer_cast<MenuSystem::TextLabel>(jsonMenu.GetMenuItem("lastDeselectedLabel"));
		lastPressed = std::static_pointer_cast<MenuSystem::TextLabel>(jsonMenu.GetMenuItem("lastPressedLabel"));
		checkbox = std::static_pointer_cast<MenuSystem::TextLabel>(jsonMenu.GetMenuItem("checkboxLabel"));
		fpsLabel = std::static_pointer_cast<MenuSystem::TextLabel>(jsonMenu.GetMenuItem("fpsLabel"));

		for (int i = 0; i < 5; i++)
		{
			std::string barName = "ProgressBar " + std::to_string(i + 1);
			std::string labelName = "ProgressBarLabel " + std::to_string(i + 1);
			progressBars[i] = std::static_pointer_cast<MenuSystem::ProgressBar>(jsonMenu.GetMenuItem(barName));
			valueLabels[i] = std::static_pointer_cast<MenuSystem::TextLabel>(jsonMenu.GetMenuItem(labelName));
		}

		drawArea = std::static_pointer_cast<MenuSystem::DrawArea>(jsonMenu.GetMenuItem("DrawArea"));
		drawArea->Fill(' ', MenuSystem::Utility::TextColor());

		fileList = std::static_pointer_cast<MenuSystem::List<Test*>>(jsonMenu.GetMenuItem("File list"));
		updateFileList();

		jsonMenu.Render();
	}

	bool Update(float fps)
	{
		InputEvent input = MenuSystem::API::GetInput();
		if (!jsonMenu.Update(input))
		{
			if (input.ExitPressed())
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
		if (e.state == MenuSystem::ButtonState_Selected)
			e.owner->selected->SetText("Selected: " + e.sender->GetText());
		else if (e.state == MenuSystem::ButtonState_None)
			e.owner->lastDeselected->SetText("Last deselected: " + e.sender->GetText());
		else if (e.state == MenuSystem::ButtonState_Pressed)
			e.owner->lastPressed->SetText("Last pressed: " + e.sender->GetText());

		if (e.state == MenuSystem::ButtonState_Pressed)
		{

		}

		if (e.sender->GetType() == MenuSystem::MenuItemType_Checkbox)
		{
			if (std::static_pointer_cast<MenuSystem::Checkbox<Test*>>(e.sender)->IsChecked())
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
				progressBars[i]->AddProgressValue(0.0001f * (i + 1));
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

	void updateFileList() {
		fileList->Clear();
		for (const auto& p : fs::recursive_directory_iterator(fs::current_path())) {
			fileList->AddItem(p.path().filename().string());
		}
	}

public:
	MenuSystem::Menu jsonMenu;

	std::shared_ptr<MenuSystem::TextLabel> selected;
	std::shared_ptr<MenuSystem::TextLabel> lastDeselected;
	std::shared_ptr<MenuSystem::TextLabel> lastPressed;

	std::shared_ptr<MenuSystem::TextLabel> checkbox;
	std::shared_ptr<MenuSystem::TextLabel> fpsLabel;

	std::array<std::shared_ptr<MenuSystem::ProgressBar>, 5> progressBars;
	std::array<std::shared_ptr<MenuSystem::TextLabel>, 5> valueLabels;

	std::shared_ptr<MenuSystem::DrawArea> drawArea;

	std::shared_ptr<MenuSystem::List<Test*>> fileList;
};

#endif