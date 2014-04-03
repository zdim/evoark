#pragma once
#include "TurretModule.h"
class CMissileModule :
	public CTurretModule
{
public:
	int GetType() { return (int)EntityType::MissileModule; }
	CMissileModule();
	virtual ~CMissileModule();
	void Activate() override;
};

