#include "Menu.h"

using namespace MenuSystem;
using namespace MenuSystem::Utility;

Menu::Menu() : visible(true)
{
	activeMenuItem = NULL;
}

Menu::~Menu()
{}

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
				SetAsActive(0);
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
		for(int i = 0; i < (int)nonInteractive.size(); i++)
		{
			nonInteractive.at(i)->Render();
		}

		for(int i = 0; i < (int)menuItems.size(); i++)
		{
			menuItems.at(i)->Render();
		}
	}
}

void Menu::AddMenuItem(MenuItem::MenuItem* item)
{
	if(FindItem(item) == -1)
	{
		if(item->IsInteractive())
		{
			menuItems.push_back(item);
		}
		else
		{
			nonInteractive.push_back(item);
		}
	}
}

void Menu::RemoveMenuItem(MenuItem::MenuItem* item)
{
	int index = FindItem(item);

	if(index != -1)
	{
		if(item->IsInteractive())
		{
			menuItems.erase(menuItems.begin() + index);
		}
		else
		{
			nonInteractive.erase(menuItems.begin() + index);
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
	for(int i = 0; i < (int)nonInteractive.size(); i++)
	{
		delete nonInteractive.at(i);
		nonInteractive.at(i) = NULL;
	}
	
	for(int i = 0; i < (int)menuItems.size(); i++)
	{
		delete menuItems.at(i);
		menuItems.at(i) = NULL;
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

int Menu::FindItem(const MenuItem::MenuItem* item)
{
	int index = -1;

	if(item->IsInteractive())
	{
		for(int i = 0; i < (int)menuItems.size(); i++)
		{
			if(menuItems.at(i) == item)
			{
				index = i;
				break;
			}
		}
	}
	else
	{
		for(int i = 0; i < (int)nonInteractive.size(); i++)
		{
			if(nonInteractive.at(i) == item)
			{
				index = i;
				break;
			}
		}
	}

	return index;
}

void Menu::SetAsActive(int index)
{
	if(index >= 0)
	{
		if(activeMenuItem)
		{
			activeMenuItem->SetActive(false);
		}
		activeMenuItem = menuItems.at(index);
		activeMenuItem->SetActive(true);
	}
}

int Menu::FindNextMenu(const Direction dir)
{
	int index = -1;
	MenuItem::MenuItem* currentBestChoice;
	Pos shortest = Pos(1000, 1000);
	Pos currentPos = activeMenuItem->GetPosition();

	if(dir == UP)
	{
		for(int i = 0; i < (int)menuItems.size(); i++)
		{
			if(menuItems.at(i) != activeMenuItem)
			{
				Pos pos = menuItems.at(i)->GetPosition();
				if(pos.y < currentPos.y)
				{
					if(currentPos.y - pos.y < shortest.y)
					{
						index = i;
						currentBestChoice = menuItems.at(i);
						shortest = currentPos;
						shortest -= pos;
						shortest.x = abs(shortest.x);
					}
					else if(currentPos.y - pos.y == shortest.y)
					{
						if(abs(currentPos.x - pos.x) <= shortest.x)
						{
							index = i;
							currentBestChoice = menuItems.at(i);
							shortest.x = abs(currentPos.x - pos.x);
						}
					}
				}
			}
		}
	}
	else if(dir == RIGHT)
	{
		for(int i = 0; i < (int)menuItems.size(); i++)
		{
			if(menuItems.at(i) != activeMenuItem)
			{
				Pos pos = menuItems.at(i)->GetPosition();
				if(pos.x > currentPos.x)
				{
					if(pos.x - currentPos.x < shortest.x)
					{
						index = i;
						currentBestChoice = menuItems.at(i);
						shortest = pos;
						shortest -= currentPos;
						shortest.y = abs(shortest.y);
					}
					else if(pos.x - currentPos.x == shortest.x)
					{
						if(abs(pos.y - currentPos.y) <= shortest.y)
						{
							index = i;
							currentBestChoice = menuItems.at(i);
							shortest.y = abs(pos.y - currentPos.y);
						}
					}
				}
			}
		}
	}
	else if(dir == DOWN)
	{
		for(int i = 0; i < (int)menuItems.size(); i++)
		{
			if(menuItems.at(i) != activeMenuItem)
			{
				Pos pos = menuItems.at(i)->GetPosition();
				if(pos.y > currentPos.y)
				{
					if(pos.y - currentPos.y < shortest.y)
					{
						index = i;
						currentBestChoice = menuItems.at(i);
						shortest = pos;
						shortest -= currentPos;
						shortest.x = abs(shortest.x);
					}
					else if(pos.y - currentPos.y == shortest.y)
					{
						if(abs(pos.x - currentPos.x) <= shortest.x)
						{
							index = i;
							currentBestChoice = menuItems.at(i);
							shortest.x = abs(pos.x - currentPos.x);
						}
					}
				}
			}
		}
	}
	else if(dir == LEFT)
	{
		for(int i = 0; i < (int)menuItems.size(); i++)
		{
			if(menuItems.at(i) != activeMenuItem)
			{
				Pos pos = menuItems.at(i)->GetPosition();
				if(pos.x < currentPos.x)
				{
					if(currentPos.x - pos.x < shortest.x)
					{
						index = i;
						currentBestChoice = menuItems.at(i);
						shortest = currentPos;
						shortest -= pos;
						shortest.y = abs(shortest.y);
					}
					else if(currentPos.x - pos.x == shortest.x)
					{
						if(abs(currentPos.y - pos.y) <= shortest.y)
						{
							index = i;
							currentBestChoice = menuItems.at(i);
							shortest.y = abs(currentPos.y - pos.y);
						}
					}
				}
			}
		}
	}

	return index;
}