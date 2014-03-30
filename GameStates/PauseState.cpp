#include "OptionsState.h"
#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "../SGD Wrappers/SGD_InputManager.h"
CPauseState::CPauseState()
{
}


CPauseState::~CPauseState()
{
}

CPauseState* CPauseState::GetInstance()
{
	static CPauseState instance;
	return &instance;
}

bool CPauseState::Input()
{
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape) || SGD::InputManager::GetInstance()->IsButtonPressed(0, 1))
	{
		Game::GetInstance()->PopState();
		return true;
	}
	int ret = menu->Input();
	switch (ret)
	{
	case menuReturn::Continue:
		Game::GetInstance()->PopState();
		return true;
	case menuReturn::Reload:
		Game::GetInstance()->PopState();
		Game::GetInstance()->PopState();
		return true;
	case menuReturn::Options:
		Game::GetInstance()->PushState(COptionsState::GetInstance());
		return true;
	case menuReturn::MainMenu:
		Game::GetInstance()->PopState();
		Game::GetInstance()->PopState();
		Game::GetInstance()->PopState();
		Game::GetInstance()->PushState(CMainMenuState::GetInstance());
		return true;
	default:
		return true;
	}
}

void CPauseState::Update(float dt)
{
	//Um...
}

void CPauseState::Render()
{
	menu->Render();
}

void CPauseState::Enter()
{
	std::vector<std::string> buttons;
	buttons.resize(menuReturn::count);
	buttons[menuReturn::Continue] = "Continue";
	buttons[menuReturn::Reload] = "[Reload]";
	buttons[menuReturn::MainMenu] = "Main Menu";
	buttons[menuReturn::Options] = "Options";
	menu = new CMenu(&Game::GetInstance()->Font, buttons, "Paused");
}

void CPauseState::Exit()
{
	delete menu;
	menu = nullptr;
}
