#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include <string>

#include "MenuItem.h"

namespace MenuSystem
{
	class TextLabel : public MenuItem::MenuItem
	{
	public:
		TextLabel(const Utility::Pos& pos = Utility::Pos(), const Utility::Text& text = Utility::Text(), const Utility::Pos& size = Utility::Pos());
		virtual ~TextLabel() = default;

		virtual void Render();
		virtual bool Update(InputEvent input);

		void SetColor(const Utility::TextColor color);
		void SetText(const std::string& text);
		void SetSize(const Utility::Pos& size);

		Utility::TextColor& GetTextColor();
		std::string GetText();
		Utility::Pos& GetSize();
		virtual MenuItemType GetType();
		virtual bool IsInteractive() const;

	protected:
		Utility::Text text;
		Utility::Pos size;

	};
}
#endif