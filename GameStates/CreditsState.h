#pragma once
#include "IGameState.h"
class CCreditsState :
	public IGameState
{
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

