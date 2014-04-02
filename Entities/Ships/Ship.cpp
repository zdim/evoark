//
#include "Ship.h"
#include <algorithm>
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../Graphics/Particles/ParticleSystem.h"

CShip::CShip()
{
	maxHull = 100;
	hull = maxHull;

}


CShip::~CShip()
{
}

void CShip::TakeDamage(int damage, bool collision)
{
	//if (shield > 0)
	//{
	//	shield -= damage;
	//	damage -= shield;
	//}
	//
	//if (damage <= 0)
	//{
	//	return;
	//}
	if (collision)
		damage *= COLLISION_MODIFIER;
	hull -= damage;
	if (hull <= 0)
	{
	
		SelfDestruct();
	}
}




void CShip::HandleCollision(IEntity* other)
{
	//Is the other object a ship?
	EntityType otherType = (EntityType)other->GetType();
	if (otherType >= EntityType::Player && otherType <= EntityType::Moccasin)
	{
		//This formula gets the direction from us to them (so away from us), then multiplies that by (their speed * 1.1) so that they can only fight the push from impact a little bit
		SGD::Vector dir = other->GetPosition() - position;
		dir.Normalize();
		other->AddGravity( dir * (dynamic_cast<CShip*>(other)->getSpeed() * 1.1));

		//Have the other ship take damage based on our mass and speed (not necessarily our current speed/velocity)
		//We will probably rebalance this later.
		float mass = size.width * size.height/100;
		dynamic_cast<CShip*>(other)->TakeDamage(int(mass*speed), true);
	}
	if (otherType == EntityType::Barrier)
	{
		SGD::Rectangle myRect = GetRect();
		SGD::Rectangle itsRect = other->GetRect();

		if (myRect.left < itsRect.right && myRect.right > itsRect.right)
		{
			position.x = itsRect.right + size.width/2;
		}

		if (myRect.right > itsRect.left && myRect.left < itsRect.left)
		{
			position.x = itsRect.left - size.width/2;
		}

		if (myRect.top < itsRect.bottom && myRect.bottom > itsRect.bottom)
		{
			position.y = itsRect.bottom + size.width/2;
		}

		if (myRect.bottom > itsRect.top && myRect.top < itsRect.top)
		{
			position.y = itsRect.top - size.width/2;
		}
	}
	if (otherType == EntityType::Planet)
	{
		float radius = (other->GetSize().width + size.width)/2.0f;
		SGD::Vector dir = position - other->GetPosition();
		dir.Normalize();
		SGD::Vector offset = dir * radius;
		position = other->GetPosition() + offset;
	}
}


void CShip::AddGravity(SGD::Vector grav)
{
	gravVec = grav;
}