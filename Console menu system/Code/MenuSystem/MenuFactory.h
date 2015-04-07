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
		Menu CreateMenu(json::Value& v, Owner owner)
		{
			Menu menu;
			json::Array items;

			json::Value value = v["TextLabel"];
			if (value.GetType() != json::NULLVal)
			{
				items = v["TextLabel"];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateTextLabel(menu, it);
				}
			}

			value = v["ProgressBar"];
			if (value.GetType() != json::NULLVal)
			{
				items = v["ProgressBar"];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateProgressBar(menu, it);
				}
			}

			value = v["Button"];
			if (value.GetType() != json::NULLVal)
			{
				items = v["Button"];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateButton(menu, it, owner);
				}
			}

			value = v["Checkbox"];
			if (value.GetType() != json::NULLVal)
			{
				items = v["Checkbox"];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateCheckbox(menu, it, owner);
				}
			}

			value = v["InputField"];
			if (value.GetType() != json::NULLVal)
			{
				items = v["InputField"];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateInputField(menu, it, owner);
				}
			}

			value = v["InputFieldPassword"];
			if (value.GetType() != json::NULLVal)
			{
				items = v["InputFieldPassword"];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateInputFieldPassword(menu, it, owner);
				}
			}

			value = v["List"];
			if (value.GetType() != json::NULLVal)
			{
				items = v["List"];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateList(menu, it, owner);
				}
			}

			value = v["CheckboxList"];
			if (value.GetType() != json::NULLVal)
			{
				items = v["CheckboxList"];
				for (json::Array::ValueVector::iterator it = items.begin(); it != items.end(); it++)
				{
					CreateCheckboxList(menu, it, owner);
				}
			}

			return menu;
		}

		void CreateTextLabel(Menu& menu, json::Array::ValueVector::iterator it);
		void CreateProgressBar(Menu& menu, json::Array::ValueVector::iterator it);

		template <class Owner>
		void CreateButton(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			Button<Owner>* button = new Button<Owner>(owner, NULL);
			button->SetText(GetString(it, "text"));
			button->SetSize(GetSize(it));
			button->SetPosition(GetPos(it));
			button->SetColor(GetTextColor(it, "color"));
			button->SetSelectedColor(GetTextColor(it, "selectedColor"));
			menu.AddMenuItem(GetString(it, "uniqueName"), button);
		}

		template <class Owner>
		void CreateCheckbox(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			Checkbox<Owner>* checkbox = new Checkbox<Owner>(owner, NULL);
			checkbox->SetText(GetString(it, "text"));
			checkbox->SetSize(GetSize(it));
			checkbox->SetPosition(GetPos(it));
			checkbox->SetColor(GetTextColor(it, "color"));
			checkbox->SetSelectedColor(GetTextColor(it, "selectedColor"));
			checkbox->SetChecked(GetBool(it, "checked"));
			menu.AddMenuItem(GetString(it, "uniqueName"), checkbox);
		}

		template <class Owner>
		void CreateInputField(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			InputField<Owner>* inputField = new InputField<Owner>(owner, NULL);
			inputField->SetText(GetString(it, "text"));
			inputField->SetSize(GetSize(it));
			inputField->SetPosition(GetPos(it));
			inputField->SetColor(GetTextColor(it, "color"));
			inputField->SetSelectedColor(GetTextColor(it, "selectedColor"));
			menu.AddMenuItem(GetString(it, "uniqueName"), inputField);
		}

		template <class Owner>
		void CreateInputFieldPassword(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			InputFieldPassword<Owner>* inputField = new InputFieldPassword<Owner>(owner, NULL);
			inputField->SetText(GetString(it, "text"));
			inputField->SetSize(GetSize(it));
			inputField->SetPosition(GetPos(it));
			inputField->SetColor(GetTextColor(it, "color"));
			inputField->SetSelectedColor(GetTextColor(it, "selectedColor"));
			menu.AddMenuItem(GetString(it, "uniqueName"), inputField);
		}

		template <class Owner>
		void CreateList(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			List<Owner>* list = new List<Owner>(owner, NULL);
			list->SetText(GetString(it, "text"));
			list->SetSize(GetSize(it));
			list->SetPosition(GetPos(it));
			list->SetColor(GetTextColor(it, "color"));
			list->SetSelectedColor(GetTextColor(it, "selectedColor"));
			list->SetItems(GetStrings(it, "items"));
			menu.AddMenuItem(GetString(it, "uniqueName"), list);
		}

		template <class Owner>
		void CreateCheckboxList(Menu& menu, json::Array::ValueVector::iterator it, Owner owner)
		{
			CheckboxList<Owner>* list = new CheckboxList<Owner>(owner, NULL);
			list->SetText(GetString(it, "text"));
			list->SetSize(GetSize(it));
			list->SetPosition(GetPos(it));
			list->SetColor(GetTextColor(it, "color"));
			list->SetSelectedColor(GetTextColor(it, "selectedColor"));
			list->SetItems(GetStrings(it, "items"));
			menu.AddMenuItem(GetString(it, "uniqueName"), list);
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