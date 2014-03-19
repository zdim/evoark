//
#include "Missile.h"


CMissile::CMissile()
{
}


CMissile::~CMissile()
{
}

void CMissile::HandleCollision(IEntity* other)
{
	EntityType otherType = (EntityType)other->GetType();

	//Is other a ship?
	if (otherType >= EntityType::Player && otherType <= EntityType::Mamba)
	{
		CShip* ship = dynamic_cast<CShip*>(other);
		ship->TakeDamage(damage);

	}
}
