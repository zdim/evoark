#include "Asteroid.h"
#include "Ships\Ship.h"

void CAsteroid::TakeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		//throw destroy message
	}
}

void CAsteroid::Update(float dt)
{
	velocity += gravVec;
	gravVec = SGD::Vector{0,0};
	CEntity::Update(dt);
}

void CAsteroid::HandleCollision(IEntity* other)
{
	EntityType otherType = (EntityType)other->GetType();

	//Is other a ship?
	if (otherType >= EntityType::Player && otherType <= EntityType::Moccasin)
	{
		CShip* ship = dynamic_cast<CShip*>(other);
		//Have them take damage based on our size and velocity
		float mass = size.width * size.height;
		float speed = velocity.ComputeLength();
		ship->TakeDamage(int(mass * speed));

		//Have them recieve a force based on our directions and their max speed
		SGD::Vector dir = ship->GetPosition() - position;
		dir.Normalize();
		ship->AddGravity(dir * ship->getSpeed() * 0.5f);
	}

	//Is the other an asteroid?
	if (otherType == EntityType::Asteroid)
	{
		CAsteroid* ast = dynamic_cast<CAsteroid*>(other);

		//Have it take damage based on our mass and velocity
		float mass = size.width * size.height;
		float speed = velocity.ComputeLength();
		ast->TakeDamage(int(mass*speed));

		//Apply a force based on our directions and their current speed
		SGD::Vector dir = ast->GetPosition() - position;
		dir.Normalize();
		ast->AddGravity(dir * ast->GetSpeed());
	}
}