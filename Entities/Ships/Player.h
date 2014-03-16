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
	float warpTimer;

	float shieldDelay;
	float laserDelay;
	float missileDelay;
	float wellDelay;
	float pushDelay;
	float warpDelay;

	float warpSpeed;
	float warpDuration;

public:
	CPlayer();
	virtual ~CPlayer();

	void Update(float dt) override;
	void AddGravity(SGD::Vector grav) override;

	void CreateLaser();
	void CreateMissile();
	void CreateWell();
	void CreatePush();
	void Warp();
};

