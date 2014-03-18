#pragma once
#include "../Entity.h"
class CProjectile :
	public CEntity
{
	float speed;
public:
	CProjectile();
	virtual ~CProjectile();

	float GetSpeed() {return speed;}
	void SetSpeed(float newSpeed) {speed = newSpeed;}
};

