//
#include "Mamba.h"
#include "../../EntityManager.h"

CMamba::CMamba()
{
	damage = 35;
	maxHull = 400;
	hull = maxHull;
	size = { 52, 80 };
	imageSize = { 64, 128 };
}


CMamba::~CMamba()
{
}


void CMamba::Update(float dt)
{
	if (CEntityManager::GetInstance()->GetPlayer() && CEntityManager::GetInstance()->GetPlayer()->GetTutorialPause() != -1)
		return;

	SGD::Vector dir = CCopperhead::AI(dt);
	CEnemy::Update(dt);
	CEntity::Update(dt);


}



