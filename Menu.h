#pragma once
#include <vector>
#include "SGD Wrappers\SGD_Geometry.h"
#include "Menu.h"

class Fnt;

struct CButton
{
	SGD::Rectangle box;
	std::string label;
};

class CMenu
{
	SGD::Rectangle box;
	std::vector<CButton> buttons;
	std::string label;
	SGD::Point labelPoint;
	Fnt* font;
	int cursor;

public:
	//CMenu();
	CMenu(Fnt* font, std::vector<std::string>buttonLabels,std::string label, bool fillWindow = false, bool horizontal = false, SGD::Size buttonPadding = {10, 10}, SGD::Size menuPadding = {10, 10}, SGD::Size buttonSpacing = {5,5});
	int Input();
	void Render();
	int GetCursor() { return cursor; }
};