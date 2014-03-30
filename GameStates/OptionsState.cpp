#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "OptionsState.h"


COptionsState::COptionsState()
{
}

COptionsState* COptionsState::GetInstance()
{
	static COptionsState instance;
	return &instance;
}

COptionsState::~COptionsState()
{
}

bool COptionsState::Input()
{
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape) || SGD::InputManager::GetInstance()->IsButtonPressed(0, 1))
	{
		Game::GetInstance()->PopState();
		return true;
	}

	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Right) || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Right))
	{
		if (menu->GetCursor() == menuReturn::sfx)
		{
			soundBox->Play(CSoundBox::sounds::playerLaser);

			{
				sfxVolume++;
				SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_SOUND_EFFECTS, sfxVolume * 10);
			}
		}
		else if (menu->GetCursor() == menuReturn::music && musicVolume < 10)
		{
			musicVolume++;
			SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_MUSIC, sfxVolume * 10);
		}
	}

	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::LeftArrow) || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Left))
	{
		if (menu->GetCursor() == menuReturn::sfx)
		{
			soundBox->Play(CSoundBox::sounds::playerLaser);

			if (sfxVolume > 0)
			{
				sfxVolume--;
				SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_SOUND_EFFECTS, sfxVolume * 10);
			}
		}
		else if (menu->GetCursor() == menuReturn::music && musicVolume > 0)
		{
			musicVolume--;
			SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_MUSIC, sfxVolume * 10);
		}
	}

	int ret = menu->Input();
	switch (ret)
	{
	case menuReturn::back:
		Game::GetInstance()->PopState();
		return true;
	case menuReturn::fullscreen:
		fullscreenOn = !fullscreenOn;
		// make window fullscreen
		SGD::GraphicsManager::GetInstance()->Resize(SGD::Size{ (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() }, !fullscreenOn);
		return true;
	default:
		return true;
	}
}

void COptionsState::Update(float dt)
{
	//Uhm?? Maybe some time-based graphics? This is going to be a pretty boring menu right now.

}

void COptionsState::Render()
{
	menu->Render();
}

void COptionsState::Enter()
{
	std::vector<std::string> buttons;
	buttons.resize(menuReturn::count);
	buttons[menuReturn::sfx] = "SFX";
	buttons[menuReturn::music] = "Music";
	buttons[menuReturn::fullscreen] = "Fullscreen";
	buttons[menuReturn::back] = "Back";
	menu = new CMenu(&Game::GetInstance()->Font, buttons, "Options", true);
	soundBox = CSoundBox::GetInstance();
	soundBox->Enter();

	TiXmlDocument doc("optionsSave.xml");
	if (doc.LoadFile() == false)
		return;

	TiXmlElement* root = doc.RootElement();
	if (!root)
		return;

	root->Attribute("sfx", &sfxVolume);
	root->Attribute("music", &musicVolume);
	std::string fullscrn;
	fullscrn = root->Attribute("fullscreen");
	if (fullscrn == "true") fullscreenOn = true;
	else fullscreenOn = false;
}

void COptionsState::Exit()
{
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration();
	doc.LinkEndChild(decl);

	TiXmlElement* element = new TiXmlElement("Options");
	element->SetAttribute("sfx", sfxVolume);
	element->SetAttribute("music", musicVolume);
	if (fullscreenOn)
		element->SetAttribute("fullscreen", "true");
	else
		element->SetAttribute("fullscreen", "false");
	doc.LinkEndChild(element);

	doc.SaveFile("optionsSave.xml");

	delete menu;
	menu = nullptr;
}
