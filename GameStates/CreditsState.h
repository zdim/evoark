#pragma once
#include "IGameState.h"
#include "../Menu.h"
class CCreditsState :
	public IGameState
{
	enum menuReturn { back, count };
	CMenu* menu;
public:
	CCreditsState();
	virtual ~CCreditsState();

	static CCreditsState* GetInstance();

	bool Input();
	void Update(float dt);
	void Render();

	void Enter();
	void Exit();

};

