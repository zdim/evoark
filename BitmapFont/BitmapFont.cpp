#include "BitmapFont.h"
#include "../TinyXML/tinyxml.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <algorithm>
void		Fnt::Load(const char* filePath)
{
	TiXmlDocument file(filePath);
	if (!file.LoadFile())
	{
		while (true);
	}
	TiXmlElement* root = file.RootElement();
	TiXmlElement* elem = root->FirstChildElement();
	while (elem)
	{
		procElement(elem);
		elem = elem->NextSiblingElement();
	}
}

SGD::Size	Fnt::ComputeStringSpace(std::string str)//Returns the amount of space an entire string will occupy - Usefull for buttons
{
	float width = 0;
	float height = 0;

	for (unsigned int i = 0; i < str.length(); i++)
	{
		width += characters[str[i]].size.width + characters[str[i]].offset.x;
		height = std::max(characters[str[i]].size.height + characters[str[i]].offset.y, height);
	}
	return SGD::Size{width, height};
}

void		Fnt::Write(SGD::Point pos, std::string str)
{
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	SGD::Size stringSize = ComputeStringSpace(str);
	for (unsigned int i = 0; i < str.length(); i++)
	{
		FntChar ch = characters[str[i]];
		float oldY = pos.y;
		pos.y += stringSize.height - ch.size.height;
		graphics->DrawTextureSection(image, { pos.x, pos.y }, SGD::Rectangle(ch.imagePosition, ch.size));
		pos.x += ch.size.width;
		pos.y = oldY;
	}
	//graphics->DrawTexture(image, pos);
}

void Fnt::WriteCenter(SGD::Rectangle box, std::string str)
{
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	SGD::Size stringSize = ComputeStringSpace(str);
	SGD::Point pos;
	pos.x = (box.ComputeWidth() - stringSize.width)/2 + box.left;
	pos.y = (box.ComputeHeight() - stringSize.height)/2 + box.top;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		FntChar ch = characters[str[i]];
		float oldY = pos.y;
		pos.y += stringSize.height - ch.size.height;
		graphics->DrawTextureSection(image, { pos.x, pos.y }, SGD::Rectangle(ch.imagePosition, ch.size));
		pos.x += ch.size.width;
		pos.y = oldY;
	}
}

void Fnt::procElement(TiXmlElement* elem)
{
	if (strcmp(elem->Value(),"char") == 0)
	{
		int id;
		int x;
		int y;
		int w;
		int h;
		int xoff;
		int yoff;

		elem->Attribute("id", &id);
		elem->Attribute("x", &x);
		elem->Attribute("y", &y);
		elem->Attribute("width", &w);
		elem->Attribute("height", &h);
		elem->Attribute("xoffset", &xoff);
		elem->Attribute("yoffset", &yoff);

		characters[(char)id].imagePosition = SGD::Point{ (float)x, (float)y };
		characters[(char)id].size = SGD::Size{ (float)w, (float)h };
		characters[(char)id].offset = { float(xoff), float(yoff) };
		return;
	}
	if (strcmp(elem->Value(), "info") == 0)
		return;
	if (strcmp(elem->Value(), "common") == 0)
	{
		int scaleW;
		int scaleH;
		elem->Attribute("scaleW", &scaleW);
		elem->Attribute("scaleH", &scaleH);
		imageSize = SGD::Size{ (float)scaleW, (float)scaleH};
		return;
	}
	if (strcmp(elem->Value(), "pages") == 0)
	{
		std::string imageName = elem->FirstChildElement()->Attribute("file");
		std::string imagePath = "Resources/Graphics/" + imageName;
		image = SGD::GraphicsManager::GetInstance()->LoadTexture(imagePath.c_str(), { 0, 0, 0 });
		return;
	}
	if (strcmp(elem->Value(), "chars") == 0)
	{
		TiXmlElement* letter = elem->FirstChildElement();
		while (letter)
		{
			procElement(letter);
			letter = letter->NextSiblingElement();
		}
		return;
	}
}

void Fnt::Unload()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(image);
}
