#ifndef SPRITE_H
#define SPRITE_H

#include "DrawArea.h"
#include <vector>
#include <chrono>

namespace MenuSystem
{
	class Sprite : public DrawArea
	{
	public:
		Sprite(const Utility::Pos& pos = Utility::Pos(), const float updateFrequency = 1.0, std::string filename = "");
		virtual ~Sprite();

		virtual void Render();
		virtual bool Update(InputEvent input);

		bool LoadSprite(std::string filename);

		virtual MenuItemType GetType();
		int GetCurrentFrame() const;
		int GetMaxNumberOfFrames() const;
		float GetUpdateFrequency() const;

	private:
		void switchPicture();

	private:
		int numberOfAnimationFrames;
		int currentAnimationFrame;
		float updateFrequency;

		std::chrono::system_clock::time_point lastTimePoint;
		std::chrono::duration<long long, std::milli> timeBetweenFrames;

		std::vector<CHAR_INFO*> pictures;

	};
}

#endif