#include "Menu.h"

using namespace MenuSystem;
using namespace MenuSystem::Utility;

bool Menu::Update(InputEvent input)
{
	if(visible)
	{
		if (activeMenuItem)
		{
			if (!activeMenuItem->Update(input))
			{
				if (input.LeftPressed())
				{
					SetAsActive(FindNextMenu(LEFT));
					return true;
				}
				else if (input.RightPressed())
				{
					SetAsActive(FindNextMenu(RIGHT));
					return true;
				}
				else if (input.UpPressed())
				{
					SetAsActive(FindNextMenu(UP));
					return true;
				}
				else if (input.DownPressed())
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
			if (menuItems.size() > 0)
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

std::shared_ptr<MenuItem::MenuItem> Menu::GetMenuItem(const std::string& uniqueName)
{
	return FindItem(uniqueName);
}

void Menu::AddMenuItem(const std::string& uniqueName, std::shared_ptr<MenuItem::MenuItem> item)
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
	std::shared_ptr<MenuItem::MenuItem> item = FindItem(uniqueName);

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

std::shared_ptr<MenuItem::MenuItem> Menu::FindItem(const std::shared_ptr<MenuItem::MenuItem>& item)
{
	if(item->IsInteractive())
	{
		for (const auto& it : menuItems)
		{
			if(it.second == item)
			{
				return it.second;
			}
		}
	}
	else
	{
		for(const auto& it : nonInteractive)
		{
			if(it.second == item)
			{
				return it.second;
			}
		}
	}
	return nullptr;
}

std::shared_ptr<MenuItem::MenuItem> Menu::FindItem(const std::string& uniqueName)
{
	auto it = menuItems.find(uniqueName);
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

void Menu::SetAsActive(std::shared_ptr<MenuItem::MenuItem> item)
{
	if (item != 0)
	{
		if (activeMenuItem)
		{
			activeMenuItem->SetActive(false);
		}
		activeMenuItem = item;
		activeMenuItem->SetActive(true);
	}
}

std::shared_ptr<MenuItem::MenuItem> Menu::FindNextMenu(Direction dir)
{
	std::shared_ptr<MenuItem::MenuItem> currentBestChoice = nullptr;
	Pos shortest = Pos(1000, 1000);
	Pos currentPos = activeMenuItem->GetPosition();

	if (dir == UP)
	{
		for (const auto& it : menuItems)
		{
			if (it.second != activeMenuItem)
			{
				Pos pos = it.second->GetPosition();
				if (pos.y < currentPos.y)
				{
					auto distance = abs(currentPos - pos);
					if (distance.x < shortest.x)
					{
						currentBestChoice = it.second;
						shortest = distance;
					}
					else if (distance.x == shortest.x)
					{
						if (distance.y < shortest.y)
						{
							currentBestChoice = it.second;
							shortest = distance;
						}
					}
				}
			}
		}
	}
	else if (dir == RIGHT)
	{
		for (const auto& it : menuItems)
		{
			if (it.second != activeMenuItem)
			{
				Pos pos = it.second->GetPosition();
				if (pos.x > currentPos.x)
				{
					auto distance = abs(currentPos - pos);
					if (distance.y < shortest.y)
					{
						currentBestChoice = it.second;
						shortest = distance;
					}
					else if (distance.y == shortest.y)
					{
						if (distance.x < shortest.x)
						{
							currentBestChoice = it.second;
							shortest = distance;
						}
					}
				}
			}
		}
	}
	else if (dir == DOWN)
	{
		for (const auto& it : menuItems)
		{
			if (it.second != activeMenuItem)
			{
				Pos pos = it.second->GetPosition();
				if (pos.y > currentPos.y)
				{
					auto distance = abs(currentPos - pos);
					if (distance.x < shortest.x)
					{
						currentBestChoice = it.second;
						shortest = distance;
					}
					else if (distance.x == shortest.x)
					{
						if (distance.y < shortest.y)
						{
							currentBestChoice = it.second;
							shortest = distance;
						}
					}
				}
			}
		}
	}
	else if (dir == LEFT)
	{
		for (const auto& it : menuItems)
		{
			if (it.second != activeMenuItem)
			{
				Pos pos = it.second->GetPosition();
				if (pos.x < currentPos.x)
				{
					auto distance = abs(currentPos - pos);
					if (distance.y < shortest.y)
					{
						currentBestChoice = it.second;
						shortest = distance;
					}
					else if (distance.y == shortest.y)
					{
						if (distance.x < shortest.x)
						{
							currentBestChoice = it.second;
							shortest = distance;
						}
					}
				}
			}
		}
	}

	return currentBestChoice;
}