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
public:

	static CMainMenuState* GetInstance();

	bool Input();
	void Update(float dt);
	void Render();

	void Enter();
	void Exit();
};

