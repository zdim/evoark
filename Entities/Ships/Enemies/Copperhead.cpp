//
#include "Copperhead.h"
#include "../../../SGD Wrappers/SGD_Geometry.h"
#include "../../../Message System/CreateProjectile.h"
#include "../../../Event System/EventManager.h"
#include "../../EntityManager.h"


#include "../../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../../Graphics/Particles/ParticleSystem.h"

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

	m_Engine = new CEmitter(
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetParticleData(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetEmitterSize(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetShape(),
		position,
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetNumParticles(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetSpawnRate(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetSpawnTimeFromLastSpawn(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetEmitType(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetEmitTime()
		);


	m_Engine->Initialize();
	m_Engine->SetOwner(this);

}


CCopperhead::~CCopperhead()
{
	m_Engine->Release();
	delete m_Engine;
}

void CCopperhead::Update(float dt)
{

	SGD::Vector rotatedOffset = { 0, 9 };
	rotatedOffset.Rotate(rotation);
	enginePos = position + rotatedOffset;

	m_Engine->SetEmitterPosition(enginePos);

	m_Engine->Update(dt);

	if (CEntityManager::GetInstance()->GetPlayer() && CEntityManager::GetInstance()->GetPlayer()->GetTutorialPause() != -1)
		return;

	AI(dt);
	//Rotation
	CEnemy::Update(dt);
	//Movement
	CEntity::Update(dt);
}

void CCopperhead::Render()
{
	m_Engine->Render();
	
	SGD::Rectangle rShipRegion = SGD::Rectangle(SGD::Point{ 0, 0 }, size);

	SGD::Point renderPoint = offsetToCamera();
	SGD::Color col = {};
	if (damaged > 0)
	{
		col = { 155, 155, 155 };
	}

	SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint, rShipRegion, rotation, size / 2, col);
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
