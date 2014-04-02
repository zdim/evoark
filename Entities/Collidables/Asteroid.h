#pragma once
#include "../Entity.h"

class CAsteroid : public CEntity
{
	int health = 500;
	float speed = 100;
public:

	bool IsCircle() override {return true;}
	int GetType() {return (int)EntityType::Asteroid;}
	void Clamp() override;
	int GetHealth() {return health;}
	void SetHealth(int newHP) {health = newHP;}
	void SetVelocity(SGD::Vector newVel) override { CEntity::SetVelocity(newVel); speed = newVel.ComputeLength(); }
	float GetSpeed() { return velocity.ComputeLength(); }

	void TakeDamage(int damage);
	void HandleCollision(IEntity* other) override;
	virtual void AddGravity(SGD::Vector grav) override;

	void Update(float dt) override;
};