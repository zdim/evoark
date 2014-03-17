
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
		members[i]->SetPosition(destinations[i]);
	}
	CalculateDestinations();
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
			SGD::Vector offset = SGD::Vector
				{shipSize * 2.0f * (cosf(i/members.size() * 2.0f * SGD::PI)),
				shipSize * 2.0f * (sinf(i/members.size() * 2.0f * SGD::PI))};
		}
	}
}

void CLeader::Update(float dt)
{
	//AI not in this user story. Just need a stub to build
}