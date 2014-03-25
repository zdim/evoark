#pragma once
#include "../Game.h"
#include "../../Menu.h"
#include "../IGameState.h"
class CGameOverState : public IGameState
{


	CGameOverState();
	~CGameOverState();

	enum menuReturn { play, exit, count };
	CMenu* menu;

public:
	

	static CGameOverState* GetInstance();

	bool Input();
	void Update(float dt);
	void Render();

	void Enter();
	void Exit();
};

