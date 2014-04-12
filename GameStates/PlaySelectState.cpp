#include "PlaySelectState.h"
#include "Game.h"
#include "GameplayState.h"

CPlaySelectState::CPlaySelectState()
{
}


CPlaySelectState::~CPlaySelectState()
{
}

CPlaySelectState* CPlaySelectState::GetInstance()
{
	static CPlaySelectState instance;
	return &instance;
}

bool CPlaySelectState::Input()
{
	int ret = menu->Input();
	switch (ret)
	{
	case menuReturn::newgame:
		Game::GetInstance()->PopState();
		
		Game::GetInstance()->PushState(CGameplayState::GetInstance());
		return true;
	case menuReturn::tutorial:
		CGameplayState::GetInstance()->SetLevel(Level::Tutorial);
		Game::GetInstance()->PushState(CGameplayState::GetInstance());
		return true;
	case menuReturn::back:
		Game::GetInstance()->PopState();
		return false;
	default:
		return true;
	}
}

void CPlaySelectState::Update(float dt)
{

}

void CPlaySelectState::Render()
{
	menu->Render();
}

void CPlaySelectState::Enter()
{
	std::vector<std::string> buttons;
	buttons.resize(menuReturn::count);
	buttons[menuReturn::cont] = "Continue";
	buttons[menuReturn::newgame] = "New Game";
	buttons[menuReturn::loadgame] = "Load Game";
	buttons[menuReturn::tutorial] = "Tutorial";
	buttons[menuReturn::back] = "Back";
	menu = new CMenu(&Game::GetInstance()->Font, buttons, "EvoArk", { 0, 0 }, true);
}

void CPlaySelectState::Exit()
{
	delete menu;
	menu = nullptr;
}