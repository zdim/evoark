#pragma once
#include "../Entity.h"

class CAsteroid : public CEntity
{
	int health = 500;
public:

	bool IsCircle() override {return true;}
	int GetType() {return (int)EntityType::Asteroid;}
	void Clamp() override;
	int GetHealth() {return health;}
	void SetHealth(int newHP) {health = newHP;}

	float GetSpeed() { return velocity.ComputeLength(); }

	void TakeDamage(int damage);
	void HandleCollision(IEntity* other) override;
	virtual void AddGravity(SGD::Vector grav) override;

	//void Update(float dt) override;
};