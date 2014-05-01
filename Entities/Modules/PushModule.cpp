//
#include "PushModule.h"
#include "../../Message System/CreateProjectile.h"
#include "../../Entities/Ships/Enemies/Coral.h"
#include "../../Graphics/Particles/ParticleSystem.h"

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

		SGD::Vector vToTarget = target->GetPosition() - owner->GetPosition();


		SGD::Vector offset = { 0, owner->GetSize().height * -0.5f };
		offset.Rotate(rotation);
		SGD::Point pos = owner->GetPosition() + offset;
		if (vToTarget.ComputeLength() <= 600 )
		{
			CParticleSystem::GetInstance()->AddEmitterPos(17, pos);
			CreateProjectileMessage* Msg = new CreateProjectileMessage(EntityType::Push, pos, { 150, 150 }, rotation, damage, tier, radius);
			Msg->QueueMessage();
		}
		
		timer = 0;
	}
}