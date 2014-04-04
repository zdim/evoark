#pragma once
#include "Module.h"
class CShieldModule :
	public CModule
{
	int shieldMax = 500;
	int shield = 500;
	float regen = 200;
public:
	int GetType(){ return (int)EntityType::ShieldModule; }
	CShieldModule();
	virtual ~CShieldModule();

	void Update(float dt);
	int RequestShield(int damage);
	int GetShield() { return shield;  }
};

