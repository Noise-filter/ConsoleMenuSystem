#include "MenuItem.h"

using namespace MenuSystem::MenuItem;
using namespace MenuSystem::Utility;

unsigned int MenuItem::currentID = 0;

MenuItem::MenuItem(Pos pos)
	: ID(currentID++), pos(pos), active(false), visible(true)
{}

void MenuItem::SetVisible(bool visible)
{
	this->visible = visible;
}

void MenuItem::SetPosition(const Pos& pos)
{
	this->pos = pos;
}

void MenuItem::SetActive(const bool active)
{
	this->active = active;
}

bool MenuItem::IsActive()
{
	return active;
}

unsigned int MenuItem::GetID()
{
	return ID;
}

bool MenuItem::GetVisible()
{
	return visible;
}

Pos& MenuItem::GetPosition()
{
	return pos;
}

bool MenuItem::operator ==(const MenuItem& obj)
{
	return (this->ID == obj.ID);
}

bool MenuItem::operator !=(const MenuItem& obj)
{
	return !(*this == obj);
}