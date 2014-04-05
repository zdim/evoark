#pragma once
#include "SGD Wrappers\SGD_Handle.h"
#include "SGD Wrappers\SGD_AudioManager.h"

class CSoundBox
{

	SGD::AudioManager* audio;

	SGD::HAudio uiHighlightSFX = SGD::INVALID_HANDLE;
	SGD::HAudio uiSuccessSFX = SGD::INVALID_HANDLE;
	SGD::HAudio uiFailureSFX = SGD::INVALID_HANDLE;

	SGD::HAudio playerLaserSFX = SGD::INVALID_HANDLE;
	SGD::HAudio playerMissileSFX = SGD::INVALID_HANDLE;
	SGD::HAudio playerWarpSFX = SGD::INVALID_HANDLE;
	SGD::HAudio playerLevelUpSFX = SGD::INVALID_HANDLE;

	SGD::HAudio creamMusic = SGD::INVALID_HANDLE;
public:
	enum sounds { uiHighlight, uiSuccess, uiFailure, playerLaser, playerMissile, playerWarp, playerLevelUp, cream, };

	static CSoundBox* GetInstance();
	void Enter();
	void Exit();

	void Play(int _soundEnum, bool _loop);

	CSoundBox();
	~CSoundBox();
};

