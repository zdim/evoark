//
#include "Moccasin.h"
#include "../../../Message System/BossKilledMessage.h"

CMoccasin::CMoccasin()
{
}


CMoccasin::~CMoccasin()
{
}

void CMoccasin::SelfDestruct()
{
	CCoral::SelfDestruct();
	BossKilledMessage* msg = new BossKilledMessage;
	msg->QueueMessage();
}

void CMoccasin::AddModule()
{
	if (modules.size() >= (unsigned int)EntityType::WarpModule - (unsigned int)EntityType::BaseModule)
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
	switch (newModType)
	{
	case EntityType::BaseModule:
		modules.push_back(new CModule);
		break;
	case EntityType::EngineModule:
		modules.push_back(new CEngine);
		break;
	case EntityType::ShieldModule:
		modules.push_back(new CShieldModule);
		break;
	case EntityType::LaserModule:
		modules.push_back(new CLaserModule);
		break;
	case EntityType::MissileModule:
		modules.push_back(new CMissileModule);
		break;
	case EntityType::WellModule:
		modules.push_back(new CWellModule);
		break;
	case EntityType::PushModule:
		modules.push_back(new CPushModule);
		break;
	case EntityType::WarpModule:
		modules.push_back(new CWarpModule);
		break;
	}
}