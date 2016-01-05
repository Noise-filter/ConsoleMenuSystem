#ifndef DRAW_AREA_H
#define DRAW_AREA_H

#include "MenuItem.h"

namespace MenuSystem
{
	class DrawArea : public MenuItem::MenuItem
	{
	public:
		DrawArea(const Utility::Pos& pos = Utility::Pos(), const Utility::Pos& size = Utility::Pos());
		virtual ~DrawArea();

		virtual void Render();
		virtual bool Update(InputEvent input);

		void SetCharacter(const char character, const Utility::Pos& pos);
		void SetCharacter(const char character, const Utility::Pos& pos, const Utility::TextColor& color);

		void Fill(const char character, const Utility::TextColor& color);

		char GetCharacter(const Utility::Pos& pos);

		void SetSize(const Utility::Pos& size);

		Utility::Pos& GetSize();
		virtual MenuItemType GetType();
		virtual bool IsInteractive() const;

	private:
		Utility::Pos size;
		CHAR_INFO* buffer;
	};
}

#endif