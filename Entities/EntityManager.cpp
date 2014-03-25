
#include "EntityManager.h"
#include "Ships\Player.h"
#include "Ships\Human.h"
#include "Ships\Enemies\Cobra.h"	//Also includes Copperhead indirectly
#include "Ships\Enemies\Mamba.h"
#include "Ships\Enemies\Moccasin.h"	//Also includes Coral indirectly
#include "Collidables\Trigger.h"
#include "Projectiles\Missile.h"	//Also includes Laser indirectly
#include "..\SGD Wrappers\SGD_GraphicsManager.h"
#include "..\GameStates\Game.h"

CEntityManager::CEntityManager()
{
}


CEntityManager::~CEntityManager()
{
}

CEntityManager* CEntityManager::GetInstance()
{
	static CEntityManager instance;
	return &instance;
}

void CEntityManager::Initialize()
{
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	images.resize((int)EntityType::Count);
	for (unsigned int i = 0; i < images.size(); i++)
	{
		images[i] = SGD::INVALID_HANDLE;
	}
	images[(int)EntityType::Player]		= graphics->LoadTexture("Resources/Graphics/shipTmp.png");
	images[(int)EntityType::Human]		= graphics->LoadTexture("Resources/Graphics/shipTmp.png");
	images[(int)EntityType::Copperhead] = graphics->LoadTexture("Resources/Graphics/Ship1.png");
	images[(int)EntityType::Cobra]		= graphics->LoadTexture("Resources/Graphics/Ship3.png");
	images[(int)EntityType::Mamba]		= graphics->LoadTexture("Resources/Graphics/Ship2.png");
	images[(int)EntityType::Coral]		= graphics->LoadTexture("Resources/Graphics/Ship4.png");
	images[(int)EntityType::Moccasin]	= graphics->LoadTexture("Resources/Graphics/Ship6.png");
	images[(int)EntityType::Laser]		= graphics->LoadTexture("Resources/Graphics/Laser.png");
	images[(int)EntityType::Missile]	= graphics->LoadTexture("Resources/Graphics/Missile.png");

	//Change this when we have module assets
	images[(int)EntityType::BaseModule] = graphics->LoadTexture("Resources/Graphics/shipTmp.png");
	images[(int)EntityType::EngineModule] = graphics->LoadTexture("Resources/Graphics/shipTmp.png");
	images[(int)EntityType::ShieldModule] = graphics->LoadTexture("Resources/Graphics/Ship1.png");
	images[(int)EntityType::LaserModule] = graphics->LoadTexture("Resources/Graphics/Ship3.png");
	images[(int)EntityType::MissileModule] = graphics->LoadTexture("Resources/Graphics/Ship2.png");

	images[(int)EntityType::Stargate] = graphics->LoadTexture("Resources/Graphics/Stargate.png");
}											  	
											  
void CEntityManager::Terminate()			  	
{											  
	DestroyAll();
	DestroyAllLeaders();
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
	for (unsigned int i = 0; i < (unsigned int)EntityType::Count; i++)
	{
		if (images[i] != SGD::INVALID_HANDLE)
		{
			graphics->UnloadTexture(images[i]);
			images[i] = SGD::INVALID_HANDLE;
		}
	}
	images.clear();
}


void CEntityManager::Spawn(EntityType type, SGD::Point position, unsigned int amount, bool coord) //Spawns either one entity, or a flock of enemies, making the leader object in the process
{
	switch (type)
	{
	case EntityType::BaseClass:
		//throw
		break;
	case EntityType::Player:
	{
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
	}
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
										   coord = copperheads[i];
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
								   leaders.push_back(leader);
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
									  coord = cobras[i];
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
							  leaders.push_back(leader);
							  break;
	}
	case EntityType::Mamba:
	{
							  CLeader* leader = nullptr;
							  leader = new CLeader;
							  EntityGroup mambas;
							  mambas.resize(amount);
							  for (unsigned int i = 0; i < mambas.size(); i++)
							  {
								  if (0 == i && coord && !coordinator)
								  {
									  mambas[i] = new CMambaCoord();
									  coord = mambas[i];
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
							  leaders.push_back(leader);
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
								  //corals[i]->SetImageSize({ 96, 78 });
								  corals[i]->SetSize({ 64, 64 });
								  dynamic_cast<CCoral*>(corals[i])->SetImages(images);
								  bigEnemies.push_back(corals[i]);
								  ships.push_back(corals[i]);
							  }
							  leader->SetHome(position);
							  leader->Assign(corals);
							  leaders.push_back(leader);
							  break;
	}
	case EntityType::Moccasin:
	{
								
	}
	case EntityType::Stargate:
		stargate = new Trigger();
		stargate->SetImage(images[(int)EntityType::Stargate]);
		stargate->SetSize({64, 64});
		stationaries.push_back(stargate);

	}
}

void CEntityManager::SpawnProjectile(EntityType type, SGD::Point position, SGD::Size ownerSize, float rotation, int damage, unsigned int tier, float radius)
{
	switch (type)
	{
	case EntityType::Laser:
	{
							  CLaser* laser = new CLaser();
							  laser->SetImage(images[(int)EntityType::Laser]);
							  laser->SetSize({ 2, 8 });
							  laser->SetImageSize({ 74, 290 });

							  SGD::Vector offset = {0.0,-1.0};
							  offset.Rotate(rotation);
							  offset *= (ownerSize.height + laser->GetSize().height)*0.75f;
							  position+=offset;
							  laser->SetPosition(position);
							  laser->SetRotation(rotation);
							  laser->SetDamage(damage);
							  SGD::Vector vel = { 0, -400 };
							  vel.Rotate(rotation);
							  laser->SetVelocity(vel);


							  projectiles.push_back(laser);
							  break;
	}
	case EntityType::Missile:
	{
								CMissile* missile = new CMissile();
								missile->SetImage(images[(int)EntityType::Missile]);
								missile->SetSize({ 4, 16 });
								missile->SetImageSize({ 8, 32 });

								SGD::Vector offset = {0.0,-1.0};
								offset.Rotate(rotation);
								offset *= (ownerSize.height + missile->GetSize().height) *0.6f;
								position += offset;
								
								missile->SetPosition(position);
								missile->SetRotation(rotation);
								missile->SetDamage(damage);

								SGD::Vector vel = {0, -400};
								vel.Rotate(rotation);
								missile->SetVelocity(vel);

								if (tier >= 3)
								{
									missile->FindTarget();
								}

								projectiles.push_back(missile);
								break;
	}
	}
}

//int CEntityManager::GetDamageFromEntity(IEntity* entity, EntityType projType)
//{
//	EntityType type = (EntityType)entity->GetType();
//	switch (type)
//	{
//	case EntityType::Player:
//	{
//		dynamic_cast<CPlayer*>(entity)->GetLaserLevel();
//		break;
//	}
//	case EntityType::Human:
//		break;
//	case EntityType::Copperhead:
//	case EntityType::Cobra:
//	case EntityType::Mamba:
//	case EntityType::Coordinator:
//		break;
//	case EntityType::LaserModule:
//		break;
//	case EntityType::MissileModule:
//		break;
//	case EntityType::WellModule:
//		break;
//	case EntityType::PushModule:
//		break;
//	case EntityType::WarpModule:
//		break;
//	}
//}

void CEntityManager::ClearTargeted(IEntity* entity)	//Iterates through the groups that could potentially have this entity targeted, and tells them to untarget it.
{
	if (!entity)
		return;

	for (unsigned int i = 0; i < smallEnemies.size(); i++)
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(smallEnemies[i]);
		if (enemy->GetTarget() == entity)
			enemy->SetTarget(nullptr);
	}
	for (unsigned int i = 0; i < bigEnemies.size(); i++)
	{
		CEnemy* enemy = dynamic_cast<CEnemy*>(bigEnemies[i]);
		if (enemy->GetTarget() == entity)
			enemy->SetTarget(nullptr);
	}
	for (unsigned int i = 0; i < allies.size(); i++)
	{
		CHuman* ally = dynamic_cast<CHuman*>(allies[i]);
		if (ally->GetTarget() == entity)
			ally->SetTarget(nullptr);
	}
}

int CEntityManager::FindLeaderIndex(IEntity* entity)
{
	for (unsigned int i = 0; i < leaders.size(); i++)
	{
		if (leaders[i]->FindInFlock(entity) >= 0)
			return i;
	}
	return -1;
}

void CEntityManager::RemoveFromLeader(IEntity* entity)
{
	int l = FindLeaderIndex(entity);
	if (l < 0)
		return;
	leaders[l]->Remove(entity);
}

void CEntityManager::RemoveFromGroup(EntityGroup& group, IEntity* entity)
{
	for (unsigned int i = 0; i < group.size(); i++)
	{
		if (group[i] == entity)
		{
			group.erase(group.begin()+i);
			return;
		}
	}
}

void CEntityManager::Destroy(IEntity* entity)	//Calls ClearTargeted() on the given entity, then entity->release, and erases the pointer from the list.
{
	if (!entity)
		return;

	ClearTargeted(entity);
	switch ((EntityType)entity->GetType())
	{
	case EntityType::Player:
		RemoveFromGroup(ships, entity);
		//player->Release();
		player = nullptr;
		break;
	case EntityType::Human:
		dynamic_cast<CHuman*>(entity)->SetTarget(nullptr);
		RemoveFromGroup(ships, entity);
		RemoveFromGroup(allies, entity);
		break;
	case EntityType::Copperhead:
	case EntityType::Cobra:
	case EntityType::Mamba:
		dynamic_cast<CEnemy*>(entity)->SetTarget(nullptr);
		RemoveFromGroup(smallEnemies, entity);
		RemoveFromGroup(ships, entity);
		RemoveFromLeader(entity);
		break;
	case EntityType::Coral:
	case EntityType::Moccasin:
		dynamic_cast<CEnemy*>(entity)->SetTarget(nullptr);
		dynamic_cast<CCoral*>(entity)->DestroyAllModules();
		RemoveFromGroup(bigEnemies, entity);
		RemoveFromGroup(ships, entity);
		RemoveFromLeader(entity);
		break;
	case EntityType::Missile:
		dynamic_cast<CMissile*>(entity)->SetTarget(nullptr);
	case EntityType::Laser:
		RemoveFromGroup(projectiles, entity);
		break;
	}
	entity->Release();
}

void CEntityManager::DestroyGroup(EntityGroup& group)	//Iterates through every entity in a group, calling Destroy()
{
	while(group.size())
	{
		Destroy(group[0]);
	}
}

void CEntityManager::DestroyAll()	//Calls DestroyGroup on all groups
{
	DestroyGroup(ships);
	DestroyGroup(projectiles);
	DestroyGroup(asteroids);
	DestroyGroup(stationaries);
	DestroyGroup(gravObjects);
}

void CEntityManager::DestroyLeader(CLeader* l)
{
	for (unsigned int i = 0; i < leaders.size(); i++)
	{
		if (leaders[i] == l)
		{
			leaders.erase(leaders.begin()+i);
			delete l;
			return;
		}
	}
}

void CEntityManager::DestroyAllLeaders()
{
	for (unsigned int i = 0; i < leaders.size(); i++)
	{
		delete leaders[i];
	}
	leaders.resize(0);
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

	if (!thing1 || !thing2)
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
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		ships[i]->Update(dt);
	}
	for (unsigned int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->Update(dt);
	}
	for (unsigned int i = 0; i < stationaries.size(); i++)
	{
		stationaries[i]->Update(dt);
	}

	CheckCollision(ships, ships);
	CheckCollision(projectiles, ships);
	CheckCollision(ships, stationaries);
}

void CEntityManager::Render()
{
	SGD::Rectangle screen = { SGD::Point{ 0, 0 }, SGD::Size{Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() } };
	//SGD::Rectangle test = { SGD::Point{ 0, 0 }, SGD::Size{ 400, 400 } }; // rect. for testing culling
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		if (ships[i]->GetRect().IsIntersecting(CCamera::GetInstance()->GetBoxInWorld()))
			ships[i]->Render();
	}
	for (unsigned int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->GetRect().IsIntersecting(CCamera::GetInstance()->GetBoxInWorld()))
			projectiles[i]->Render();
	}
	for (unsigned int i = 0; i < stationaries.size(); i++)
	{
		if (stationaries[i]->GetRect().IsIntersecting(CCamera::GetInstance()->GetBoxInWorld()))
			stationaries[i]->Render();
	}
	//If player exists, he SHOULD be in the EntityGroup "ships"
	//if (player)
	//if (player->GetRect().IsIntersecting(screen))
	//	player->Render();
}