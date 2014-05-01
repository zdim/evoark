//
#include "Ship.h"
#include <algorithm>
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../Graphics/Particles/ParticleSystem.h"
#include "../../SoundBox.h"
#include "../../Camera.h"
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
		damage = int((float)damage * COLLISION_MODIFIER);

	if (offsetToCamera().IsWithinRectangle(CCamera::GetInstance()->GetBoxInWorld()))
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::enemyShieldDamage, false);

	hull -= damage;
	if (hull <= 0)
	{
		if (this->GetType() == (int)EntityType::Human )
		{
			CParticleSystem::GetInstance()->AddEmitter(20, this);
			CParticleSystem::GetInstance()->AddEmitter(21, this);
			CParticleSystem::GetInstance()->AddEmitter(22, this);
			CParticleSystem::GetInstance()->RemoveEmitter(this);
		}

		SelfDestruct();
	}
}




void CShip::HandleCollision(IEntity* other)
{
	//Is the other object a ship?
	EntityType otherType = (EntityType)other->GetType();
	
	if (otherType >= EntityType::Player && otherType <= EntityType::Coordinator)
	{
		
		//This formula gets the direction from us to them (so away from us), then multiplies that by (their speed * 1.1) so that they can only fight the push from impact a little bit
		SGD::Vector dir = other->GetPosition() - position;
		dir.Normalize();
		other->AddGravity( dir * (dynamic_cast<CShip*>(other)->getSpeed() * 1.1f));
		//Have the other ship take damage based on our mass and speed (not necessarily our current speed/velocity)
		//We will probably rebalance this later.
		float mass = size.width * size.height/100;
		float currspeed = velocity.ComputeLength();
		dynamic_cast<CShip*>(other)->TakeDamage(int(mass*currspeed), true);
	}
	if (otherType == EntityType::Barrier)
	{
		SGD::Rectangle myRect = GetRect();
		SGD::Rectangle itsRect = other->GetRect();

		if (myRect.left < itsRect.right && myRect.right > itsRect.right
			&& myRect.top < itsRect.bottom && myRect.bottom > itsRect.top)
		{
			float width = itsRect.right - myRect.left;
			if (myRect.top < itsRect.bottom && myRect.bottom > itsRect.bottom
				&& myRect.left < itsRect.right && myRect.right > itsRect.left)
			{
				float height = itsRect.bottom - myRect.top;
				if(height < width)
					position.y += height;
				else
					position.x += width;
			}
			else if (myRect.bottom > itsRect.top && myRect.top < itsRect.top
				&& myRect.left < itsRect.right && myRect.right > itsRect.left)
			{
				float height = myRect.bottom - itsRect.top;
				if (height < width)
					position.y -= height;
				else
					position.x += width;
			}
			else
				position.x += width;
		}
		else if (myRect.right > itsRect.left && myRect.left < itsRect.left
			&& myRect.top < itsRect.bottom && myRect.bottom > itsRect.top)
		{
			float width = myRect.right - itsRect.left;
			if (myRect.top < itsRect.bottom && myRect.bottom > itsRect.bottom
				&& myRect.left < itsRect.right && myRect.right > itsRect.left)
			{
				float height = itsRect.bottom - myRect.top;
				if (height < width)
					position.y += height;
				else
					position.x -= width;
			}
			else if (myRect.bottom > itsRect.top && myRect.top < itsRect.top
				&& myRect.left < itsRect.right && myRect.right > itsRect.left)
			{
				float height = myRect.bottom - itsRect.top;
				if (height < width)
					position.y -= height;
				else
					position.x -= width;
			}
			else
				position.x -= width;
		}
		if (myRect.top < itsRect.bottom && myRect.bottom > itsRect.bottom
			&& myRect.left < itsRect.right && myRect.right > itsRect.left)
		{
			float height = itsRect.bottom - myRect.top;
			position.y += height;
		}
		else if (myRect.bottom > itsRect.top && myRect.top < itsRect.top
			&& myRect.left < itsRect.right && myRect.right > itsRect.left)
		{
			float height = myRect.bottom - itsRect.top;
				position.y -= height;
		}
	}
	if (otherType == EntityType::Planet)
	{
		float radius = (other->GetSize().width + size.width)/2.0f;
		SGD::Vector dir = position - other->GetPosition();
		dir.Normalize();
		SGD::Vector offset = dir * radius;
		position = other->GetPosition() + offset;
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::enemyHullDamage,false);
	}
}


void CShip::AddGravity(SGD::Vector grav)
{
	gravVec = grav;
}