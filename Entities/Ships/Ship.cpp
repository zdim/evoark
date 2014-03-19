//
#include "Ship.h"
#include <algorithm>
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

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

	hull -= damage;
	if (hull <= 0)
	{
		//Destroy thing
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
		other->AddGravity( dir * (dynamic_cast<CShip*>(other)->getSpeed() * 0.5f)); //1.025

		//Have the other ship take damage based on our mass and speed (not necessarily our current speed/velocity)
		//We will probably rebalance this later.
		float mass = size.width * size.height/100;
		dynamic_cast<CShip*>(other)->TakeDamage(mass*speed, true);
	}
}

void CShip::Render()
{
	SGD::Color color = {};
	if (hull < maxHull)
		color = SGD::Color{ 255, 0, 0 };
	float scale = std::max(size.width / imageSize.width, size.height / imageSize.height);
	SGD::GraphicsManager::GetInstance()->DrawTexture(image, position - size / 2, rotation, imageSize / 2, color, { scale, scale });
}

void CShip::AddGravity(SGD::Vector grav)
{
	gravVec += grav;
}