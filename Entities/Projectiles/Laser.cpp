#include "Laser.h"
#include "../Ships/Ship.h"
#include "../Asteroid.h"
#include "../../Message System/DestroyEntityMessage.h"
#include "../../Camera.h"

CLaser::CLaser()
{

}

CLaser::~CLaser()
{

}

void CLaser::Update(float dt)
{
	velocity += gravVec;
	gravVec = SGD::Vector{0,0};
	CEntity::Update(dt);
	if (position.IsWithinRectangle(CCamera::GetInstance()->GetBoxInWorld()))
		SelfDestruct();
}

void CLaser::HandleCollision(IEntity* other)
{
	EntityType otherType = (EntityType)other->GetType();
	
	//Is other a ship?
	if (otherType >= EntityType::Player && otherType <= EntityType::Mamba)
	{
		CShip* ship = dynamic_cast<CShip*>(other);
		ship->TakeDamage(damage);

		//Throw a message to destroy this
		SelfDestruct();
	}

	//Is other an asteroid?
	if (otherType == EntityType::Asteroid)
	{
		CAsteroid* ast = dynamic_cast<CAsteroid*>(other);
		ast->TakeDamage(damage);
	}
}
