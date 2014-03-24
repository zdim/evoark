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
	//Rotation
	CEnemy::Update(dt);
	//Movement
	CEntity::Update(dt);
}

SGD::Vector CCopperhead::AI(float dt)
{
	laserTimer += dt;
	//Determine rotation and dir, but NOT velocity
	return SGD::Vector{0,0};
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