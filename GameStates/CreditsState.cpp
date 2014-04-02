#include "CreditsState.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "Game.h"
CCreditsState::CCreditsState()
{
}


CCreditsState::~CCreditsState()
{
}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState instance;
	return &instance;
}

bool CCreditsState::Input()
{
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape) || SGD::InputManager::GetInstance()->IsButtonDown(0, 1))
	{
		Game::GetInstance()->PopState();
		return true;
	}

	return true;
}

void CCreditsState::Update(float dt)
{

}

void CCreditsState::Render()
{
	int screenWidth = Game::GetInstance()->GetScreenWidth();
	int screenHeight = Game::GetInstance()->GetScreenHeight();

	SGD::GraphicsManager::GetInstance()->DrawRectangle({ 0, 0, (float)screenWidth, (float)screenHeight }, { 0, 0, 0 });
	Game::GetInstance()->Font.WriteCenter( SGD::Rectangle{ { screenWidth * .25f, screenHeight * .1f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Credits");
	Game::GetInstance()->Font.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .3f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "John O'Leske");
	Game::GetInstance()->Font.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .35f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Rob Martinez");
	Game::GetInstance()->Font.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .5f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "JD Sullivan");
	Game::GetInstance()->Font.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .55f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Vladimir Golovan");
	Game::GetInstance()->Font.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .6f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Zach DiMarco");

}

void CCreditsState::Enter()
{

}

void CCreditsState::Exit()
{

}