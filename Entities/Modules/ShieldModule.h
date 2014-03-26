#pragma once
#include "Module.h"
class CShieldModule :
	public CModule
{
public:
	int GetType(){ return (int)EntityType::ShieldModule; }
	CShieldModule();
	virtual ~CShieldModule();
};

