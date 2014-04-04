//
#include "Moccasin.h"
#include "../../../Message System/BossKilledMessage.h"

CMoccasin::CMoccasin()
{
	expValue = 100;
	modulePositions.push_back({ -40, -40 });
	modulePositions.push_back({ 40, -40 });
	modulePositions.push_back({ 40, 40 });

}


CMoccasin::~CMoccasin()
{
}


void CMoccasin::Init(int l)
{
	for (int i = 0; i < l; i++)
		AddModule();

	switch (l)
	{
	case 1:
		m_nLevel = 1;
		hull = 2500;

		break;
	}
}



void CMoccasin::SelfDestruct()
{
	CCoral::SelfDestruct();
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