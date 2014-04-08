//
#include "PushModule.h"
#include "../../Message System/CreateProjectile.h"
#include "../../Entities/Ships/Enemies/Moccasin.h"

CPushModule::CPushModule()
{
	cooldown = 5;
	timer = cooldown;
	damage = 45;
}


CPushModule::~CPushModule()
{
}

void CPushModule::Activate()
{
	if (timer >= cooldown) 
	{
		SGD::Point pos = dynamic_cast<CMoccasin*>(GetOwner())->GetTarget()->GetPosition();
		pos.x -= 25;
		pos.y += 25;
		CreateProjectileMessage* Msg = new CreateProjectileMessage(EntityType::Push,pos , { 150, 150 }, rotation, damage, tier, radius);
		Msg->QueueMessage();
		timer = 0;
	}
}