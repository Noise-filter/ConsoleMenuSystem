#include "Sprite.h"

#include <fstream>

#include "Graphics.h"
#include "Input.h"

using namespace MenuSystem;
using namespace MenuSystem::Utility;
using namespace MenuSystem::Graphics;

using namespace std;

Sprite::Sprite(const Utility::Pos& pos, const float updateFrequency, std::string filename)
	: DrawArea(pos, (1, 1)), updateFrequency(updateFrequency)
{
	delete[] buffer;
	buffer = nullptr;

	if (!filename.empty())
	{
		LoadSprite(filename);
	}

	currentAnimationFrame = 0;
	this->lastTimePoint = std::chrono::system_clock::now();
	timeBetweenFrames = std::chrono::milliseconds::duration((int)(updateFrequency * 1000));
}

Sprite::~Sprite()
{
	buffer = nullptr;
	for (int i = 0; i < numberOfAnimationFrames; i++)
	{
		delete[] pictures[i];
	}
}

void Sprite::Render()
{
	if (visible)
	{
		switchPicture();
		Graphics::GraphicsAPI::PrintBuffer(buffer, this->pos, this->size);
	}
}

bool Sprite::Update(InputEvent input)
{
	return false;
}

bool Sprite::LoadSprite(std::string filename)
{
	ifstream inFile(filename.c_str());

	if (inFile)
	{
		int sizeX, sizeY, numberOfFrames;
		inFile >> sizeX >> sizeY >> numberOfFrames;
		inFile.ignore(1000, '\n');
		size.x = sizeX;
		size.y = sizeY;
		numberOfAnimationFrames = numberOfFrames;

		for (const auto& picture : pictures)
		{
			delete[] picture;
		}
		pictures.clear();
		pictures.reserve(numberOfFrames);

		for (int i = 0; i < numberOfFrames; i++)
		{
			pictures.push_back(new CHAR_INFO[sizeX * sizeY]);
			for (int y = 0; y < sizeY; y++)
			{
				std::string str;
				getline(inFile, str);

				for (int x = 0; x < sizeX; x++)
				{
					pictures[i][x + y * sizeY].Char.AsciiChar = str[x];
				}
			}

			for (int y = 0; y < sizeY; y++)
			{
				std::string str;
				getline(inFile, str);

				for (int x = 0; x < sizeX; x++)
				{
					pictures[i][x + y * sizeY].Attributes = str[x];
				}
			}
		}
		buffer = pictures[0];
	}

	return true;
}

MenuItemType Sprite::GetType()
{
	return MenuItem_Sprite;
}

int Sprite::GetCurrentFrame() const
{
	return currentAnimationFrame;
}

int Sprite::GetMaxNumberOfFrames() const
{
	return numberOfAnimationFrames;
}

float Sprite::GetUpdateFrequency() const
{
	return updateFrequency;
}

void MenuSystem::Sprite::switchPicture()
{
	auto currentTimePoint = std::chrono::system_clock::now();

	if (currentTimePoint - lastTimePoint > timeBetweenFrames)
	{
		lastTimePoint = std::chrono::system_clock::now();
		++currentAnimationFrame;
		if (currentAnimationFrame >= numberOfAnimationFrames)
		{
			currentAnimationFrame = 0;
		}
		buffer = pictures[currentAnimationFrame];
	}
}
