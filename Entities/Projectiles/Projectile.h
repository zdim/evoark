#pragma once
#include "../Entity.h"
class CProjectile :
	public CEntity
{
protected:
	float speed;
	int tier = 0;
public:
	CProjectile();
	virtual ~CProjectile();

	float GetSpeed() {return speed;}
	void SetSpeed(float newSpeed) {speed = newSpeed;}
	int GetTier() { return tier; }
	void SetTier(int newTier) { tier = newTier; }
};

