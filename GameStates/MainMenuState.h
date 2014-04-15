#pragma once
#include "IGameState.h"
#include "Game.h"
#include "../Menu.h"
class CMainMenuState :
	public IGameState
{
	enum menuReturn {play, options, credits, exit, count};
	CMenu* menu;

	CMainMenuState();
	virtual ~CMainMenuState();

	SGD::HTexture titleTexture = SGD::INVALID_HANDLE;

	SGD::HTexture backgroundStars1 = SGD::INVALID_HANDLE;
	SGD::HTexture backgroundStars2 = SGD::INVALID_HANDLE;
	SGD::HTexture backgroundSmoke = SGD::INVALID_HANDLE;

	//SGD::Point backgroundStars1Pos = SGD::Point{ 0, 0 };
	SGD::Point backgroundStars2Pos = SGD::Point{ 0, 0 };
	SGD::Point backgroundStars2PosSecond = SGD::Point{ 1024, 0 };

	SGD::Point backgroundSmokePos = SGD::Point{ 0, 0 };
	SGD::Point backgroundSmokePosSecond = SGD::Point{ 1024, 0 };

public:

	static CMainMenuState* GetInstance();

	bool Input();
	void Update(float dt);
	void Render();

	void Enter();
	void Exit();
};

