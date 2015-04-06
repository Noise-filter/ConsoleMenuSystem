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

#include <vector>
#include <map>

namespace MenuSystem
{
	class Menu
	{
	public:
		Menu();
		virtual ~Menu();

		bool Update(InputEvent input);
		void Render();

		MenuItem::MenuItem* GetMenuItem(const std::string uniqueName);
		void AddMenuItem(const std::string uniqueName, MenuItem::MenuItem* item);
		void RemoveMenuItem(const std::string uniqueName);
		void Clear();

		template <class Owner>
		void SetCallbackFunction(void(*EventFunc)(MenuSystem::ButtonEvent<Owner>&))
		{
			for (std::map<std::string, MenuItem::MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
			{
				((Button<Owner>*)it->second)->SetEventCallback(EventFunc);
			}
		}

		/* 
		* Will use 'delete' on all entries to the menu interactive and non interactive items. And clear the arrays.
		* !Warning only use this if you know that all entries are dynamically allocated with new.
		*/
		void DeleteAll();

		void SetVisible(bool visible);

		bool IsVisible();

		Menu& operator=(const Menu& menu);

	private:
		enum Direction
		{
			UP,
			RIGHT,
			DOWN,
			LEFT,
		};

		//Returns the index the item is at in the array.
		//Returns -1 if it can't find it.
		MenuItem::MenuItem* FindItem(const MenuItem::MenuItem* item);
		MenuItem::MenuItem* FindItem(const std::string uniqueName);

		void SetAsActive(MenuItem::MenuItem* item);
		MenuItem::MenuItem* FindNextMenu(const Direction dir);

	protected:
		bool visible;
		MenuItem::MenuItem* activeMenuItem;

		std::map<std::string, MenuItem::MenuItem*> menuItems;
		std::map<std::string, MenuItem::MenuItem*> nonInteractive;

	};
}

#endif