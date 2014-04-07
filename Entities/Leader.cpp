
#include "Leader.h"
#include <algorithm>
#include "Ships\Enemies\Coral.h"
#include "../GameStates/GameplayState.h"
#include "EntityManager.h"
#include <vector>

std::vector<SGD::Vector> equidistantPointsInCircle(int numPoints, float radius)
{
	std::vector<SGD::Vector> points(numPoints);
	for (int i = 0; i < numPoints; i++)
	{
		float size = (float)numPoints;
		float a = i / size;
		float toCos = a * 2.0f * SGD::PI;
		float cos = cosf(toCos);
		float sin = sinf(toCos);
		points[i] = {radius * cos, radius * sin};
	}
	return points;
}

CLeader::CLeader()
{
	state = LeaderState::Return;
}

CLeader::~CLeader()
{
	SetTarget(nullptr);
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
		members[i]->SetLeader(this);
	}
	CalculateDestinations();
	Teleport();
	return true;
}

void CLeader::CalculateDestinations()
{
	float shipSize = std::max(members[0]->GetSize().width, members[0]->GetSize().height);
	if (target == nullptr)
	{
		float radius = std::max(members[0]->GetSize().width, members[0]->GetSize().height);
		std::vector<SGD::Vector> offsets = equidistantPointsInCircle(members.size(), members[0]->GetSize().height * 3);
		for (unsigned int i = 0; i < members.size(); i++)
		{
			destinations[i] = home + offsets[i];
		}

		//destinations[0] = home;
		//for (unsigned int i = 1; i < destinations.size(); i++)
		//{
		//	// sloppy, but it works for now. adjusted because it was always giving cos = 1 and sin = 0
		//	float size = (float)members.size();
		//	float a = i / size;
		//	float toCos = a * 2.0f * SGD::PI;
		//	float cos = cosf(toCos);
		//	float sin = sinf(toCos);
		//	//I changed the 2.0f in the following lines to 3.0f because the ships were WAY too close together.
		//	//We may even want to change it to 4 when we're spawning them in a larger environment.
		//	SGD::Vector offset = SGD::Vector
		//		{shipSize * 3.0f * cos,
		//		shipSize * 3.0f * sin};

		//	destinations[i] = { home.x + offset.x, home.y + offset.y };
		//}
	}
	else
	{
		float radius = std::max(members[0]->GetSize().width, members[0]->GetSize().height);
		std::vector<SGD::Vector> offsets = equidistantPointsInCircle(members.size(), members[0]->GetSize().height * 3);
		for (unsigned int i = 0; i < members.size(); i++)
		{
			destinations[i] = target->GetPosition() + offsets[i];
		}
	}
}

void CLeader::SetDestinations()
{
	for (unsigned int i = 0; i < destinations.size(); i++)
	{
		members[i]->SetDestination(destinations[i]);
	}
}

void CLeader::Teleport()
{
	for (unsigned int i = 0; i < destinations.size(); i++)
	{
		members[i]->SetPosition(destinations[i]);
	}
}

bool CLeader::DestinationsOffscreen()
{
	SGD::Rectangle screen = CCamera::GetInstance()->GetBoxInWorld();
	screen.left -= members[0]->GetSize().width;
	screen.right += members[0]->GetSize().width;
	screen.top -= members[0]->GetSize().height;
	screen.bottom += members[0]->GetSize().height;
	for (unsigned int i = 0; i < destinations.size(); i++)
	{
		if (destinations[i].IsWithinRectangle(screen))
		{
			return false;
		}
	}
	return true;
}

void CLeader::Update(float dt)
{
	timer += dt;
	//AI not in this user story. Just need a stub to build
	if (target)
	{
		float distance = (members[0]->GetPosition() - target->GetPosition()).ComputeLength();
		for (unsigned int i = 1; i < members.size(); i++)
		{
			distance = std::min(distance, SGD::Vector(members[i]->GetPosition() - target->GetPosition()).ComputeLength());
		}
		if (distance > 250)
		{
			SetTarget(nullptr);
			return;
		}
		CalculateDestinations();
		SetDestinations();
	}
	else if (position != home)
	{
		if (!position.IsWithinRectangle(CCamera::GetInstance()->GetBoxInWorld()))
		{
			if (state == LeaderState::Return)
			{
				if (timer >= teleportDelay && DestinationsOffscreen())
				{
					Teleport();
				}
			}
			else
			{
				state = LeaderState::Return;
				CalculateDestinations();
				timer = 0;
			}
		}
		else
		{
			state = LeaderState::Search;
		}
	}
	position = members[0]->GetPosition();
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
	if (members.size() == 1)
	{
		entity = entity;
	}
	int i = FindInFlock(entity);
	if (i < 0)
		return;
	//members[i]->Release();
	members.erase(members.begin()+i);
	if (!members.size())
	{
		CEntityManager::GetInstance()->DestroyLeader(this);
	}
	else
	{
		destinations.resize(members.size());
	}
}

void CLeader::SetTarget(CShip* newTarget)
{
	if (target == newTarget)
		return;

	if ((unsigned int)target == 0xfeeefee)
	{
		target = nullptr;
	}
	if (target)
		target->Release();
	
	target = newTarget;

	if (target)
		target->AddRef();

	for (unsigned int i = 0; i < members.size(); i++)
	{
		members[i]->SetTarget(newTarget);
	}
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
