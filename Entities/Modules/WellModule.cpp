//
#include "WellModule.h"
#include "../../Message System/CreateProjectile.h"
#include "../../Entities/Ships/Enemies/Coral.h"
#include "../../Graphics/Particles/ParticleSystem.h"
#include <algorithm>

CWellModule::CWellModule()
{
	cooldown = 10;
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
		//pos.x += 25;
		//pos.y += 25;

		float offDist = radius + std::max(owner->GetTarget()->GetSize().width, owner->GetTarget()->GetSize().height)/2;
		offDist += owner->getSpeed();

		float randAngle = 0;
		for (unsigned int i = 1; i <= 4; i++)
		{
			randAngle += SGD::PI/i * float(rand()%2);
		}

		SGD::Vector offset = {0,-1};
		offset.Rotate(randAngle);
		offset *= offDist;

		pos += offset;

		if (vToTarget.ComputeLength() <= 600)
		{
			CParticleSystem::GetInstance()->AddEmitterPos(18, pos);
			CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, pos, size, rotation, damage, tier, radius);
			msg->QueueMessage();
			timer = 0;
		}
		
	}
}
