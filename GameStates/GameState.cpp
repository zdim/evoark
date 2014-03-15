#include "Game.h"
#include "GameState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <ctime>
#include <stdlib.h>
#include "../TinyXML/tinyxml.h"
//#include "../TinyXML/tinystr.h"


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
	BackgroundImage = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/backgroundTmp.png");
	Generate();
	m_nScreenHeight = Game::GetInstance()->GetScreenHeight();
	m_nScreenWidth = Game::GetInstance()->GetScreenWidth();
}

void	CGameState::Exit(void)
{

}

bool	CGameState::Input(void)
{
	return true;
}

void	CGameState::Update(float dt)
{

}

void	CGameState::Render(void)
{
	SGD::GraphicsManager::GetInstance()->DrawTexture(BackgroundImage, { 0, 0});
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		
		SGD::GraphicsManager::GetInstance()->DrawRectangle(enemies[i].pos, enemies[i].col);
	}
}

void	CGameState::Generate()
{
	m_nQuadHeight = 300;
	m_nQuadWidth = 300;

	// --------hardcoded for example----------
	std::vector<std::string> tempNames;
	std::string blue = "blue";
	tempNames.push_back(blue);
	std::string red = "red";
	tempNames.push_back(red);
	std::string white = "white";
	tempNames.push_back(white);
	std::string green = "green";
	tempNames.push_back(green);

	Quadrant grid[4][4];
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			Quadrant q;
			q.x = x;
			q.y = y;
			q.objectType = tempNames[rand() % 4];
			q.objectAmount = rand() % 5;
			grid[x][y] = q;
		}
	}
	// --------------------------------------

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			float left, top;
			if (grid[x][y].objectType == white)
			{
				grid[x][y].objectAmount = 1;
				left = float(m_nQuadWidth * x + (m_nQuadWidth * .5) - 10);
				top = float(m_nQuadHeight * x + (m_nQuadHeight * .5) - 10);
			}
			else
			{
				left = float(m_nQuadWidth * x + rand() % m_nQuadWidth);
				top = float(m_nQuadHeight * x + rand() % m_nQuadHeight);
			}
			enemy e;
			e.pos = { left, top, left + 20, top + 20 };
			e.type = grid[x][y].objectType;
			if (grid[x][y].objectType == white)
				e.col = { 0, 0, 0 };
			if (grid[x][y].objectType == green)
				e.col = { 0, 255, 0 };
			if (grid[x][y].objectType == blue)
				e.col = { 0, 0, 255 };
			if (grid[x][y].objectType == red)
				e.col = { 255, 0, 0 };

			enemies.push_back(e);
		}
	}
}

bool CGameState::LoadXMLLevel(const char* pXMLFile)
{
	TiXmlDocument doc(pXMLFile);
	if (doc.LoadFile())
	{
		
		return true;
	}
	return false;
}