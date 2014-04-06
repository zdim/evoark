//
#include "MissileModule.h"
#include "../../Message System/CreateProjectile.h"
#include "../Ships/Enemies/Coral.h"

CMissileModule::CMissileModule()
{
	cooldown = 5;
	timer = cooldown;
}


CMissileModule::~CMissileModule()
{

}

void CMissileModule::Activate()
{
	if (timer >= cooldown)
	{
		CreateProjectileMessage* Msg = new CreateProjectileMessage(EntityType::Missile,position,size * 1.25,rotation,damage,tier,-1.0f,owner);
		Msg->QueueMessage();
		timer = 0;
	}
}
