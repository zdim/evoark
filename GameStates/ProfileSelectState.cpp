#include "ProfileSelectState.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "Game.h"
#include "../BitmapFont/BitmapFont.h"
#include "MainMenuState.h"
#include <string>

CProfileSelectState* CProfileSelectState::GetInstance()
{
	static CProfileSelectState instance;
	return &instance;
}

void CProfileSelectState::Enter()
{
	LoadProfiles();
	currentProfile = 0;
	renderedProfile = 0;
	transTimer = transDuration;
	state = MyState::Idle;

	font.Load("Resources/XML/font1.xml");
	std::vector<std::string> labels;
	labels.push_back("Play");
	labels.push_back("Create New");
	labels.push_back("Delete");
	labels.push_back("Cancel");
	labels.push_back("MainMenu");
	SGD::Size screen = SGD::Size{ (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() };
	menu = new CMenu(&Game::GetInstance()->FontPoiret, labels, "", { screen.width * .3f, screen.height * .55f }, false);

	current = SGD::Point{ (screen.width - profileSize.width) * 0.5f, (screen.height - profileSize.height) * 0.5f };
	previous = SGD::Point{ profileSize.width * -0.75f, (screen.height - profileSize.height) * 0.75f };
	 next = SGD::Point{ screen.width - profileSize.width * 0.25f, (screen.height - profileSize.height) * 0.75f };

}

void CProfileSelectState::Exit()
{
	if (confirm)
	{
		delete confirm;
		confirm = nullptr;
	}
	delete menu;
	menu = nullptr;
	font.Unload();
}

bool CProfileSelectState::Input()
{
	if (state >= MyState::Menu)
		MenuInput();
	else
		SeletionInput();
	return true;
}

void CProfileSelectState::SeletionInput()
{
	SGD::InputManager* input = SGD::InputManager::GetInstance();
#if ARCADE
	if (input->IsButtonPressed(0, 6) || input->IsButtonPressed(1, 6) || input->IsButtonPressed(0, 2) || input->IsButtonPressed(1, 2))
	{
		Game::GetInstance()->PopState();
		//Game::GetInstance()->PushState(CMainMenuState::GetInstance());
		return;
	}

	SGD::Vector joy1 = input->GetLeftJoystick(0);
	SGD::Vector joy2 = input->GetLeftJoystick(1);
	if (joy1.x > 0 || joy2.x > 0)
	{
		if (currentProfile >= 2)
			currentProfile = 0;
		else
			currentProfile++;
		state = MyState::Transition;
		transTimer = 0;
	}
	if (joy1.x < 0 || joy2.x < 0)
	{
		if (currentProfile <= 0)
			currentProfile = 2;
		else
			currentProfile--;
		state = MyState::Transition;
		transTimer = 0;
	}
	if (input->IsButtonPressed(0, 0) || input->IsButtonPressed(1, 0))
	{
		state = MyState::Menu;
	}

	if (input->IsKeyPressed(SGD::Key::MouseLeft))
	{
		SGD::Point mouse = input->GetMousePosition();
		if (mouse.IsWithinRectangle(SGD::Rectangle{ current, profileSize }))
		{
			state = MyState::Menu;
			return;
		}
		if (mouse.IsWithinRectangle(SGD::Rectangle{ next, profileSize }))
		{
			if (currentProfile >= 2)
				currentProfile = 0;
			else
				currentProfile++;
			state = MyState::Transition;
			transTimer = 0;
		}
		if (mouse.IsWithinRectangle(SGD::Rectangle{ previous, profileSize }))
		{
			if (currentProfile <= 0)
				currentProfile = 2;
			else
				currentProfile--;
			state = MyState::Transition;
			transTimer = 0;
		}
	}
#else
	if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
	{
		Game::GetInstance()->PopState();
		//Game::GetInstance()->PushState(CMainMenuState::GetInstance());
		return;
	}

	if (input->IsKeyPressed(SGD::Key::RightArrow) || input->IsDPadPressed(0, SGD::DPad::Right))
	{
		if (currentProfile >= 2)
			currentProfile = 0;
		else
			currentProfile++;
		state = MyState::Transition;
		transTimer = 0;
	}
	if (input->IsKeyPressed(SGD::Key::LeftArrow) || input->IsDPadPressed(0, SGD::DPad::Left))
	{
		if (currentProfile <= 0)
			currentProfile = 2;
		else
			currentProfile--;
		state = MyState::Transition;
		transTimer = 0;
	}
	if (input->IsKeyPressed(SGD::Key::Enter) || input->IsButtonPressed(0, 0))
	{
		state = MyState::Menu;
	}

	if (input->IsKeyPressed(SGD::Key::MouseLeft))
	{
		SGD::Point mouse = input->GetMousePosition();
		if (mouse.IsWithinRectangle(SGD::Rectangle{ current, profileSize }))
		{
			state = MyState::Menu;
			return;
		}
		if (mouse.IsWithinRectangle(SGD::Rectangle{ next, profileSize }))
		{
			if (currentProfile >= 2)
				currentProfile = 0;
			else
				currentProfile++;
			state = MyState::Transition;
			transTimer = 0;
		}
		if (mouse.IsWithinRectangle(SGD::Rectangle{ previous, profileSize }))
		{
			if (currentProfile <= 0)
				currentProfile = 2;
			else
				currentProfile--;
			state = MyState::Transition;
			transTimer = 0;
		}
	}
#endif
}

void CProfileSelectState::MenuInput()
{
	SGD::InputManager* input = SGD::InputManager::GetInstance();

	if (state == MyState::ConfirmOverwrite)
	{
#if ARCADE
		if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
#else
		if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
#endif
		{
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			return;
		}
		switch (confirm->Input())
		{
		case 0:
		{
			delete confirm;
			confirm = nullptr;
			CGameplayState::GetInstance()->DeleteProfile(currentProfile+1);
			profiles[currentProfile] = CreateProfile();
			TutorialConfirmation();
			break;
		}
		case 1:
		{
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
		}
		case -1:
		default:
			break;
		}
		return;
	}

	if (state == MyState::ConfirmDelete)
	{
#if ARCADE
		if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
#else
		if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
#endif
		{
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			return;
		}
		switch (confirm->Input())
		{
		case 0:
			CGameplayState::GetInstance()->DeleteProfile(currentProfile+1);
			profiles[currentProfile] = CreateProfile();
			//profiles[currentProfile].profile = currentProfile + 1;
			//Don't break! They both delete confirm and change state beck to menu
		case 1:
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			break;
		case -1:
		default:
			break;
		}
		return;
	}

	if (state == MyState::ConfirmTutorial)
	{
#if ARCADE
		if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
#else
		if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
#endif
		{
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			return;
		}
		switch (confirm->Input())
		{
		case 0:
			profiles[currentProfile].currLevel = Level::Gen1;
		case 1:
			CGameplayState::GetInstance()->SetSaveData(profiles[currentProfile]);
			Game::GetInstance()->PopState();
			Game::GetInstance()->PopState();
			Game::GetInstance()->PushState(CGameplayState::GetInstance());
			break;
		case 2:
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			break;
		case -1:
		default:
			break;
		}
		return;
	}

#if ARCADE
	if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
#else
	if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
#endif
	{
		state = MyState::Idle;
		return;
	}

	switch (menu->Input())
	{
	case 0:
		if (profiles[currentProfile].currLevel == Level::Tutorial)
		{
			TutorialConfirmation();
			break;
		}
		CGameplayState::GetInstance()->SetSaveData(profiles[currentProfile]);
		Game::GetInstance()->PopState();
		Game::GetInstance()->PopState();
		Game::GetInstance()->PushState(CGameplayState::GetInstance());
		break;
	case 1:
	{
		std::vector<std::string> yesno;
		yesno.push_back("Yes");
		yesno.push_back("No");
		confirm = new CMenu(&Game::GetInstance()->FontPoiret, yesno, "Overwrite?", { Game::GetInstance()->GetScreenWidth() * .55f, Game::GetInstance()->GetScreenHeight() * .6f }, false);
		state = MyState::ConfirmOverwrite;
		break;
	}
	case 2:
	{
		std::vector<std::string> yesno;
		yesno.push_back("Yes");
		yesno.push_back("No");
		confirm = new CMenu(&Game::GetInstance()->FontPoiret, yesno, "Delete?", { Game::GetInstance()->GetScreenWidth() * .55f, Game::GetInstance()->GetScreenHeight() * .6f }, false);
		state = MyState::ConfirmDelete;
		break;
	}
	case 3:
	{
		state = MyState::Idle;
		break;
	}
	case 4:
	{
		Game::GetInstance()->PopState();
		//Game::GetInstance()->PushState(CMainMenuState::GetInstance());
		break;
	}
	case -1:
	default:
		break;
	}
}


void CProfileSelectState::Update(float dt)
{
	CMainMenuState::GetInstance()->Update(dt);
	switch (state)
	{
	case MyState::Transition:
		transTimer += dt;
		if (transTimer >= transDuration)
		{
			if (renderedProfile == currentProfile - 1 || (renderedProfile == 2 && currentProfile == 0))
			{
				if (renderedProfile >= 2)
					renderedProfile = 0;
				else
					renderedProfile++;
			}
			else
			{
				if (renderedProfile <= 0)
					renderedProfile = 2;
				else
					renderedProfile--;
			}
			state = MyState::Idle;
		}
	default:
		return;
	}
}

void CProfileSelectState::Render()
{
	if (state == MyState::Transition)
	{
		TransitionRender();
		return;
	}

	//Render previous profile
	RenderProfile(currentProfile-1, previous);
	//Render next profile
	RenderProfile(currentProfile + 1, next);
	//Render center profile
	RenderProfile(currentProfile, current);

	if (state >= MyState::Menu)
	{
		SGD::GraphicsManager::GetInstance()->DrawRectangle({ { 0, 0 }, SGD::Point{ (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() } }, { 90, 0, 0, 0 });
		menu->Render();
		if (state >= MyState::ConfirmOverwrite)
		{
			SGD::GraphicsManager::GetInstance()->DrawRectangle({ { 0, 0 }, SGD::Point{ Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() } }, { 90, 0, 0, 0 });
			confirm->Render();
		}
	}
}

float floatLerp(float start, float end, float dt, float duration)
{
	float journey = end - start;
	float traveled = dt/duration;
	float position = start + journey * traveled;
	return position;
}

SGD::Point pointLerp(SGD::Point start, SGD::Point end, float dt, float duration)
{
	SGD::Point position;
	position.x = floatLerp(start.x, end.x, dt, duration);
	position.y = floatLerp(start.y, end.y, dt, duration);
	return position;
}

void CProfileSelectState::TransitionRender()
{
	SGD::Point renderedNext;
	SGD::Point renderedPrevious;
	SGD::Point renderedCurrent;
	bool lerpForward = renderedProfile == currentProfile - 1 || (renderedProfile == 2 && currentProfile == 0);

	if (lerpForward)
	{
		//Lerp forward a profile
		renderedNext = pointLerp(next, current, transTimer, transDuration);
		renderedPrevious = pointLerp(previous, next, transTimer, transDuration);
		renderedCurrent = pointLerp(current, previous, transTimer, transDuration);
	}
	else
	{
		renderedNext = pointLerp(next, previous, transTimer, transDuration);
		renderedPrevious = pointLerp(previous, current, transTimer, transDuration);
		renderedCurrent = pointLerp(current, next, transTimer, transDuration);
	}

	if (transTimer >= transDuration * 0.5f)
	{
		if (lerpForward)
		{
			RenderProfile(renderedProfile, renderedCurrent);
			RenderProfile(renderedProfile - 1, renderedPrevious);
			RenderProfile(renderedProfile + 1, renderedNext);
		}
		else
		{
			RenderProfile(renderedProfile + 1, renderedNext);
			RenderProfile(renderedProfile, renderedCurrent);
			RenderProfile(renderedProfile - 1, renderedPrevious);
		}
	}
	else
	{
		if (lerpForward)
		{
			RenderProfile(renderedProfile - 1, renderedPrevious);
			RenderProfile(renderedProfile, renderedCurrent);
			RenderProfile(renderedProfile + 1, renderedNext);
		}
		else
		{
			RenderProfile(renderedProfile + 1, renderedNext);
			RenderProfile(renderedProfile - 1, renderedPrevious);
			RenderProfile(renderedProfile, renderedCurrent);
		}
	}
}

void CProfileSelectState::LoadProfiles()
{
	profiles.clear();
	CGameplayState* loader = CGameplayState::GetInstance();
	for (unsigned int i = 1; i < 4; i++)
	{
		loader->SetProfile(i);
		profiles.push_back(loader->LoadProfile());
	}
	for (unsigned int i = 0; i < 3; i++)
	{
		if (profiles[i].profile == 0)
		{
			currentProfile = i;
			profiles[i] = CreateProfile();
			//profiles[i].profile = i + 1;
		}
	}
	currentProfile = 0;
}

saveData CProfileSelectState::CreateProfile()
{
	saveData profile;
	profile.profile = currentProfile+1;
	if (profile.profile > 3)
		profile.profile = 1;
	profile.currLevel = Level::Tutorial;

	profile.playerStat.level = 1;
	profile.playerStat.exp = 0;
	profile.playerStat.expRequired = 100;
	profile.playerStat.laserLevel = 0;
	profile.playerStat.missileLevel = 0;
	profile.playerStat.perks = 1;
	profile.playerStat.pushLevel = 0;
	profile.playerStat.warpLevel = 0;
	profile.playerStat.wellLevel = 0;

	profile.waveStat.alliesSaved = 0;
	profile.waveStat.enemiesKilled = 0;

	profile.world.saved = false;

	return profile;
}

void CProfileSelectState::RenderProfile(int index, SGD::Point pos)
{
	SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle{ pos, profileSize }, SGD::Color(0,0, 155));
	if (index > 2)
		index = 0;
	if (index < 0)
		index = 2;

	SGD::Point fontCursor = pos;
	saveData profile = profiles[index];
	std::string text = "Profile " + std::to_string(profile.profile);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;
	float topline = fontCursor.y;

	text = "Player Level: " + std::to_string(profile.playerStat.level);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Laser Level: " + std::to_string(profile.playerStat.laserLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Missile Level: " + std::to_string(profile.playerStat.missileLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Well Level: " + std::to_string(profile.playerStat.wellLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Push Level: " + std::to_string(profile.playerStat.pushLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Warp Level: " + std::to_string(profile.playerStat.warpLevel);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	fontCursor.y = topline;
	fontCursor.x += 200;

	text = "Experience: " + std::to_string(profile.playerStat.exp) + "/" + std::to_string(profile.playerStat.expRequired);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Perks: " + std::to_string(profile.playerStat.perks);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Sectors from home:\n" + std::to_string(int(Level::Final) - int(profile.currLevel));
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Allies Rescued: " + std::to_string(profile.waveStat.alliesSaved);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;

	text = "Enemies Killed: " + std::to_string(profile.waveStat.enemiesKilled);
	font.Write(fontCursor, text);
	fontCursor.y += font.ComputeStringSpace(text).height;
	fontCursor.y += 10;
}

void CProfileSelectState::TutorialConfirmation()
{
	std::vector<std::string> buttons;
	buttons.push_back("Yes");
	buttons.push_back("No");
	buttons.push_back("Cancel");
	
	confirm = new CMenu(&Game::GetInstance()->FontPoiret, buttons, "Skip Tutorial?", { Game::GetInstance()->GetScreenWidth() * .55f, Game::GetInstance()->GetScreenHeight() * .6f }, false);
	state = MyState::ConfirmTutorial;
}
