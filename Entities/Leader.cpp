
#include "Leader.h"
#include <algorithm>
#include "Ships\Enemies\Coral.h"
#include "../GameStates/GameplayState.h"
#include "EntityManager.h"

CLeader::CLeader()
{
	state = LeaderState::Return;
}

CLeader::~CLeader()
{

}

bool CLeader::Assign(const EntityGroup& flock)
{
	if (!members.empty())
		return false;

	members.resize(flock.size());
	destinations.resize(flock.size());
	for (unsigned int i = 0; i < members.size(); i++)
	{
		members[i] = dynamic_cast<CEnemy*>(flock[i]);
		//members[i]->SetPosition(destinations[i]);
		members[i]->AddRef();
	}
	CalculateDestinations();
	for (unsigned int i = 0; i < members.size(); i++)
	{
		//members[i] = flock[i];
		members[i]->SetPosition(destinations[i]);
	}
	return true;
}

void CLeader::CalculateDestinations()
{
	float shipSize = std::max(members[0]->GetSize().width, members[0]->GetSize().height);
	if (target == nullptr)
	{
		destinations[0] = home;
		for (unsigned int i = 1; i < destinations.size(); i++)
		{
			// sloppy, but it works for now. adjusted because it was always giving cos = 1 and sin = 0
			float size = (float)members.size();
			float a = i / size;
			float toCos = a * 2.0f * SGD::PI;
			float cos = cosf(toCos);
			float sin = sinf(toCos);
			//I changed the 2.0f in the following lines to 3.0f because the ships were WAY too close together.
			//We may even want to change it to 4 when we're spawning them in a larger environment.
			SGD::Vector offset = SGD::Vector
				{shipSize * 3.0f * cos,
				shipSize * 3.0f * sin};

			destinations[i] = { home.x + offset.x, home.y + offset.y };
		}
	}
}

void CLeader::Update(float dt)
{
	//AI not in this user story. Just need a stub to build
}

int CLeader::FindInFlock(IEntity* entity)
{
	for (unsigned int i = 0; i < members.size(); i++)
	{
		if (members[i] == entity)
			return i;
	}
	return -1;
}

void CLeader::Remove(IEntity* entity)
{
	entity->Release();
	int i = FindInFlock(entity);
	if (i < 0)
		return;
	//members[i]->Release();
	members.erase(members.begin()+i);
	if (!members.size())
	{
		CEntityManager::GetInstance()->DestroyLeader(this);
	}
}

void CLeader::SetTarget(CShip* newTarget)
{
	if (target == newTarget)
		return;

	if (target)
		target->Release();
	
	if (newTarget)
		newTarget->AddRef();

	target = newTarget;
}

void CLeader::GetEntityData(std::vector<EntityData>& flockData)
{
	flockData.clear();
	if (GetType() == EntityType::Coral)
	{
		return;
	}
	EntityType t = (EntityType)members[0]->GetType();
	for (unsigned int i = 0; i < members.size(); i++)
	{
		EntityData data;
		data.type = t;
		data.coord = members[i]->IsCoordinator();
		data.position = members[i]->GetPosition();
		data.hull = members[i]->getHull();
		data.shield = 0;
		flockData.push_back(data);
	}
}

void CLeader::GetEntityData(std::vector<ModularEntityData>& flockData)
{
	flockData.clear();
	if (GetType() != EntityType::Coral)
	{
		return;
	}
	EntityType t = (EntityType)members[0]->GetType();
	for (unsigned int i = 0; i < members.size(); i++)
	{
		ModularEntityData data;
		CCoral* coral = dynamic_cast<CCoral*>(members[i]);
		data.type = t;
		data.position = coral->GetPosition();
		data.modules = coral->GetModuleData();
		flockData.push_back(data);
	}
}
