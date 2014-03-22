#include "Game.h"
#include "GameState.h"
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
	BackgroundImage = graphics->LoadTexture("Resources/Graphics/backgroundTmp.png");

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


	pSystem.Init();

	SGD::MessageManager::GetInstance()->Initialize(&MessageProc);
	
 } 

void	CTestLevelState::Exit(void)
{
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
	}
	if (input->IsKeyDown(SGD::Key::Alt) && input->IsKeyPressed(SGD::Key::Q))
	{
		Game::GetInstance()->PopState();
		Game::GetInstance()->PopState();
		return false;
	}
	return true;
}

void	CTestLevelState::Update(float dt)
{
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

	pSystem.Render();

	EntityManager->Render();
}

void	CTestLevelState::Generate()
{
	if (LoadXMLLevel("Resources/XML/World/worldXML.xml"))
	{
		for (int i = 0; i < m_nNumQuadsWidth; i++)
		{
			QuadCol& col = world[i];
			for (int j = 0; j < m_nNumQuadsHeight; j++)
			{

				float left = float(m_nQuadWidth * i + rand() % m_nQuadWidth);
				float top = float(m_nQuadHeight * j + rand() % m_nQuadHeight);

				switch (col[j].objType)
				{
				case PLAYER:
					EntityManager->Spawn(EntityType::Player, { float(m_nQuadWidth * i + (m_nQuadWidth * .5)), float(m_nQuadHeight * j + (m_nQuadHeight * .5))});
					break;
				case COPPERHEAD:
					EntityManager->Spawn(EntityType::Copperhead, { left, top }, col[j].objectAmount);
					break;
				case COBRA:
					EntityManager->Spawn(EntityType::Cobra, { left, top }, col[j].objectAmount);
					break;
				case MAMBA:
					EntityManager->Spawn(EntityType::Mamba, { left, top }, col[j].objectAmount);
					break;
				case CORAL:
					EntityManager->Spawn(EntityType::Coral, { left, top }, col[j].objectAmount);
					break;
				case MOCASSIN:
					EntityManager->Spawn(EntityType::Moccasin, { left, top }, col[j].objectAmount);
					break;
				case ASTEROID:
					EntityManager->Spawn(EntityType::Asteroid, { left, top }, col[j].objectAmount);
					break;

				}
			}
		}
	}
	else
	{

	//	//m_nQuadHeight = 300;
	//	//m_nQuadWidth = 300;
	//	// --------hardcoded for example----------
	//	std::vector<std::string> tempNames;
	//	std::string blue = "blue";
	//	tempNames.push_back(blue);
	//	std::string red = "red";
	//	tempNames.push_back(red);
	//	std::string white = "white";
	//	tempNames.push_back(white);
	//	std::string green = "green";
	//	tempNames.push_back(green);
	//	Quadrant grid[4][4];
	//	for (int x = 0; x < 4; x++)
	//	{
	//		for (int y = 0; y < 4; y++)
	//		{
	//			Quadrant q;
	//			q.x = x;
	//			q.y = y;
	//			q.objType = tempNames[rand() % 4];
	//			q.objectAmount = rand() % 5;
	//			grid[x][y] = q;
	//		}
	//	}
	//	// --------------------------------------
	//}
	//for (int x = 0; x < 4; x++)
	//{
	//	for (int y = 0; y < 4; y++)
	//	{
	//		float left, top;
	//		if (grid[x][y].objectType == white)
	//		{
	//			grid[x][y].objectAmount = 1;
	//			left = float(m_nQuadWidth * x + (m_nQuadWidth * .5) - 10);
	//			top = float(m_nQuadHeight * x + (m_nQuadHeight * .5) - 10);
	//		}
	//		else
	//		{
	//			left = float(m_nQuadWidth * x + rand() % m_nQuadWidth);
	//			top = float(m_nQuadHeight * x + rand() % m_nQuadHeight);
	//		}
	//		enemy e;
	//		e.pos = { left, top, left + 20, top + 20 };
	//		e.type = grid[x][y].objectType;
	//		if (grid[x][y].objectType == white)
	//			e.col = { 255, 255, 255 };
	//		if (grid[x][y].objectType == green)
	//			e.col = { 0, 255, 0 };
	//		if (grid[x][y].objectType == blue)
	//			e.col = { 0, 0, 255 };
	//		if (grid[x][y].objectType == red)
	//			e.col = { 255, 0, 0 };

	//		enemies.push_back(e);
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
	world.resize(m_nNumQuadsWidth);
	for (unsigned int size = 0; size < world.size(); size++)
		world[size].resize(m_nNumQuadsHeight);

	TiXmlElement* pQuad = pDetails->FirstChildElement("Quad");

	while (pQuad != nullptr)
	{
		Quadrant q;
		pQuad->Attribute("x", &q.x);
		pQuad->Attribute("y", &q.y);
		pQuad->Attribute("possibleTypes", &q.possibleObjects);

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
		else if (type == "NONE")
			q.objType = NONE;

		world[q.y][q.x] = q;


		pQuad = pQuad->NextSiblingElement("Quad");
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