#pragma once
#include "Module.h"
class CWarpModule :
	public CModule
{
public:
	int GetType() { return (int)EntityType::WarpModule; }
	CWarpModule();
	virtual ~CWarpModule();
};

