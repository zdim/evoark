
#include "EntityManager.h"
#include "Ships\Player.h"
#include "Ships\Human.h"
#include "Ships\Enemies\Cobra.h"	//Also includes Copperhead indirectly
#include "Ships\Enemies\Mamba.h"
#include "Ships\Enemies\Moccasin.h"	//Also includes Coral indirectly
#include "Collidables\Trigger.h"
#include "Projectiles\Missile.h"	//Also includes Laser indirectly
#include "Projectiles\Well.h"
#include "Projectiles\Push.h"
#include "Collidables\InvisibleTrigger.h"
#include "Collidables\Asteroid.h"
#include "Collidables\Barrier.h"
#include "..\SGD Wrappers\SGD_GraphicsManager.h"
#include "..\GameStates\Game.h"
#include "..\Message System\VictoryMessage.h"
#include "../Message System/CreateEntityMessage.h"

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
	images[(int)EntityType::Copperhead] = graphics->LoadTexture("Resources/Graphics/Ship1.png", { 0, 0, 0 });
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
	images[(int)EntityType::WellModule] = graphics->LoadTexture("Resources/Graphics/Ship4.png");
	images[(int)EntityType::PushModule] = graphics->LoadTexture("Resources/Graphics/Ship6.png");
	images[(int)EntityType::WarpModule] = graphics->LoadTexture("Resources/Graphics/shipTmp.png");

	images[(int)EntityType::Well] = graphics->LoadTexture("Resources/Graphics/GravWellIcon.png");
	images[(int)EntityType::Push] = graphics->LoadTexture("Resources/Graphics/GravPushIcon.png");

	images[(int)EntityType::Stargate] = graphics->LoadTexture("Resources/Graphics/Stargate.png");
	images[(int)EntityType::Planet] = graphics->LoadTexture("Resources/Graphics/planet.png");
	images[(int)EntityType::Barrier] = graphics->LoadTexture("Resources/Graphics/wallTile.png");
	images[(int)EntityType::Asteroid] = graphics->LoadTexture("Resources/Graphics/asteroid.png");
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

IEntity* CEntityManager::GetCoordinator()
{
	if (dynamic_cast<CCobraCoord*>(coordinator)) return dynamic_cast<CCobraCoord*>(coordinator);
	if (dynamic_cast<CCopperheadCoord*>(coordinator)) return dynamic_cast<CCopperheadCoord*>(coordinator);
	if (dynamic_cast<CMambaCoord*>(coordinator)) return dynamic_cast<CMambaCoord*>(coordinator);
	return nullptr;

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
		player->SetSize({ 32, 32 });
		//player->SetImageSize({ 384, 415 });
		dynamic_cast<CShip*>(player)->setSpeed(200);
		ships.push_back(player);

		break;
	}
	case EntityType::Human:
	{
							  IEntity* human = new CHuman();
							  human->SetPosition(position);
							  human->SetImage(images[(int)EntityType::Human]);
							  human->SetSize({32,32});
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
										   CCopperheadCoord* C = new CCopperheadCoord();
										   copperheads[i] = C;
										   coordinator = C;
									   }
									   else
									   {
										   copperheads[i] = new CCopperhead();
									   }
									   copperheads[i]->SetImage(images[(int)EntityType::Copperhead]);
									   copperheads[i]->SetSize({ 32, 32 });
									   //copperheads[i]->SetImageSize({ 70, 94 });
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
									  CCobraCoord* C = new CCobraCoord;
									  cobras[i] = C;
									  coordinator = C;
								  }
								  else
								  {
									  cobras[i] = new CCobra();
								  }
								  cobras[i]->SetImage(images[(int)EntityType::Cobra]);
								  //cobras[i]->SetImageSize({ 77, 93 });
								  cobras[i]->SetSize({ 32, 32 });
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
									  CMambaCoord* C = new CMambaCoord;
									  mambas[i] = C;
									  coordinator = C;
								  }
								  else
								  {
									  mambas[i] = new CMamba();
								  }
								  mambas[i]->SetImage(images[(int)EntityType::Mamba]);
								  //mambas[i]->SetImageSize({ 96, 78 });
								  mambas[i]->SetSize({ 32, 32 });
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
								  corals[i]->SetSize({ 128, 128 });
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
								 if (boss)
									 return;
								 CMoccasin* moccasin = new CMoccasin;
								 amount--;
								 for (amount = amount; amount > 0; amount--)
								 {
									 moccasin->AddModule();
								 }
								 moccasin->SetImage(images[(int)EntityType::Moccasin]);
								 moccasin->SetSize({256,256});
								 moccasin->SetImages(images);
								 bigEnemies.push_back(moccasin);
								 ships.push_back(moccasin);

								 moccasin->SetPosition(position);
								 boss = moccasin;
								 break;
	}
	case EntityType::Stargate:
	{
		if (stargate)
			return;
		stargate = new Trigger();
		stargate->SetImage(images[(int)EntityType::Stargate]);
		stargate->SetSize({64, 64});
		stargate->SetPosition(position);
		CVictoryMessage* msg = new CVictoryMessage;
		dynamic_cast<Trigger*>(stargate)->Assign(msg);
		stationaries.push_back(stargate);
		break;
	}
	case EntityType::InvisTrigger:
	{
								InvisTrigger* trig = new InvisTrigger;
								trig->SetPosition(position);
								trig->SetSize({512,512});
								CreateEntityMessage* msg = new CreateEntityMessage(trig, (EntityType)amount);
								trig->Assign(msg);
								stationaries.push_back(trig);
								break;
	}

	}
}

void CEntityManager::SpawnProjectile(EntityType type, SGD::Point position, SGD::Size ownerSize, float rotation, int damage, unsigned int tier, float radius, IEntity* owner)
{
	switch (type)
	{
	case EntityType::Laser:
	{
							  CLaser* laser = new CLaser();
							  laser->SetImage(images[(int)EntityType::Laser]);
							  laser->SetSize({ 2, 8 });
							  //laser->SetImageSize({ 74, 290 });

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
								//missile->SetImageSize({ 8, 32 });

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
	case EntityType::Well:
	{
							 CWell* well = new CWell;
							 well->SetImage(images[(int)EntityType::Well]);
							 well->SetRadius(radius);
							 well->SetVelocity({0,0});
							 
							 //SGD::Vector offset = { 0.0, -1.0 };
							 //offset.Rotate(rotation);
							 //offset *= (ownerSize.height + well->GetSize().height) *0.6f;
							 //position += offset;

							 well->SetPosition(position);
							 well->SetRotation(rotation);
							 well->SetStrength(damage);
							 gravObjects.push_back(well);
							 break;
	}
	case EntityType::Push:
	{
							 CPush* push = new CPush;
							 push->SetImage(images[(int)EntityType::Push]);
							 push->SetRadius(radius);
							 push->SetVelocity({ 0, 0 });
							 push->SetSize({256,256});
							 push->SetOwner(owner);
							 
							 //SGD::Vector offset = { 0.0, -1.0 };
							 //offset.Rotate(rotation);
							 //offset *= (ownerSize.height + push->GetSize().height) * 0.25f;
							 //position += offset;

							 push->SetPosition(position);
							 push->SetRotation(rotation);
							 push->SetStrength(damage);
							 gravObjects.push_back(push);
							 break;
	}
	}
}

void CEntityManager::SpawnCollidable(EntityType type, SGD::Point position, SGD::Size size, SGD::Vector velocity)
{
	switch (type)
	{
	case EntityType::Planet:
	{
		CPlanet* planet = new CPlanet();
		planet->SetPosition(position);
		planet->SetImage(images[(int)EntityType::Planet]);
		stationaries.push_back(planet);
		break;
	}
	case EntityType::Barrier:
	{
								CBarrier* barrier = new CBarrier();
								barrier->SetPosition(position);
								barrier->SetSize(size);
								barrier->SetImage(images[(int)EntityType::Barrier]);
								stationaries.push_back(barrier);

		break;
	}
	case EntityType::Asteroid:
	{
								 CAsteroid* asteroid = new CAsteroid();
								 asteroid->SetPosition(position);
								 asteroid->SetSize(size);
								 //If the velocity is defaulted
								 if (velocity == SGD::Vector{ 0, 0 })
								 {
									 //Set the velocity to move 100 pixels/second upward
									 velocity = SGD::Vector{0,-100};
									 //Pick a random rotation in radians (note: % requires to int-values, so I multiply by 1,000 here to maintain some precision)
									 float rotation = float(rand() % int(2 * SGD::PI * 1000));
									 //Rotate by that random rotation value, dividing it back down into 0 <= rotation <= 2PI
									 velocity.Rotate(rotation/1000.0f);
								 }
								 asteroid->SetVelocity(velocity);
								 asteroid->SetImage(images[(int)EntityType::Asteroid]);
								 asteroids.push_back(asteroid);
		break;
	}
	default:
		break;
	}
}

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
	if (entity == player)
		entity = player;
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
		if (GetCoordinator() == entity)
		{
			coordinator = nullptr;
		}
		break;
	case EntityType::Moccasin:
		boss = nullptr;
	case EntityType::Coral:
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
	case EntityType::Well:
	case EntityType::Push:
		RemoveFromGroup(gravObjects, entity);
		break;
	case EntityType::Stargate:
		stargate = nullptr;
	case EntityType::InvisTrigger:
	case EntityType::Planet:
		RemoveFromGroup(stationaries, entity);
		break;
	case EntityType::Asteroid:
		RemoveFromGroup(asteroids, entity);
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
			//return circleRectCollision(thing1, thing2);
			return circlecollision(thing1, thing2);
		}
	}
	else
	{
		if (thing2->IsCircle())
		{
			//return circleRectCollision(thing2, thing1);
			return circlecollision(thing1, thing2);
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
		circleLineInterection(circle->GetPosition(), circle->GetSize().width / 2.0f, A, B) >= 0 ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width / 2.0f, B, C) >= 0 ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width / 2.0f, C, D) >= 0 ||
		circleLineInterection(circle->GetPosition(), circle->GetSize().width / 2.0f, D, A) >= 0;
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
	for (unsigned int i = 0; i < gravObjects.size(); i++)
	{
		gravObjects[i]->Update(dt);
	}
	for (unsigned int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->Update(dt);
	}

	CheckCollision(ships, ships);
	CheckCollision(projectiles, ships);
	CheckCollision(ships, stationaries);

	CheckCollision(asteroids, stationaries);
	CheckCollision(asteroids, ships);
	CheckCollision(asteroids, projectiles);
	
	if (gravObjects.size())
	{
		CheckCollision(ships, gravObjects);
		CheckCollision(projectiles, gravObjects);
		CheckCollision(asteroids, gravObjects);
	}
}

void CEntityManager::Render()
{
	SGD::Rectangle screen = { SGD::Point{ 0, 0 }, SGD::Size{ (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() } };
	//SGD::Rectangle test = { SGD::Point{ 0, 0 }, SGD::Size{ 400, 400 } }; // rect. for testing culling
	for (unsigned int i = 0; i < stationaries.size(); i++)
	{
		if (stationaries[i]->GetRect().IsIntersecting(CCamera::GetInstance()->GetBoxInWorld()))
			stationaries[i]->Render();
	}

	for (unsigned int i = 0; i < gravObjects.size(); i++)
	{
		if (gravObjects[i]->GetRect().IsIntersecting(CCamera::GetInstance()->GetBoxInWorld()))
			gravObjects[i]->Render();
	}

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
	for (unsigned int i = 0; i < asteroids.size(); i++)
	{
		if (asteroids[i]->GetRect().IsIntersecting(CCamera::GetInstance()->GetBoxInWorld()))
			asteroids[i]->Render();
	}

	//If player exists, he SHOULD be in the EntityGroup "ships"
	//if (player)
	//if (player->GetRect().IsIntersecting(screen))
	//	player->Render();
}