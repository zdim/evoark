#pragma once
#include "Module.h"
class CWarpModule :
	public CModule
{
	float duration = 1;
public:
	void Activate() {timer = 0;}
	bool isActive() {return timer <= duration;}
	int GetType() { return (int)EntityType::WarpModule; }
	CWarpModule() {cooldown = 4; timer = cooldown;}
	virtual ~CWarpModule() {}
};

