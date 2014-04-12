#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "OptionsState.h"
#include "MainMenuState.h"
#include <sstream>

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
	SGD::InputManager* input = SGD::InputManager::GetInstance();

	if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
	{
		Game::GetInstance()->PopState();
		return true;
	}

	if (input->IsKeyPressed(SGD::Key::Right) || input->IsDPadPressed(0, SGD::DPad::Right) || (input->IsKeyPressed(SGD::Key::MouseLeft)))
	{
		if (menu->GetCursor() == menuReturn::sfx)
		{
			soundBox->Play(CSoundBox::sounds::playerLaser, false);
			if (sfxVolume < 10)
			{
				sfxVolume++;
				SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_SOUND_EFFECTS, sfxVolume * 10);
			}
		}
		else if (menu->GetCursor() == menuReturn::music && musicVolume < 10)
		{
			musicVolume++;
			SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_MUSIC, musicVolume * 10);
		}
	}

	if (input->IsKeyPressed(SGD::Key::LeftArrow) || input->IsDPadPressed(0, SGD::DPad::Left) || (input->IsKeyPressed(SGD::Key::MouseRight)))
	{
		if (menu->GetCursor() == menuReturn::sfx)
		{
			soundBox->Play(CSoundBox::sounds::playerLaser, false);

			if (sfxVolume > 0)
			{
				sfxVolume--;
				SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_SOUND_EFFECTS, sfxVolume * 10);
			}
		}
		else if (menu->GetCursor() == menuReturn::music && musicVolume > 0)
		{
			musicVolume--;
			SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioManager::VolumeType::MASTER_MUSIC, musicVolume * 10);
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
	CMainMenuState::GetInstance()->Update(dt);
}

void COptionsState::Render()
{
	SGD::GraphicsManager::GetInstance()->DrawRectangle({ { 0, 0 }, SGD::Point{ Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() } }, { 150, 0, 0, 0 });

	menu->Render();

	std::ostringstream sfxString;
	sfxString << sfxVolume;
	Game::GetInstance()->FontPoiret.Write({ Game::GetInstance()->GetScreenWidth() * .56f, Game::GetInstance()->GetScreenHeight() * .57f }, sfxString.str().c_str());
	std::ostringstream musString;
	musString << musicVolume;
	Game::GetInstance()->FontPoiret.Write({ Game::GetInstance()->GetScreenWidth() * .56f, Game::GetInstance()->GetScreenHeight() * .62f }, musString.str().c_str());
	if (fullscreenOn)
	{
		Game::GetInstance()->FontPoiret.Write({ Game::GetInstance()->GetScreenWidth() * .56f, Game::GetInstance()->GetScreenHeight() * .67f }, "On");
	}
	else
		Game::GetInstance()->FontPoiret.Write({ Game::GetInstance()->GetScreenWidth() * .56f, Game::GetInstance()->GetScreenHeight() * .67f }, "Off");

}

void COptionsState::Enter()
{
	std::vector<std::string> buttons;
	buttons.resize(menuReturn::count);
	buttons[menuReturn::sfx] = "SFX";
	buttons[menuReturn::music] = "Music";
	buttons[menuReturn::fullscreen] = "Fullscreen";
	buttons[menuReturn::back] = "Back";
	menu = new CMenu(&Game::GetInstance()->FontPoiret, buttons, "Options", { Game::GetInstance()->GetScreenWidth() * .4f, Game::GetInstance()->GetScreenHeight() * .52f }, false);
	soundBox = CSoundBox::GetInstance();
	//soundBox->Enter();
	std::string path = Game::GetInstance()->GetAppDataPath() + "optionsSave.xml";
	TiXmlDocument doc(path.c_str());
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

	std::string path = Game::GetInstance()->GetAppDataPath() + "optionsSave.xml";
	doc.SaveFile(path.c_str());

	delete menu;
	menu = nullptr;
}
