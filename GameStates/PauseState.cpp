#include "OptionsState.h"
#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "UpgradeState.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"

#include "GameplayState.h" //Comment out later -- Debug stuff
#include "GameState.h"
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
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape) || SGD::InputManager::GetInstance()->IsButtonPressed(0, 1) || SGD::InputManager::GetInstance()->IsButtonPressed(0, 7))
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
	case menuReturn::ForceCheckpoint:
		CTestLevelState::GetInstance()->Save();
		return true;
	case menuReturn::ForceSave:
		CGameplayState::GetInstance()->SaveProfile();
		return true;
	case menuReturn::Upgrades:
		Game::GetInstance()->PushState(CUpgradeState::GetInstance());
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
	SGD::GraphicsManager::GetInstance()->DrawRectangle({ { 0, 0 }, SGD::Point{ Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() } }, { 50, 0, 0, 0 });
	menu->Render();
}

void CPauseState::Enter()
{
	std::vector<std::string> buttons;
	buttons.resize(menuReturn::count);
	buttons[menuReturn::Continue] = "Resume";
	buttons[menuReturn::ForceCheckpoint] = "[Checkpoint]";
	buttons[menuReturn::ForceSave] = "[Save]";
	buttons[menuReturn::Upgrades] = "Upgrades";
	buttons[menuReturn::MainMenu] = "Main Menu";
	buttons[menuReturn::Options] = "Options";
	menu = new CMenu(&Game::GetInstance()->FontPoiret, buttons, "Paused", { Game::GetInstance()->GetScreenWidth() * .2f, Game::GetInstance()->GetScreenHeight() * .4 }, false);
}

void CPauseState::Exit()
{
	delete menu;
	menu = nullptr;
}
