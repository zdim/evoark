//
#include "Copperhead.h"


CCopperhead::CCopperhead()
{
}


CCopperhead::~CCopperhead()
{
}

void CCopperhead::Update(float dt)
{
	AI(dt);
	//Movement
	CEntity::Update(dt);
}

SGD::Vector CCopperhead::AI(float dt)
{
	laserTimer += dt;
	//Determine rotation and dir, but NOT velocity
	return SGD::Vector{0,0};
}