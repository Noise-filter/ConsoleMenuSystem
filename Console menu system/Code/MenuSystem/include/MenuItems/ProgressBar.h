#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include "TextLabel.h"
#include "../Graphics.h"

namespace MenuSystem
{
	class ProgressBar : public TextLabel
	{
	public:
		ProgressBar(const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos(), const bool showProcentText = true);
		virtual ~ProgressBar();

		virtual void Render();
		virtual bool Update()
		{
			return true;
		}

		bool IsFull();
		float GetProgressValue();
		void SetProgressValue(float value);
		void AddProgressValue(float value);
		void SetShowProcentValue(bool showText);
		int GetProcentValue();
		void Reset();

		virtual MenuItemType GetType();

	private:
		void ClampProgressValue();
		void RenderProcentText();

	protected:
		float progressValue;
		bool showProcentText;


		const unsigned char box = 219;

	};

}

#endif