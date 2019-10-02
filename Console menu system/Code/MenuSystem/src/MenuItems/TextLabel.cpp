#include "TextLabel.h"

#include "Graphics.h"
#include "Input.h"

using namespace MenuSystem;
using namespace MenuSystem::Utility;
using namespace MenuSystem::Graphics;

using namespace std;

TextLabel::TextLabel(const Pos& pos, const Text& text, const Pos& size)
	: MenuItem(pos), text(text), size(size)
{}

void TextLabel::Render()
{
	if(visible)
	{
		GraphicsAPI::PrintText(this->text, this->pos, this->size);
	}
}

bool TextLabel::Update(InputEvent input)
{
	return true;
}

void TextLabel::SetColor(const TextColor color)
{
	this->text.color = color;
}

void TextLabel::SetText(const string& text)
{
	GraphicsAPI::ClearScreen(pos, this->size);
	this->text.textString = text;
}

void TextLabel::SetSize(const Pos& size)
{
	GraphicsAPI::ClearScreen(pos, this->size);
	this->size = size;
}

TextColor& TextLabel::GetTextColor()
{
	return text.color;
}

string TextLabel::GetText()
{
	return text.textString;
}

Pos& TextLabel::GetSize()
{
	return size;
}

MenuItemType TextLabel::GetType()
{
	return MenuItemType_TextLabel;
}

bool TextLabel::IsInteractive() const
{
	return false;
}