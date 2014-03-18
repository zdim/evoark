#pragma once
#include "TurretModule.h"
class CLaserModule :
	public CTurretModule
{
	int damage;
public:
	CLaserModule();
	virtual ~CLaserModule();

	int GetDamage() {return damage;}
	void SetDamage(int newDam) {damage = newDam;}

	void Activate() override;
};

