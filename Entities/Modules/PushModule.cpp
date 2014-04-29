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

		SGD::Vector vToTarget =
		{
			target->GetPosition().x - dynamic_cast<CCoral*>(GetOwner())->GetPosition().x,
			target->GetPosition().y - dynamic_cast<CCoral*>(GetOwner())->GetPosition().y
		};


		SGD::Vector offset = { 0, -GetOwner()->GetSize().height/2 };
		offset.Rotate(rotation + GetOwner()->GetRotation());
		SGD::Point pos = owner->GetPosition() + offset;
		if (vToTarget.ComputeLength() <= 600 )
		{
			CParticleSystem::GetInstance()->AddEmitterPos(17, pos);
			CreateProjectileMessage* Msg = new CreateProjectileMessage(EntityType::Push, pos, { 150, 150 }, rotation + owner->GetRotation(), damage, tier, radius);
			Msg->QueueMessage();
		}
		
		timer = 0;
	}
}