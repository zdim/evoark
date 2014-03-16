
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
	graphics = SGD::GraphicsManager::GetInstance();
	BackgroundImage = graphics->LoadTexture("Resources/Graphics/backgroundTmp.png");

	//JD's Test flock, ally and player
//	EnitityManager.Spawn(EntityType::Player, {100,150}, 1);
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
	//EnitityManager.Update(dt);
}

void	CGameState::Render(void)
{
	graphics->DrawTexture(BackgroundImage, { 0, 0 });
	//EnitityManager.Render();
}
