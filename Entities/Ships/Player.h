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
	float wellTimer = 0;
	float pushTimer = 0;
	float warpTimer = 0;

	float shieldDelay;
	float laserDelay;
	float missileDelay;
	float wellDelay = 6.0f;
	float pushDelay = 6.0f;
	float warpDelay = 3.0f;

	float warpSpeed;
	float warpDuration = 1;

	bool arrowsOn = false;

	float explosionTimer;
	float explosionTime; 


public:
	CPlayer();
	virtual ~CPlayer();

	int GetType() override {return (int)EntityType::Player;}
	void Update(float dt) override;
	void AddGravity(SGD::Vector grav) override;
	void TakeDamage(int damage, bool collision = false) override;

	int GetShield() { return shield; }
	int GetMaxShield() { return maxShield; }
	float GetWellDelay() { return wellDelay; }
	float GetPushDelay() { return pushDelay; }
	float GetWarpDelay() { return warpDelay; }
	float GetWellTimer() { return wellTimer; }
	float GetPushTimer() { return pushTimer; }
	float GetWarpTimer() { return warpTimer; }
	bool GetArrowsOn() { return arrowsOn; }

	//void HandleCollision(IEntity* other) override;
	//Coment out later:
	void Render() override;

	void CreateLaser();
	void CreateMissile();
	void CreateWell();
	void CreatePush();
	void Warp();
};

