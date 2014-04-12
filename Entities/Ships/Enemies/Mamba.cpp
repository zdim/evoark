//
#include "Mamba.h"
#include "../../EntityManager.h"

CMamba::CMamba()
{
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



