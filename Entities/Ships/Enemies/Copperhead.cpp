//
#include "Copperhead.h"
#include "../../../SGD Wrappers/SGD_Geometry.h"
#include "../../../Message System/CreateProjectile.h"
#include "../../../Event System/EventManager.h"
#include "../../EntityManager.h"


CCopperhead::CCopperhead()
{
	damage = 25;
	laserTimer = 0;
	laserDelay = 1;
    m_fMissileDelay = 2;
    m_fMissileTimer = 0;
    m_nMissileDamage = 75;
	expValue = 10;

	size = { 32, 32 };

	CEventManager::GetInstance().Register(dynamic_cast<Listener*>(this), EventID::position);
}


CCopperhead::~CCopperhead()
{
}

void CCopperhead::Update(float dt)
{
	if (CEntityManager::GetInstance()->GetPlayer() && CEntityManager::GetInstance()->GetPlayer()->GetTutorialPause() != -1)
		return;

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

	if (target != nullptr )
	{
		SGD::Vector vToTarget =
		{
			GetTarget()->GetPosition().x - this->GetPosition().x,
			GetTarget()->GetPosition().y - this->GetPosition().y
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

	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, size, rotation, damage,0,1.0f,this);
	msg->QueueMessage();
}


void CCopperhead::CreateMissile()
{
	if (m_fMissileTimer <= m_fMissileDelay)
		return;
	m_fMissileTimer = 0;

	SGD::Point pos1 = position;

	SGD::Vector offset = { 0.5f, 0.0f };
	offset.Rotate(rotation);
	offset *= (size.height + 4) *0.5f + 4 * 0.1f;
	pos1 += offset;

	SGD::Point pos2 = position;

	SGD::Vector offset2 = { -0.5f, 0.0f };
	offset2.Rotate(rotation);
	offset2 *= (size.height + 4) *0.5f + 4 * 0.1f;
	pos2 += offset2;

	
	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Missile, pos1, size, rotation, m_nMissileDamage, 0, 1.0f, this);
	msg->QueueMessage();
	CreateProjectileMessage* msg2 = new CreateProjectileMessage(EntityType::Missile, pos2, size, rotation, m_nMissileDamage, 0, 1.0f, this);
	msg2->QueueMessage();
}
