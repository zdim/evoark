#pragma once
#include "Planet.h"

class CAsteroid : public CPlanet
{
	SGD::Vector velocity;
	int health;
public:

	int GetHealth() {return health;}
	void SetHealth(int newHP) {health = newHP;}

	float GetSpeed() { return velocity.ComputeLength(); }

	void TakeDamage(int damage);
	void HandleCollision(IEntity* other) override;

	void Update(float dt) override;
};