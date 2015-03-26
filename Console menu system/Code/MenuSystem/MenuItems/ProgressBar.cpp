#include "ProgressBar.h"

using namespace MenuSystem;

ProgressBar::ProgressBar(const Utility::Pos& pos, const Utility::Text& text, const Utility::Pos& size)
	: TextLabel(pos, text, size)
{
	progressValue = 0.0f;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Render()
{
	int length = size.x;
	if (visible)
	{
		std::string boxes;
		int numberOfBoxes = length * progressValue + 0.5f;
		int dots = length - numberOfBoxes;
		for (int i = 0; i < numberOfBoxes; i++)
		{
			boxes.push_back(219);
		}

		for (int i = 0; i < dots; i++)
		{
			boxes.push_back('.');
		}

		Graphics::GraphicsAPI::ClearScreen(pos, size);
		Graphics::GraphicsAPI::PrintText(Utility::Text(boxes, text.color), pos, size);
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