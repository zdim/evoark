#pragma once
#include "../Entity.h"
class CShip :
	public CEntity
{
protected:
	int hull;
	int maxHull;
	float speed;
public:
	CShip();
	virtual ~CShip();

	virtual int getHull() {return hull;}
	virtual int getMaxHull() {return maxHull;}
	virtual float getSpeed() {return speed;}

	virtual void setHull(int newHull) { hull = newHull; }
	virtual void setMaxHull(int newMaxHull) { maxHull = newMaxHull; }
	virtual void setSpeed(float newSpeed) { speed = newSpeed; } 
};

