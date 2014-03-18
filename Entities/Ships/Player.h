#pragma once
#include "Ship.h"
class CPlayer :
	public CShip
{
	int shield;
	int maxShield;
	int shieldRegen;

	unsigned int exp;
	unsigned int expRequired;
	unsigned int perks;
	unsigned int laserLevel;
	unsigned int missileLevel;
	unsigned int wellLevel;
	unsigned int pushLevel;
	unsigned int warpLevel;

	float shieldTimer;
	float laserTimer;
	float missileTimer;
	float wellTimer;
	float pushTimer;
	float warpTimer = 0;

	float shieldDelay;
	float laserDelay;
	float missileDelay;
	float wellDelay;
	float pushDelay;
	float warpDelay = 1;

	float warpSpeed;
	float warpDuration = 1;

public:
	CPlayer();
	virtual ~CPlayer();

	int GetType() override {return (int)EntityType::Player;}
	void Update(float dt) override;
	void AddGravity(SGD::Vector grav) override;
	void TakeDamage(int damage) override;
	//void HandleCollision(IEntity* other) override;
	//Coment out later:
	void Render() override;

	void CreateLaser();
	void CreateMissile();
	void CreateWell();
	void CreatePush();
	void Warp();
};

