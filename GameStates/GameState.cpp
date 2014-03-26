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
#include "../Message System/DestroyEntityMessage.h"
#include "LevelStates\GameOverState.h"
#include "../Message System/CreateProjectile.h"
#include "../Entities/Ships/Player.h"

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

	objArrow = graphics->LoadTexture("Resources/Graphics/Arrow.png");

	//JD's Test flock, ally and player
	EntityManager = CEntityManager::GetInstance();
	EntityManager->Initialize();
	//EntityManager->Spawn(EntityType::Player, SGD::Point{100,150});

	Generate();
	//EntityManager->Spawn(EntityType::Player, { 150, 150 });
	//EntityManager->Spawn(EntityType::Copperhead, { 200, 200 });
	//EntityManager->Spawn(EntityType::Coral, { 200, 200 });
	//EntityManager->Spawn(EntityType::Stargate, {200,200});
	m_nScreenHeight = Game::GetInstance()->GetScreenHeight();
	m_nScreenWidth = Game::GetInstance()->GetScreenWidth();

	player = EntityManager->GetPlayer();
	cam = CCamera::GetInstance();
	cam->Initiallize(player, SGD::Size{m_nScreenWidth,m_nScreenHeight});


	SGD::MessageManager::GetInstance()->Initialize(&MessageProc);
	
 } 

void	CTestLevelState::Exit(void)
{
	cam->Terminate();
	if (BackgroundImage != SGD::INVALID_HANDLE)
		graphics->UnloadTexture(BackgroundImage);
	graphics->UnloadTexture(objArrow);


	//Terminating Messages or events before Entity manager will BREAK it on the NEXT level.
	//Terminate EntityManager FIRST :3
	EntityManager->Terminate();
	SGD::MessageManager::GetInstance()->Terminate();
	SGD::MessageManager::GetInstance()->DeleteInstance();
	CEventManager::GetInstance().ClearEvents();
	CEventManager::GetInstance().ClearListeners();
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



	SGD::MessageManager::GetInstance()->Update();
	CEventManager::GetInstance().Update();
}

void	CTestLevelState::Render(void)
{
	graphics->DrawTexture(BackgroundImage, { cam->GetOffset().x, cam->GetOffset().y });


	// draw grids
	//for (int i = 0; i < m_nNumQuadsWidth; i++)
	//{
	//	for (int j = 0; j < m_nNumQuadsHeight; j++)
	//	{
	//		SGD::Rectangle r = { SGD::Point{ float(m_nQuadWidth * i), float(m_nQuadHeight * j) }, SGD::Size{ float(m_nQuadWidth), float(m_nQuadHeight) } };
	//		graphics->DrawRectangle(r, SGD::Color{ 0, 0, 0, 0 }, { 255, 255, 255 });
	//	}
	//}

	Game::GetInstance()->Font.Write(SGD::Point{150,150},"testing");
	

	EntityManager->Render();
	UI((CPlayer*)player, EntityManager->GetAllies(), EntityManager->GetCoordinator(), EntityManager->GetStargate());
}

void	CTestLevelState::Generate()
{
	if (LoadXMLLevel("Resources/XML/World/testWorld2.xml"))
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
					EntityManager->Spawn(EntityType::Copperhead, col[j].pos, col[j].objectAmount, true);
					break;
				case COBRA:
					EntityManager->Spawn(EntityType::Cobra, col[j].pos, col[j].objectAmount, true);
					break;
				case MAMBA:
				EntityManager->Spawn(EntityType::Mamba, col[j].pos, col[j].objectAmount, true);
					break;
				case CORAL:
					EntityManager->Spawn(EntityType::Coral, col[j].pos, col[j].objectAmount);
					break;
				case MOCASSIN:
					//EntityManager->Spawn(EntityType::Moccasin, { float(m_nQuadWidth * i + (m_nQuadWidth * .5)), float(m_nQuadHeight * j + (m_nQuadHeight * .5)) }, 1);
					break;
				case ASTEROID:
					EntityManager->Spawn(EntityType::Asteroid, col[j].pos, col[j].objectAmount);
					break;
				case HUMAN:
					EntityManager->Spawn(EntityType::Human, col[j].pos, 1);
					break;
				default:
					break;
				}
			}
		}

		for (int i = 0; i < events.size(); i++)
		{
			if (events[i].eType == "STARGATE")
			{
				EntityManager->Spawn(EntityType::Stargate, { events[i].area.left, events[i].area.top }, 1, false);
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
	case MessageID::CreateProjectile:
	{
								   const CreateProjectileMessage* lMsg = dynamic_cast<const CreateProjectileMessage*>(msg);
		CTestLevelState::GetInstance()->EntityManager->SpawnProjectile(lMsg->GetProjType(),lMsg->GetPosition(),lMsg->GetOwnerSize(),lMsg->GetRotation(),lMsg->GetDamage(), lMsg->GetTier());
		break;
	}
	case MessageID::DestroyEntity:
	{
									 const DestroyEntityMessage* dMsg = dynamic_cast<const DestroyEntityMessage*>(msg);

									 CTestLevelState::GetInstance()->EntityManager->Destroy(dMsg->GetEntity());
									 break;
	}
	case MessageID::GameOver:
	{
								Game::GetInstance()->PushState(CGameOverState::GetInstance());
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
		m_nScreenWidth * .66f * _player->getHull() / _player->getMaxHull(),
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
		m_nScreenWidth * .66f * _player->GetShield() / _player->GetMaxShield(),
		m_nScreenHeight * .90f };

	// experience bar
	SGD::Rectangle expBox = {
		m_nScreenWidth * .25f,
		m_nScreenHeight * .97f,
		m_nScreenWidth * .74f,
		m_nScreenHeight * .98f
	};

	SGD::Rectangle exp = {
		m_nScreenWidth * .25f,
		m_nScreenWidth * .97f,
		m_nScreenWidth * .74f * _player->GetExp() / _player->GetReqExp(),
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
		wellBox.bottom};

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
		for (int i = 0; i < _allies.size(); i++)
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
		/*SGD::Vector toCoordinator = _coordinator->GetPosition() - _player->GetPosition();
		if (toCoordinator.ComputeLength() > 400)
		{
		toCoordinator.Normalize();
		SGD::Point coordArrowPos = { m_nScreenWidth * .5f, m_nScreenHeight * .5f };
		coordArrowPos += toCoordinator * 200;
		float coordArrowRot = atan2(_coordinator->GetPosition().y - _player->GetPosition().y, _coordinator->GetPosition().x - _player->GetPosition().x) + SGD::PI / 2;

		graphics->DrawTexture(objArrow, coordArrowPos, coordArrowRot, {}, { 200, 200, 50, 0 }, { .15f, .15f });
		}*/

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

}
