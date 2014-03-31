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
	playerLaserSFX = audio->LoadAudio("Resources/Audio/PlayerLaser1.wav");
	creamMusic = audio->LoadAudio("Resources/Audio/cream.xwm");
}

void CSoundBox::Exit()
{
	audio->UnloadAudio(playerLaserSFX);
	audio->UnloadAudio(creamMusic);

}

void CSoundBox::Play(int _soundEnum, bool _loop)
{
	SGD::HAudio soundToPlay = SGD::INVALID_HANDLE;
	switch (_soundEnum)
	{
	case playerLaser:
		soundToPlay = playerLaserSFX;
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
