#pragma once
#include "IGameState.h"

#include "../Menu.h"

class CPlaySelectState : public IGameState
{
	enum menuReturn { cont, newgame, loadgame, tutorial, back, count };
	CMenu* menu;

public:
	CPlaySelectState();
	virtual ~CPlaySelectState();

	static CPlaySelectState* GetInstance();

	bool Input();
	void Update(float dt);
	void Render();

	void Enter();
	void Exit();
};

