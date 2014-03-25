
#include "Leader.h"
#include <algorithm>

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
		members[i] = flock[i];
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
			float size = members.size();
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