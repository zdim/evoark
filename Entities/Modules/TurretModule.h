#pragma once
#include "Module.h"
#include "../Ships/Ship.h"
class CTurretModule :
	public CModule
{
protected:
	CShip* target;
	int damage;

	float delay;
	float timer;
public:
	CTurretModule();
	virtual ~CTurretModule();

	int GetType() { return (int)EntityType::BaseClass; }
	const CShip* GetTarget() {return target;}
	void SetTarget(CShip* newTarget); //{ target = newTarget; }

	virtual void Update(float dt) override;
};

