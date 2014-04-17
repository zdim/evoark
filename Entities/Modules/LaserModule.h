#pragma once
#include "TurretModule.h"
class CLaserModule :
	public CTurretModule
{
	float m_fSprayTimer;
	float m_nSprayCD;

	//Regular module spray
	float shotTimer;
	float shotDelay;
	int shotDuration;
	int shotCount;

public:
	CLaserModule();
	virtual ~CLaserModule();

	int GetType() {return (int)EntityType::LaserModule;}
	int GetDamage() {return damage;}
	void SetDamage(int newDam) {damage = newDam;}
	void Update(float dt);
	void Activate() override;
};

