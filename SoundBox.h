#pragma once
#include "SGD Wrappers\SGD_Handle.h"
#include "SGD Wrappers\SGD_AudioManager.h"

class CSoundBox
{

	SGD::AudioManager* audio;

	SGD::HAudio uiHighlightSFX = SGD::INVALID_HANDLE;
	SGD::HAudio uiSuccessSFX = SGD::INVALID_HANDLE;
	SGD::HAudio uiFailureSFX = SGD::INVALID_HANDLE;
	SGD::HAudio uiEnterSFX = SGD::INVALID_HANDLE;
	SGD::HAudio uiSwishSFX = SGD::INVALID_HANDLE;

	SGD::HAudio playerLaserSFX = SGD::INVALID_HANDLE;
	SGD::HAudio playerLaserFinalSFX = SGD::INVALID_HANDLE;
	SGD::HAudio playerMissileSFX = SGD::INVALID_HANDLE;
	SGD::HAudio playerWarpSFX = SGD::INVALID_HANDLE;
	SGD::HAudio playerWellSFX = SGD::INVALID_HANDLE;
	SGD::HAudio playerPushSFX = SGD::INVALID_HANDLE;
	SGD::HAudio playerLevelUpSFX = SGD::INVALID_HANDLE;

	SGD::HAudio enemyShieldDamageSFX = SGD::INVALID_HANDLE;
	SGD::HAudio enemyHullDamageSFX = SGD::INVALID_HANDLE;

	SGD::HAudio missileHitSFX = SGD::INVALID_HANDLE;


	SGD::HAudio copperheadExplosion    = SGD::INVALID_HANDLE;
	SGD::HAudio cobraExlosion     = SGD::INVALID_HANDLE;
	SGD::HAudio mediumExplosion    = SGD::INVALID_HANDLE;
	SGD::HAudio coralExplosion    = SGD::INVALID_HANDLE;
	SGD::HAudio moccasinExplosion = SGD::INVALID_HANDLE;


	SGD::HAudio creamMusic = SGD::INVALID_HANDLE;
	SGD::HAudio ambientMusic = SGD::INVALID_HANDLE;
	SGD::HAudio slowTranceMusic = SGD::INVALID_HANDLE;
public:
	enum sounds { uiHighlight, uiSuccess, uiFailure, uiEnter, uiSwish, playerLaser, playerLaserFinal, playerMissile, playerWarp, playerWell, playerPush, playerLevelUp, enemyShieldDamage, enemyHullDamage, cream, ambient, slowTrance, missileHit,
		copperheadE, cobraE, mExplosion, cExplosion, bossExplosion
	};

	static CSoundBox* GetInstance();
	void Enter();
	void Exit();

	void Play(int _soundEnum, bool _loop);

	CSoundBox();
	~CSoundBox();
};

