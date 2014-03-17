#pragma once
#include "Enemy.h"
class CCopperhead :
	public CEnemy
{
protected:
	int damage;

	float laserTimer;
	float laserDelay;
public:
	CCopperhead();
	virtual ~CCopperhead();

	void Update(float dt);
	void AddGrav(SGD::Vector grav) { gravVec += grav; }
	SGD::Vector AI(float dt); //Everything in the update, except move -- To simplify CCobra
};

class CCopperheadCoord : public CCopperhead, public Coordinator
{
	
};