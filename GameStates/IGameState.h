#pragma once
class IGameState
{
public:
	IGameState();
	virtual ~IGameState();

	virtual bool Input();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Exit();
	virtual void Enter();
};

