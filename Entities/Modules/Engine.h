#pragma once
#include "Module.h"
class CEngine :
	public CModule
{
public:
	CEngine();
	virtual ~CEngine();
	int GetType() { return (int)EntityType::EngineModule; }

};

