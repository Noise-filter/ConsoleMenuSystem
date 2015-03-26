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

namespace MenuSystem
{
	class Menu
	{
	public:
		Menu();
		virtual ~Menu();

		bool Update(InputEvent input);
		void Render();

		void AddMenuItem(MenuItem::MenuItem* item);
		void RemoveMenuItem(MenuItem::MenuItem* item);
		void Clear();

		/* 
		* Will use 'delete' on all entries to the menu interactive and non interactive items. And clear the arrays.
		* !Warning only use this if you know that all entries are dynamically allocated with new.
		*/
		void DeleteAll();

		void SetVisible(bool visible);

		bool IsVisible();

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
		int FindItem(const MenuItem::MenuItem* item);

		void SetAsActive(int index);
		int FindNextMenu(const Direction dir);

		

	protected:
		bool visible;
		MenuItem::MenuItem* activeMenuItem;

		std::vector<MenuItem::MenuItem*> menuItems;
		std::vector<MenuItem::MenuItem*> nonInteractive;

	};
}

#endif