//
#include "Cobra.h"


CCobra::CCobra()
{
}


CCobra::~CCobra()
{
}

void CCobra::Update(float dt)
{
	SGD::Vector dir = CCopperhead::AI(dt);
	CEnemy::Update(dt);
	CEntity::Update(dt);
}

void CCobra::AddGrav(SGD::Vector grav)
{
	if (warpTimer >= warpDuration)
		gravVec += grav;
}
