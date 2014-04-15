#include "../SoundBox.h"
#include "MainMenuState.h"

#include "ProfileSelectState.h"
#include "OptionsState.h"
#include "CreditsState.h"
//#include "PlaySelectState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"

CMainMenuState::CMainMenuState()
{
}

CMainMenuState* CMainMenuState::GetInstance()
{
	static CMainMenuState instance;
	return &instance;
}

CMainMenuState::~CMainMenuState()
{
}

bool CMainMenuState::Input()
{
	int ret = menu->Input();
	switch (ret)
	{
	case menuReturn::play:
		//Game::GetInstance()->PopState();

		Game::GetInstance()->PushState(CProfileSelectState::GetInstance());
		//Game::GetInstance()->PushState(CPlaySelectState::GetInstance());
		return true;
	case menuReturn::options:
		Game::GetInstance()->PushState(COptionsState::GetInstance());
		return true;
	case menuReturn::credits:
		Game::GetInstance()->PushState(CCreditsState::GetInstance());
		return true;
	case menuReturn::exit:
		Game::GetInstance()->PopState();
		return false;
	default:
		return true;
	}
}

void CMainMenuState::Update(float dt)
{
	//Uhm?? Maybe some time-based graphics? This is going to be a pretty boring menu right now.
	backgroundStars2Pos.x -= 3 * dt;
	backgroundStars2PosSecond.x -= 3 * dt;

	if (backgroundStars2Pos.x < -Game::GetInstance()->GetScreenWidth())
		backgroundStars2Pos.x = Game::GetInstance()->GetScreenWidth() * 2;

	if (backgroundStars2PosSecond.x < -Game::GetInstance()->GetScreenWidth())
		backgroundStars2PosSecond.x = Game::GetInstance()->GetScreenWidth() * 2;

	backgroundSmokePos.x -= 100 * dt;
	backgroundSmokePosSecond.x -= 100 * dt;

	if (backgroundSmokePos.x <= -1024)
		backgroundSmokePos.x = backgroundSmokePosSecond.x + 1024;

	if (backgroundSmokePosSecond.x <= -1024)
		backgroundSmokePosSecond.x = backgroundSmokePos.x + 1024;
}

void CMainMenuState::Render()
{
	SGD::GraphicsManager::GetInstance()->DrawTexture(backgroundStars1, { 0, 0 });
	SGD::GraphicsManager::GetInstance()->DrawTexture(backgroundStars2, backgroundStars2Pos);
	SGD::GraphicsManager::GetInstance()->DrawTexture(backgroundStars2, backgroundStars2PosSecond);
	SGD::GraphicsManager::GetInstance()->DrawTextureSection(backgroundSmoke, backgroundSmokePos, { 0, 0, 1024.f, 768.f }, 0, {}, { 40, 90, 100, 40 });
	SGD::GraphicsManager::GetInstance()->DrawTextureSection(backgroundSmoke, backgroundSmokePosSecond, { 0, 0, 1024.f, 768.f }, 0, {}, { 40, 90, 100, 40 });
	SGD::GraphicsManager::GetInstance()->DrawRectangle({ { 0, 0 }, SGD::Point{ Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() } }, { 50, 0, 0, 0 });
	if (Game::GetInstance()->GetTopState() != CProfileSelectState::GetInstance())
	{
		SGD::GraphicsManager::GetInstance()->DrawTexture(titleTexture, { Game::GetInstance()->GetScreenWidth() * .07f, Game::GetInstance()->GetScreenHeight() * .4f });
		SGD::GraphicsManager::GetInstance()->DrawLine({ Game::GetInstance()->GetScreenWidth() * .1f, Game::GetInstance()->GetScreenHeight() * .53f }, { Game::GetInstance()->GetScreenWidth() * .7f, Game::GetInstance()->GetScreenHeight() * .53f }, { 240, 255, 255, 255 });
		menu->Render();
	}
}

void CMainMenuState::Enter()
{
	std::vector<std::string> buttons;
	buttons.resize(menuReturn::count);
	buttons[menuReturn::play] = "Play";
	buttons[menuReturn::options] = "Options";
	buttons[menuReturn::credits] = "Credits";
	buttons[menuReturn::exit] = "Exit";
	menu = new CMenu(&Game::GetInstance()->FontPoiret, buttons, "", { Game::GetInstance()->GetScreenWidth() * .2f, Game::GetInstance()->GetScreenHeight() * .5f }, false, false);
	//CSoundBox::GetInstance()->Enter();
	CSoundBox::GetInstance()->Play(CSoundBox::sounds::ambient, true);

	titleTexture = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/EightOneTitle.png");

	backgroundStars1 = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/stars2new.png");
	backgroundStars2 = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/stars1new.png");
	backgroundSmoke = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/Smoke.png");

	//backgroundSmokePosSecond.x = 1024;
	//backgroundStars2PosSecond.x = 1024;
}

void CMainMenuState::Exit()
{
	//CSoundBox::GetInstance()->Exit();
	delete menu;
	menu = nullptr;
	SGD::GraphicsManager::GetInstance()->UnloadTexture(titleTexture);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(backgroundStars1);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(backgroundStars2);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(backgroundSmoke);
}
