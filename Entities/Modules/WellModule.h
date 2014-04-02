#pragma once
#include "TurretModule.h"
class CWellModule :
	public CTurretModule
{
	float radius = 128.0f;
public:
	int GetType(){ return(int)EntityType::WellModule; }
	CWellModule();
	virtual ~CWellModule();
	void Activate();
};

