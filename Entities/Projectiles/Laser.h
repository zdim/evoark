#pragma once
#include "Projectile.h"
#include "../../SGD Wrappers/SGD_Handle.h"

class CLaser : public CProjectile
{
protected:
	int damage = 10;
	unsigned int tier = 0;
	SGD::HAudio hitSound = SGD::INVALID_HANDLE;
public:
	CLaser();
	~CLaser();

	void Clamp() override;
	int GetType() { return (int)EntityType::Laser; }
	void Update(float dt) override;
	void Render() override;
	int GetDamage() {return damage;}
	void SetDamage(int newDam) {damage = newDam;}
	void SetTier(unsigned int _tier) { tier = _tier; }

	void AddGravity(SGD::Vector grav) override;

	SGD::HAudio SetSound() {return hitSound;}
	void SetSound(SGD::HAudio newSound) {hitSound = newSound;}

	void HandleCollision(IEntity* other) override;
};