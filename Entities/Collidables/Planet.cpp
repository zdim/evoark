#include "Planet.h"
#include "../Ships/Ship.h"
#include "Asteroid.h"

void CPlanet::Update(float dt)
{
}

void CPlanet::HandleCollision(IEntity* other)
{
	//Is the other object a ship?
	EntityType otherType = (EntityType)other->GetType();
	SGD::Vector dir = other->GetPosition() - position;
	dir.Normalize();
	if (otherType >= EntityType::Player && otherType <= EntityType::Moccasin)
	{
		//This formula gets the direction from us to them (so away from us), then multiplies that by (their speed * 1.1) so that they can only fight the push from impact a little bit
		other->AddGravity(dir * (dynamic_cast<CShip*>(other)->getSpeed() * 1.1));
	}

	//Is other an asteroid?
	if (otherType == EntityType::Asteroid)
	{
		CAsteroid* ast = dynamic_cast<CAsteroid*>(other);
		//Get the asteroid's speed
		float speed = ast->GetVelocity().ComputeLength();
		//Make a new velocity going in a different direction with the same speed
		ast->SetVelocity(dir*speed);
	}
}
