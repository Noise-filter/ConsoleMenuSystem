#ifndef LIST_H
#define LIST_H

#include <memory>
#include <vector>
#include <algorithm>
#include "Button.h"

namespace MenuSystem
{
	template <class Owner>
	class List : public Button<Owner>
	{
	public:
		List(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
				const Utility::TextColor selectedColor = Utility::TextColor());
		virtual ~List() = default;

		void Render();
		bool Update(InputEvent input);

		virtual void AddItem(const std::string& name, int index = -1);

		virtual void SetItems(std::vector<std::string>& items);

		virtual void SetEventCallback(EventFunc func);

		void RemoveItem(int index);
		void RemoveItem(const std::string& name);

		/*
		* Removes all checkboxes from the list.
		*/
		void Clear();

		size_t GetNumberOfItems();
		virtual MenuItemType GetType();

	protected:
		int FindMenuItem(const std::string& name);
		void ScrollList();
		void SelectItem(int index);
		int GetActualSize();

	protected:
		std::vector<std::shared_ptr<Button<Owner>>> menuItems;
		int selectedItem;
		int listStart;
		int listEnd;

	};

	template <class Owner>
	List<Owner>::List(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos, const Utility::Text& text, const Utility::Pos& size,
			const Utility::TextColor selectedColor)
			: Button(owner, callbackFunction, pos, text, size, selectedColor)
	{
		selectedItem = -1;
		listStart = listEnd = 0;
	}

	template <class Owner>
	void List<Owner>::Render()
	{
		if(visible)
		{
			Graphics::GraphicsAPI::ClearScreen(pos, size);
			Utility::Pos renderPos = this->pos;
			if(active)
			{
				Graphics::GraphicsAPI::PrintText(Utility::Text(text.textString, selectedColor), pos, size);
			}
			else
			{
				Graphics::GraphicsAPI::PrintText(text, pos, size);
			}

			for(int i = listStart; i < listEnd; i++)
			{
				renderPos.y += 1;
				menuItems.at(i)->SetPosition(renderPos);
				menuItems.at(i)->Render();
			}
		}
	}

	template <class Owner>
	bool List<Owner>::Update(InputEvent input)
	{
		if(GetNumberOfItems() > 0)
		{
			if(selectedItem == -1)
			{
				if (input.EnterPressed())
				{
					selectedItem = 0;
					menuItems.at(selectedItem)->SetActive(true);
					ScrollList();
					Graphics::GraphicsAPI::ClearScreen(pos, size);
					return true;
				}
			}
			else
			{
				if(input.EnterPressed())
				{
					return menuItems.at(selectedItem)->Update(input);
				}
				else if(input.ExitPressed())
				{
					menuItems.at(selectedItem)->SetActive(false);
					selectedItem = 0;
					ScrollList();
					selectedItem = -1;
				}
				else if(input.UpPressed())
				{
					SelectItem(selectedItem - 1);
				}
				else if(input.DownPressed())
				{
					SelectItem(selectedItem + 1);
				}
				else if (input.GetVirtualKeyCode() == VK_HOME)
				{
					SelectItem(0);
				}
				else if (input.GetVirtualKeyCode() == VK_END)
				{
					SelectItem((int)GetNumberOfItems() - 1);
				}
				else if (input.GetVirtualKeyCode() == VK_PRIOR)
				{
					SelectItem(selectedItem - GetActualSize() + 1);
				}
				else if (input.GetVirtualKeyCode() == VK_NEXT)
				{
					SelectItem(selectedItem + GetActualSize() - 1);
				}

				return true;
			}
		}

		return false;
	}

	template <class Owner>
	void List<Owner>::AddItem(const std::string& name, int index)
	{
		if(FindMenuItem(name) == -1)
		{
			if(index < 0 || index > GetNumberOfItems()-1)
			{
				index = (int)GetNumberOfItems();
			}
			auto button = std::make_shared<Button<Owner>>(owner, eventCallback, Utility::Pos(), Utility::Text(name), Utility::Pos(size.x, 1), selectedColor);
			menuItems.insert(menuItems.begin() + index, button);
			listEnd++;
		}
		ScrollList();
	}
		
	template <class Owner>
	void List<Owner>::SetItems(std::vector<std::string>& items)
	{
		Clear();
		for (const auto& item : items) 
		{
			AddItem(item);
		}
	}

	template <class Owner>
	void List<Owner>::SetEventCallback(EventFunc func)
	{
		for (const auto& item : menuItems)
		{
			item->SetEventCallback(func);
		}
		this->eventCallback = func;
	}
	
	template <class Owner>
	void List<Owner>::RemoveItem(int index)
	{
		if(index < 0 || index > GetNumberOfItems()-1)
			return;

		menuItems.erase(menuItems.begin() + index);
		listEnd--;
		ScrollList();
	}

	template <class Owner>
	void List<Owner>::RemoveItem(const std::string& name)
	{
		RemoveCheckbox(FindCheckbox(name));
	}

	template <class Owner>
	void List<Owner>::Clear()
	{
		menuItems.clear();
		listStart = listEnd = 0;
	}

	template <class Owner>
	size_t List<Owner>::GetNumberOfItems() { return menuItems.size(); }

	template <class Owner>
	MenuItemType List<Owner>::GetType() { return MenuItemType_List; }
	
	template <class Owner>
	int List<Owner>::FindMenuItem(const std::string& name)
	{
		auto it = std::find_if(menuItems.begin(), menuItems.end(), [&](auto menuItem) { return menuItem->GetText() == name; });
		if (it == menuItems.end()) {
			return -1;
		}
		return it - menuItems.begin();
	}

	template <class Owner>
	void List<Owner>::ScrollList()
	{
		int sizeY = GetActualSize();
		sizeY -= 1;	//Remove top label.

		if(listEnd - listStart > sizeY)
		{
			listEnd = listStart + sizeY;
		}

		if(selectedItem != -1)
		{
			if(selectedItem < listStart)
			{
				listStart = selectedItem;
				if(listEnd - listStart > sizeY)
					listEnd = sizeY + listStart;
			}
			if(selectedItem >= listEnd)
			{
				listEnd = selectedItem+1;
				if(listEnd - listStart > sizeY)
					listStart = listEnd - sizeY;
			}
		}
	}

	template <class Owner>
	void List<Owner>::SelectItem(int index)
	{
		if (index < 0)
			index = 0;
		else if (index >= GetNumberOfItems())
			index = GetNumberOfItems() - 1;

		menuItems.at(selectedItem)->SetActive(false);
		selectedItem = index;
		menuItems.at(selectedItem)->SetActive(true);
		ScrollList();
		Graphics::GraphicsAPI::ClearScreen(pos, size);
	}

	template <class Owner>
	int List<Owner>::GetActualSize()
	{
		int sizeY = this->size.y;
		if (sizeY == 0)
		{
			sizeY = Graphics::GraphicsAPI::GetWindow().GetWindowSize().y - pos.y;
		}
		return sizeY;
	}
}

#endif