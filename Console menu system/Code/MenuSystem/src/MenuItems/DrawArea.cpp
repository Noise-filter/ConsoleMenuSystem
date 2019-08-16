#include "DrawArea.h"

#include "Graphics.h"
#include "Input.h"

using namespace MenuSystem;
using namespace MenuSystem::Utility;
using namespace MenuSystem::Graphics;

using namespace std;

DrawArea::DrawArea(const Utility::Pos& pos, const Utility::Pos& size) 
	: MenuItem(pos), size(size)
{
	buffer = new CHAR_INFO[size.x * size.y];
	Fill(' ', TextColor());
}

DrawArea::~DrawArea()
{
	delete[] buffer;
}

void DrawArea::Render()
{
	if (visible)
	{
		Graphics::GraphicsAPI::PrintBuffer(buffer, this->pos, this->size);
	}
}

bool DrawArea::Update(InputEvent input)
{

	return true;
}

void DrawArea::SetCharacter(const char character, const Utility::Pos& pos)
{
	buffer[pos.x + pos.y * size.x].Char.AsciiChar = character;
}

void DrawArea::SetCharacter(const char character, const Utility::Pos& pos, const Utility::TextColor& color)
{
	buffer[pos.x + pos.y * size.x].Char.AsciiChar = character;
	buffer[pos.x + pos.y * size.x].Attributes = color.GetColor();
}

void DrawArea::Fill(const char character, const Utility::TextColor& color)
{
	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			SetCharacter(character, Pos(x, y), color);
		}
	}
}

char DrawArea::GetCharacter(const Utility::Pos& pos)
{
	return buffer[pos.x + pos.y * size.x].Char.AsciiChar;
}

void DrawArea::SetSize(const Utility::Pos& size)
{
	this->size = size;
}

Utility::Pos& DrawArea::GetSize()
{
	return size;
}

MenuItemType DrawArea::GetType()
{
	return MenuItemType_DrawArea;
}

bool DrawArea::IsInteractive() const
{
	return false;
}