//
#include "Cobra.h"
#include "../../EntityManager.h"
#include "../../../Graphics/Particles/ParticleSystem.h"
#include "../../../SGD Wrappers/SGD_GraphicsManager.h"

CCobra::CCobra()
{
	damage = 35;
	maxHull = 350;
	hull = maxHull;
	warpDelay = 4;
	warpTimer = warpDelay;
	warpDuration = 1;
	warpSpeed = 300;
	expValue = 20;
	size = { 32, 32 };


	m_Engine = new CEmitter(
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetParticleData(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetEmitterSize(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetShape(),
		position,
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetNumParticles(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetSpawnRate(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetSpawnTimeFromLastSpawn(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetEmitType(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetEmitTime()
		);


	m_Engine->Initialize();
	m_Engine->SetOwner(this);


	m_Engine2 = new CEmitter(
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetParticleData(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetEmitterSize(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetShape(),
		position,
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetNumParticles(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetSpawnRate(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetSpawnTimeFromLastSpawn(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetEmitType(),
		CParticleSystem::GetInstance()->GetParticleEffect(28)->GetEmitTime()
		);


	m_Engine2->Initialize();
	m_Engine2->SetOwner(this);
}


CCobra::~CCobra()
{
	CParticleSystem::GetInstance()->RemoveEmitter(this);

	m_Engine->Release();
	delete m_Engine;

	m_Engine2->Release();
	delete m_Engine2;
}

void CCobra::Update(float dt)
{
	SGD::Vector rotatedOffset = { 7, 17 };
	rotatedOffset.Rotate(rotation);
	enginePos = position + rotatedOffset;

	m_Engine->SetEmitterPosition(enginePos);

	m_Engine->Update(dt);

	SGD::Vector rotatedOffset2 = { -7, 17 };
	rotatedOffset2.Rotate(rotation);
	enginePos2 = position + rotatedOffset2;

	m_Engine2->SetEmitterPosition(enginePos2);

	m_Engine2->Update(dt);

	if (CEntityManager::GetInstance()->GetPlayer() && CEntityManager::GetInstance()->GetPlayer()->GetTutorialPause() != -1)
		return;

	warpTimer += dt;
	SGD::Vector dir = CCopperhead::AI(dt);



	if (target != nullptr)
		Warp();

	CEnemy::Update(dt);

	if (warpTimer <= warpDuration)
	{
		SGD::Vector forward = { 0, -1 };
		forward.Rotate(rotation);
		velocity += forward * warpSpeed;
	}




	CEntity::Update(dt);
}

void CCobra::Warp()
{

	if (warpTimer > warpDelay)
	{
		CParticleSystem::GetInstance()->AddEmitter(16, this);
		warpTimer = 0;
	}
}


void CCobra::Render()
{
	m_Engine->Render();
	m_Engine2->Render();


	SGD::Rectangle rShipRegion = SGD::Rectangle(SGD::Point{ 0, 0 }, size);

	SGD::Point renderPoint = offsetToCamera();
	SGD::Color col = {};
	if (damaged > 0)
	{
		col = { 155, 155, 155 };
	}

	SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint, rShipRegion, rotation, size / 2, col);
}






void CCobra::AddGrav(SGD::Vector grav)
{
	if (warpTimer >= warpDuration)
		gravVec += grav;
}

void CCobra::TakeDamage(int damage, bool collision)
{
	if (collision && warpTimer <= warpDuration)
		return;
	CCopperhead::TakeDamage(damage, collision);
}

void CCobra::HandleCollision(IEntity* other)
{
	EntityType otherType = (EntityType)other->GetType();

	if (otherType >= EntityType::Player && otherType <= EntityType::Coordinator)
	{

		//This formula gets the direction from us to them (so away from us), then multiplies that by (their speed * 1.1) so that they can only fight the push from impact a little bit
		SGD::Vector dir = other->GetPosition() - position;
		dir.Normalize();
		other->AddGravity(dir * (dynamic_cast<CShip*>(other)->getSpeed() * 1.1f));
		//Have the other ship take damage based on our mass and speed (not necessarily our current speed/velocity)
		//We will probably rebalance this later.
		float mass = size.width * size.height / 100;
		float currspeed = velocity.ComputeLength();
		dynamic_cast<CShip*>(other)->TakeDamage(int(mass * currspeed * 5), true);
	}
	else
	{
		CCopperhead::HandleCollision(other);
	}
}