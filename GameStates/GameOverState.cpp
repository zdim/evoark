#include "GameOverState.h"
#include "GameplayState.h"
#include "Game.h"
#include "GameState.h"
#include "CreditsState.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"


CGameOverState::CGameOverState()
{
	m_fTimer = 0;
	m_fDelay = 2;
	win = false;
}


CGameOverState::~CGameOverState()
{
}

CGameOverState* CGameOverState::GetInstance()
{
	static CGameOverState instance;
	return &instance;
}


bool CGameOverState::Input()
{
	if (m_fTimer > m_fDelay)
	{

		int ret = menu->Input();
		switch (ret)
		{
		case menuReturn::play:
			Game::GetInstance()->PopState();
			if (CGameplayState::GetInstance()->GetLevel() == Level::Final && CTestLevelState::GetInstance()->GetBossStatus() == true)
			{
				CGameplayState::GetInstance()->SetLevel(Level::Gen1);
				Game::GetInstance()->PopState();
				Game::GetInstance()->PopState();
				Game::GetInstance()->PushState(CMainMenuState::GetInstance());
				Game::GetInstance()->PushState(CCreditsState::GetInstance());
			}
			else
				Game::GetInstance()->PopState();

			return true;
		case menuReturn::mainmenu:
			Game::GetInstance()->PopState();
			Game::GetInstance()->PopState();
			Game::GetInstance()->PushState(CMainMenuState::GetInstance());
			return true;
		case menuReturn::exit:
			Game::GetInstance()->PopState();
			Game::GetInstance()->PopState();
			Game::GetInstance()->PopState();
			return false;
		default:
			return true;
		}
	}
	return true;
}

void CGameOverState::Update(float dt)
{
	m_fTimer += dt;
	if (m_fTimer < m_fDelay)
	{
		Game* _game = Game::GetInstance();
		Game::GetInstance()->GetLevelState()->Update(dt);
	}
}

void CGameOverState::Render()
{

	if (m_fTimer > m_fDelay)
	{
		SGD::GraphicsManager::GetInstance()->DrawRectangle({ { 0, 0 }, SGD::Point{ (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() } }, { 100, 0, 0, 0 });
		menu->Render();
	}
}

void CGameOverState::Enter()
{
	std::vector<std::string> buttons;
	buttons.resize(menuReturn::count);
	buttons[menuReturn::play] = "Continue";
	buttons[menuReturn::mainmenu] = "Main Menu";
	buttons[menuReturn::exit] = "Exit";

	if ( win == false )
		menu = new CMenu(&Game::GetInstance()->FontPoiret, buttons, "You Died", { 0, 0 }, true);
	if (win == true)
		menu = new CMenu(&Game::GetInstance()->FontPoiret, buttons, "You Win!", { 0, 0 }, true);
}

void CGameOverState::Exit()
{
	delete menu;
	menu = nullptr;
}
