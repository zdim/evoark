#pragma once
#include "Ship.h"
#include "../../Event System/IListener.h"
class CHuman :
	public CShip, public Listener
{
private:
	CShip* target = nullptr;
	bool godMode;
	bool initial = false;

	int damage = 5;
	float laserDelay = 0.15f;
	float laserTimer = laserDelay;

	float turnRate;

	float rescueDelay;
	float rescueTimer;
	bool rescued = false;

	void Clamp() override { if(!rescued)CEntity::Clamp(); } //Don't clamp them if they're rescued
public:
	CHuman();
	virtual ~CHuman();

	int GetType() override { return (int)EntityType::Human; }
	void Update(float dt);
	void AddGrav(SGD::Vector grav) {gravVec += grav;}

	//stubbing for now
	CShip* GetTarget() {return target;}
	void SetTarget(CShip* newTarget);
	void HandleEvent(CCustomEvent* e);
	void DetectShip(CShip* other);
	void CreateLaser();
	void TakeDamage(int damage, bool collision) override { CShip::TakeDamage(damage,collision);}
	void SelfDestruct() override { CShip::SelfDestruct(); }
	void initializeRescueAI();
	void RescueAI(float dt);
	bool IsRescued() {return rescued;}
};