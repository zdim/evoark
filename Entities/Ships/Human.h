#pragma once
#include "Ship.h"
class CHuman :
	public CShip
{
private:
	CShip target;
	bool godMode;

	float laserTimer;
	float laserDelay;
	
	float turnRate;
public:
	CHuman();
	virtual ~CHuman();

	int GetType() override { return (int)EntityType::Human; }
	void Update(float dt);
	void AddGrav(SGD::Vector grav) {gravVec += grav;}
};

