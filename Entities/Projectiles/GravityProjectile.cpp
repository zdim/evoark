//
#include "GravityProjectile.h"
#include "../../Message System/DestroyEntityMessage.h"

CGravityProjectile::CGravityProjectile()
{
	timer = 0;
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
		DestroyEntityMessage* msg = new DestroyEntityMessage(this);
		msg->QueueMessage();
	}
}