//
#include "LaserModule.h"
#include "../../Message System/CreateProjectile.h"
#include "../Ships/Enemies/Moccasin.h"

CLaserModule::CLaserModule()
{
	m_nSprayCD = 3;
	cooldown = 0.25;
	m_fSprayTimer = m_nSprayCD;
	timer = cooldown;
}


CLaserModule::~CLaserModule()
{
}

void CLaserModule::Update(float dt)
{
	timer += dt;

	if (GetOwner()->GetType() == (int) EntityType::Moccasin )
	m_fSprayTimer += dt;

	float test = owner->GetRotation();
	SGD::Vector rotatedOffset = posOffset;
	rotatedOffset.Rotate(owner->GetRotation());
	position = owner->GetPosition() + rotatedOffset;

	rotation = owner->GetRotation() + rotOffset;

	
}


void CLaserModule::Activate()
{
	if (GetOwner()->GetType() == (int)EntityType::Moccasin)
	{
		if (m_fSprayTimer >= m_nSprayCD)
		{
			if (dynamic_cast<CMoccasin*>(GetOwner())->GetLevel() == 3)
			{
				for (int i = 0; i < 20; i++)
				{
					CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, size * 1.25, GetRotation() * i, damage, tier, -1.0f, owner);
					msg->QueueMessage();
				}

				m_fSprayTimer = 0;
			}

		}
	}


	if (timer >= cooldown)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, size * 1.25, GetRotation(), damage, tier, -1.0f, owner);
		msg->QueueMessage();
		timer = 0;
	}
}