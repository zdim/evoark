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
	Game::GetInstance()->FontPoiret.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .1f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Credits");
	Game::GetInstance()->FontPoiret.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .3f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Executive Producer - John O'Leske");
	Game::GetInstance()->FontPoiret.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .35f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Associate Producer - Rob Martinez");
	Game::GetInstance()->FontPoiret.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .5f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Programmer - JD Sullivan");
	Game::GetInstance()->FontPoiret.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .55f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Programmer - Vladimir Golovan");
	Game::GetInstance()->FontPoiret.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .6f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Programmer - Zach DiMarco");
	Game::GetInstance()->FontPoiret.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .65f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Artist - Gregory Bay");
	Game::GetInstance()->FontPoiret.WriteCenter(SGD::Rectangle{ { screenWidth * .25f, screenHeight * .7f }, SGD::Size{ screenWidth * .5f, screenHeight * .1f } }, "Artist - Caris Frazier");

}

void CCreditsState::Enter()
{

}

void CCreditsState::Exit()
{

}