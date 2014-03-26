#pragma once
#include "TurretModule.h"
class CWellModule :
	public CTurretModule
{
public:
	int GetType(){ return(int)EntityType::WellModule; }
	CWellModule();
	virtual ~CWellModule();
};

