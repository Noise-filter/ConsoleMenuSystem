#ifndef MENU_H
#define MENU_H

#include "MenuItems\MenuItem.h"
#include "MenuItems\TextLabel.h"
#include "MenuItems\Button.h"
#include "MenuItems\Checkbox.h"
#include "MenuItems\List.h"
#include "MenuItems\CheckboxList.h"
#include "MenuItems\InputField.h"
#include "MenuItems\InputFieldPassword.h"
#include "MenuItems\ProgressBar.h"
#include "MenuItems\DrawArea.h"
#include "MenuItems\Sprite.h"

#include <vector>
#include <map>
#include <memory>

namespace MenuSystem
{
	class Menu
	{
	public:
		Menu() : visible(true) {}

		bool Update(InputEvent input);
		void Render();

		std::shared_ptr<MenuItem::MenuItem> GetMenuItem(const std::string& uniqueName);
		void AddMenuItem(const std::string& uniqueName, std::shared_ptr<MenuItem::MenuItem> item);
		void RemoveMenuItem(const std::string& uniqueName);
		void Clear();

		template <class Owner>
		void SetCallbackFunction(void(*EventFunc)(MenuSystem::ButtonEvent<Owner>&))
		{
			for (const auto& it : menuItems)
			{
				std::static_pointer_cast<MenuSystem::Button<Owner>>(it.second)->SetEventCallback(EventFunc);
			}
		}

		void SetVisible(bool visible);

		bool IsVisible();

		bool IsEmpty();

	private:
		enum Direction
		{
			UP,
			RIGHT,
			DOWN,
			LEFT,
		};

		std::shared_ptr<MenuItem::MenuItem> FindItem(const std::shared_ptr<MenuItem::MenuItem>& item);
		std::shared_ptr<MenuItem::MenuItem> FindItem(const std::string& uniqueName);

		void SetAsActive(std::shared_ptr<MenuItem::MenuItem> item);
		std::shared_ptr<MenuItem::MenuItem> FindNextMenu(Direction dir);

	protected:
		std::map<std::string, std::shared_ptr<MenuItem::MenuItem>> menuItems;
		std::map<std::string, std::shared_ptr<MenuItem::MenuItem>> nonInteractive;

		std::shared_ptr<MenuItem::MenuItem> activeMenuItem;
		bool visible;

	};
}

#endif