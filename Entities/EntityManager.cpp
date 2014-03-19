
#include "EntityManager.h"
#include "Ships\Player.h"
#include "Ships\Human.h"
#include "Ships\Enemies\Cobra.h"
#include "Ships\Enemies\Mamba.h"
#include "Ships\Enemies\Moccasin.h"
#include "..\SGD Wrappers\SGD_GraphicsManager.h"
#include "..\GameStates\Game.h"

CEntityManager::CEntityManager()
{
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	images.resize((int)EntityType::Count);
	for (unsigned int i = 0; i < images.size(); i++)
	{
		images[i] = SGD::INVALID_HANDLE;
	}
	images[(int)EntityType::Player] = graphics->LoadTexture("Resources/Graphics/shipTmp.png");
	images[(int)EntityType::Human] = graphics->LoadTexture("Resources/Graphics/shipTmp.png");
	images[(int)EntityType::Copperhead] = graphics->LoadTexture("Resources/Graphics/Ship1.png");
	images[(int)EntityType::Cobra] = graphics->LoadTexture("Resources/Graphics/Ship3.png");
	images[(int)EntityType::Mamba] = graphics->LoadTexture("Resources/Graphics/Ship2.png");
	images[(int)EntityType::Coral] = graphics->LoadTexture("Resources/Graphics/Ship4.png");
	images[(int)EntityType::Moccasin] = graphics->LoadTexture("Resources/Graphics/Ship6.png");

}


CEntityManager::~CEntityManager()
{
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	for (unsigned int i = 0; i < images.size(); i++)
	{
		if (images[i] != SGD::INVALID_HANDLE)
		{
			graphics->UnloadTexture(images[i]);
			images[i] = SGD::INVALID_HANDLE;
		}
	}
}

void CEntityManager::Spawn(EntityType type, SGD::Point position, unsigned int amount, bool coord) //Spawns either one entity, or a flock of enemies, making the leader object in the process
{
	switch (type)
	{
	case EntityType::BaseClass:
		//throw
		break;
	case EntityType::Player:
		if (player != nullptr)
			return;

		player = new CPlayer();
		player->SetImage(images[(int)EntityType::Player]);
		player->SetPosition(position);
		player->SetSize({ 16, 16 });
		player->SetImageSize({ 384, 415 });
		dynamic_cast<CShip*>(player)->setSpeed(200);
		ships.push_back(player);

		break;
	case EntityType::Human:
	{
							  IEntity* human = new CHuman();
							  human->SetPosition(position);
							  human->SetImage(images[(int)EntityType::Human]);
							  allies.push_back(human);
							  ships.push_back(human);
							  type = (EntityType)amount;
							  if (type < EntityType::Copperhead || type > EntityType::Mamba)
								  type = EntityType::Copperhead;
							  Spawn(type, position + SGD::Vector{ 100, 0 }, 1);
							  break;
	}
	case EntityType::Copperhead:
	{
								   CLeader* leader = new CLeader();
								   EntityGroup copperheads;
								   copperheads.resize(amount);
								   for (unsigned int i = 0; i < copperheads.size(); i++)
								   {
									   if (0 == i && coord && !coordinator)
									   {
										   copperheads[i] = new CCopperheadCoord();
									   }
									   else
									   {
										   copperheads[i] = new CCopperhead();
									   }
									   copperheads[i]->SetImage(images[(int)EntityType::Copperhead]);
									   copperheads[i]->SetSize({ 16, 16 });
									   copperheads[i]->SetImageSize({ 70, 94 });
									   smallEnemies.push_back(copperheads[i]);
									   ships.push_back(copperheads[i]);
								   }
								   leader->SetHome(position);
								   leader->Assign(copperheads); //Leader repositions entities
								   break;
	}
	case EntityType::Cobra:
	{
							  CLeader* leader = new CLeader();
							  EntityGroup cobras;
							  cobras.resize(amount);
							  for (unsigned int i = 0; i < cobras.size(); i++)
							  {
								  if (0 == i && coord && !coordinator)
								  {
									  cobras[i] = new CCobraCoord();
								  }
								  else
								  {
									  cobras[i] = new CCobra();
								  }
								  cobras[i]->SetImage(images[(int)EntityType::Cobra]);
								  cobras[i]->SetImageSize({ 77, 93 });
								  cobras[i]->SetSize({ 16, 16 });
								  smallEnemies.push_back(cobras[i]);
								  ships.push_back(cobras[i]);
							  }
							  leader->SetHome(position);
							  leader->Assign(cobras);
							  break;
	}
	case EntityType::Mamba:
	{
							  CLeader* leader = new CLeader();
							  EntityGroup mambas;
							  mambas.resize(amount);
							  for (unsigned int i = 0; i < mambas.size(); i++)
							  {
								  if (0 == i && coord && !coordinator)
								  {
									  mambas[i] = new CMambaCoord();
								  }
								  else
								  {
									  mambas[i] = new CMamba();
								  }
								  mambas[i]->SetImage(images[(int)EntityType::Mamba]);
								  mambas[i]->SetImageSize({ 96, 78 });
								  mambas[i]->SetSize({ 16, 16 });
								  smallEnemies.push_back(mambas[i]);
								  ships.push_back(mambas[i]);
							  }
							  leader->SetHome(position);
							  leader->Assign(mambas);
							  break;
	}
	case EntityType::Coral:
	{
							  CLeader* leader = new CLeader();
							  EntityGroup corals;
							  corals.resize(amount);
							  for (unsigned int i = 0; i < corals.size(); i++)
							  {
								  corals[i] = new CCoral();
								  corals[i]->SetImage(images[(int)EntityType::Coral]);
								  corals[i]->SetImageSize({ 96, 78 });
								  corals[i]->SetSize({ 16, 16 });
								  bigEnemies.push_back(corals[i]);
								  ships.push_back(corals[i]);
							  }
							  leader->SetHome(position);
							  leader->Assign(corals);
							  break;
	}
	case EntityType::Moccasin:
	{
								
	}
	}
}

void CEntityManager::ClearTargeted(CEntity* entity)	//Iterates through the groups that could potentially have this entity targeted, and tells them to untarget it.
{

}

void CEntityManager::Destroy(CEntity* entity)	//Calls ClearTargeted() on the given entity, then entity->release, and erases the pointer from the list.
{

}

void CEntityManager::DestroyGroup(EntityType group)	//Iterates through every entity in a group, calling Destroy()
{

}

void CEntityManager::DestroyAll()	//Calls DestroyGroup on all groups
{

}

void CEntityManager::CheckCollision(EntityGroup& group1, EntityGroup& group2)
{
	EntityGroup* smallGroup;
	EntityGroup* bigGroup;

	if (group1.size() < group2.size())
	{
		smallGroup = &group1;
		bigGroup = &group2;
	}
	else
	{
		smallGroup = &group2;
		bigGroup = &group1;
	}

	//That's about to be a lot of (*group)[]-> operations.
	EntityGroup& small = *smallGroup;
	EntityGroup& big = *bigGroup;
	//Much better

	if (group1 == group2)
	{
		for (unsigned int i = 0; i < small.size(); i++)
		{
			for (unsigned int j = i + 1; j < small.size(); j++)
			{
				if (ShapedCollisions(small[i], big[j]))
				{
					small[i]->HandleCollision(big[j]);
					big[j]->HandleCollision(small[i]);
				}
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < small.size(); i++)
		{
			for (unsigned int j = 0; j < big.size(); j++)
			{
				if (ShapedCollisions(small[i], big[j]))
				{
					small[i]->HandleCollision(big[j]);
					big[j]->HandleCollision(small[i]);
				}
			}
		}
	}
}

bool CEntityManager::ShapedCollisions(IEntity* thing1, IEntity* thing2)
{
	if (thing1 == thing2)
		return false;

	if (thing1->IsCircle())
	{
		if (thing2->IsCircle())
		{
			return circlecollision(thing1, thing2);
		}
		else
		{
			return circleRectCollision(thing1, thing2);
		}
	}
	else
	{
		if (thing2->IsCircle())
		{
			return circleRectCollision(thing2, thing1);
		}
		else
		{
			return rectCollision(thing1, thing2);
		}
	}
}

float CEntityManager::circleLineInterection(SGD::Point circlePoint, float radius, SGD::Point p1, SGD::Point p2)
{
	//incidence = r^2 * dr ^ 2 - D^2
	//where dr = sqrrt(dx^2 + dy^2)
	//dx = p2.x - p1.x; dy = p2.y - p1.y
	//D = p1.x * p2.y - p2.x * p1.y

	//and r is the radius of a circle whose center is at (0,0)

	//Form an offset to calculate from.
	SGD::Vector offset = SGD::Point{ 0, 0 } -circlePoint;

	//offset the points of the line to test against an origin circle
	p1 += offset;
	p2 += offset;
	float dr = sqrt(pow((p2.x - p1.x), 2.0f) + pow((p2.y - p1.y), 2.0f));
	float D = p1.x * p2.y - p2.x * p1.y;

	//incidence < 0 means no intersection. == 0 means only one instercestion point. > 0 means 2 intersection points
	return pow(radius, 2.0f) * pow(dr, 2.0f) - pow(D, 2.0f);
}

bool CEntityManager::circlecollision(IEntity* circle1, IEntity* circle2)
{
	float distance = SGD::Vector(circle2->GetPosition() - circle1->GetPosition()).ComputeLength();
	float collisionDistance = circle1->GetSize().width / 2.0f + circle2->GetSize().width / 2.0f;
	return distance < collisionDistance;
}

bool CEntityManager::circleRectCollision(IEntity* circle, IEntity* rect)
{
	SGD::Point A = SGD::Point{ rect->GetRect().left, rect->GetRect().top };
	SGD::Point B = SGD::Point{ rect->GetRect().right, rect->GetRect().top };
	SGD::Point C = SGD::Point{ rect->GetRect().right, rect->GetRect().bottom };
	SGD::Point D = SGD::Point{ rect->GetRect().left, rect->GetRect().bottom };
	return circle->GetPosition().IsWithinRectangle(rect->GetRect()) ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width / 2.0f, A, B) ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width / 2.0f, B, C) ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width / 2.0f, C, D) ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width / 2.0f, D, A);
}

bool CEntityManager::rectCollision(IEntity* rect1, IEntity* rect2)
{
	SGD::Rectangle box1 = rect1->GetRect();
	SGD::Rectangle box2 = rect2->GetRect();
	return box1.IsIntersecting(box2);
}

void CEntityManager::Update(float dt)
{
	for (unsigned int i = 0; i < leaders.size(); i++)
	{
		leaders[i]->Update(dt);
	}
	for (unsigned int i = 0; i < smallEnemies.size(); i++)
	{
		smallEnemies[i]->Update(dt);
	}
	if (player)
		player->Update(dt);

	CheckCollision(ships, ships);
}

void CEntityManager::Render()
{
	SGD::Rectangle screen = { SGD::Point{ 0, 0 }, SGD::Size{Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() } };
	//SGD::Rectangle test = { SGD::Point{ 0, 0 }, SGD::Size{ 400, 400 } }; // rect. for testing culling
	for (unsigned int i = 0; i < smallEnemies.size(); i++)
	{
		if (smallEnemies[i]->GetRect().IsIntersecting(screen))
			smallEnemies[i]->Render();
	}
	if (player)
	if (player->GetRect().IsIntersecting(screen))
		player->Render();
}