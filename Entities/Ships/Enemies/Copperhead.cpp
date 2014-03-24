//
#include "Copperhead.h"
#include "../../../SGD Wrappers/SGD_Geometry.h"
#include "../../../Message System/CreateProjectile.h"

CCopperhead::CCopperhead()
{
	damage = 25;
	laserTimer = 0;
	laserDelay = 1;
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
	//Determine rotation and dir, but NOT velocity

	if (GetTarget() != nullptr)
	{
		SGD::Vector vToTarget =
		{
			GetTarget()->GetPosition().x - this->GetPosition().x,
			GetTarget()->GetPosition().y - this->GetPosition().y,
		};

		SGD::Vector forward = { 0, -1 };
		forward.Rotate(rotation);
		float angle = forward.ComputeAngle(vToTarget);
		
		if (vToTarget.ComputeLength() <= 400 && angle >= SGD::PI / 35.0f )
		{
			CreateLaser();
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
