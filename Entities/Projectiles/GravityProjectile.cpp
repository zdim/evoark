//
#include "GravityProjectile.h"


CGravityProjectile::CGravityProjectile()
{
}


CGravityProjectile::~CGravityProjectile()
{
}

void CGravityProjectile::Update(float dt)
{
	timer += dt;
	if (timer >= duration)
	{
		//Send destroy message
	}
}