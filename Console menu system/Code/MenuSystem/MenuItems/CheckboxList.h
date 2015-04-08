#ifndef CHECKBOX_LIST_H
#define CHECKBOX_LIST_H

#include "List.h"
#include "Button.h"
#include "Checkbox.h"

namespace MenuSystem
{
	template <class Owner>
	class CheckboxList : public List<Owner>
	{
	public:
		CheckboxList(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
				const Utility::TextColor selectedColor = Utility::TextColor());
		virtual ~CheckboxList();

		/*
		* Adds an additional checkbox to the list. Won't add the checkbox if there is an existing with the same name.
		* @name: The name the checkbox should use. Can't be the same as another checkbox in the same list.
		* @index[optional]: The position the new checkbox should be inserted at. If the index does not exist it will be placed last.
		*/
		void AddItem(std::string name, int index = -1);

		virtual void SetItems(std::vector<std::string>& items);

		void Check(int index);
		void Uncheck(int index);
		void CheckAll();
		void UncheckAll();

		bool IsNoneChecked();
		bool IsAllChecked();
		bool IsChecked(int index);

		/*
		* Return the number of checkboxes that are checked.
		*/
		int GetNumberOfChecked();
		virtual MenuItemType GetType();

	private:
		
	};
	
	template <class Owner>
	CheckboxList<Owner>::CheckboxList(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
			const Utility::TextColor selectedColor = Utility::TextColor())
			: List(owner, callbackFunction, pos, text, size, selectedColor)
	{}

	template <class Owner>
	CheckboxList<Owner>::~CheckboxList()
	{}

	template <class Owner>
	void CheckboxList<Owner>::AddItem(std::string name, int index)
	{
		if(FindMenuItem(name) == -1)
		{
			if(index < 0 || index > GetNumberOfItems()-1)
			{
				index = GetNumberOfItems();
			}
			Checkbox<Owner>* checkbox = new Checkbox<Owner>(owner, eventCallback, Utility::Pos(), Utility::Text(name), Utility::Pos(size.x, 1), selectedColor, false);
			menuItems.insert(menuItems.begin() + index, checkbox);
			listEnd++;
		}
		ScrollList();
	}

	template <class Owner>
	void CheckboxList<Owner>::SetItems(std::vector<std::string>& items)
	{
		Clear();
		for (int i = 0; i < (int)items.size(); i++)
		{
			AddItem(items.at(i));
		}
	}

	template <class Owner>
	void CheckboxList<Owner>::Check(int index)
	{
		if(index < 0 || index > GetNumberOfItems()-1)
			return;

		((Checkbox<Owner>*)menuItems.at(index))->SetChecked(true);
	}

	template <class Owner>
	void CheckboxList<Owner>::Uncheck(int index)
	{
		if(index < 0 || index > GetNumberOfItems()-1)
			return;

		((Checkbox<Owner>*)menuItems.at(index))->SetChecked(false);
	}

	template <class Owner>
	void CheckboxList<Owner>::CheckAll()
	{
		for(int i = 0; i < GetNumberOfItems(); i++)
			((Checkbox<Owner>*)menuItems.at(i))->SetChecked(true);
	}

	template <class Owner>
	void CheckboxList<Owner>::UncheckAll()
	{
		for(int i = 0; i < GetNumberOfItems(); i++)
			((Checkbox<Owner>*)menuItems.at(i))->SetChecked(false);
	}


	template <class Owner>
	bool CheckboxList<Owner>::IsNoneChecked() { return (GetNumberOfChecked() == 0); }

	template <class Owner>
	bool CheckboxList<Owner>::IsAllChecked() { return (GetNumberOfChecked() == GetNumberOfItems()); }

	template <class Owner>
	bool CheckboxList<Owner>::IsChecked(int index) { return ((Checkbox<Owner>*)menuItems.at(i))->IsChecked(); }

	template <class Owner>
	int CheckboxList<Owner>::GetNumberOfChecked()
	{
		int num = 0;
		for(int i = 0; i < GetNumberOfItems(); i++)
		{
			if (((Checkbox<Owner>*)menuItems.at(i))->IsChecked())
			{
				num++;
			}
		}
		return num;
	}

	template <class Owner>
	MenuItemType CheckboxList<Owner>::GetType() { return MenuItemType_Checkbox; }
}
#endif