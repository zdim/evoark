#pragma once
#include "TurretModule.h"
class CPushModule :
	public CTurretModule
{
	float radius = SGD::PI/2;
public:
	int GetType(){ return (int)EntityType::PushModule; }
	CPushModule();
	virtual ~CPushModule();
	void Activate();
};

