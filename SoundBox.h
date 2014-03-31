#pragma once
#include "SGD Wrappers\SGD_Handle.h"
#include "SGD Wrappers\SGD_AudioManager.h"

class CSoundBox
{

	SGD::AudioManager* audio;
	SGD::HAudio playerLaserSFX = SGD::INVALID_HANDLE;

	SGD::HAudio creamMusic = SGD::INVALID_HANDLE;
public:
	enum sounds { playerLaser, cream, };

	static CSoundBox* GetInstance();
	void Enter();
	void Exit();

	void Play(int _soundEnum, bool _loop);

	CSoundBox();
	~CSoundBox();
};

