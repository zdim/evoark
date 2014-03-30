#pragma once
#include "IGameState.h"
#include "Game.h"
#include "../Menu.h"
#include "../SoundBox.h"
class COptionsState : public IGameState
{
	enum menuReturn {sfx, music, fullscreen, back, count};
	CMenu* menu = nullptr;

	COptionsState();
	virtual ~COptionsState();

	int sfxVolume = 0;
	int musicVolume = 0;
	bool fullscreenOn = false;

	CSoundBox* soundBox = nullptr;
public:

	static COptionsState* GetInstance();

	bool Input();
	void Update(float dt);
	void Render();

	void Enter();
	void Exit();
};

