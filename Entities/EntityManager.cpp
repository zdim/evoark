
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
#include "Collidables\Shield.h"
#include "Collidables\ModuleShield.h"
#include "Collidables\RepairStation.h"
#include "..\SGD Wrappers\SGD_GraphicsManager.h"
#include "..\GameStates\Game.h"
#include "..\Message System\VictoryMessage.h"
#include "../Message System/CreateEntityMessage.h"
#include "../Message System/CreateTriggerMessage.h"
#include "Collidables\EventTrigger.h"
#include "../GameStates/GameplayState.h"

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
	images[(int)EntityType::Player] = graphics->LoadTexture("Resources/Graphics/shipTmp.png");
	images[(int)EntityType::Human] = graphics->LoadTexture("Resources/Graphics/shipTmp.png");
	images[(int)EntityType::Copperhead] = graphics->LoadTexture("Resources/Graphics/Ship1.png", { 0, 0, 0 });
	images[(int)EntityType::Cobra] = graphics->LoadTexture("Resources/Graphics/Ship3.png");
	images[(int)EntityType::Mamba] = graphics->LoadTexture("Resources/Graphics/Ship2.png");
	images[(int)EntityType::Coral] = graphics->LoadTexture("Resources/Graphics/Ship4.png");
	images[(int)EntityType::Moccasin] = graphics->LoadTexture("Resources/Graphics/Ship6.png");
	images[(int)EntityType::Laser] = graphics->LoadTexture("Resources/Graphics/Laser.png");
	images[(int)EntityType::Missile] = graphics->LoadTexture("Resources/Graphics/Missile.png");

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
	images[(int)EntityType::Shield] = graphics->LoadTexture("Resources/Graphics/Shield.png");
	images[(int)EntityType::ModuleShield] = graphics->LoadTexture("Resources/Graphics/Shield.png");
	images[(int)EntityType::RepairStation] = graphics->LoadTexture("Resources/Graphics/station.png", { 0, 0, 0, 0 });

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


							   CShield* shield = new CShield();
							   shield->SetPosition(position);
							   shield->SetImage(images[(int)EntityType::Shield]);

							   player = new CPlayer();
							   player->SetImage(images[(int)EntityType::Player]);
							   player->SetPosition(position);
							   player->SetSize({ 32, 32 });
							   dynamic_cast<CPlayer*>(player)->SetStats(CGameplayState::GetInstance()->GetSaveData().playerStat);
							   dynamic_cast<CPlayer*>(player)->SetShield(shield);
							   //player->SetImageSize({ 384, 415 });
							   dynamic_cast<CShip*>(player)->setSpeed(200);
							   shield->SetOwner(dynamic_cast<CShip*>(player));
							   ships.push_back(player);
							   ships.push_back(shield);
							   break;
	}
	case EntityType::Human:
	{
							  IEntity* human = new CHuman();
							  human->SetPosition(position);
							  human->SetImage(images[(int)EntityType::Human]);
							  human->SetSize({ 32, 32 });
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
								  ships.push_back(dynamic_cast<CCoral*>(corals[i])->GetShield());
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

								 dynamic_cast<CMoccasin*>(moccasin)->Init((int)CGameplayState::GetInstance()->GetLevel());

								 moccasin->SetImage(images[(int)EntityType::Moccasin]);
								 moccasin->SetSize({ 256, 256 });
								 moccasin->SetImages(images);

								 bigEnemies.push_back(moccasin);
								 ships.push_back(moccasin);
								 ships.push_back(dynamic_cast<CCoral*>(moccasin)->GetShield());

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
								 stargate->SetSize({ 64, 64 });
								 stargate->SetPosition(position);
								 CVictoryMessage* msg = new CVictoryMessage;
								 dynamic_cast<Trigger*>(stargate)->Assign(msg);
								 stationaries.push_back(stargate);
								 break;
	}
	case EntityType::InvisTrigger:
	{
									 /*InvisTrigger* trig = new InvisTrigger;
									 trig->SetPosition(position);
									 trig->SetSize({ 512, 512 });
									 CreateEntityMessage* msg = new CreateEntityMessage(trig, (EntityType)amount);
									 trig->Assign(msg);
									 stationaries.push_back(trig);
									 break;*/

	}

	}
}


void CEntityManager::SpawnCarrierShips(SGD::Point position, CShip* target, int amount)
{

	CLeader* leader = new CLeader();
	EntityGroup copperheads;
	copperheads.resize(amount);
	for (unsigned int i = 0; i < copperheads.size(); i++)
	{
		copperheads[i] = new CCopperhead();
		
		copperheads[i]->SetImage(images[(int)EntityType::Copperhead]);
		copperheads[i]->SetSize({ 32, 32 });
		dynamic_cast<CEnemy*>(copperheads[i])->SetTarget(target);
		smallEnemies.push_back(copperheads[i]);
		ships.push_back(copperheads[i]);
	}
	leader->SetHome(position);
	leader->Assign(copperheads); //Leader repositions entities
	leaders.push_back(leader);

}

void CEntityManager::SpawnProjectile(EntityType type, SGD::Point position, SGD::Size ownerSize, float rotation, int damage, unsigned int tier, float radius, IEntity* owner)
{
	switch (type)
	{
	case EntityType::Laser:
	{
							  if (tier < 2)
							  {
								  CLaser* laser = new CLaser();
								  laser->SetImage(images[(int)EntityType::Laser]);
								  laser->SetSize({ 2, 8 });
								  //laser->SetImageSize({ 74, 290 });

								  SGD::Vector offset = { 0.0, -1.0 };
								  offset.Rotate(rotation);
								  offset *= (ownerSize.height + laser->GetSize().height)*0.5f + laser->GetSize().height * 0.25f;
								  position += offset;
								  laser->SetPosition(position);
								  laser->SetRotation(rotation);
								  laser->SetDamage(damage);
								  SGD::Vector vel = { 0, -650 };
								  vel.Rotate(rotation);
								  laser->SetVelocity(vel);
								  laser->SetTier(tier);
								  laser->SetOwner(owner);
								  projectiles.push_back(laser);
							  }
							  else
							  {
								  CLaser* laser = new CLaser();
								  CLaser* laserTwo = new CLaser();
								  laserTwo->SetImage(images[(int)EntityType::Laser]);
								  laser->SetImage(images[(int)EntityType::Laser]);
								  laserTwo->SetSize({ 2, 8 });
								  laser->SetSize({ 2, 8 });
								  //laser->SetImageSize({ 74, 290 });
								  SGD::Vector offset = { 0.5f, -1.0f };
								  SGD::Vector offset2 = { -0.5f, -1.0f };
								  SGD::Point pos2 = position;
								  offset.Rotate(rotation);
								  offset *= (ownerSize.height + laser->GetSize().height)*0.5f + laser->GetSize().height * 0.25f;
								  position += offset;
								  offset2.Rotate(rotation);
								  offset2 *= (ownerSize.height + laser->GetSize().height)*0.5f + laser->GetSize().height * 0.25f;
								  pos2 += offset2;
								  laserTwo->SetPosition(position);
								  laserTwo->SetRotation(rotation);
								  laserTwo->SetDamage(damage);
								  laser->SetPosition(pos2);
								  laser->SetRotation(rotation);
								  laser->SetDamage(damage);
								  SGD::Vector vel = { 0, -650 };
								  vel.Rotate(rotation);
								  laserTwo->SetVelocity(vel);
								  laserTwo->SetTier(tier);
								  laser->SetVelocity(vel);
								  laser->SetOwner(owner);
								  laserTwo->SetOwner(owner);
								  laser->SetTier(tier); projectiles.push_back(laser);
								  projectiles.push_back(laserTwo);
							  }
							  break;
	}
	case EntityType::Missile:
	{
								if (tier < 2)
								{
									CMissile* missile = new CMissile();
									missile->SetImage(images[(int)EntityType::Missile]);
									missile->SetSize({ 4, 16 });
									//missile->SetImageSize({ 8, 32 });

									SGD::Vector offset = { 0.0, -1.0 };
									offset.Rotate(rotation);
									offset *= (ownerSize.height + missile->GetSize().height) *0.5f + missile->GetSize().height * 0.25f;
									position += offset;

									missile->SetPosition(position);
									missile->SetRotation(rotation);
									missile->SetDamage(damage);

									SGD::Vector vel = { 0, -620 };
									vel.Rotate(rotation);
									missile->SetVelocity(vel);
									missile->SetOwner(owner);
									projectiles.push_back(missile);
								}

								else if (tier > 1)
								{
									CMissile* missile = new CMissile();
									CMissile* missileTwo = new CMissile();
									missile->SetImage(images[(int)EntityType::Missile]);
									missile->SetSize({ 4, 16 });
									missileTwo->SetImage(images[(int)EntityType::Missile]);
									missileTwo->SetSize({ 4, 16 });
									//missile->SetImageSize({ 8, 32 });
									SGD::Point pos2 = position;

									SGD::Vector offset = { 0.5f, -1.0f };
									offset.Rotate(rotation);
									offset *= (ownerSize.height + missile->GetSize().height) *0.5f + missile->GetSize().height * 0.25f;
									position += offset;

									SGD::Vector offset2 = { -0.5f, -1.0f };
									offset2.Rotate(rotation);
									offset2 *= (ownerSize.height + missile->GetSize().height) *0.5f + missile->GetSize().height * 0.25f;
									pos2 += offset2;

									missile->SetPosition(position);
									missile->SetRotation(rotation);
									missile->SetDamage(damage);

									missileTwo->SetPosition(pos2);
									missileTwo->SetRotation(rotation);
									missileTwo->SetDamage(damage);

									SGD::Vector vel = { 0, -400 };
									vel.Rotate(rotation);
									missile->SetVelocity(vel);
									missileTwo->SetVelocity(vel);
									missile->SetOwner(owner);
									missile->SetOwner(owner);

									if (tier == 3)
									{
										missile->SetTier(3);
										missileTwo->SetTier(3);
									}

									projectiles.push_back(missile);
									projectiles.push_back(missileTwo);
								}
								break;
	}
	case EntityType::Well:
	{
							 CWell* well = new CWell;
							 well->SetImage(images[(int)EntityType::Well]);
							 well->SetRadius(radius);
							 well->SetVelocity({ 0, 0 });

							 //SGD::Vector offset = { 0.0, -1.0 };
							 //offset.Rotate(rotation);
							 //offset *= (ownerSize.height + well->GetSize().height) *0.6f;
							 //position += offset;

							 well->SetPosition(position);
							 well->SetRotation(rotation);
							 well->SetStrength((float)damage);
							 gravObjects.push_back(well);
							 break;
	}
	case EntityType::Push:
	{
							 CPush* push = new CPush;
							 push->SetImage(images[(int)EntityType::Push]);
							 push->SetRadius(radius);
							 push->SetVelocity({ 0, 0 });
							 push->SetSize({ 256, 256 });
							 push->SetOwner(owner);

							 //SGD::Vector offset = { 0.0, -1.0 };
							 //offset.Rotate(rotation);
							 //offset *= (ownerSize.height + push->GetSize().height) * 0.25f;
							 //position += offset;

							 push->SetPosition(position);
							 push->SetRotation(rotation);
							 push->SetStrength((float)damage);
							 gravObjects.push_back(push);
							 break;
	}
	}
}


void CEntityManager::SpawnStation(SGD::Point position, SGD::Size size, CMoccasin* owner )
{
	CRepairStation* station = new CRepairStation();
	station->SetPosition(position);
	station->SetSize(size);
	station->SetOwner(owner);
	station->SetImage(images[(int)EntityType::RepairStation]);
	ships.push_back(station);
}


void CEntityManager::SpawnCollidable(EntityType type, SGD::Point position, SGD::Size size, SGD::Vector velocity, int eventType)
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
									 velocity = SGD::Vector{ 0, -100 };
									 //Pick a random rotation in radians (note: % requires to int-values, so I multiply by 1,000 here to maintain some precision)
									 float rotation = float(rand() % int(2 * SGD::PI * 1000));
									 //Rotate by that random rotation value, dividing it back down into 0 <= rotation <= 2PI
									 velocity.Rotate(rotation / 1000.0f);
								 }
								 asteroid->SetVelocity(velocity);
								 asteroid->SetImage(images[(int)EntityType::Asteroid]);
								 asteroids.push_back(asteroid);
								 break;
	}
	case EntityType::Stargate:
	{
								 if (stargate)
									 return;
								 stargate = new Trigger();
								 stargate->SetImage(images[(int)EntityType::Stargate]);
								 stargate->SetSize(size);
								 stargate->SetPosition(position);
								 CVictoryMessage* msg = new CVictoryMessage;
								 dynamic_cast<Trigger*>(stargate)->Assign(msg);
								 stationaries.push_back(stargate);
								 break;
	}
	case EntityType::InvisTrigger:
	{
									 /* InvisTrigger* trig = new InvisTrigger;
									  trig->SetPosition(position);
									  trig->SetSize(size);
									  CreateTriggerMessage* msg = new CreateTriggerMessage(eventType);
									  trig->Assign(msg);
									  stationaries.push_back(trig);
									  break;*/

									 EventTrigger* trig = new EventTrigger();
									 trig->SetType(eventType);
									 position += size / 2;
									 trig->SetPosition(position);
									 trig->SetSize(size);
									 stationaries.push_back(trig);
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
			group.erase(group.begin() + i);
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

	case EntityType::Shield:
		RemoveFromGroup(ships, entity);
		break;

	case EntityType::ModuleShield:
		RemoveFromGroup(ships, entity);
		break;

	case EntityType::RepairStation:
		RemoveFromGroup(ships, entity);
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
	case EntityType::EventTrigger:
	case EntityType::Planet:
	case EntityType::Barrier:
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
	while (group.size())
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
			leaders.erase(leaders.begin() + i);
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
	SGD::Rectangle screen = CCamera::GetInstance()->GetBoxInWorld();
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
			if (!small[i]->GetRect().IsIntersecting(screen))
			{continue;}
			for (unsigned int j = i + 1; j < big.size(); j++)
			{
				if (!big[j]->GetRect().IsIntersecting(screen))
				{continue;}
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
			if (!small[i]->GetRect().IsIntersecting(screen))
				continue;
			for (unsigned int j = 0; j < big.size(); j++)
			{
				if (!big[j]->GetRect().IsIntersecting(screen))
					continue;
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
	SGD::Rectangle screen = CCamera::GetInstance()->GetBoxInWorld();
	screen.top -= 300;
	screen.left -= 300;
	screen.right += 300;
	screen.bottom += 300;

	for (unsigned int i = 0; i < leaders.size(); i++)
	{
		leaders[i]->Update(dt);
	}
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		//if(ships[i]->GetRect().IsIntersecting(screen))
			ships[i]->Update(dt);
	}
	for (unsigned int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->GetRect().IsIntersecting(screen))
			projectiles[i]->Update(dt);
	}
	for (unsigned int i = 0; i < stationaries.size(); i++)
	{
		if (stationaries[i]->GetRect().IsIntersecting(screen))
			stationaries[i]->Update(dt);
	}
	for (unsigned int i = 0; i < gravObjects.size(); i++)
	{
		if (gravObjects[i]->GetRect().IsIntersecting(screen))
			gravObjects[i]->Update(dt);
	}
	for (unsigned int i = 0; i < asteroids.size(); i++)
	{
		//if (asteroids[i]->GetRect().IsIntersecting(screen))
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
		if (stationaries[i]->GetRect().IsIntersecting(CCamera::GetInstance()->GetBoxInWorld()) && stationaries[i]->GetType() != (int)EntityType::InvisTrigger)
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

void CEntityManager::Save()
{
	saveData save = CGameplayState::GetInstance()->GetSaveData();

	//save.world.size = Game::GetInstance()->GetLevelState()->GetWorldSize();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(player);
	save.playerStat.exp = pPlayer->GetExp();
	save.playerStat.expRequired = pPlayer->GetReqExp();
	save.playerStat.level = pPlayer->GetLevel();
	save.playerStat.perks = pPlayer->GetPerks();
	save.playerStat.laserLevel = pPlayer->GetLaserLevel();
	save.playerStat.missileLevel = pPlayer->GetMissileLevel();
	save.playerStat.wellLevel = pPlayer->GetWellLevel();
	save.playerStat.pushLevel = pPlayer->GetPushLevel();
	save.playerStat.warpLevel = pPlayer->GetWarpLevel();

	if (boss)
	{
		save.world.boss.type = EntityType::Moccasin;
		save.world.boss.position = boss->GetPosition();
		save.world.boss.modules = boss->GetModuleData();
	}
	else
	{
		save.world.boss.type = EntityType::BaseClass;
	}

	EntityData playerEnt;
	playerEnt.coord = false;
	playerEnt.type = EntityType::Player;
	playerEnt.position = player->GetPosition();
	playerEnt.hull = pPlayer->getHull();
	playerEnt.shield = pPlayer->GetShield();

	save.world.entities.clear();
	save.world.entities.push_back(playerEnt);

	for (unsigned int i = 0; i < allies.size(); i++)
	{
		EntityData ally;
		ally.coord = false;
		ally.type = EntityType::Human;
		ally.position = allies[i]->GetPosition();
		ally.hull = dynamic_cast<CShip*>(allies[i])->getHull();
		ally.shield = 0;
		save.world.entities.push_back(ally);
	}

	save.world.collidables.clear();

	for (unsigned int i = 0; i < asteroids.size(); i++)
	{
		CollidableData col;
		col.type = EntityType::Asteroid;
		col.size = asteroids[i]->GetSize();
		col.position = asteroids[i]->GetPosition();
		//Asteroids will heal between saving and loading. 
		//Not a big loss, really since they go offscreen so frequently anyway, it's impossible to really keep track of which ones you've damaged.
		save.world.collidables.push_back(col);
	}

	for (unsigned int i = 0; i < stationaries.size(); i++)
	{
		CollidableData col;
		col.type = (EntityType)stationaries[i]->GetType();
		col.size = stationaries[i]->GetSize();
		col.position = stationaries[i]->GetPosition();
		save.world.collidables.push_back(col);
	}

	save.world.flocks.clear();
	save.world.modFlocks.clear();

	for (unsigned int i = 0; i < leaders.size(); i++)
	{
		if (leaders[i]->GetType() == EntityType::Coral)
		{
			//Add to modFlocks
			ModularFlock flock;
			flock.type = EntityType::Coral;
			flock.home = leaders[i]->GetHome();
			flock.backup = leaders[i]->IsBackup();
			leaders[i]->GetEntityData(flock.members);
			save.world.modFlocks.push_back(flock);
		}
		else
		{
			//Add to flocks
			Flock flock;
			flock.type = leaders[i]->GetType();
			flock.home = leaders[i]->GetHome();
			flock.backup = leaders[i]->IsBackup();
			leaders[i]->GetEntityData(flock.members);
			save.world.flocks.push_back(flock);
		}
	}

	save.world.saved = true;
	CGameplayState::GetInstance()->SetSaveData(save);
}

EntityGroup CEntityManager::CreateCopperheadLeader(Flock& data)
{
	EntityGroup copperheads;
	copperheads.resize(data.members.size());
	for (unsigned int j = 0; j < copperheads.size(); j++)
	{
		if (data.members[j].coord && !coordinator)
		{
			CCopperheadCoord* C = new CCopperheadCoord();
			copperheads[j] = C;
			coordinator = C;
		}
		else
		{
			copperheads[j] = new CCopperhead();
		}
		copperheads[j]->SetImage(images[(int)EntityType::Copperhead]);
		copperheads[j]->SetSize({ 32, 32 });
		//copperheads[i]->SetImageSize({ 70, 94 });
		smallEnemies.push_back(copperheads[j]);
		ships.push_back(copperheads[j]);
	}
	return copperheads;
}

EntityGroup CEntityManager::CreateCobraLeader(Flock& data)
{
	EntityGroup cobras;
	cobras.resize(data.members.size());
	for (unsigned int i = 0; i < cobras.size(); i++)
	{
		if (data.members[i].coord && !coordinator)
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
	return cobras;
}

EntityGroup CEntityManager::CreateMambaLeader(Flock& data)
{
	EntityGroup mambas;
	mambas.resize(data.members.size());
	for (unsigned int i = 0; i < mambas.size(); i++)
	{
		if (data.members.size() && !coordinator)
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
	return mambas;
}

void CEntityManager::CreateLeader(Flock& data)
{
	CLeader* leader = new CLeader;
	EntityGroup flock;
	switch (data.type)
	{
	case EntityType::Copperhead:
		flock = CreateCopperheadLeader(data);
		break;
	case EntityType::Cobra:
		flock = CreateCobraLeader(data);
		break;
	case EntityType::Mamba:
		flock = CreateMambaLeader(data);
		break;
	default:
		return;
	}
	leader->SetHome(data.home);
	leader->Assign(flock); //Leader repositions entities
	for (unsigned int j = 0; j < flock.size(); j++)
	{
		dynamic_cast<CShip*>(flock[j])->setHull(data.members[j].hull);
		if (data.backup)
		{
			flock[j]->SetPosition(data.members[j].position);
		}
	}
	leaders.push_back(leader);
}

void CEntityManager::CreateLeader(ModularFlock& data)
{
	CLeader* leader = new CLeader();
	EntityGroup corals;
	corals.resize(data.members.size());
	for (unsigned int i = 0; i < corals.size(); i++)
	{
		corals[i] = new CCoral();
		corals[i]->SetImage(images[(int)EntityType::Coral]);
		//corals[i]->SetImageSize({ 96, 78 });
		corals[i]->SetSize({ 128, 128 });
		bigEnemies.push_back(corals[i]);
		ships.push_back(corals[i]);
	}
	leader->SetHome(data.home);
	leader->Assign(corals);
	leaders.push_back(leader);
	for (unsigned int j = 0; j < corals.size(); j++)
	{
		dynamic_cast<CCoral*>(corals[j])->SetModuleData(data.members[j].modules);
		dynamic_cast<CCoral*>(corals[j])->SetImages(images);
		if (data.backup)
		{
			corals[j]->SetPosition(data.members[j].position);
		}
	}
}

void CEntityManager::Load()
{
	saveData save = CGameplayState::GetInstance()->GetSaveData();

	if (save.world.boss.type == EntityType::Moccasin)
	{
		boss = new CMoccasin;
		boss->SetModuleData(save.world.boss.modules);
		boss->SetImage(images[(int)EntityType::Moccasin]);
		boss->SetSize({ 256, 256 });
		boss->SetImages(images);
		bigEnemies.push_back(boss);
		ships.push_back(boss);
		boss->SetPosition(save.world.boss.position);
	}

	for (unsigned int i = 0; i < save.world.entities.size(); i++)
	{
		if (save.world.entities[i].type == EntityType::Player)
		{
			CShield* shield = new CShield();
			shield->SetPosition(save.world.entities[i].position);
			shield->SetImage(images[(int)EntityType::Shield]);

			player = new CPlayer();
			player->SetImage(images[(int)EntityType::Player]);
			player->SetPosition(save.world.entities[i].position);
			player->SetSize({ 32, 32 });
			player->SetStats(CGameplayState::GetInstance()->GetSaveData().playerStat);
			player->SetShield(shield);
			player->setSpeed(200);
			shield->SetOwner(dynamic_cast<CShip*>(player));

			player->SetShieldValue(save.world.entities[i].shield);
			player->setHull(save.world.entities[i].hull);

			ships.push_back(player);
			ships.push_back(shield);
		}
		else
		{
			CShip* human = new CHuman();
			human->SetPosition(save.world.entities[i].position);
			human->SetImage(images[(int)EntityType::Human]);
			human->SetSize({ 32, 32 });

			human->setHull(save.world.entities[i].hull);

			allies.push_back(human);
			ships.push_back(human);
			break;
		}
	}

	for (unsigned int i = 0; i < save.world.collidables.size(); i++)
	{
		SpawnCollidable(save.world.collidables[i].type, save.world.collidables[i].position, save.world.collidables[i].size);
	}

	for (unsigned int i = 0; i < save.world.flocks.size(); i++)
	{
		CreateLeader(save.world.flocks[i]);
	}

	for (unsigned int i = 0; i < save.world.modFlocks.size(); i++)
	{
		CreateLeader(save.world.modFlocks[i]);
	}
}
