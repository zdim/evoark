#pragma once
#include "../Entity.h"
class CShip :
	public CEntity
{
protected:
	int hull = 100;
	int maxHull = 100;
	float speed = 1;
public:
	CShip();
	virtual ~CShip();

	virtual void TakeDamage(int damage);
	void HandleCollision(IEntity* other) override;

	//Comment this out later?
	void Render() override;


	virtual int getHull() {return hull;}
	virtual int getMaxHull() {return maxHull;}
	virtual float getSpeed() {return speed;}

	virtual void setHull(int newHull) { hull = newHull; }
	virtual void setMaxHull(int newMaxHull) { maxHull = newMaxHull; }
	virtual void setSpeed(float newSpeed) { speed = newSpeed; } 
};

