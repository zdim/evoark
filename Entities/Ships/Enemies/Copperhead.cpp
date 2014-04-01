//
#include "Copperhead.h"
#include "../../../SGD Wrappers/SGD_Geometry.h"
#include "../../../Message System/CreateProjectile.h"



CCopperhead::CCopperhead()
{
	damage = 25;
	laserTimer = 0;
	laserDelay = 1;
    m_fMissileDelay = 2;
    m_fMissileTimer = 0;
    m_nMissileDamage = 75;
	expValue = 10;
}


CCopperhead::~CCopperhead()
{
}

void CCopperhead::Update(float dt)
{
	AI(dt);
	//Rotation
	CEnemy::Update(dt);
	//Movement
	CEntity::Update(dt);
}

SGD::Vector CCopperhead::AI(float dt)
{
	laserTimer += dt;
	m_fMissileTimer += dt;
	//Determine rotation and dir, but NOT velocity

	if (target)
	{
		SGD::Vector vToTarget =
		{
			GetTarget()->GetPosition().x - this->GetPosition().x,
			GetTarget()->GetPosition().y - this->GetPosition().y,
		};

		SGD::Vector direction = { 0, -1 };
		direction.Rotate(rotation);
		float angle = direction.ComputeAngle(vToTarget);
		
		if (vToTarget.ComputeLength() <= 400 && angle < SGD::PI / 4.0f )
		{
			CreateLaser();
			
		}
		if (vToTarget.ComputeLength() <= 800 && angle < SGD::PI / 4.0f )
		{	
			if (GetType() == (int)EntityType::Mamba)
			{
				CreateMissile();
			}
			if (GetType() == 8)
			{
			
			}
		}
		

	}



	return SGD::Vector{ 0, 0 };
}

//Does copperhead not have shield? I though all alien ships had shield, but the visio file and the documentation both list only hull for small ships.
//void CCopperhead::TakeDamage(int damage)
//{
//	if (shield > 0)
//	{
//		shield -= damage;
//		damage -= shield;
//	}
//
//	if (damage <= 0)
//	{
//		return;
//	}
//
//	hull -= damage;
//	if (hull <= 0)
//	{
//		//Send gameOver message
//	}
//}


void CCopperhead::CreateLaser()
{
	if (laserTimer <= laserDelay)
		return;
	laserTimer = 0;

	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, size, rotation, damage);
	msg->QueueMessage();
}


void CCopperhead::CreateMissile()
{
	if (m_fMissileTimer <= m_fMissileDelay)
		return;
	m_fMissileTimer = 0;

	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Missile, position, size, rotation, m_nMissileDamage);
	msg->QueueMessage();
}
