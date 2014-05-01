#pragma once
#include <map>
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../TinyXML/tinyxml.h"
#include "../SGD Wrappers/SGD_Handle.h"
struct FntChar
{
	SGD::Size size;
	SGD::Point imagePosition;
	SGD::Vector offset;
};

class Fnt
{
	SGD::Size imageSize;
	std::map<char, FntChar> characters;
	SGD::HTexture image;

	void procElement(TiXmlElement* elem);
public:
	Fnt(){};
	~Fnt(){};

	void Load(const char* file);
	void Unload();
	SGD::Size ComputeStringSpace(std::string str); //Returns the amount of space an entire string will occupy - Usefull for buttons
	void Write(SGD::Point pos, std::string str, bool selected = false, char opacity = (char)255);
	void WriteCenter(SGD::Rectangle box, std::string str, bool selected = false);

};