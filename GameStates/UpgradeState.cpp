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

	if (input->IsKeyPressed(SGD::Key::Enter))
	{
		switch (cursor)
		{
		case laserOne:
			if (player->GetPerks() > 0 && player->GetLaserLevel() == 0)
			{
				player->LaserLevelUp();
				player->RemovePerk();
			}
			break;
		case laserTwo:
			if (player->GetPerks() > 0 && player->GetLaserLevel() == 1)
			{
				player->LaserLevelUp();
				player->RemovePerk();
			}
			break;
		case laserThree:
			if (player->GetPerks() > 1 && player->GetLaserLevel() == 2)
			{
				player->LaserLevelUp();
				player->RemovePerk(); player->RemovePerk();
			}
			break;
		case missileOne:
			if (player->GetPerks() > 0 && player->GetMissileLevel() == 0)
			{
				player->MissileLevelUp();
				player->RemovePerk();
			}
			break; 
		case missileTwo:
			if (player->GetPerks() > 0 && player->GetMissileLevel() == 1)
			{
				player->MissileLevelUp();
				player->RemovePerk();
			}
			break;
		case missileThree:
			if (player->GetPerks() > 1 && player->GetMissileLevel() == 2)
			{
				player->MissileLevelUp();
				player->RemovePerk(); player->RemovePerk();
			}
			break;
		case wellOne:
			if (player->GetPerks() > 0 && player->GetWellLevel() == 0)
			{
				player->WellLevelUp();
				player->RemovePerk();
			}
			break;
		case wellTwo:
			if (player->GetPerks() > 0 && player->GetWellLevel() == 1)
			{
				player->WellLevelUp();
				player->RemovePerk();
			}
			break;
		case wellThree:
			if (player->GetPerks() > 1 && player->GetWellLevel() == 2)
			{
				player->WellLevelUp();
				player->RemovePerk(); player->RemovePerk();
			}
			break;
		case pushOne:
			if (player->GetPerks() > 0 && player->GetPushLevel() == 0)
			{
				player->PushLevelUp();
				player->RemovePerk();
			}
			break;
		case pushTwo:
			if (player->GetPerks() > 0 && player->GetPushLevel() == 1)
			{
				player->PushLevelUp();
				player->RemovePerk();
			}
			break;
		case pushThree:
			if (player->GetPerks() > 1 && player->GetPushLevel() == 2)
			{
				player->PushLevelUp();
				player->RemovePerk(); player->RemovePerk();
			}
			break;
		case warpOne:
			if (player->GetPerks() > 0 && player->GetWarpLevel() == 0)
			{
				player->WarpLevelUp();
				player->RemovePerk();
			}
			break;
		case warpTwo:
			if (player->GetPerks() > 0 && player->GetWarpLevel() == 1)
			{
				player->WarpLevelUp();
				player->RemovePerk();
			}
			break;
		case warpThree:
			if (player->GetPerks() > 1 && player->GetWarpLevel() == 2)
			{
				player->WarpLevelUp();
				player->RemovePerk(); player->RemovePerk();
			}
			break;
		default:
			break;
		}
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

	switch (player->GetLaserLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .15f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .15f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .15f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	switch (player->GetMissileLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .3f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .3f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .3f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	switch (player->GetWarpLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .45f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .45f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .45f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	switch (player->GetWellLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .6f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .6f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .6f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	switch (player->GetPushLevel())
	{
	case 0:
		graphics->DrawRectangle({ { screenWidth * .75f, screenHeight * .25f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 1:
		graphics->DrawRectangle({ { screenWidth * .75f, screenHeight * .4f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
	case 2:
		graphics->DrawRectangle({ { screenWidth * .75f, screenHeight * .55f }, SGD::Size{ 64, 64 } }, { 200, 200, 200, 150 });
		break;
	default:
		break;
	}

	// draw selected box
	graphics->DrawRectangle({ { screenWidth * .15f * (cursor / 3 + 1), screenHeight * (.55f - (cursor % 3) * .15f) }, SGD::Size{ 64, 64 } }, { 0, 0, 0, 0 }, { 255, 255, 255 }, 2);
}

void CUpgradeState::Enter()
{
	iconTexture = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/upgradeIcon.png");
	player = CEntityManager::GetInstance()->GetPlayer();
}

void CUpgradeState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(iconTexture);
}