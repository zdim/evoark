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

		SGD::Vector vToTarget =
		{
			dynamic_cast<CCoral*>(GetOwner())->GetTarget()->GetPosition().x - dynamic_cast<CCoral*>(GetOwner())->GetPosition().x,
			dynamic_cast<CCoral*>(GetOwner())->GetTarget()->GetPosition().y - dynamic_cast<CCoral*>(GetOwner())->GetPosition().y
		};


		SGD::Point pos = dynamic_cast<CCoral*>(GetOwner())->GetTarget()->GetPosition();
		pos.x -= 25;
		pos.y += 25;
		if (vToTarget.ComputeLength() <= 600 )
		{
			CreateProjectileMessage* Msg = new CreateProjectileMessage(EntityType::Push, pos, { 150, 150 }, rotation, damage, tier, radius);
			Msg->QueueMessage();
		}
		
		timer = 0;
	}
}