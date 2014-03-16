#pragma once
#include "../Ship.h"
#include "../../Leader.h"
class CEnemy :
	public CShip
{
	float turnRate;
public:
	CEnemy();
	virtual ~CEnemy();
};