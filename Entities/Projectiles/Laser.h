#pragma once
#include "Projectile.h"
#include "../../SGD Wrappers/SGD_Handle.h"

class CLaser : public CProjectile
{
protected:
	int damage = 10;
	SGD::HAudio hitSound = SGD::INVALID_HANDLE;
public:
	CLaser();
	~CLaser();

	int GetType() { return (int)EntityType::Laser; }
	void Update(float dt) override;
	int GetDamage() {return damage;}
	void SetDamage(int newDam) {damage = newDam;}

	SGD::HAudio SetSound() {return hitSound;}
	void SetSound(SGD::HAudio newSound) {hitSound = newSound;}

	void HandleCollision(IEntity* other) override;
};