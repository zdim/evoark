
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

void CEntityManager::CheckCollision(EntityGroup group1, EntityGroup group2)
{

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