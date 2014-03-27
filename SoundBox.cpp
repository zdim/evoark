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
}

void CSoundBox::Exit()
{
	audio->UnloadAudio(playerLaserSFX);

}

void CSoundBox::Play(int _soundEnum)
{
	SGD::HAudio soundToPlay = SGD::INVALID_HANDLE;
	switch (_soundEnum)
	{
	case playerLaser:
		soundToPlay = playerLaserSFX;
	default:
		break;
	}

	audio->PlayAudio(soundToPlay);
}
