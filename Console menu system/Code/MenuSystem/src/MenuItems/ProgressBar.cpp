#include "ProgressBar.h"

using namespace MenuSystem;
using namespace Utility;

ProgressBar::ProgressBar(const Utility::Pos& pos, const Utility::Text& text, const Utility::Pos& size, const bool showProcentText)
	: TextLabel(pos, text, size)
{
	progressValue = 0.0f;
	this->showProcentText = showProcentText;

	if (this->size.x < 4)
	{
		this->showProcentText = false;
	}
}

void ProgressBar::Render()
{
	if (visible)
	{
		int length = size.x;
		int numberOfBoxes = (int)(length * progressValue + 0.5f);
		int dots = length - numberOfBoxes;

		std::string boxes(length, '.');
		for (int i = 0; i < numberOfBoxes; i++)
		{
			boxes.at(i) = box;
		}

		Graphics::GraphicsAPI::PrintText(Utility::Text(std::move(boxes), text.color), pos, size);
	
		if (showProcentText)
		{
			RenderProcentText();
		}
	}
}

void ProgressBar::RenderProcentText()
{
	int middle = size.x / 2;
	int numberOfBoxes = (int)(size.x * progressValue + 0.5f);

	TextColor textColor = text.color;
	std::string procentText = std::to_string((int)(progressValue * 100));
	procentText += '%';

	Pos textPos = pos;
	textPos.x += middle - (int)(procentText.size() / 2);

	for (int i = 0; i < (int)procentText.size(); i++)
	{
		if (textPos.x < pos.x + numberOfBoxes)
		{
			textColor.backgroundColor = text.color.textColor;
			textColor.textColor = text.color.backgroundColor;
		}
		else
		{
			textColor.backgroundColor = text.color.backgroundColor;
			textColor.textColor = text.color.textColor;
		}

		Graphics::GraphicsAPI::UseColor(textColor);
		Graphics::GraphicsAPI::PrintCharacter(textPos, procentText.at(i));

		textPos.x++;
	}
}

bool ProgressBar::IsFull()
{
	return (progressValue == 1.0f);
}

float ProgressBar::GetProgressValue()
{
	return progressValue;
}

void ProgressBar::SetProgressValue(float value)
{
	progressValue = value;
	ClampProgressValue();
}

void ProgressBar::AddProgressValue(float value)
{
	progressValue += value;
	ClampProgressValue();
}

void ProgressBar::SetShowProcentValue(bool showText)
{
	showProcentText = showText;
}

int ProgressBar::GetProcentValue()
{
	return (int)(progressValue * 100);
}

void ProgressBar::Reset()
{
	progressValue = 0.0f;
}

void ProgressBar::ClampProgressValue()
{
	if (progressValue > 1.0f)
		progressValue = 1.0f;
	else if (progressValue < 0.0f)
		progressValue = 0.0f;
}

MenuItemType ProgressBar::GetType()
{
	return MenuItemType_ProgressBar;
}