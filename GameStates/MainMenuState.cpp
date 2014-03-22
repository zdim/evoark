
#include "MainMenuState.h"
#include "GameplayState.h"

CMainMenuState::CMainMenuState()
{
}

CMainMenuState* CMainMenuState::GetInstance()
{
	static CMainMenuState instance;
	return &instance;
}

CMainMenuState::~CMainMenuState()
{
}

bool CMainMenuState::Input()
{
	int ret = menu->Input();
	switch (ret)
	{
	case menuReturn::play:
		Game::GetInstance()->PopState();
		Game::GetInstance()->PushState(CGameplayState::GetInstance());
		return true;
	case menuReturn::exit:
		Game::GetInstance()->PopState();
		return false;
	default:
		return true;
	}
}

void CMainMenuState::Update(float dt)
{
	//Uhm?? Maybe some time-based graphics? This is going to be a pretty boring menu right now.
}

void CMainMenuState::Render()
{
	menu->Render();
}

void CMainMenuState::Enter()
{
	std::vector<std::string> buttons;
	buttons.resize(menuReturn::count);
	buttons[menuReturn::play] = "Play";
	buttons[menuReturn::exit] = "Exit";
	menu = new CMenu(&Game::GetInstance()->Font, buttons, "EvoArk!!", true);
}

void CMainMenuState::Exit()
{
	delete menu;
	menu = nullptr;
}
