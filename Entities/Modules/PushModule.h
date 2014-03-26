#pragma once
#include "TurretModule.h"
class CPushModule :
	public CTurretModule
{
public:
	int GetType(){ return (int)EntityType::PushModule; }
	CPushModule();
	virtual ~CPushModule();
};

