//
#include "Cobra.h"
#include "../../EntityManager.h"
#include "../../../Graphics/Particles/ParticleSystem.h"

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
}


CCobra::~CCobra()
{
	CParticleSystem::GetInstance()->RemoveEmitter(this);
}

void CCobra::Update(float dt)
{
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
		other->AddGravity(dir * (dynamic_cast<CShip*>(other)->getSpeed() * 1.1) * 2);
		//Have the other ship take damage based on our mass and speed (not necessarily our current speed/velocity)
		//We will probably rebalance this later.
		float mass = size.width * size.height / 100;
		float currspeed = velocity.ComputeLength();
		dynamic_cast<CShip*>(other)->TakeDamage(int(mass * currspeed * 2), true);
	}
	else
	{
		CCopperhead::HandleCollision(other);
	}
}