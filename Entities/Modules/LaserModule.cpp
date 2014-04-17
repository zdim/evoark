//
#include "LaserModule.h"
#include "../../Message System/CreateProjectile.h"
#include "../Ships/Enemies/Moccasin.h"

CLaserModule::CLaserModule()
{
	damage = 20;

	m_nSprayCD = 3;
	m_fSprayTimer = m_nSprayCD;

	cooldown = 1;
	timer = cooldown;

	//For regular modules spray
	shotDelay = 0.05f;
	shotTimer = shotDelay;
	shotDuration = 5;
	shotCount = 0;
}


CLaserModule::~CLaserModule()
{

}

void CLaserModule::Update(float dt)
{
	timer += dt;
	shotTimer += dt;
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
			if (dynamic_cast<CMoccasin*>(GetOwner())->GetLevel() == 4 )
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
		if (shotTimer >= shotDelay)
		{
			float rotOff = float(rand() % int(SGD::PI/2 * 100000)) / 100000.0f;
			rotOff *= 1 + (rand()%1 * -2);
			CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, size * 1.25, GetRotation() + rotOff, damage, tier, -1.0f, owner);
			msg->QueueMessage();
			shotTimer = 0;
			shotCount++;
			if (shotCount >= shotDuration)
			{
				timer = 0;
				shotCount = 0;
			}
		}
	}
}