//
#include "ShieldModule.h"
#include "../Ships/Enemies/Coral.h"
CShieldModule::CShieldModule()
{
	
	cooldown = 4;
}


CShieldModule::~CShieldModule()
{
}

void CShieldModule::Update(float dt)
{


	CModule::Update(dt);
	if (timer >= cooldown)
	{
		shield += regen * dt;
		if (shield > shieldMax)
			shield = shieldMax;
	}


}

int CShieldModule::RequestShield(int damage)
{
	int ret;
	if (damage > shield)
		ret = shield;
	else
		ret = damage;
	shield -= damage;
	if (shield < 0)
		shield = 0;
	timer = 0;
	return ret;
}