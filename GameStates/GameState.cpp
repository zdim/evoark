
#include "GameState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"


CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

CGameState* CGameState::GetInstance(void)
{
	static CGameState instance;
	return &instance;
}

void	CGameState::Enter(void)
{
	BackgroundImage = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/backgroundTmp.png");
}

void	CGameState::Exit(void)
{

}

bool	CGameState::Input(void)
{
	return true;
}

void	CGameState::Update(float dt)
{

}

void	CGameState::Render(void)
{
	SGD::GraphicsManager::GetInstance()->DrawTexture(BackgroundImage, { 0, 0});
}
