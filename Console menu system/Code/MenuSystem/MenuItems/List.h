#ifndef LIST_H
#define LIST_H

#include <vector>
#include "Button.h"

namespace MenuSystem
{
	template <class Owner>
	class List : public Button<Owner>
	{
	public:
		List(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
				const Utility::TextColor selectedColor = Utility::TextColor());
		virtual ~List();

		void Render();
		bool Update(InputEvent input);

		virtual void AddItem(std::string name, int index = -1);
		void AddItem(MenuItem* item, int index = -1);

		virtual void SetItems(std::vector<std::string>& items);
		void SetItems(std::vector<MenuItem*>& items);

		virtual void SetEventCallback(EventFunc func);

		void RemoveItem(int index);
		void RemoveItem(std::string name);

		/*
		* Removes all checkboxes from the list.
		*/
		void Clear();

		int GetNumberOfItems();
		virtual MenuItemType GetType();

	protected:
		int FindMenuItem(std::string name);
		void ScrollList();
		void SelectItem(int index);
		int GetActualSize();

	protected:
		std::vector<Button<Owner>*> menuItems;
		int selectedItem;
		int listStart;
		int listEnd;

	};

	template <class Owner>
	List<Owner>::List(const Owner owner, EventFunc callbackFunction, const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(),
			const Utility::TextColor selectedColor = Utility::TextColor())
			: Button(owner, callbackFunction, pos, text, size, selectedColor)
	{
		selectedItem = -1;
		listStart = listEnd = 0;
	}

	template <class Owner>
	List<Owner>::~List()
	{
		Clear();
	}
	
	template <class Owner>
	void List<Owner>::Render()
	{
		if(visible)
		{
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
					SelectItem(GetNumberOfItems() - 1);
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
	void List<Owner>::AddItem(std::string name, int index)
	{
		if(FindMenuItem(name) == -1)
		{
			if(index < 0 || index > GetNumberOfItems()-1)
			{
				index = GetNumberOfItems();
			}
			Button<Owner>* button = new Button<Owner>(owner, eventCallback, Utility::Pos(), Utility::Text(name), Utility::Pos(size.x, 1), selectedColor);
			menuItems.insert(menuItems.begin() + index, button);
			listEnd++;
		}
		ScrollList();
	}

	template <class Owner>
	void List<Owner>::AddItem(MenuItem* item, int index)
	{

	}
		
	template <class Owner>
	void List<Owner>::SetItems(std::vector<std::string>& items)
	{
		Clear();
		for(int i = 0; i < (int)items.size(); i++)
		{
			AddItem(items.at(i));
		}
	}

	template <class Owner>
	void List<Owner>::SetItems(std::vector<MenuItem*>& items)
	{

	}

	template <class Owner>
	void List<Owner>::SetEventCallback(EventFunc func)
	{
		for (int i = 0; i < (int)menuItems.size(); i++)
		{
			menuItems.at(i)->SetEventCallback(func);
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
	void List<Owner>::RemoveItem(std::string name)
	{
		RemoveCheckbox(FindCheckbox(name));
	}

	template <class Owner>
	void List<Owner>::Clear()
	{
		for(int i = 0; i < GetNumberOfItems(); i++)
		{
			delete menuItems.at(i);
			menuItems.at(i) = NULL;
		}
		menuItems.clear();
		listStart = listEnd = 0;
	}

	template <class Owner>
	int List<Owner>::GetNumberOfItems() { return (int)menuItems.size(); }

	template <class Owner>
	MenuItemType List<Owner>::GetType() { return MenuItemType_List; }
	
	template <class Owner>
	int List<Owner>::FindMenuItem(std::string name)
	{
		for(int i = 0; i < (int)GetNumberOfItems(); i++)
		{
			if(name == menuItems.at(i)->GetText())
			{
				return i;
			}
		}
		return -1;
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
			sizeY = Graphics::GraphicsAPI::GetWindow()->GetWindowSize().y - pos.y;
		}
		return sizeY;
	}
}

#endif