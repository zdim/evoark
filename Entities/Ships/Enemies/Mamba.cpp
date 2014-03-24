//
#include "Mamba.h"
#include "../../../Message System/CreateProjectile.h"

CMamba::CMamba()
{
}


CMamba::~CMamba()
{
}


void CMamba::Update(float dt)
{
	SGD::Vector dir = CCopperhead::AI(dt);
	CEnemy::Update(dt);
	CEntity::Update(dt);

	m_fMissileTimer += dt;
	//Determine rotation and dir, but NOT velocity

	if (GetTarget() != nullptr)
	{
		SGD::Vector vToTarget =
		{
			GetTarget()->GetPosition().x - this->GetPosition().x,
			GetTarget()->GetPosition().y - this->GetPosition().y,
		};


		if (vToTarget.ComputeLength() <= 800)
		{
			CreateMissile();
		}

	}
}

void CMamba::AddGrav(SGD::Vector grav)
{
	
}



void CMamba::CreateMissile()
{
	if (m_fMissileTimer <= m_fMissileDelay)
		return;
	m_fMissileTimer = 0;
	//TODO: Send CreateMissile message

	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Missile, position, size, rotation, damage);
	msg->QueueMessage();
}
