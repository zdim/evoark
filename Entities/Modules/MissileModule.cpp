//
#include "MissileModule.h"
#include "../../Message System/CreateProjectile.h"

CMissileModule::CMissileModule()
{
	cooldown = 15;
	timer = cooldown;
}


CMissileModule::~CMissileModule()
{

}

void CMissileModule::Activate()
{
	if (timer >= cooldown)
	{
		CreateProjectileMessage* Msg = new CreateProjectileMessage(EntityType::Missile,position,size,rotation,damage,tier);
		Msg->QueueMessage();
		timer = 0;
	}
}
