#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "UpgradeState.h"
#include "Game.h"

CUpgradeState::CUpgradeState()
{
}


CUpgradeState::~CUpgradeState()
{
}

CUpgradeState* CUpgradeState::GetInstance()
{
	static CUpgradeState instance;
	return &instance;
}

bool CUpgradeState::Input()
{
	SGD::InputManager* input = SGD::InputManager::GetInstance();

	if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
	{
		Game::GetInstance()->PopState();
		return true;
	}

	if (input->IsKeyPressed(SGD::Key::Up))
	{
		if (cursor == laserThree || cursor == missileThree || cursor == warpThree || cursor == wellThree || cursor == pushThree)
			cursor -= 2;
		else
			cursor++;
	}

	else if (input->IsKeyPressed(SGD::Key::Down))
	{
		if (cursor == laserOne || cursor == missileOne || cursor == warpOne || cursor == wellOne || cursor == pushOne)
			cursor += 2;
		else
			cursor--;
	}

	else if (input->IsKeyPressed(SGD::Key::Right))
	{
		if (cursor == pushOne || cursor == pushTwo || cursor == pushThree)
			cursor -= 12;
		else
			cursor += 3;
	}

	else if (input->IsKeyPressed(SGD::Key::Left))
	{
		if (cursor == laserOne || cursor == laserTwo || cursor == laserThree)
			cursor += 12;
		else
			cursor -= 3;
	}

	return true;
}

void CUpgradeState::Update(float dt)
{
	//Um...
}

void CUpgradeState::Render()
{
	int screenWidth = Game::GetInstance()->GetScreenWidth();
	int screenHeight = Game::GetInstance()->GetScreenHeight();
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	graphics->DrawRectangle({ 0, 0, (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() }, { 0, 0, 0 });
	Game::GetInstance()->Font.WriteCenter({ screenWidth * .15f,  screenHeight * .75f, screenWidth * .30f, screenHeight * .85f }, "Lasers");
	Game::GetInstance()->Font.WriteCenter({ screenWidth * .30f, screenHeight * .75f, screenWidth * .45f, screenHeight * .85f }, "Missiles");
	Game::GetInstance()->Font.WriteCenter({ screenWidth * .45f, screenHeight * .75f, screenWidth * .60f, screenHeight * .85f }, "Warp");
	Game::GetInstance()->Font.WriteCenter({ screenWidth * .60f, screenHeight * .75f, screenWidth * .75f, screenHeight * .85f }, "Well");
	Game::GetInstance()->Font.WriteCenter({ screenWidth * .75f, screenHeight * .75f, screenWidth * .9f,  screenHeight * .85f }, "Push");

	// draw upgrade boxes / icons
	graphics->DrawTexture(iconTexture, { screenWidth * .15f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .15f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .15f, screenHeight * .55f });
	graphics->DrawTexture(iconTexture, { screenWidth * .30f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .30f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .30f, screenHeight * .55f });
	graphics->DrawTexture(iconTexture, { screenWidth * .45f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .45f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .45f, screenHeight * .55f });
	graphics->DrawTexture(iconTexture, { screenWidth * .60f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .60f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .60f, screenHeight * .55f });
	graphics->DrawTexture(iconTexture, { screenWidth * .75f, screenHeight * .25f });
	graphics->DrawTexture(iconTexture, { screenWidth * .75f, screenHeight * .4f });
	graphics->DrawTexture(iconTexture, { screenWidth * .75f, screenHeight * .55f });

	// draw selected box
	graphics->DrawRectangle({ { screenWidth * .15f * (cursor / 3 + 1), screenHeight * (.55f - (cursor % 3) * .15f) }, SGD::Size{ 64, 64 } }, { 0, 0, 0, 0 }, { 255, 255, 255 }, 2);
}

void CUpgradeState::Enter()
{
	iconTexture = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/upgradeIcon.png");

}

void CUpgradeState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(iconTexture);
}