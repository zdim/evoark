#pragma once
#include "../Ship.h"
#include "../../Leader.h"
class CEnemy :
	public CShip
{
	float turnRate;
	CShip* target;
public:
	CEnemy();
	virtual ~CEnemy();

	CShip* GetTarget() {return target;}
	void SetTarget(CShip* newTarget);
};