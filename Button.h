#pragma once
#include "SGD Wrappers\SGD_Geometry.h"
#include <string>
#include <vector>

class Button
{
	SGD::Rectangle box;
	std::string label;
public:
	SGD::Rectangle GetBox() {return box;}
	std::string GetLabel() {return label;}
	void SetBox(SGD::Rectangle newBox) {box = newBox;}
	void SetLabel(std::string newLabel) {label = newLabel;}
	void Render(bool selected);
	Button();
	~Button();
};

class Menu
{
	SGD::Rectangle box;
	std::vector<Button> buttons;
	short cursor;
	std::string label;
public:
	SGD::Rectangle GetBox() {return box;}
	std::string GetLabel() {return label;}
	void SetBox(SGD::Rectangle newBox) {box = newBox;}
	void SetLabel(std::string newLabel) {label = newLabel;}
	void AddButton(std::string label);
	void Render();
	short Update();
	Menu(){}
	~Menu(){}
};