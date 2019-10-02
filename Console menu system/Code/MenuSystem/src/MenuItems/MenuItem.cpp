#include "MenuItem.h"

using namespace MenuSystem::MenuItem;
using namespace MenuSystem::Utility;

unsigned int MenuItem::currentID = 0;

MenuItem::MenuItem(Pos pos)
	: ID(currentID++), pos(pos), active(false), visible(true)
{}

void MenuItem::SetVisible(bool visible) noexcept
{
	this->visible = visible;
}

void MenuItem::SetPosition(const Pos& pos) noexcept
{
	this->pos = pos;
}

void MenuItem::SetActive(bool active) noexcept
{
	this->active = active;
}

bool MenuItem::IsActive() const noexcept
{
	return active;
}

unsigned int MenuItem::GetID() const noexcept
{
	return ID;
}

bool MenuItem::GetVisible() const noexcept
{
	return visible;
}

Pos& MenuItem::GetPosition()
{
	return pos;
}

bool MenuItem::operator ==(const MenuItem& obj) const noexcept
{
	return (this->ID == obj.ID);
}

bool MenuItem::operator !=(const MenuItem& obj) const noexcept
{
	return !(*this == obj);
}