
#include "EntityManager.h"
#include "Ships\Player.h"
#include "Ships\Human.h"
#include "Ships\Enemies\Cobra.h" //Includes Copperhead and leader indirectly
#include "..\SGD Wrappers\SGD_GraphicsManager.h"

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
	images[(int)EntityType::Copperhead] = graphics->LoadTexture("Resources/Graphics/shipTmp.png");
	images[(int)EntityType::Cobra] = graphics->LoadTexture("Resources/Graphics/shipTmp.png");
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

void CEntityManager::Spawn(EntityType type, SGD::Point position, unsigned int amount) //Spawns either one entity, or a flock of enemies, making the leader object in the process
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
		break;
	case EntityType::Human:
	{
		IEntity* human = new CHuman();
		human->SetPosition(position);
		human->SetImage(images[(int)EntityType::Human]);
		allies.push_back(human);
		type = (EntityType)amount;
		if (type < EntityType::Copperhead || type > EntityType::Mamba)
			type = EntityType::Copperhead;
		Spawn(type, position + SGD::Vector{100, 0}, 1);
		break;
	}
	case EntityType::Copperhead:
	{
		CLeader* leader = new CLeader();
		EntityGroup copperheads;
		copperheads.resize(amount);
		for (unsigned int i = 0; i < copperheads.size(); i++)
		{
			copperheads[i] = new CCopperhead();
			copperheads[i]->SetImage(images[(int)EntityType::Copperhead]);
			smallEnemies.push_back(copperheads[i]);
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
			cobras[i] = new CCobra();
			cobras[i]->SetImage(images[(int)EntityType::Cobra]);
			smallEnemies.push_back(cobras[i]);
		}
		leader->SetHome(position);
		leader->Assign(cobras);
		break;
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

	for (unsigned int i = 0; i < small.size(); i++)
	{
		for (unsigned int j = 0; j < big.size(); j++)
		{
			if (small[i]->IsCircle())
			{
				if (big[j]->IsCircle())
				{
					if (circlecollision(small[i], big[j]))
					{
						small[i]->HandleCollision(big[j]);
						big[j]->HandleCollision(small[i]);
					}
				}
				else
				{
					if (circleRectCollision(small[i], big[j]))
					{
						small[i]->HandleCollision(big[j]);
						big[j]->HandleCollision(small[i]);
					}
				}
			}
			else
			{
				if (big[j]->IsCircle())
				{
					if (circleRectCollision(big[j], small[i]))
					{
						small[i]->HandleCollision(big[j]);
						big[j]->HandleCollision(small[i]);
					}
				}
				else
				{
					if (rectCollision(small[i], big[j]))
					{
						small[i]->HandleCollision(big[j]);
						big[j]->HandleCollision(small[i]);
					}
				}
			}
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
	SGD::Vector offset = SGD::Point{0,0} - circlePoint;
	
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
	float collisionDistance = circle1->GetSize().width/2.0f + circle2->GetSize().width/2.0f;
	return distance < collisionDistance;
}

bool CEntityManager::circleRectCollision(IEntity* circle, IEntity* rect)
{
	SGD::Point A = SGD::Point{ rect->GetRect().left, rect->GetRect().top };
	SGD::Point B = SGD::Point{ rect->GetRect().right, rect->GetRect().top };
	SGD::Point C = SGD::Point{ rect->GetRect().right, rect->GetRect().bottom };
	SGD::Point D = SGD::Point{ rect->GetRect().left, rect->GetRect().bottom };
	return circle->GetPosition().IsWithinRectangle(rect->GetRect()) ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width/2.0f, A, B) ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width/2.0f, B, C) ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width/2.0f, C, D) ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width/2.0f, D, A);
}

bool CEntityManager::rectCollision(IEntity* rect1, IEntity* rect2)
{

	return rect1->GetRect().IsIntersecting(rect2->GetRect());
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

	
}

void CEntityManager::Render()
{
	for (unsigned int i = 0; i < smallEnemies.size(); i++)
	{
		smallEnemies[i]->Render();
	}
	if (player)
		player->Render();
}