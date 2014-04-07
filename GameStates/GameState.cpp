#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include "../TinyXML/tinyxml.h"
//#include "../TinyXML/tinystr.h"
//#include "../Graphics/Particles/Flyweight.h"
//#include "../Graphics/Particles/Emitter.h"
#include "../SGD Wrappers/SGD_MessageManager.h"
#include "../Event System/EventManager.h"
#include "../Message System/CreateEntityMessage.h"
#include "../Entities/Collidables/EventTrigger.h"
#include "../Message System/DestroyEntityMessage.h"
#include "../Message System/CreateEntityMessage.h"

#include "GameOverState.h"
#include "../Message System/CreateProjectile.h"
#include "../Entities/Ships/Player.h"
#include "../SoundBox.h"
#include "../GameStates/GameplayState.h"
#include "../GameStates/MainMenuState.h"

//comment out
#include "../Entities/Ships/Enemies/Moccasin.h"

CTestLevelState::CTestLevelState()
{
	testing = "";

}


CTestLevelState::~CTestLevelState()
{
}

CTestLevelState* CTestLevelState::GetInstance(void)
{
	static CTestLevelState instance;
	return &instance;
}

void	CTestLevelState::Enter(void)
{
	m_bLoaded = false;
	srand((unsigned int)time(nullptr));
	graphics = SGD::GraphicsManager::GetInstance();


	testing = "Resources";
	m_nLine = 0;
	Render();
	graphics->Update();

	objArrow = graphics->LoadTexture("Resources/Graphics/Arrow.png");
	backgroundBlack = graphics->LoadTexture("Resources/Graphics/backgroundBlack3.png", { 50, 255, 255, 255 });
	backgroundNebula = graphics->LoadTexture("Resources/Graphics/Smoke.png");
	backgroundStars = graphics->LoadTexture("Resources/Graphics/stars1new.png", { 0, 0, 0 });
	backgroundStars1 = graphics->LoadTexture("Resources/Graphics/stars2new.png", { 0, 0, 0 });
	backgroundStars2 = graphics->LoadTexture("Resources/Graphics/stars3.png", { 0, 0, 0 });

	EntityManager = CEntityManager::GetInstance();
	EntityManager->Initialize();
	soundBox = CSoundBox::GetInstance();
	//soundBox->Enter();
	soundBox->Play(CSoundBox::sounds::slowTrance, true);

	EntityManager->Spawn(EntityType::Moccasin, { 600, 600 }, 1);
	//EntityManager->GetBoss()->Init(4);
	//EntityManager->GetBoss()->SetImages(EntityManager->GetImages());

	//Get SaveData and load based on it
	saveData save = CGameplayState::GetInstance()->GetSaveData();
	if (save.world.saved == true)
	{
		Load();
	}
	else
	{
		Generate();
		Save();
	}
	testing = "Level";
	m_nLine += 100;
	Render();
	graphics->Update();

	//EntityManager->Spawn(EntityType::Stargate, {200,200});
	if (BackgroundImage == SGD::INVALID_HANDLE)
		BackgroundImage = graphics->LoadTexture("Resources/Graphics/starfield.jpg");
	player = EntityManager->GetPlayer();
	//Spawn Coral near the player
	//EntityManager->Spawn(EntityType::Coral, player->GetPosition() + SGD::Vector{ 100, 100 });
	//Spawn Moccasin near the player

	//EntityManager->Spawn(EntityType::InvisTrigger, player->GetPosition() + SGD::Vector{ 200, 200 }, (unsigned int)EntityType::Coral);


	m_nScreenHeight = Game::GetInstance()->GetScreenHeight();
	m_nScreenWidth = Game::GetInstance()->GetScreenWidth();
	cam = CCamera::GetInstance();
	cam->Initiallize(player, SGD::Size{ (float)m_nScreenWidth, (float)m_nScreenHeight });

	nebulaPos = { cam->GetOffset().x, cam->GetOffset().y };
	stars1Pos = { cam->GetOffset().x, cam->GetOffset().y };
	stars2Pos = { cam->GetOffset().x, cam->GetOffset().y };
	starsPos = { cam->GetOffset().x, cam->GetOffset().y };

	SGD::MessageManager::GetInstance()->Initialize(&MessageProc);

	testing = "Initializing";
	m_nLine += 30;
	Render();
	graphics->Update();



	m_bLoaded = true;
}

void	CTestLevelState::Exit(void)
{
	m_bBossKilled = false;

	cam->Terminate();
	if (BackgroundImage != SGD::INVALID_HANDLE)
		graphics->UnloadTexture(BackgroundImage);
	graphics->UnloadTexture(backgroundBlack);
	graphics->UnloadTexture(objArrow);
	graphics->UnloadTexture(backgroundBlack);
	graphics->UnloadTexture(backgroundNebula);
	graphics->UnloadTexture(backgroundStars);
	graphics->UnloadTexture(backgroundStars1);
	graphics->UnloadTexture(backgroundStars2);
	//soundBox->Exit();

	//Terminating Messages or events before Entity manager will BREAK it on the NEXT level.
	//Terminate EntityManager FIRST :3
	EntityManager->Terminate();
	SGD::MessageManager::GetInstance()->Terminate();
	SGD::MessageManager::GetInstance()->DeleteInstance();
	CEventManager::GetInstance().ClearEvents();
	CEventManager::GetInstance().ClearListeners();


	if (CGameplayState::GetInstance()->GetLevel() != Level::Tutorial)
		CGameplayState::GetInstance()->SaveProfile();
}

bool	CTestLevelState::Input(void)
{
	SGD::InputManager* input = SGD::InputManager::GetInstance();
	if (input->IsKeyDown(SGD::Key::Alt) && input->IsKeyPressed(SGD::Key::R))
	{
		Game::GetInstance()->PopState();
		return true;
	}
	if (input->IsKeyDown(SGD::Key::Alt) && input->IsKeyPressed(SGD::Key::Q))
	{
		Game::GetInstance()->PopState();
		Game::GetInstance()->PopState();
		return false;
	}
	if (input->IsKeyPressed(SGD::Key::Escape))
	{
		Game::GetInstance()->PushState(CPauseState::GetInstance());
		return true;
	}
	if (input->IsKeyDown(SGD::Key::Alt) && input->IsKeyPressed(SGD::Key::C))
	{
		cam->SetTarget(EntityManager->GetStargate());
		return true;
	}
	if (input->IsKeyDown(SGD::Key::Alt) && input->IsKeyPressed(SGD::Key::P))
	{
		cam->SetTarget(EntityManager->GetPlayer());
		return true;
	}
	//if (input->IsKeyDown(SGD::Key::K))
	//{
	//	CMoccasin* boss = dynamic_cast<CMoccasin*>(EntityManager->GetBoss());
	//	boss->TakeDamage(10000);
	//}
	return true;
}

void	CTestLevelState::Update(float dt)
{
	EntityManager->Update(dt);
	SGD::MessageManager::GetInstance()->Update();
	CEventManager::GetInstance().Update();
	cam->Update(dt);

	// parallax effect
	nebulaPos = { cam->GetOffset().x * .5f, cam->GetOffset().y * .5f };
	stars1Pos = { cam->GetOffset().x * .1f, cam->GetOffset().y * .1f };
	stars2Pos = { cam->GetOffset().x * .2f, cam->GetOffset().y * .2f };
	starsPos = { cam->GetOffset().x * .3f, cam->GetOffset().y * .3f };
}

void	CTestLevelState::Render(void)
{
	if (m_bLoaded == true)
	{

		//graphics->DrawTexture(BackgroundImage, { cam->GetOffset().x, cam->GetOffset().y });
		//graphics->DrawTexture(backgroundBlack, { 0, 0 });

		for (int i = 0; i < 4; i++)
		{
			//graphics->DrawTexture(backgroundStars2, stars2Pos + SGD::Vector{ stars2Pos.x * i, stars2Pos.y * i });
			for (int j = 0; j < 4; j++)
			{


				graphics->DrawTexture(backgroundStars1, stars1Pos + SGD::Vector{ 1024.f * i, 768.f * j });
				graphics->DrawTexture(backgroundStars, starsPos + SGD::Vector{ 1024.f * i, 768.f * j });
				//graphics->DrawTexture(backgroundNebula, nebulaPos + SGD::Vector{ 1024 * i, 768 * j }, 0, {}, { 200, 50, 120, 100 });

				graphics->DrawTextureSection(backgroundNebula, { nebulaPos.x + 1024.f * i, nebulaPos.y + 768.f * j }, { 0, 0, 1024.f, 768.f }, 0, {}, { 50, 50, 120, 100 });
			}
		}
		graphics->DrawRectangle({ 0, 0, 2000, 2000 }, { 150, 0, 0, 0 });

		EntityManager->Render();

		UI((CPlayer*)player, EntityManager->GetAllies(), EntityManager->GetCoordinator(), EntityManager->GetStargate());
	}
	else if (m_bLoaded == false)
	{
		Game::GetInstance()->Font.Write(SGD::Point{ 150, 150 }, testing);
		//graphics->DrawRectangle({ 0, 0, 200, 200 }, { 150, 245, 0, 0 });

		graphics->DrawLine({ 200, 200 }, { 350, 200 }, { 0, 255, 0 }, 5);

		graphics->DrawLine({ 200, 200 }, { 200.f + m_nLine, 200 }, { 255, 0, 0 }, 5);

		//graphics->DrawLine({ 150, 150 }, { 300, 150 }, { 255, 255, 0 }, 10);
	}

}

void	CTestLevelState::Generate()
{
	bool loadSuccess = false;
	bool genLevel = true;
	switch (CGameplayState::GetInstance()->GetLevel())
	{
	case Level::Tutorial:
		loadSuccess = LoadXMLLevel("Resources/XML/World/tutorialLevel.xml");
		genLevel = false;
		break;
	case Level::Gen1:


		loadSuccess = LoadXMLLevel("Resources/XML/World/levelOne.xml");
		testing += "1";
		//loadSuccess = LoadXMLLevel("Resources/XML/World/JDTest.xml");
		break;
	case Level::Gen2:
		loadSuccess = LoadXMLLevel("Resources/XML/World/levelTwo.xml");
		testing += "2";
		break;
	case Level::Gen3:
		loadSuccess = LoadXMLLevel("Resources/XML/World/levelThree.xml");
		testing += "3";
		break;
	case Level::Waves:
		loadSuccess = LoadXMLLevel("Resources/XML/World/finalLevel.xml");
		genLevel = false;
		break;
	}
	if (loadSuccess)
	{
		int _alliesSpawned = 0;
		for (int i = 0; i < m_nNumQuadsWidth; i++)
		{
			QuadCol& col = world[i];
			for (int j = 0; j < m_nNumQuadsHeight; j++)
			{

				if (col[j].randomized)
				{
					col[j].pos.x = float(m_nQuadWidth * i + rand() % m_nQuadWidth);
					col[j].pos.y = float(m_nQuadHeight * j + rand() % m_nQuadHeight);
				}
				switch (col[j].objType)
				{
				case PLAYER:
					EntityManager->Spawn(EntityType::Player, { float(m_nQuadWidth * i + (m_nQuadWidth * .5)), float(m_nQuadHeight * j + (m_nQuadHeight * .5)) });
					break;
				case COPPERHEAD:

					EntityManager->Spawn(EntityType::Copperhead, col[j].pos, col[j].objectAmount, genLevel);
					break;
				case COBRA:

					EntityManager->Spawn(EntityType::Cobra, col[j].pos, col[j].objectAmount, genLevel);
					break;
				case MAMBA:

					EntityManager->Spawn(EntityType::Mamba, col[j].pos, col[j].objectAmount, genLevel);
					break;
				case CORAL:
					EntityManager->Spawn(EntityType::Coral, col[j].pos, col[j].objectAmount);
					break;
				case MOCASSIN:

					EntityManager->Spawn(EntityType::Moccasin, { float(m_nQuadWidth * i + (m_nQuadWidth * .5)), float(m_nQuadHeight * j + (m_nQuadHeight * .5)) }, (int)CGameplayState::GetInstance()->GetLevel());
					break;
				case ASTEROID:
					EntityManager->SpawnCollidable(EntityType::Asteroid, col[j].pos, SGD::Size{ 32, 32 });
					break;
				case PLANET:
					EntityManager->SpawnCollidable(EntityType::Planet, col[j].pos);
					break;
				case HUMAN:
					if (genLevel == false)
					{
						if (CGameplayState::GetInstance()->GetSaveData().waveStat.alliesSaved == 0 && _alliesSpawned == 11) break;
						if (CGameplayState::GetInstance()->GetSaveData().waveStat.alliesSaved < 3 && _alliesSpawned == 12) break;
						if (CGameplayState::GetInstance()->GetSaveData().waveStat.alliesSaved < 5 && _alliesSpawned == 13) break;
					}
					EntityManager->Spawn(EntityType::Human, col[j].pos, 1);
					_alliesSpawned++;
					break;
				case COORDINATOR:
					EntityManager->Spawn(EntityType::Mamba, col[j].pos, col[j].objectAmount, true);
					break;
				default:
					break;
				}
			}
		}

		for (unsigned int i = 0; i < events.size(); i++)
		{
			int eventID = -1;
			if (events[i].eType == "STARGATE")
			{

				EntityManager->SpawnCollidable(EntityType::Stargate, { events[i].area.left, events[i].area.top }, { events[i].area.bottom - events[i].area.top, events[i].area.right - events[i].area.left });
				continue;
			}

			else if (events[i].eType == "TUTORIAL.MOVEMENT")
			{

				eventID = (int)triggerID::tutMovement;
			}
			else if (events[i].eType == "TUTORIAL.LASERS")
			{
				eventID = (int)triggerID::tutLasers;
			}
			else if (events[i].eType == "TUTORIAL.MISSILES")
			{
				eventID = (int)triggerID::tutMissiles;
			}
			else if (events[i].eType == "TUTORIAL.WARP")
			{
				eventID = (int)triggerID::tutWarp;
			}
			else if (events[i].eType == "TUTORIAL.WELL")
			{
				eventID = (int)triggerID::tutWell;
			}
			else if (events[i].eType == "TUTORIAL.PUSH")
			{
				eventID = (int)triggerID::tutPush;
			}
			else if (events[i].eType == "TUTORIAL.COORDINATOR")
			{
				eventID = (int)triggerID::tutCoordinator;
			}
			else if (events[i].eType == "TUTORIAL.ALLY")
			{
				eventID = (int)triggerID::tutHuman;
			}
			else if (events[i].eType == "TUTORIAL.BOSS")
			{
				eventID = (int)triggerID::tutBoss;
			}

			EntityManager->SpawnCollidable(EntityType::InvisTrigger, { events[i].area.left, events[i].area.top }, { events[i].area.right - events[i].area.left, events[i].area.bottom - events[i].area.top }, { 0, 0 }, eventID);

		}
	}
	else
	{

	}
}

bool CTestLevelState::LoadXMLLevel(const char* pXMLFile)
{
	TiXmlDocument doc(pXMLFile);
	if (doc.LoadFile() == false)
		return false;

	TiXmlElement* pRoot = doc.RootElement();
	if (!pRoot)
		return false;

	TiXmlElement* pDetails = pRoot->FirstChildElement();
	pDetails->Attribute("width", &m_nNumQuadsWidth);
	pDetails->Attribute("height", &m_nNumQuadsHeight);
	pDetails->Attribute("quadWidth", &m_nQuadWidth);
	pDetails->Attribute("quadHeight", &m_nQuadHeight);

	// get number of events
	int numEvents;
	pDetails->Attribute("events", &numEvents);
	events.resize(numEvents);

	// get number of collision rects
	int numCollision;
	pDetails->Attribute("collision", &numCollision);
	collisionRects.resize(numCollision);

	// get background image path
	std::string background;
	background = pDetails->Attribute("background");
	if (background.length() > 0)
	{
		background = "Resources/Graphics/" + background;
		BackgroundImage = graphics->LoadTexture(background.c_str());
	}
	saveData save = CGameplayState::GetInstance()->GetSaveData();
	save.world.background = background;
	CGameplayState::GetInstance()->SetSaveData(save);

	world.resize(m_nNumQuadsWidth);
	for (unsigned int size = 0; size < world.size(); size++)
		world[size].resize(m_nNumQuadsHeight);

	TiXmlElement* pQuad = pDetails->FirstChildElement("Quad");

	for (int quadCount = 0; quadCount < m_nNumQuadsHeight * m_nNumQuadsWidth; quadCount++)
	{
		Quadrant q;
		pQuad->Attribute("x", &q.x);
		pQuad->Attribute("y", &q.y);
		pQuad->Attribute("possibleTypes", &q.possibleObjects);
		if (q.possibleObjects > 0)
		{
			// select random object
			int randomObject = rand() % q.possibleObjects;
			std::string type;
			TiXmlElement* pType = pQuad->FirstChildElement("Type");

			for (int i = 0; i < q.possibleObjects; i++)
			{
				if (i < randomObject)
				{
					pType = pType->NextSiblingElement("Type");
					continue;
				}

				type = pType->Attribute("type");
				pType->Attribute("amount", &q.objectAmount);
				std::string random = pType->Attribute("randomized");
				if (random == "True")
					q.randomized = true;
				else
					q.randomized = false;

				// create ints to store into the position
				int _x, _y;
				pType->Attribute("x", &_x);
				pType->Attribute("y", &_y);
				q.pos = { (float)_x, (float)_y };
				break;
			}

			if (type == "PLAYER")
				q.objType = PLAYER;
			else if (type == "COPPERHEAD")
				q.objType = COPPERHEAD;
			else if (type == "COBRA")
				q.objType = COBRA;
			else if (type == "MAMBA")
				q.objType = MAMBA;
			else if (type == "CORAL")
				q.objType = CORAL;
			else if (type == "MOCCASIN")
				q.objType = MOCASSIN;
			else if (type == "ASTEROID")
				q.objType = ASTEROID;
			else if (type == "PLANET")
				q.objType = PLANET;
			else if (type == "HUMAN")
				q.objType = HUMAN;
			else if (type == "COORDINATOR")
				q.objType = COORDINATOR;
			else if (type == "NONE")
				q.objType = NONE;
		}
		else
		{
			q.objectAmount = 0;
			q.objType = NONE;
			q.pos = { 0, 0 };
			q.randomized = false;
		}
		world[q.x][q.y] = q;

		pQuad = pQuad->NextSiblingElement();
	}

	//TiXmlElement * pEvent = pQuad->NextSiblingElement();
	for (int i = 0; i < numEvents; i++)
	{
		Event e;

		// create ints to store into the event rect
		int _left, _top, _width, _height;
		e.eType = pQuad->Attribute("type");
		pQuad->Attribute("x", &_left);
		pQuad->Attribute("y", &_top);
		pQuad->Attribute("width", &_width);
		pQuad->Attribute("height", &_height);
		e.area = { (float)_left, (float)_top, float(_left + _width), float(_top + _height) };

		events[i] = e;
		pQuad = pQuad->NextSiblingElement();
	}

	for (int i = 0; i < numCollision; i++)
	{
		SGD::Rectangle r = { 0, 0, 0, 0 };
		int _left, _top, _width, _height;

		pQuad->Attribute("x", &_left);
		pQuad->Attribute("y", &_top);
		pQuad->Attribute("width", &_width);
		pQuad->Attribute("height", &_height);
		r = { (float)_left, (float)_top, float(_left + _width), float(_top + _height) };
		collisionRects[i] = r;
		pQuad = pQuad->NextSiblingElement();
	}

	for (int i = 0; i < numCollision; i++)
	{
		SGD::Point position;
		position.x = float(collisionRects[i].left + collisionRects[i].right) / 2.0f;
		position.y = float(collisionRects[i].top + collisionRects[i].bottom) / 2.0f;
		SGD::Size s = collisionRects[i].ComputeSize();
		EntityManager->SpawnCollidable(EntityType::Barrier, position, s);
	}

	return true;

}

void CTestLevelState::MessageProc(const SGD::Message* msg)
{
	MessageID id = msg->GetMessageID();
	switch (id)
	{
	case MessageID::CreateEntity:
	{
									const CreateEntityMessage* cMsg = dynamic_cast<const CreateEntityMessage*>(msg);
									if (dynamic_cast<CMoccasin*>(cMsg->GetSender())->GetLevel() == 1 )
									{
										

										SGD::Point randPosition = cMsg->GetSender()->GetPosition();
										randPosition.x += rand() % 1000 + 700;
										randPosition.y += rand() % 1000 + 700;
										int m_nAsteroidSize[3] = { 32, 64, 128 };
										int size = m_nAsteroidSize[rand() % 3];

										SGD::Vector dir = dynamic_cast<CMoccasin*>(cMsg->GetSender())->GetTarget()->GetPosition() - randPosition;								
										dir.Normalize();
										SGD::Vector velocity = dir * 100;
										
										CTestLevelState::GetInstance()->EntityManager->SpawnCollidable(EntityType::Asteroid, randPosition, SGD::Size{ (float)size, (float)size }, velocity);
									}
									if (dynamic_cast<CMoccasin*>(cMsg->GetSender())->GetLevel() == 2 )
									{
										SGD::Point pos = cMsg->GetSender()->GetPosition();
										SGD::Point pos1 = { pos.x + 200, pos.y + 100 };
										SGD::Point pos2 = { pos.x + 100, pos.y + 200 };
										SGD::Point pos3 = { pos.x - 200, pos.y + 100 };
										SGD::Point pos4 = { pos.x - 100, pos.y + 200 };

										CTestLevelState::GetInstance()->EntityManager->SpawnStation(pos1, { 64, 64 }, dynamic_cast<CMoccasin*>(cMsg->GetSender()));
										CTestLevelState::GetInstance()->EntityManager->SpawnStation(pos2, { 64, 64 }, dynamic_cast<CMoccasin*>(cMsg->GetSender()));
										CTestLevelState::GetInstance()->EntityManager->SpawnStation(pos3, { 64, 64 }, dynamic_cast<CMoccasin*>(cMsg->GetSender()));
										CTestLevelState::GetInstance()->EntityManager->SpawnStation(pos4, { 64, 64 }, dynamic_cast<CMoccasin*>(cMsg->GetSender()));
									}
									if (dynamic_cast<CMoccasin*>(cMsg->GetSender())->GetLevel() == 3)
									{		
										SGD::Point pos = cMsg->GetSender()->GetPosition();
										SGD::Point pos1 = { pos.x + 200, pos.y + 100 };
										CTestLevelState::GetInstance()->EntityManager->SpawnCarrierShips(pos1, dynamic_cast<CMoccasin*>(cMsg->GetSender())->GetTarget(), dynamic_cast<CMoccasin*>(cMsg->GetSender())->GetShipNumbers());
									}

									break;
	}
	case MessageID::CreateProjectile:
	{
										const CreateProjectileMessage* lMsg = dynamic_cast<const CreateProjectileMessage*>(msg);
										CTestLevelState::GetInstance()->EntityManager->SpawnProjectile(lMsg->GetProjType(), lMsg->GetPosition(), lMsg->GetOwnerSize(), lMsg->GetRotation(), lMsg->GetDamage(), lMsg->GetTier(), lMsg->GetRadius(), lMsg->GetOwner());
										switch (lMsg->GetProjType())
										{
										case EntityType::Laser:
											CTestLevelState::GetInstance()->soundBox->Play(CSoundBox::sounds::playerLaser, false);
											break;
										case EntityType::Missile:
											CTestLevelState::GetInstance()->soundBox->Play(CSoundBox::sounds::playerMissile, false);
											break;
										default:
											break;
										};
										break;

	}
	case MessageID::DestroyEntity:
	{
									 const DestroyEntityMessage* dMsg = dynamic_cast<const DestroyEntityMessage*>(msg);
									 if (dMsg->GetEntity()->GetType() >= (int)EntityType::Copperhead && dMsg->GetEntity()->GetType() <= (int)EntityType::Moccasin)
									 {
										 if (dMsg->GetEntity()->GetPosition().IsWithinRectangle(CCamera::GetInstance()->GetBoxInWorld()))
											 dynamic_cast<CPlayer*>(CTestLevelState::GetInstance()->player)->AddExp(dynamic_cast<CEnemy*>(dMsg->GetEntity())->GetExpValue());
									 }
									 CTestLevelState::GetInstance()->EntityManager->Destroy(dMsg->GetEntity());
									 break;
	}
	case MessageID::GameOver:
	{
								Game::GetInstance()->PushState(CGameOverState::GetInstance());
								break;
	}
	case MessageID::BossKilled:
	{
								  GetInstance()->m_bBossKilled = true;
								  break;

	}
	case MessageID::Victory:
	{
							   if (GetInstance()->m_bBossKilled == true)
							   {

								   if (CGameplayState::GetInstance()->GetLevel() == Level::Tutorial)
								   {
									   CGameplayState::GetInstance()->SetLevel(Level::Gen1);
									   CGameplayState::GetInstance()->GetSaveData().world.saved = false;
								   }
								   else if (CGameplayState::GetInstance()->GetLevel() == Level::Gen1)
								   {
									   CGameplayState::GetInstance()->SetLevel(Level::Gen2);
									   CGameplayState::GetInstance()->GetSaveData().world.saved = false;
								   }
								   else if (CGameplayState::GetInstance()->GetLevel() == Level::Gen2)
								   {
									   CGameplayState::GetInstance()->SetLevel(Level::Gen3);
									   CGameplayState::GetInstance()->GetSaveData().world.saved = false;
								   }
								   else if (CGameplayState::GetInstance()->GetLevel() == Level::Gen3)
								   {
									   CGameplayState::GetInstance()->SetLevel(Level::Waves);
									   CGameplayState::GetInstance()->GetSaveData().world.saved = false;
								   }

								   CGameOverState::GetInstance()->SetWin(true);
								   Game::GetInstance()->PushState(CGameOverState::GetInstance());

								   break;
							   }
							   break;
	}
	}
}

IEntity* CTestLevelState::GetPlayer()
{
	return player;
}

void CTestLevelState::UI(CPlayer* _player, std::vector<IEntity*> _allies, IEntity* _coordinator, IEntity* _stargate)
{
	// set hullbar
	SGD::Rectangle hullBox = {
		m_nScreenWidth * .33f,
		m_nScreenHeight * .92f,
		m_nScreenWidth * .66f,
		m_nScreenHeight * .95f
	};

	// display player's hull percentage
	SGD::Rectangle hull = {
		m_nScreenWidth * .33f,
		m_nScreenHeight * .92f,
		m_nScreenWidth * .33f * _player->getHull() / _player->getMaxHull() + m_nScreenWidth * .33f,
		m_nScreenHeight * .95f
	};

	// set shield bar
	SGD::Rectangle shieldBox = {
		m_nScreenWidth * .33f,
		m_nScreenHeight * .87f,
		m_nScreenWidth * .66f,
		m_nScreenHeight * .90f };

	// display player's shield percentange
	SGD::Rectangle shield = {
		m_nScreenWidth * .33f,
		m_nScreenHeight * .87f,
		m_nScreenWidth * .33f * _player->GetShield() / _player->GetMaxShield() + m_nScreenWidth * .33f,
		m_nScreenHeight * .90f };

	// experience bar
	SGD::Rectangle expBox = {
		m_nScreenWidth * .25f,
		m_nScreenHeight * .97f,
		m_nScreenWidth * .75f,
		m_nScreenHeight * .98f
	};

	SGD::Rectangle exp = {
		m_nScreenWidth * .25f,
		m_nScreenHeight * .97f,
		m_nScreenWidth * .50f * _player->GetExp() / _player->GetReqExp() + m_nScreenWidth * .25f,
		m_nScreenHeight * .98f
	};

	// set gravity well box
	SGD::Rectangle wellBox = {
		m_nScreenWidth * .40f,
		m_nScreenHeight * .8f,
		m_nScreenWidth * .44f,
		m_nScreenHeight * .85f };

	// gravity well cooldown calculation
	float wellCooldownPercentage = _player->GetWellTimer() / _player->GetWellDelay();

	SGD::Rectangle wellCD = {
		wellBox.left,
		wellBox.top + m_nScreenHeight * .05f * wellCooldownPercentage,
		wellBox.right,
		wellBox.bottom };

	// set gravity push box
	SGD::Rectangle pushBox = {
		m_nScreenWidth * .48f,
		m_nScreenHeight * .8f,
		m_nScreenWidth * .52f,
		m_nScreenHeight * .85f };

	// gravity push cooldown calculation
	float pushCooldownPercentage = _player->GetPushTimer() / _player->GetPushDelay();

	SGD::Rectangle pushCD = {
		pushBox.left,
		pushBox.top + m_nScreenHeight * .05f * pushCooldownPercentage,
		pushBox.right,
		pushBox.bottom };

	// set warp box
	SGD::Rectangle warpBox = {
		m_nScreenWidth * .56f,
		m_nScreenHeight * .8f,
		m_nScreenWidth * .60f,
		m_nScreenHeight * .85f };

	// warp cooldown calculation
	float warpCooldownPercentage = _player->GetWarpTimer() / _player->GetWarpDelay();

	SGD::Rectangle warpCD = {
		warpBox.left,
		warpBox.top + m_nScreenHeight * .05f * warpCooldownPercentage,
		warpBox.right,
		warpBox.bottom };

	// arrows
	if (_player->GetArrowsOn())
	{
		// allies
		for (unsigned int i = 0; i < _allies.size(); i++)
		{
			SGD::Vector toTarget = _allies[i]->GetPosition() - _player->GetPosition();
			float allyDistance = toTarget.ComputeLength();
			//std::ostringstream oss;
			//oss << allyDistance;
			if (allyDistance > 400)
			{
				toTarget.Normalize();

				SGD::Point arrowPos = { m_nScreenWidth * .5f, m_nScreenHeight * .5f };
				arrowPos += toTarget * 200;
				float arrowRot = atan2(_allies[i]->GetPosition().y - _player->GetPosition().y, _allies[i]->GetPosition().x - _player->GetPosition().x) + SGD::PI * .5f;

				graphics->DrawTexture(objArrow, arrowPos, arrowRot, {}, { 200, 0, 200, 150 }, { .15f, .15f });
				//graphics->DrawString(oss.str().c_str(), { arrowPos.x, arrowPos.y + 20 });
			}
		}

		// commented out until coordinator is fixed
		if (_coordinator)
		{
			SGD::Vector toCoordinator = _coordinator->GetPosition() - _player->GetPosition();
			if (toCoordinator.ComputeLength() > 400)
			{
				toCoordinator.Normalize();
				SGD::Point coordArrowPos = { m_nScreenWidth * .5f, m_nScreenHeight * .5f };
				coordArrowPos += toCoordinator * 200;
				float coordArrowRot = atan2(_coordinator->GetPosition().y - _player->GetPosition().y, _coordinator->GetPosition().x - _player->GetPosition().x) + SGD::PI / 2;

				graphics->DrawTexture(objArrow, coordArrowPos, coordArrowRot, {}, { 200, 200, 50, 0 }, { .15f, .15f });
			}
		}
		SGD::Vector toStargate = _stargate->GetPosition() - _player->GetPosition();
		if (toStargate.ComputeLength() > 400)
		{
			toStargate.Normalize();
			SGD::Point stargateArrowPos = { m_nScreenWidth * .5f, m_nScreenHeight * .5f };
			stargateArrowPos += toStargate * 200;
			float stargateArrowRot = atan2(_stargate->GetPosition().y - _player->GetPosition().y, _stargate->GetPosition().x - _player->GetPosition().x) + SGD::PI * .5f;

			graphics->DrawTexture(objArrow, stargateArrowPos, stargateArrowRot, {}, { 200, 150, 150, 20 }, { .15f, .15f });
		}
	}
	// draw exp
	graphics->DrawRectangle(exp, { 0, 250, 50 });
	graphics->DrawRectangle(expBox, { 50, 30, 30, 30 }, { 255, 255, 255 }, 1);

	// draw hull
	graphics->DrawRectangle(hull, { 185, 150, 0 });
	graphics->DrawRectangle(hullBox, { 50, 30, 30, 30 }, { 255, 255, 255 }, 1);

	// draw shield
	graphics->DrawRectangle(shield, { 0, 150, 200 });
	graphics->DrawRectangle(shieldBox, { 50, 30, 30, 30 }, { 255, 255, 255 }, 1);

	// draw well
	graphics->DrawTexture(_player->GetWellIcon(), { wellBox.left, wellBox.top }, 0, {}, {}, { .6f, .6f });
	if (_player->GetWellTimer() < _player->GetWellDelay())
		graphics->DrawRectangle(wellCD, SGD::Color{ 150, 200, 0, 0 });
	graphics->DrawRectangle(wellBox, { 50, 30, 30, 30 }, { 255, 255, 255 }, 1);

	// draw push
	graphics->DrawTexture(_player->GetPushIcon(), { pushBox.left, pushBox.top }, 0, {}, {}, { .6f, .6f });
	if (_player->GetPushTimer() < _player->GetPushDelay())
		graphics->DrawRectangle(pushCD, SGD::Color{ 150, 200, 0, 0 });
	graphics->DrawRectangle(pushBox, { 50, 30, 30, 30 }, { 255, 255, 255 }, 1);

	// draw warp
	graphics->DrawTexture(_player->GetWarpIcon(), { warpBox.left, warpBox.top }, 0, {}, {}, { .6f, .6f });
	if (_player->GetWarpTimer() < _player->GetWarpDelay())
		graphics->DrawRectangle(warpCD, SGD::Color{ 150, 200, 0, 0 });
	graphics->DrawRectangle(warpBox, { 50, 30, 30, 30 }, { 255, 255, 255 }, 1);

	// draw level
	std::ostringstream levelString;
	levelString << _player->GetLevel();
	Game::GetInstance()->Font.WriteCenter(SGD::Rectangle{ m_nScreenWidth * .26f, m_nScreenHeight * .90f, m_nScreenWidth * .31f, m_nScreenHeight * .97f }, levelString.str().c_str());
}

void CTestLevelState::Save()
{
	saveData save = CGameplayState::GetInstance()->GetSaveData();


	save.world.size = SGD::Size{ (float)m_nNumQuadsWidth, (float)m_nNumQuadsHeight };
	save.world.quadSize = SGD::Size{ (float)m_nQuadHeight, (float)m_nQuadHeight };
	CGameplayState::GetInstance()->SetSaveData(save);
	EntityManager->Save();
}

void CTestLevelState::Load()
{
	saveData save = CGameplayState::GetInstance()->GetSaveData();




	m_nNumQuadsWidth = (int)save.world.size.width;
	m_nNumQuadsHeight = (int)save.world.size.height;
	m_nQuadWidth = (int)save.world.quadSize.width;
	m_nQuadHeight = (int)save.world.quadSize.height;
	EntityManager->Load();
}
