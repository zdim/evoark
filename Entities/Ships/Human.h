#pragma once
#include "Ship.h"
#include "../../Event System/IListener.h"
class CHuman :
	public CShip, public Listener
{
private:
	CShip* target = nullptr;
	bool godMode;

	int damage = 5;
	float laserTimer;
	float laserDelay;
	
	float turnRate;
public:
	CHuman();
	virtual ~CHuman();

	int GetType() override { return (int)EntityType::Human; }
	void Update(float dt);
	void AddGrav(SGD::Vector grav) {gravVec += grav;}

	//stubbing for now
	IEntity* GetTarget() {return target;}
	void SetTarget(CShip* newTarget);
	void HandleEvent(CCustomEvent* e);
	void DetectShip(CShip* other);
	void CreateLaser();
	void TakeDamage(int damage, bool collision) override { CShip::TakeDamage(damage,collision);}
	void SelfDestruct() override { CShip::SelfDestruct(); }
};