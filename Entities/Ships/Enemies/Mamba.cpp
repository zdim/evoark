//
#include "Mamba.h"


CMamba::CMamba()
{
}


CMamba::~CMamba()
{
}


void CMamba::Update(float dt)
{
	SGD::Vector dir = CCopperhead::AI(dt);
	CEnemy::Update(dt);
	CEntity::Update(dt);


}



