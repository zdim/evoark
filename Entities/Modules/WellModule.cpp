//
#include "WellModule.h"
#include "../../Message System/CreateProjectile.h"

CWellModule::CWellModule()
{
	cooldown = 5;
	timer = cooldown;
}


CWellModule::~CWellModule()
{
}

void CWellModule::Activate()
{
	if (timer >= cooldown)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, target->GetPosition(), size, rotation, damage, tier, radius);
		msg->QueueMessage();
		timer = 0;
	}
}
