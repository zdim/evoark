#pragma once
#include "../Game.h"
#include "../../Menu.h"
#include "../IGameState.h"
class CGameOverState : public IGameState
{


	CGameOverState();
	~CGameOverState();

	float m_fTimer;
	float m_fDelay;

	enum menuReturn { play, exit, count };
	CMenu* menu;
	bool win; 



public:
	

	static CGameOverState* GetInstance();

	bool Input();
	void Update(float dt);
	void Render();

	void Enter();
	void Exit();

	void SetWin(bool s) { win = s; }
};

