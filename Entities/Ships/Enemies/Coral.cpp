//
#include "Coral.h"


CCoral::CCoral()
{

}


CCoral::~CCoral()
{
}

void CCoral::Update(float dt)
{
	if (engine)
	{
		engine->Update(dt);
	}
	
}

void CCoral::Render()
{

}

void CCoral::HandleCollision(IEntity* other)
{

}

void CCoral::DestroyModule(CModule* mod)
{
	if (mod == engine)
	{
		engine = nullptr;
	}
	else if (mod == cockpit)
	{
		//SelfDestruct
	}
	else if (mod == shieldMod)
	{
		shieldMod = nullptr;
	}
	else if (mod == laser)
	{
		laser = nullptr;
	}
	else if (mod == ability)
	{
		ability = nullptr;
	}
	mod->Release();
}

void CCoral::SelfDestruct(void)
{
	engine->Release();
	cockpit->Release();
	shieldMod->Release();
	laser->Release();
	ability->Release();
	//Send a destroy message
}
