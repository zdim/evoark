#pragma once
#include "Projectile.h"
class CGravityProjectile :
	public CProjectile
{
protected:
	float radius;	//Angle for push. Size for well.
	float strength;
	float duration;
	float timer;
public:
	CGravityProjectile();
	virtual ~CGravityProjectile();

	float GetRadius() { return radius; }
	float GetStrength() { return strength; }
	float GetDuraion() { return duration; }
	float GetTimer() { return timer; }
	virtual void SetRadius	(float newVal) { radius		= newVal; }
	void SetStrength(float newVal) { strength	= newVal; }
	void SetDuraion	(float newVal) { duration	= newVal; }
	void SetTimer	(float newVal) { timer		= newVal; }

	bool IsCircle() override { return true; }

	virtual void Update(float dt);
};

