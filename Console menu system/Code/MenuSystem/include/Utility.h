#ifndef UTILITY_H
#define UTILITY_H

#include <array>
#include <string>

namespace MenuSystem
{
	namespace Utility
	{
		struct Pos
		{
			Pos(int X = 0, int Y = 0);

			Pos& operator =(const Pos& obj);

			Pos& operator -=(const Pos& obj);
			Pos& operator +=(const Pos& obj);
			Pos& operator *=(const Pos& obj);
			Pos& operator /=(const Pos& obj);

			friend Pos operator-(Pos lhs, const Pos& rhs);

			bool operator ==(const Pos& obj);
			bool operator !=(const Pos& obj);

			int x;
			int y;
		};

		Pos abs(const Pos& pos);

		enum COLOR
		{
			COLOR_Red,
			COLOR_Red_Intense,
			COLOR_Green,
			COLOR_Green_Intense,
			COLOR_Blue,
			COLOR_Blue_Intense,

			COLOR_Yellow,
			COLOR_Yellow_Intense,
			COLOR_Magenta,
			COLOR_Magenta_Intense,
			COLOR_Cyan,
			COLOR_Cyan_Intense,

			COLOR_Black,
			COLOR_Black_Intense,			//Same as COLOR_Gray
			COLOR_Gray,						//Same as COLOR_Black_Intense
			COLOR_White,
			COLOR_White_Intense,

			COLOR_Count,
			COLOR_Unknown = -1,
		};

		struct Color
		{
			Color(bool red = false, bool green = false, bool blue = false, bool Intense = false);
			Color(COLOR color);
			Color(std::string colorName);

			bool operator ==(const Color& obj);
			bool operator !=(const Color& obj);

			bool operator ==(const COLOR& color);
			bool operator !=(const COLOR& color);

			//Red, Green, Blue, Intense
			std::array<bool, 4> value;
		};

		struct TextColor
		{
			TextColor(Color text = Color(COLOR_White), Color background = Color(COLOR_Black));

			unsigned short GetColor() const;

			bool operator ==(const TextColor& obj);
			bool operator !=(const TextColor& obj);

			Color textColor;
			Color backgroundColor;
		};

		struct Text
		{
			Text(const std::string& text = "", TextColor color = TextColor());
			Text(std::string&& text, TextColor color);

			std::string textString;
			TextColor color;
		};
	}
}

#endif