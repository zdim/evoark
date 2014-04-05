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
	playerLevelUpSFX = audio->LoadAudio("Resources/Audio/PlayerLevelUp.wav");
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
	audio->UnloadAudio(creamMusic);
	audio->UnloadAudio(playerLevelUpSFX);
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
	case playerLevelUp:
		soundToPlay = playerLevelUpSFX;
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
