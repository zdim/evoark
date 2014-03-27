//
#include "Cobra.h"


CCobra::CCobra()
{
	warpTimer = 0;
	warpDelay = 4;
	warpDuration = 1;
	warpSpeed = 45;
}


CCobra::~CCobra()
{
}

void CCobra::Update(float dt)
{
	warpTimer += dt; 
	SGD::Vector dir = CCopperhead::AI(dt);

	Warp();

	if (warpTimer <= warpDuration)
	{
		velocity = dir * (speed + warpSpeed);
	}
	else
		velocity = dir * speed; 

	CEnemy::Update(dt);
	CEntity::Update(dt);
}

void CCobra::Warp()
{
	if (warpTimer > warpDelay)
		warpTimer = 0;
}

void CCobra::AddGrav(SGD::Vector grav)
{
	if (warpTimer >= warpDuration)
		gravVec += grav;
}
