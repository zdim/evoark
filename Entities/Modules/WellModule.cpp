//
#include "WellModule.h"
#include "../../Message System/CreateProjectile.h"
#include "../../Entities/Ships/Enemies/Coral.h"
#include "../../Graphics/Particles/ParticleSystem.h"

CWellModule::CWellModule()
{
	cooldown = 100;
	timer = cooldown;
	damage = 75;
}


CWellModule::~CWellModule()
{
}

void CWellModule::Activate()
{
	if (timer >= cooldown)
	{

		SGD::Vector vToTarget =
		{
			target->GetPosition().x - dynamic_cast<CCoral*>(GetOwner())->GetPosition().x,
			target->GetPosition().y - dynamic_cast<CCoral*>(GetOwner())->GetPosition().y
		};


		SGD::Point pos = dynamic_cast<CCoral*>(GetOwner())->GetTarget()->GetPosition();
		pos.x += 25;
		pos.y += 25;

		if (vToTarget.ComputeLength() <= 600)
		{
			CParticleSystem::GetInstance()->AddEmitterPos(18, target->GetPosition());
			CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, target->GetPosition(), size, rotation, damage, tier, radius);
			msg->QueueMessage();
			timer = 0;
		}
		
	}
}
