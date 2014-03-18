#pragma once
#include "Laser.h"
#include "../Ships/Ship.h"
class CMissile :
	public CLaser
{
	CShip* target = nullptr;
public:
	CMissile();
	virtual ~CMissile();

	const CShip* GetTarget() {return target;}
	void SetTarget(CShip* newTarget) {target = newTarget;}

	void HandleCollision(IEntity* other) override;
};

