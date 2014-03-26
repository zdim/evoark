#include "GameOverState.h"
#include "../GameplayState.h"

CGameOverState::CGameOverState()
{
	m_fTimer = 0;
	m_fDelay = 4;
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
			Game::GetInstance()->PopState();
			return true;
		case menuReturn::exit:
			Game::GetInstance()->PopState();
			return false;
		default:
			return true;
		}
	}
}

void CGameOverState::Update(float dt)
{
	m_fTimer += dt;
	if (m_fTimer < m_fDelay)
	{
		Game::GetInstance()->GetLevelState()->Update(dt);
	}
}

void CGameOverState::Render()
{
	if (m_fTimer > m_fDelay )
	menu->Render();
}

void CGameOverState::Enter()
{
	std::vector<std::string> buttons;
	buttons.resize(menuReturn::count);
	buttons[menuReturn::play] = "Again";
	buttons[menuReturn::exit] = "Exit";
	menu = new CMenu(&Game::GetInstance()->Font, buttons, "You Lost!!", true);
}

void CGameOverState::Exit()
{
	delete menu;
	menu = nullptr;
}
