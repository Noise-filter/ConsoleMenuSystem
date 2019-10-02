#include "Menu.h"

using namespace MenuSystem;
using namespace MenuSystem::Utility;

Menu::Menu() : visible(true)
{
	activeMenuItem = nullptr;
}

bool Menu::Update(InputEvent input)
{
	if(visible)
	{
		if(activeMenuItem)
		{
			if(!activeMenuItem->Update(input))
			{
				if(input.LeftPressed())
				{
					SetAsActive(FindNextMenu(LEFT));
					return true;
				}
				else if(input.RightPressed())
				{
					SetAsActive(FindNextMenu(RIGHT));
					return true;
				}
				else if(input.UpPressed())
				{
					SetAsActive(FindNextMenu(UP));
					return true;
				}
				else if(input.DownPressed())
				{
					SetAsActive(FindNextMenu(DOWN));
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		else
		{
			if(menuItems.size() > 0)
			{
				SetAsActive(menuItems.begin()->second);
				return Update(input);
			}
			return false;
		}
	}
	return false;
}

void Menu::Render()
{
	if(visible)
	{
		for (const auto& menuItem : nonInteractive)
		{
			menuItem.second->Render();
		}

		for (const auto& menuItem : menuItems)
		{
			menuItem.second->Render();
		}
	}
}

MenuItem::MenuItem* Menu::GetMenuItem(const std::string& uniqueName)
{
	return FindItem(uniqueName);
}

void Menu::AddMenuItem(const std::string& uniqueName, MenuItem::MenuItem* item)
{
	if(FindItem(uniqueName) == nullptr)
	{
		if(item->IsInteractive())
		{
			menuItems[uniqueName] = item;
		}
		else
		{
			nonInteractive[uniqueName] = item;
		}
	}
}

void Menu::RemoveMenuItem(const std::string& uniqueName)
{
	MenuItem::MenuItem* item = FindItem(uniqueName);

	if (item != nullptr)
	{
		if(item->IsInteractive())
		{
			menuItems.erase(uniqueName);
		}
		else
		{
			nonInteractive.erase(uniqueName);
		}
	}
}

void Menu::Clear()
{
	menuItems.clear();
	nonInteractive.clear();
}

void Menu::DeleteAll()
{
	for(auto it = nonInteractive.begin(); it != nonInteractive.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
	
	for (auto it = menuItems.begin(); it != menuItems.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}

	Clear();
}

void Menu::SetVisible(bool visible)
{
	this->visible = visible;
}

bool Menu::IsVisible()
{
	return visible;
}

bool Menu::IsEmpty()
{
	return (menuItems.empty() && nonInteractive.empty());
}

MenuItem::MenuItem* Menu::FindItem(const MenuItem::MenuItem* item)
{
	if(item->IsInteractive())
	{
		for (std::map<std::string, MenuItem::MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
		{
			if(it->second == item)
			{
				return it->second;
			}
		}
	}
	else
	{
		for(std::map<std::string, MenuItem::MenuItem*>::iterator it = nonInteractive.begin(); it != nonInteractive.end(); it++)
		{
			if(it->second == item)
			{
				return it->second;
			}
		}
	}
	return nullptr;
}

MenuItem::MenuItem* Menu::FindItem(const std::string& uniqueName)
{
	std::map<std::string, MenuItem::MenuItem*>::iterator it = menuItems.find(uniqueName);
	if (it != menuItems.end())
	{
		return it->second;
	}

	it = nonInteractive.find(uniqueName);
	if (it != nonInteractive.end())
	{
		return it->second;
	}

	return nullptr;
}

void Menu::SetAsActive(MenuItem::MenuItem* item)
{
	if (item != 0)
	{
		if(activeMenuItem)
		{
			activeMenuItem->SetActive(false);
		}
		activeMenuItem = item;
		activeMenuItem->SetActive(true);
	}
}

MenuItem::MenuItem* Menu::FindNextMenu(Direction dir)
{
	MenuItem::MenuItem* currentBestChoice = nullptr;
	Pos shortest = Pos(1000, 1000);
	Pos currentPos = activeMenuItem->GetPosition();

	if(dir == UP)
	{
		for (std::map<std::string, MenuItem::MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
		{
			if(it->second != activeMenuItem)
			{
				Pos pos = it->second->GetPosition();
				if(pos.y < currentPos.y)
				{
					if(currentPos.y - pos.y < shortest.y)
					{
						currentBestChoice = it->second;
						shortest = currentPos;
						shortest -= pos;
						shortest.x = abs(shortest.x);
					}
					else if(currentPos.y - pos.y == shortest.y)
					{
						if(abs(currentPos.x - pos.x) <= shortest.x)
						{
							currentBestChoice = it->second;
							shortest.x = abs(currentPos.x - pos.x);
						}
					}
				}
			}
		}
	}
	else if(dir == RIGHT)
	{
		for (std::map<std::string, MenuItem::MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
		{
			if (it->second != activeMenuItem)
			{
				Pos pos = it->second->GetPosition();
				if(pos.x > currentPos.x)
				{
					if(pos.x - currentPos.x < shortest.x)
					{
						currentBestChoice = it->second;
						shortest = pos;
						shortest -= currentPos;
						shortest.y = abs(shortest.y);
					}
					else if(pos.x - currentPos.x == shortest.x)
					{
						if(abs(pos.y - currentPos.y) <= shortest.y)
						{
							currentBestChoice = it->second;
							shortest.y = abs(pos.y - currentPos.y);
						}
					}
				}
			}
		}
	}
	else if(dir == DOWN)
	{
		for (std::map<std::string, MenuItem::MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
		{
			if (it->second != activeMenuItem)
			{
				Pos pos = it->second->GetPosition();
				if(pos.y > currentPos.y)
				{
					if(pos.y - currentPos.y < shortest.y)
					{
						currentBestChoice = it->second;
						shortest = pos;
						shortest -= currentPos;
						shortest.x = abs(shortest.x);
					}
					else if(pos.y - currentPos.y == shortest.y)
					{
						if(abs(pos.x - currentPos.x) <= shortest.x)
						{
							currentBestChoice = it->second;
							shortest.x = abs(pos.x - currentPos.x);
						}
					}
				}
			}
		}
	}
	else if(dir == LEFT)
	{
		for (std::map<std::string, MenuItem::MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
		{
			if(it->second != activeMenuItem)
			{
				Pos pos = it->second->GetPosition();
				if(pos.x < currentPos.x)
				{
					if(currentPos.x - pos.x < shortest.x)
					{
						currentBestChoice = it->second;
						shortest = currentPos;
						shortest -= pos;
						shortest.y = abs(shortest.y);
					}
					else if(currentPos.x - pos.x == shortest.x)
					{
						if(abs(currentPos.y - pos.y) <= shortest.y)
						{
							currentBestChoice = it->second;
							shortest.y = abs(currentPos.y - pos.y);
						}
					}
				}
			}
		}
	}

	return currentBestChoice;
}

Menu& Menu::operator=(const Menu& menu)
{
	this->activeMenuItem = menu.activeMenuItem;
	this->menuItems = menu.menuItems;
	
	this->nonInteractive.insert(menu.nonInteractive.begin(), menu.nonInteractive.end());
	this->visible = menu.visible;
	
	return *this;
}