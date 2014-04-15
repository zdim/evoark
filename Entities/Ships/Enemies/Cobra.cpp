//
#include "Cobra.h"
#include "../../EntityManager.h"
#include "../../../Graphics/Particles/ParticleSystem.h"

CCobra::CCobra()
{
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
