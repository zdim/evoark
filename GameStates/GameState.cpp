#include "Game.h"
#include "GameState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <ctime>
#include <stdlib.h>
#include "../TinyXML/tinyxml.h"
//#include "../TinyXML/tinystr.h"
//#include "../Graphics/Particles/Flyweight.h"
//#include "../Graphics/Particles/Emitter.h"

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
	graphics = SGD::GraphicsManager::GetInstance();
	BackgroundImage = graphics->LoadTexture("Resources/Graphics/backgroundTmp.png");

	//JD's Test flock, ally and player
//	EnitityManager.Spawn(EntityType::Player, {100,150}, 1);
	srand((unsigned int)time(nullptr));

	Generate();
	m_nScreenHeight = Game::GetInstance()->GetScreenHeight();
	m_nScreenWidth = Game::GetInstance()->GetScreenWidth();


	pSystem.Init();

	
 } 

void	CGameState::Exit(void)
{
	dataParticleTest = nullptr;
	delete dataParticleTest;
}

bool	CGameState::Input(void)
{
	return true;
}

void	CGameState::Update(float dt)
{
	//EnitityManager.Update(dt);

	pSystem.Update(dt);

}

void	CGameState::Render(void)
{
	graphics->DrawTexture(BackgroundImage, { 0, 0 });

	pSystem.Render();

	//EnitityManager.Render();
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].type != NONE)
			SGD::GraphicsManager::GetInstance()->DrawRectangle({ enemies[i].pos.x, enemies[i].pos.y, enemies[i].pos.x + 20, enemies[i].pos.y + 20 }, enemies[i].col);
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
				enemy e;

				float left = float(m_nQuadWidth * j + rand() % m_nQuadWidth);
				float top = float(m_nQuadHeight * i + rand() % m_nQuadHeight);
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
				enemies.push_back(e);
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

			//pType->Attribute("type", &type);
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
		//world[count % 4].push_back(q);
		//for (int i = 0; i < m_nNumQuadsWidth; i++)
		//{
		//	QuadCol& col = world[i];
		//	for (int j = 0; j < m_nNumQuadsHeight; j++)
		//	{
		//		col[j] = q;
		//	}
		//}

		world[q.y][q.x] = q;

		count++;
		pQuad = pQuad->NextSiblingElement("Quad");
	}

	return true;

}