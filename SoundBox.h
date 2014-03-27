#pragma once
#include "SGD Wrappers\SGD_Handle.h"
#include "SGD Wrappers\SGD_AudioManager.h"

class CSoundBox
{

	SGD::AudioManager* audio;
	SGD::HAudio playerLaserSFX = SGD::INVALID_HANDLE;
public:
	enum sounds { playerLaser, };

	static CSoundBox* GetInstance();
	void Enter();
	void Exit();

	void Play(int _soundEnum);

	CSoundBox();
	~CSoundBox();
};

