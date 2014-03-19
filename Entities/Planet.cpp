#include "Planet.h"
#include "Ships/Ship.h"

void CPlanet::Update(float dt)
{

}

void CPlanet::HandleCollision(IEntity* other)
{
	EntityType otherType = (EntityType)other->GetType();
	if (otherType >= EntityType::Player && otherType <= EntityType::Moccasin)
	{
		CShip* ship = dynamic_cast<CShip*>(other);
		SGD::Vector dir = ship->GetPosition() - position;
		dir.Normalize();
		ship->AddGravity(dir * ship->getSpeed() * 3.0f);
	}
}
