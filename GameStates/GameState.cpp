#include "Game.h"
#include "GameState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <ctime>
#include <stdlib.h>
#include "../TinyXML/tinyxml.h"
//#include "../TinyXML/tinystr.h"
#include "../Graphics/Particles/Flyweight.h"
#include "../Graphics/Particles/Emitter.h"

CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

CGameState* CGameState::GetInstance(void)
{
	static CGameState instance;
	return &instance;
}

void	CGameState::Enter(void)
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

	TestParticle = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/test.png");

	dataParticleTest = new CFlyweight(TestParticle, { 0.4f, 0.4f }, { 0.1f, 0.1f },
		255, 127, 0, 0, 
		255, 255, 0, 0, 
		1, 1,
		35, 5, 35, 5);

	dataParticleTest2 = new CFlyweight(TestParticle, { 0.4f, 0.4f }, { 0.1f, 0.1f },
		255, 150, 0, 0,
		255, 1, 0, 1,
		1, 1,
		15, 5, 15, 5);


	SGD::Size tempSize = { 4, 4 };
	SGD::Point tempPosition = { 333, 333 };

	SGD::Size tempSize2 = { 3, 3 };
	SGD::Point tempPosition2 = { 150, 150 };


	testEmit = new CEmitter(dataParticleTest, tempSize, tempPosition, 150,0.01f,1.0f,true,30);
	testEmit2 = new CEmitter(dataParticleTest2, tempSize2, tempPosition2, 25, 0.3f, 0.3f,false,5);
	testEmit->Initialize();
	testEmit2->Initialize();
} 

void	CGameState::Exit(void)
{
	delete dataParticleTest;
	dataParticleTest = nullptr;
	delete EntityManager;
	EntityManager = nullptr;
}

bool	CGameState::Input(void)
{
	return true;
}

void	CGameState::Update(float dt)
{
	EntityManager->Update(dt);
	testEmit->Update(dt);
	testEmit2->Update(dt);

}

void	CGameState::Render(void)
{
	graphics->DrawTexture(BackgroundImage, { 0, 0 });

	// draw grids
	for (unsigned int i = 0; i < m_nNumQuadsWidth; i++)
	{
		for (unsigned int j = 0; j < m_nNumQuadsHeight; j++)
		{
			SGD::Rectangle r = { SGD::Point{ m_nQuadWidth * i, m_nQuadHeight * j }, SGD::Size{ m_nQuadWidth, m_nQuadHeight } };
			graphics->DrawRectangle(r, SGD::Color{ 0, 0, 0, 0 }, { 255, 255, 255 });
		}
	}

	testEmit->Render();
	testEmit2->Render();
	EntityManager->Render();
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].type != NONE)
			graphics->DrawRectangle({ enemies[i].pos.x, enemies[i].pos.y, enemies[i].pos.x + 20, enemies[i].pos.y + 20 }, enemies[i].col);
	}
}

void	CGameState::Generate()
{
	if (LoadXMLLevel("worldXML.xml"))
	{
		for (int i = 0; i < m_nNumQuadsWidth; i++)
		{
			QuadCol& col = world[i];
			for (int j = 0; j < m_nNumQuadsHeight; j++)
			{
				/*enemy e;

				float left = float(m_nQuadWidth * i + rand() % m_nQuadWidth);
				float top = float(m_nQuadHeight * j + rand() % m_nQuadHeight);
				e.pos = { left, top };
				e.size = { 20, 20 };
				e.type = col[j].objType;
				switch (col[j].objType)
				{
				case PLAYER:
					e.pos = { float(m_nQuadWidth * i + (m_nQuadWidth * .5) - 10), float(m_nQuadHeight * j + (m_nQuadHeight * .5) - 10) };
					e.col = { 255, 255, 255 };
					break;
				case COPPERHEAD:
					e.col = { 255, 0, 0 };
					break;
				case COBRA:
					e.col = { 0, 255, 0 };
					break;
				case MAMBA:
					e.col = { 0, 0, 255 };
					break;
				case CORAL:
					e.col = { 255, 255, 0 };
					break;
				case MOCASSIN:
					e.col = { 127, 127, 127 };
					break;
				case ASTEROID:
					e.col = { 255, 0, 255 };
					break;
				

				}
				enemies.push_back(e);*/
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


bool CGameState::LoadXMLLevel(const char* pXMLFile)
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
	int count = 0;
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

		count++;
		pQuad = pQuad->NextSiblingElement("Quad");
	}

	return true;

}