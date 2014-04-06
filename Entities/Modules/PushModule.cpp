//
#include "PushModule.h"
#include "../../Message System/CreateProjectile.h"

CPushModule::CPushModule()
{
	cooldown = 5;
	timer = cooldown;
}


CPushModule::~CPushModule()
{
}

void CPushModule::Activate()
{
	if (timer >= cooldown)
	{
		CreateProjectileMessage* Msg = new CreateProjectileMessage(EntityType::Push, position,size,rotation,damage,tier,radius);
		Msg->QueueMessage();
		timer = 0;
	}
}