#include "Utility.h"

#include <Windows.h>

using namespace MenuSystem::Utility;

using namespace std;

/*********************************
			Pos
**********************************/

Pos::Pos(int X, int Y) : x(X), y(Y)
{}

Pos::Pos(const Pos& obj)
{
	this->x = obj.x;
	this->y = obj.y;
}

Pos& Pos::operator =(const Pos& obj)
{
	this->x = obj.x;
	this->y = obj.y;
	return *this;
}

Pos& Pos::operator -=(const Pos& obj)
{
	this->x -= obj.x;
	this->y -= obj.y;
	return *this;
}

Pos& Pos::operator +=(const Pos& obj)
{
	this->x += obj.x;
	this->y += obj.y;
	return *this;
}

Pos& Pos::operator *=(const Pos& obj)
{
	this->x *= obj.x;
	this->y *= obj.y;
	return *this;
}

Pos& Pos::operator /=(const Pos& obj)
{
	this->x /= obj.x;
	this->y /= obj.y;
	return *this;
}

bool Pos::operator ==(const Pos& obj)
{
	return (this->x == obj.x && this->y == obj.y);
}

bool Pos::operator !=(const Pos& obj)
{
	return !(*this == obj);
}


/*********************************
			Color
**********************************/

Color ConvertColor(const COLOR color);
COLOR ConvertColor(const Color& color);

Color::Color(bool red, bool green, bool blue, bool intensity)
{
	value[0] = red;
	value[1] = green;
	value[2] = blue;
	value[3] = intensity;
}

Color::Color(COLOR color)
{
	*this = ConvertColor(color);
}

bool Color::operator ==(const Color& obj)
{
	return (value[0] == obj.value[0] && value[1] == obj.value[1] && value[2] == obj.value[2] && value[3] == obj.value[3]);
}

bool Color::operator !=(const Color& obj)
{
	return !(*this == obj);
}

bool Color::operator ==(const COLOR& color)
{
	return (*this == ConvertColor(color));
}

bool Color::operator !=(const COLOR& color)
{
	return (*this != ConvertColor(color));
}

/*********************************
			TextColor
**********************************/

TextColor::TextColor(Color text, Color background) : textColor(text), backgroundColor(background)
{}

short TextColor::GetColor()
{
	short attributes = 0;

	if(textColor.value[0]) attributes |= FOREGROUND_RED;
	if(textColor.value[1]) attributes |= FOREGROUND_GREEN;
	if(textColor.value[2]) attributes |= FOREGROUND_BLUE;
	if(textColor.value[3]) attributes |= FOREGROUND_INTENSITY;
	
	if(backgroundColor.value[0]) attributes |= BACKGROUND_RED;
	if(backgroundColor.value[1]) attributes |= BACKGROUND_GREEN;
	if(backgroundColor.value[2]) attributes |= BACKGROUND_BLUE;
	if(backgroundColor.value[3]) attributes |= BACKGROUND_INTENSITY;

	return attributes;
}

bool TextColor::operator ==(const TextColor& obj)
{
	return (this->textColor == obj.textColor && this->backgroundColor == obj.backgroundColor);
}

bool TextColor::operator !=(const TextColor& obj)
{
	return !(*this == obj);
}

/*********************************
			Text
**********************************/

Text::Text(string text, TextColor color)
	: textString(text), color(color)
{}

//Helper function for converting enum 'COLOR' to a Color struct.
Color ConvertColor(const COLOR color)
{
	switch(color)
	{
	case COLOR_Red:					return Color(1, 0, 0, 0);
	case COLOR_Red_Intense:			return Color(1, 0, 0, 1);
	case COLOR_Green:				return Color(0, 1, 0, 0);
	case COLOR_Green_Intense:		return Color(0, 1, 0, 1);
	case COLOR_Blue:				return Color(0, 0, 1, 0);
	case COLOR_Blue_Intense:		return Color(0, 0, 1, 1);

	case COLOR_Yellow:				return Color(1, 1, 0, 0);
	case COLOR_Yellow_Intense:		return Color(1, 1, 0, 1);
	case COLOR_Magenta:				return Color(1, 0, 1, 0);
	case COLOR_Magenta_Intense:		return Color(1, 0, 1, 1);
	case COLOR_Cyan:				return Color(0, 1, 1, 0);
	case COLOR_Cyan_Intense:		return Color(0, 1, 1, 1);

	case COLOR_Black:				return Color(0, 0, 0, 0);
	case COLOR_Black_Intense:									//Same as COLOR_Gray
	case COLOR_Gray:				return Color(0, 0, 0, 1);	//Same as COLOR_Black_Intense
	case COLOR_White:				return Color(1, 1, 1, 0);
	case COLOR_White_Intense:		return Color(1, 1, 1, 1);

	default:						return Color(1, 1, 1, 0);
	}
	return Color(1, 1, 1, 0);
}

//Helper function for converting Color struct to a enum COLOR.
COLOR ConvertColor(const Color& color)
{
	if(Color(1, 0, 0, 0) == color)	return COLOR_Red;
	if(Color(1, 0, 0, 1) == color)	return COLOR_Red_Intense;
	if(Color(0, 1, 0, 0) == color)	return COLOR_Green;
	if(Color(0, 1, 0, 1) == color)	return COLOR_Green_Intense;
	if(Color(0, 0, 1, 0) == color)	return COLOR_Blue;
	if(Color(0, 0, 1, 1) == color)	return COLOR_Blue_Intense;

	if(Color(1, 1, 0, 0) == color)	return COLOR_Yellow;
	if(Color(1, 1, 0, 1) == color)	return COLOR_Yellow_Intense;
	if(Color(1, 0, 1, 0) == color)	return COLOR_Magenta;
	if(Color(1, 0, 1, 1) == color)	return COLOR_Magenta_Intense;
	if(Color(0, 1, 1, 0) == color)	return COLOR_Cyan;
	if(Color(0, 1, 1, 1) == color)	return COLOR_Cyan_Intense;

	if(Color(0, 0, 0, 0) == color)	return COLOR_Black;
	//if(color == Color(0, 0, 0, 1))	return COLOR_Black_Intense;	//Same as COLOR_Gray
	if(Color(0, 0, 0, 1) == color)	return COLOR_Gray;				//Same as COLOR_Black_Intense
	if(Color(1, 1, 1, 0) == color)	return COLOR_White;
	if(Color(1, 1, 1, 1) == color)	return COLOR_White_Intense;

	return Color_Unknown;
}