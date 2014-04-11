//
#include "Moccasin.h"
#include "../../../Message System/BossKilledMessage.h"
#include "../../../Message System/CreateEntityMessage.h"
#include "../../EntityManager.h"
#include "../../Collidables/ModuleShield.h"

CMoccasin::CMoccasin()
{
	expValue = 100;
	modulePositions.push_back({ -40, -40 });
	modulePositions.push_back({ 40, -40 });
	modulePositions.push_back({ 40, 40 });
	m_fTimer = 0;
	m_fAsteroidCD = 8;
	m_fShipCD = 5;
	leader = nullptr;
	m_bStationsUP = false;
	m_nNumberOfShips = 1;
	speed = 25;
}


CMoccasin::~CMoccasin()
{
}


void CMoccasin::Init(int l)
{
	for (int i = 0; i < 3; i++)
		AddModule();


	switch (l)
	{
	case 0:
		m_nLevel = 0;
		break;
	case 1:
		m_nLevel = 1;
		break;
	case 2:
		m_nLevel = 2;	
		break;
	case 3:
		m_nLevel = 3;
		break;
	case 4:
		m_nLevel = 4;
		break;
	}
	
}


void CMoccasin::Update(float dt)
{
	m_fTimer += dt;

	if (m_nLevel == 1)
	{
		if (m_fTimer >= m_fAsteroidCD && target != nullptr)
		{
			CreateEntityMessage* msg = new CreateEntityMessage(this);
			msg->QueueMessage();
			m_fTimer = 0;
		}

	}

	if (m_nLevel == 2 && m_bStationsUP == false )
	{
		CreateEntityMessage* msg = new CreateEntityMessage(this);
		msg->QueueMessage();
		m_bStationsUP = true;
	}

	
	if (m_nLevel == 3 || m_nLevel == 4 )
	{
		if (m_fTimer >= m_fShipCD && target != nullptr)
		{
			CreateEntityMessage* msg = new CreateEntityMessage(this);
			msg->QueueMessage();
			m_nNumberOfShips += (rand() % 2 + 1);
			m_fTimer = 0;
		}	
	}

	if (target)
	{
		SGD::Vector dir = target->GetPosition() - position;
		if (dir.ComputeLength() > 500 )
		{
			dir.Normalize();
			velocity = dir * speed;
		}
		else velocity = {0,0};
	}
	else
	{
		velocity = { 0, 0 };
	}

	position += (velocity)* dt;
	
	CCoral::Update(dt);
}


void CMoccasin::SelfDestruct()
{
	CCoral::SelfDestruct();
	CCustomEvent* e = new CCustomEvent(EventID::bossdead, nullptr, this);
	e->Queue();
	BossKilledMessage* msg = new BossKilledMessage;
	msg->QueueMessage();

}





void CMoccasin::AddModule()
{
	if (modules.size() > (unsigned int)EntityType::WarpModule - (unsigned int)EntityType::BaseModule)
		return;

	std::vector<EntityType> available;
	for (unsigned int i = (unsigned int)EntityType::BaseModule; i <= (unsigned int)EntityType::WarpModule; i++)
	{
		unsigned int j;
		for (j = 0; j < modules.size(); j++)
		{
			if (modules[j]->GetType() == i)
				break;
		}
		if (j == modules.size())
		{
			available.push_back((EntityType)i);
		}
	}

	EntityType newModType = available[rand() % available.size()];
	CModule* newMod = nullptr;
	switch (newModType)
	{
	case EntityType::BaseModule:
		newMod = new CModule;
		break;
	case EntityType::EngineModule:
		newMod = new CEngine;
		break;
	case EntityType::ShieldModule:
		newMod = new CShieldModule;
		break;
	case EntityType::LaserModule:
		newMod = new CLaserModule;
		break;
	case EntityType::MissileModule:
		newMod = new CMissileModule;
		break;
	case EntityType::WellModule:
		newMod = new CWellModule;
		break;
	case EntityType::PushModule:
		newMod = new CPushModule;
		break;
	case EntityType::WarpModule:
		newMod = new CWarpModule;
		break;
	}

	newMod->SetOffset(modulePositions[modules.size()]);
	newMod->SetOwner(this);
	modules.push_back(newMod);
}
