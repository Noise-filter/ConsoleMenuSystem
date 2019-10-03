#include "MenuFactory.h"

#include <fstream>

using namespace MenuSystem;

void MenuFactory::CreateTextLabel(Menu& menu, json::Array::ValueVector::iterator it)
{
	MenuFactory factory;
	auto label = std::make_shared<TextLabel>();
	label->SetText(factory.GetString(it, "text"));
	label->SetPosition(factory.GetPos(it));
	label->SetSize(factory.GetSize(it));
	label->SetColor(factory.GetTextColor(it, "color"));
	menu.AddMenuItem(factory.GetString(it, "uniqueName"), label);
}

void MenuFactory::CreateProgressBar(Menu& menu, json::Array::ValueVector::iterator it)
{
	MenuFactory factory;
	auto bar = std::make_shared<ProgressBar>();
	bar->SetText(factory.GetString(it, "text"));
	bar->SetPosition(factory.GetPos(it));
	bar->SetSize(factory.GetSize(it));
	bar->SetColor(factory.GetTextColor(it, "color"));
	bar->SetShowProcentValue(factory.GetBool(it, "showText"));
	menu.AddMenuItem(factory.GetString(it, "uniqueName"), bar);
}

void MenuFactory::CreateDrawArea(Menu& menu, json::Array::ValueVector::iterator it)
{
	MenuFactory factory;
	auto area = std::make_shared<DrawArea>(factory.GetPos(it), factory.GetSize(it));
	menu.AddMenuItem(factory.GetString(it, "uniqueName"), area);
}

void MenuFactory::CreateSprite(Menu& menu, json::Array::ValueVector::iterator it)
{
	MenuFactory factory;
	auto area = std::make_shared<Sprite>(factory.GetPos(it), factory.GetFloat(it, "updateFrequency"), factory.GetString(it, "filename"));
	menu.AddMenuItem(factory.GetString(it, "uniqueName"), area);
}

Utility::Pos MenuFactory::GetPos(json::Array::ValueVector::iterator it)
{
	Utility::Pos pos;

	json::Value p = it->ToObject()["pos"];
	if (p.GetType() != json::ArrayVal)
	{
		return pos;
	}

	int s = (int)p.ToArray().size();
	if (s > 0)
		pos.x = p.ToArray()[0].ToInt();
	if (s > 1)
		pos.y = p.ToArray()[1].ToInt();

	return pos;
}

Utility::Pos MenuFactory::GetSize(json::Array::ValueVector::iterator it)
{
	Utility::Pos size;

	json::Value p = it->ToObject()["size"];
	if (p.GetType() != json::ArrayVal)
	{
		return size;
	}

	int s = (int)p.ToArray().size();
	if (s > 0)
		size.x = p.ToArray()[0].ToInt();
	if (s > 1)
		size.y = p.ToArray()[1].ToInt();

	return size;
}

Utility::TextColor MenuFactory::GetTextColor(json::Array::ValueVector::iterator it, std::string name)
{
	json::Value v = it->ToObject()[name];
	if (v.GetType() != json::ObjectVal)
	{
		return Utility::TextColor();
	}

	return Utility::TextColor(GetColor(v, "text"), GetColor(v, "background"));
}

Utility::Color MenuFactory::GetColor(json::Value jsonColor, std::string name)
{
	Utility::Color color;
	json::Value bColor = jsonColor[name];
	if (bColor.GetType() == json::StringVal)
	{
		color = Utility::Color(bColor.ToString());
	}
	else if (bColor.GetType() == json::ArrayVal)
	{
		bool values[4] = { 0, 0, 0, 0 };
		for (int i = 0; i < 4 && i < (int)bColor.size(); i++)
		{
			values[i] = bColor.ToArray()[i].ToInt();
		}
		color = Utility::Color(values[0], values[1], values[2], values[3]);
	}

	return color;
}

std::string MenuFactory::GetString(json::Array::ValueVector::iterator it, const std::string name)
{
	json::Value v = it->ToObject()[name];
	if (v.GetType() != json::StringVal)
	{
		return "";
	}

	return v.ToString();
}

std::vector<std::string> MenuFactory::GetStrings(json::Array::ValueVector::iterator it, const std::string name)
{
	json::Value v = it->ToObject()[name];
	if (v.GetType() != json::ArrayVal && v.GetType() != json::StringVal)
	{
		return std::vector<std::string>();
	}

	std::vector<std::string> strings;

	if (v.GetType() == json::ArrayVal)
	{
		json::Array stringArray = v.ToArray();
		for (json::Array::ValueVector::iterator i = stringArray.begin(); i != stringArray.end(); i++)
		{
			strings.push_back(i->ToString());
		}
	}
	else if (v.GetType() == json::StringVal)
	{
		strings.push_back(v.ToString());
	}

	return strings;
}

bool MenuFactory::GetBool(json::Array::ValueVector::iterator it, const std::string name)
{
	json::Value v = it->ToObject()[name];
	if (v.GetType() != json::BoolVal)
	{
		return false;
	}

	return v.ToBool();
}

float MenuFactory::GetFloat(json::Array::ValueVector::iterator it, const std::string name)
{
	json::Value v = it->ToObject()[name];
	if (v.GetType() != json::FloatVal && v.GetType() != json::DoubleVal)
	{
		return false;
	}

	return v.ToFloat();
}

std::string MenuFactory::ReadFile(std::string filename)
{
	std::ifstream inFile(filename);
	if (!inFile)
	{
		return "";
	}

	std::string jsonFile;

	inFile.seekg(0, std::ios::end);
	jsonFile.reserve((unsigned int)inFile.tellg());
	inFile.seekg(0, std::ios::beg);

	jsonFile.assign((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

	return jsonFile;
}