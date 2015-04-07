#ifndef MENU_FACTORY_H
#define MENU_FACTORY_H

#include "Menu.h"
#include "Json\json.h"

namespace MenuSystem
{
	class MenuFactory
	{
	public:
		template <class Owner>
		static Menu Create(std::string filename, Owner owner)
		{
			MenuFactory factory;

			std::string jsonFile = factory.ReadFile(filename);
			if (jsonFile.empty())
			{
				return Menu();
			}

			json::Value v = json::Deserialize(jsonFile);

			if (v.GetType() == json::NULLVal)
			{
				return Menu();
			}

			return factory.CreateMenu(v, owner);
		}


	private:
		std::string ReadFile(std::string filename);


		template <class Owner>
		void CreateNonInteractiveMenuItem(Menu& menu, json::Value& v, Owner owner, std::string menuItem, void(*CreateFunction)(Menu&, json::Array::ValueVector::iterator))
		{
			json::Value value = v[menuItem];
			if (value.GetType() != json::NULLVal)
			{
				json::Array items = v[menuItem];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateFunction(menu, it);
				}
			}
		}

		template <class Owner>
		void CreateInteractiveMenuItem(Menu& menu, json::Value& v, Owner owner, std::string menuItem, void(*CreateFunction)(Menu&, json::Array::ValueVector::iterator, Owner))
		{
			json::Value value = v[menuItem];
			if (value.GetType() != json::NULLVal)
			{
				json::Array items = v[menuItem];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateFunction(menu, it, owner);
				}
			}
		}

		template <class Owner>
		Menu CreateMenu(json::Value& v, Owner owner)
		{
			Menu menu;
			json::Array items;

			CreateNonInteractiveMenuItem<Owner>(menu, v, owner, "TextLabel", (MenuFactory::CreateTextLabel));
			CreateNonInteractiveMenuItem<Owner>(menu, v, owner, "ProgressBar", (MenuFactory::CreateProgressBar));

			CreateInteractiveMenuItem<Owner>(menu, v, owner, "Button", (MenuFactory::CreateButton));
			CreateInteractiveMenuItem<Owner>(menu, v, owner, "Checkbox", (MenuFactory::CreateCheckbox));
			CreateInteractiveMenuItem<Owner>(menu, v, owner, "InputField", (MenuFactory::CreateInputField));
			CreateInteractiveMenuItem<Owner>(menu, v, owner, "InputFieldPassword", (MenuFactory::CreateInputFieldPassword));
			CreateInteractiveMenuItem<Owner>(menu, v, owner, "List", (MenuFactory::CreateList));
			CreateInteractiveMenuItem<Owner>(menu, v, owner, "CheckboxList", (MenuFactory::CreateCheckboxList));

			return menu;
		}

		static void CreateTextLabel(Menu& menu, json::Array::ValueVector::iterator it);
		static void CreateProgressBar(Menu& menu, json::Array::ValueVector::iterator it);

		template <class Owner>
		static void CreateButton(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			MenuFactory factory;
			Button<Owner>* button = new Button<Owner>(owner, NULL);
			button->SetText(factory.GetString(it, "text"));
			button->SetSize(factory.GetSize(it));
			button->SetPosition(factory.GetPos(it));
			button->SetColor(factory.GetTextColor(it, "color"));
			button->SetSelectedColor(factory.GetTextColor(it, "selectedColor"));
			menu.AddMenuItem(factory.GetString(it, "uniqueName"), button);
		}

		template <class Owner>
		static void CreateCheckbox(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			MenuFactory factory;
			Checkbox<Owner>* checkbox = new Checkbox<Owner>(owner, NULL);
			checkbox->SetText(factory.GetString(it, "text"));
			checkbox->SetSize(factory.GetSize(it));
			checkbox->SetPosition(factory.GetPos(it));
			checkbox->SetColor(factory.GetTextColor(it, "color"));
			checkbox->SetSelectedColor(factory.GetTextColor(it, "selectedColor"));
			checkbox->SetChecked(factory.GetBool(it, "checked"));
			menu.AddMenuItem(factory.GetString(it, "uniqueName"), checkbox);
		}

		template <class Owner>
		static void CreateInputField(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			MenuFactory factory;
			InputField<Owner>* inputField = new InputField<Owner>(owner, NULL);
			inputField->SetText(factory.GetString(it, "text"));
			inputField->SetSize(factory.GetSize(it));
			inputField->SetPosition(factory.GetPos(it));
			inputField->SetColor(factory.GetTextColor(it, "color"));
			inputField->SetSelectedColor(factory.GetTextColor(it, "selectedColor"));
			menu.AddMenuItem(factory.GetString(it, "uniqueName"), inputField);
		}

		template <class Owner>
		static void CreateInputFieldPassword(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			MenuFactory factory;
			InputFieldPassword<Owner>* inputField = new InputFieldPassword<Owner>(owner, NULL);
			inputField->SetText(factory.GetString(it, "text"));
			inputField->SetSize(factory.GetSize(it));
			inputField->SetPosition(factory.GetPos(it));
			inputField->SetColor(factory.GetTextColor(it, "color"));
			inputField->SetSelectedColor(factory.GetTextColor(it, "selectedColor"));
			menu.AddMenuItem(factory.GetString(it, "uniqueName"), inputField);
		}

		template <class Owner>
		static void CreateList(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			MenuFactory factory;
			List<Owner>* list = new List<Owner>(owner, NULL);
			list->SetText(factory.GetString(it, "text"));
			list->SetSize(factory.GetSize(it));
			list->SetPosition(factory.GetPos(it));
			list->SetColor(factory.GetTextColor(it, "color"));
			list->SetSelectedColor(factory.GetTextColor(it, "selectedColor"));
			list->SetItems(factory.GetStrings(it, "items"));
			menu.AddMenuItem(factory.GetString(it, "uniqueName"), list);
		}

		template <class Owner>
		static void CreateCheckboxList(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			MenuFactory factory;
			CheckboxList<Owner>* list = new CheckboxList<Owner>(owner, NULL);
			list->SetText(factory.GetString(it, "text"));
			list->SetSize(factory.GetSize(it));
			list->SetPosition(factory.GetPos(it));
			list->SetColor(factory.GetTextColor(it, "color"));
			list->SetSelectedColor(factory.GetTextColor(it, "selectedColor"));
			list->SetItems(factory.GetStrings(it, "items"));
			menu.AddMenuItem(factory.GetString(it, "uniqueName"), list);
		}

		Utility::Pos GetPos(json::Array::ValueVector::iterator it);
		Utility::Pos GetSize(json::Array::ValueVector::iterator it);
		Utility::TextColor GetTextColor(json::Array::ValueVector::iterator it, std::string name);
		Utility::Color GetColor(json::Value jsonColor, std::string name);
		std::string GetString(json::Array::ValueVector::iterator it, const std::string name);
		std::vector<std::string> GetStrings(json::Array::ValueVector::iterator it, const std::string name);
		bool GetBool(json::Array::ValueVector::iterator it, const std::string name);

	private:

	};
}

#endif