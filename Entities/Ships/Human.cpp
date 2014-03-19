//
#include "Human.h"


CHuman::CHuman()
{
}


CHuman::~CHuman()
{
}

void CHuman::Update(float dt)
{
	laserTimer += dt;

	//AI
	//Movement
	CEntity::Update(dt);
}