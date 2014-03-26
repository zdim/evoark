//
#include "LaserModule.h"
#include "../../Message System/CreateProjectile.h"

CLaserModule::CLaserModule()
{
	cooldown = 0.25;
}


CLaserModule::~CLaserModule()
{
}

void CLaserModule::Activate()
{
	if (timer >= cooldown)
	{
		//Send a create laser message
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, size, GetRotation(), damage);
		msg->QueueMessage();
	}
}