#include "GameStates\Game.h"
#include "Menu.h"
#include "BitmapFont\BitmapFont.h"
#include "SGD Wrappers\SGD_GraphicsManager.h"
#include "SGD Wrappers\SGD_InputManager.h"
#include "SoundBox.h"
#include <algorithm>
#include "WinMain.h"
CMenu::CMenu(Fnt* _font, std::vector<std::string>buttonLabels, std::string _label, SGD::Point topMidPos, bool centered, bool fillWindow, bool _horizontal, SGD::Size buttonPadding, SGD::Size menuPadding, SGD::Size buttonSpacing)
{
	font = _font;
	label = _label;
	cursor = 0;
	horizontal = _horizontal;
	buttons.resize(buttonLabels.size());
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		buttons[i].label = buttonLabels[i];
	}
	SGD::Size buttonSize = {0,0};
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		std::string text = ">" + buttonLabels[i] + "<";
		SGD::Size temp = font->ComputeStringSpace(text);
		buttonSize.width = std::max(buttonSize.width, temp.width );
		buttonSize.height = std::max(buttonSize.height, temp.height);
	}
	buttonSize += buttonPadding;
	SGD::Size menuSize;
	SGD::Size labelSize = font->ComputeStringSpace(label) + buttonPadding * 2;
	if (horizontal)
	{
		menuSize.width = buttonSize.width * buttons.size() + buttonSpacing.width * (buttons.size() + 1);
		menuSize.width = std::max(menuSize.width, labelSize.width + buttonSpacing.width * 2);
		menuSize.height = buttonSize.height + buttonSpacing.height * 3 + labelSize.height;
	}
	else
	{
		menuSize.width = buttonSize.width + buttonSpacing.width * 2;
		menuSize.width = std::max(menuSize.width, labelSize.width + buttonSpacing.width * 2);
		menuSize.height = buttonSize.height * buttons.size() + labelSize.height + buttonSpacing.height * (buttons.size() + 2);
	}
	
	SGD::Point menuTL;

	if (topMidPos == SGD::Point{ 0, 0 })
	{
		menuTL.x = (Game::GetInstance()->GetScreenWidth() - menuSize.width) / 2;
		menuTL.y = (Game::GetInstance()->GetScreenHeight() - menuSize.height) / 2;
	}

	else
	{
		menuTL.x = topMidPos.x - menuSize.width * .5f;
		menuTL.y = topMidPos.y;
	}

	box = SGD::Rectangle(menuTL, menuSize);
	SGD::Point buttonTL;
	if (horizontal)
	{
		buttonTL.x = menuTL.x + buttonSpacing.width;
	}
	else if (centered)
	{
		buttonTL.x = (menuSize.width - buttonSize.width) / 2 + menuTL.x + buttonSpacing.width;
	}
	else if (!horizontal && !centered)
	{
		buttonTL.x = menuTL.x + 10;
	}
	buttonTL.y = menuTL.y + buttonSpacing.height;

	SGD::Rectangle labelBox = SGD::Rectangle(buttonTL,buttonSize);
	labelPoint.x = (labelBox.ComputeWidth() -labelSize.width)/2 + labelBox.left;
	labelPoint.y = (labelBox.ComputeHeight() - labelSize.height) / 2 + labelBox.top;
	buttonTL.y += buttonSize.height;

	if (horizontal)
	{
		for (unsigned int i = 0; i < buttons.size(); i++)
		{
			buttons[i].box = SGD::Rectangle(buttonTL, buttonSize);
			buttonTL.x += buttonSize.width + buttonSpacing.width;
		}
	}
	else
	{
		for (unsigned int i = 0; i < buttons.size(); i++)
		{
			buttons[i].box = SGD::Rectangle(buttonTL, buttonSize);
			buttonTL.y += buttonSize.height + buttonSpacing.height;
		}
	}

	if (fillWindow)
	{
		box.left = 0;
		box.top = 0;
		box.right = (float)Game::GetInstance()->GetScreenWidth();
		box.bottom = (float)Game::GetInstance()->GetScreenHeight();
	}
	else
	{
		box.left -= menuPadding.width;
		box.right += menuPadding.width;
		box.top -= menuPadding.height;
		box.bottom += menuPadding.height;
	}
}

int CMenu::Input()
{
	
	if (buttons.empty())
		return -2;	//Uninitiallized

	SGD::InputManager* input = SGD::InputManager::GetInstance();

	if (input->GetMouseMovement() != SGD::Vector{ 0, 0 })
	{
		SGD::Point mousePos = input->GetMousePosition();
		bool success = false;
		for (unsigned int i = 0; i < buttons.size(); i++)
		{
			if (mousePos.IsWithinRectangle(buttons[i].box))
			{
				if (cursor != i)
					CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
				cursor = i;
				success = true;
				break;
			}
		}
		if (success == false)
			cursor = -1;
	}
	if (horizontal)
	{
		if (input->IsKeyPressed(SGD::Key::Right) || input->IsDPadPressed(0, SGD::DPad::Right)) // || input->controllerstuff
		{
			if (cursor >= (int)buttons.size() - 1)
				cursor = 0;
			else
				cursor++;

			CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
		}
		if (input->IsKeyPressed(SGD::Key::Left) || input->IsDPadPressed(0, SGD::DPad::Left)) // || input->controllerstuff
		{
			if (cursor <= 0)
				cursor = buttons.size() - 1;
			else
				cursor--;

			CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
		}
	}
	else
	{
#if ARCADE
		SGD::Vector LeftJoystick = input->GetLeftJoystick(0);
		
#else
		if (input->IsKeyPressed(SGD::Key::Down) || input->IsDPadPressed(0, SGD::DPad::Down)) // || input->controllerstuff
		{
			if (cursor >= (int)buttons.size() - 1)
				cursor = 0;
			else
				cursor++;

			CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
		}
		if (input->IsKeyPressed(SGD::Key::Up) || input->IsDPadPressed(0, SGD::DPad::Up)) // || input->controllerstuff
		{
			if (cursor <= 0)
				cursor = buttons.size() - 1;
			else
				cursor--;

			CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiHighlight, false);
		}
#endif
	}
	if (input->IsKeyPressed(SGD::Key::Enter) || input->IsButtonPressed(0, 0))  // || input->controllerstuff
	{
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiEnter, false);
		return cursor;
	}

	if (input->IsKeyPressed(SGD::Key::MouseLeft))
	{
		for (unsigned int i = 0; i < buttons.size(); i++)
		{
			if (input->GetMousePosition().IsWithinRectangle(buttons[i].box))
			{
				CSoundBox::GetInstance()->Play(CSoundBox::sounds::uiEnter, false);
				return i;

			}
		}
	}
	
	return -1; //This specific int means no relevant input recieved.
}

void CMenu::Render()
{
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	//graphics->DrawRectangle(box, SGD::Color{0,0,0});
	font->Write(labelPoint, label);
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		//graphics->DrawRectangle(buttons[i].box, SGD::Color{1,1,1});
		std::string text;
		text = buttons[i].label;

		if (cursor == i)
			font->Write({ buttons[i].box.left, buttons[i].box.top }, text, true);

			//text = "=" + buttons[i].label + "=";
		else
			font->Write({ buttons[i].box.left, buttons[i].box.top }, text);
		//text = buttons[i].label;

		//font->WriteCenter(buttons[i].box, text);
	}
}
