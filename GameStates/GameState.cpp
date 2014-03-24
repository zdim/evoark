#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include <ctime>
#include <stdlib.h>
#include "../TinyXML/tinyxml.h"
//#include "../TinyXML/tinystr.h"
//#include "../Graphics/Particles/Flyweight.h"
//#include "../Graphics/Particles/Emitter.h"
#include "../SGD Wrappers/SGD_MessageManager.h"
#include "../Message System/CreateEntityMessage.h"
#include "../Message System/CreateLaserMessage.h"

CTestLevelState::CTestLevelState()
{
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
	srand((unsigned int)time(nullptr));
	graphics = SGD::GraphicsManager::GetInstance();
	//BackgroundImage = graphics->LoadTexture("Resources/Graphics/backgroundTmp.png");

	//JD's Test flock, ally and player
	EntityManager = new CEntityManager();
	//EntityManager->Spawn(EntityType::Player, SGD::Point{100,150});

	// test player
	//player = new CPlayer();
	//player->SetImage(graphics->LoadTexture("Resources/Graphics/shipTmp.png"));
	//player->SetPosition(SGD::Point{ 100, 100 });
	//player->SetSize(SGD::Size{ 16, 16 });
	//dynamic_cast<CShip*>(player)->setSpeed(200.0);


	// commented out until all objects have sprites and proper initialization
	Generate();
	m_nScreenHeight = Game::GetInstance()->GetScreenHeight();
	m_nScreenWidth = Game::GetInstance()->GetScreenWidth();

	player = EntityManager->GetPlayer();
	cam = CCamera::GetInstance();
	cam->Initiallize(player, SGD::Size{m_nScreenWidth,m_nScreenHeight});

	pSystem.Init();

	SGD::MessageManager::GetInstance()->Initialize(&MessageProc);
	
 } 

void	CTestLevelState::Exit(void)
{
	cam->Terminate();
	SGD::MessageManager::GetInstance()->Terminate();
	SGD::MessageManager::GetInstance()->DeleteInstance();
	delete EntityManager;
	EntityManager = nullptr;
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
	return true;
}

void	CTestLevelState::Update(float dt)
{
	cam->Update(dt);
	EntityManager->Update(dt);

	pSystem.Update(dt);

	SGD::MessageManager::GetInstance()->Update();
}

void	CTestLevelState::Render(void)
{
	graphics->DrawTexture(BackgroundImage, { 0, 0 });

	// draw grids
	for (int i = 0; i < m_nNumQuadsWidth; i++)
	{
		for (int j = 0; j < m_nNumQuadsHeight; j++)
		{
			SGD::Rectangle r = { SGD::Point{ float(m_nQuadWidth * i), float(m_nQuadHeight * j) }, SGD::Size{ float(m_nQuadWidth), float(m_nQuadHeight) } };
			graphics->DrawRectangle(r, SGD::Color{ 0, 0, 0, 0 }, { 255, 255, 255 });
		}
	}

	Game::GetInstance()->Font.Write(SGD::Point{150,150},"testing");
	pSystem.Render();

	EntityManager->Render();
}

void	CTestLevelState::Generate()
{
	if (LoadXMLLevel("Resources/XML/World/testEditor.xml"))
	{
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
					EntityManager->Spawn(EntityType::Player, { float(m_nQuadWidth * i + (m_nQuadWidth * .5)), float(m_nQuadHeight * j + (m_nQuadHeight * .5))});
					break;
				case COPPERHEAD:
					EntityManager->Spawn(EntityType::Copperhead, col[j].pos, col[j].objectAmount);
					break;
				case COBRA:
					EntityManager->Spawn(EntityType::Cobra, col[j].pos, col[j].objectAmount);
					break;
				case MAMBA:
					EntityManager->Spawn(EntityType::Mamba, col[j].pos, col[j].objectAmount);
					break;
				case CORAL:
					//EntityManager->Spawn(EntityType::Coral, col[j].pos, col[j].objectAmount);
					break;
				case MOCASSIN:
					//EntityManager->Spawn(EntityType::Moccasin, { float(m_nQuadWidth * i + (m_nQuadWidth * .5)), float(m_nQuadHeight * j + (m_nQuadHeight * .5)) }, 1);
					break;
				case ASTEROID:
					EntityManager->Spawn(EntityType::Asteroid, col[j].pos, col[j].objectAmount);
					break;
				default:
					break;
				}
			}
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
			else if (type == "MOCASSIN")
				q.objType = MOCASSIN;
			else if (type == "ASTEROID")
				q.objType = ASTEROID;
			else if (type == "PLANET")
				q.objType = PLANET;
			else if (type == "HUMAN")
				q.objType = HUMAN;
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
		world[q.y][q.x] = q;


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
		events.push_back(e);
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
		collisionRects.push_back(r);
		pQuad = pQuad->NextSiblingElement();
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
		break;
	}
	case MessageID::CreateLaser:
	{
								   const CreateLaserMessage* lMsg = dynamic_cast<const CreateLaserMessage*>(msg);
								   unsigned int tier = 1;
								   if (lMsg->GetBoost())
								   {
									   tier = 3;
								   }
		CTestLevelState::GetInstance()->EntityManager->SpawnProjectile(EntityType::Laser,lMsg->GetPosition(),lMsg->GetRotation(),lMsg->GetDamage(), tier);
	}
	}
}

IEntity* CTestLevelState::GetPlayer()
{
	return player;
}
