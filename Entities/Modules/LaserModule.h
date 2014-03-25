#pragma once
#include "TurretModule.h"
class CLaserModule :
	public CTurretModule
{
public:
	CLaserModule();
	virtual ~CLaserModule();

	int GetDamage() {return damage;}
	void SetDamage(int newDam) {damage = newDam;}

	void Activate() override;
};

