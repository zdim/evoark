
#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"

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
	menu = new CMenu(&Game::GetInstance()->Font, buttons, "Paused");
}

void CPauseState::Exit()
{
	delete menu;
	menu = nullptr;
}
