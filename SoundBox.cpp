#include "SoundBox.h"


CSoundBox::CSoundBox()
{

}

CSoundBox::~CSoundBox()
{
}

CSoundBox* CSoundBox::GetInstance(void)
{
	static CSoundBox instance;
	return &instance;
}

void CSoundBox::Enter()
{
	audio = SGD::AudioManager::GetInstance();
	uiHighlightSFX = audio->LoadAudio("Resources/Audio/UIHighlight.wav");
	uiFailureSFX = audio->LoadAudio("Resources/Audio/UIFailure.wav");
	uiSuccessSFX = audio->LoadAudio("Resources/Audio/UISuccess.wav");
	playerLaserSFX = audio->LoadAudio("Resources/Audio/PlayerLaser1.wav");
	playerMissileSFX = audio->LoadAudio("Resources/Audio/PlayerMissile.wav");
	playerWarpSFX = audio->LoadAudio("Resources/Audio/PlayerWarp.wav");
	playerWellSFX = audio->LoadAudio("Resources/Audio/PlayerWell3Sec.wav");
	playerPushSFX = audio->LoadAudio("Resources/Audio/PlayerPush.wav");
	playerLevelUpSFX = audio->LoadAudio("Resources/Audio/PlayerLevelUp.wav");
	enemyHullDamageSFX = audio->LoadAudio("Resources/Audio/EnemyHullDamage.wav");
	enemyShieldDamageSFX = audio->LoadAudio("Resources/Audio/EnemyShieldDamage.wav");
	creamMusic = audio->LoadAudio("Resources/Audio/cream.xwm");
}

void CSoundBox::Exit()
{
	audio->UnloadAudio(uiHighlightSFX);
	audio->UnloadAudio(uiFailureSFX);
	audio->UnloadAudio(uiSuccessSFX);
	audio->UnloadAudio(playerLaserSFX);
	audio->UnloadAudio(playerMissileSFX);
	audio->UnloadAudio(playerWarpSFX);
	audio->UnloadAudio(playerWellSFX);
	audio->UnloadAudio(playerPushSFX);
	audio->UnloadAudio(playerLevelUpSFX);
	audio->UnloadAudio(enemyHullDamageSFX);
	audio->UnloadAudio(enemyShieldDamageSFX);
	audio->UnloadAudio(creamMusic);

}

void CSoundBox::Play(int _soundEnum, bool _loop)
{
	SGD::HAudio soundToPlay = SGD::INVALID_HANDLE;
	switch (_soundEnum)
	{
	case uiHighlight:
		soundToPlay = uiHighlightSFX;
		break;
	case uiSuccess:
		soundToPlay = uiSuccessSFX;
		break;
	case uiFailure:
		soundToPlay = uiFailureSFX;
		break;
	case playerLaser:
		soundToPlay = playerLaserSFX;
		break;
	case playerMissile:
		soundToPlay = playerMissileSFX;
		break;
	case playerWarp:
		soundToPlay = playerWarpSFX;
		break;
	case playerWell:
		soundToPlay = playerWellSFX;
		break;
	case playerPush:
		soundToPlay = playerPushSFX;
		break;
	case playerLevelUp:
		soundToPlay = playerLevelUpSFX;
		break;
	case enemyHullDamage:
		soundToPlay = enemyHullDamageSFX;
		break;
	case enemyShieldDamage:
		soundToPlay = enemyShieldDamageSFX;
		break;
	case cream:
		soundToPlay = creamMusic;
		break;
	default:
		break;
	}

	if (_loop && audio->IsAudioPlaying(soundToPlay))
		return;
	audio->PlayAudio(soundToPlay, _loop);
}
