//
#include "Coral.h"
#include "../../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../EntityManager.h"
CCoral::CCoral()
{
	engine = new CEngine();
	cockpit = new CModule();
	shieldMod = new CShieldModule();
	laser = new CLaserModule();

	engine->SetOffset(SGD::Vector{ 0, 20 });
	cockpit->SetOffset(SGD::Vector{ 0, -20 });
	shieldMod->SetOffset(SGD::Vector{ 20, 0 });
	laser->SetOffset(SGD::Vector{ -20, 0 });

	engine->SetOwner(this);
	cockpit->SetOwner(this);
	shieldMod->SetOwner(this);
	laser->SetOwner(this);

	//Randomly pick an ability when all projectiles are made.
}


CCoral::~CCoral()
{
}

void CCoral::Update(float dt)
{
	CEnemy::Update(dt);
	if (engine)
	{
		engine->Update(dt);
	}
	if (cockpit)
	{
		cockpit->Update(dt);
	}
	else
	{
		SelfDestruct();
	}
	if (shieldMod)
	{
		shieldMod->Update(dt);
	}
	if (laser)
	{
		laser->Update(dt);
	}
	if (ability)
	{
		ability->Update(dt);
	}	
}

void CCoral::Render()
{
	CEntity::Render();
	if (engine)
	{
		engine->Render();
	}
	if (cockpit)
	{
		cockpit->Render();
	}
	//else
	//{
	//	SelfDestruct();
	//}
	if (shieldMod)
	{
		shieldMod->Render();
	}
	if (laser)
	{
		laser->Render();
	}
	if (ability)
	{
		ability->Render();
	}
}

void CCoral::HandleCollision(IEntity* other)
{
	CEntityManager* EM = CEntityManager::GetInstance();
	EM->ShapedCollisions(engine, other);
	EM->ShapedCollisions(cockpit, other);
	EM->ShapedCollisions(shieldMod,other);
	EM->ShapedCollisions(laser, other);
	EM->ShapedCollisions(ability, other);
}

void CCoral::DestroyModule(CModule* mod)
{
	if (mod == nullptr)
		return;
	if (mod == engine)
	{
		engine = nullptr;
	}
	else if (mod == cockpit)
	{
		SelfDestruct();
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

void CCoral::SetImages(std::vector<SGD::HTexture>& images)
{
	engine->SetImage(images[(int)EntityType::EngineModule]);
	cockpit->SetImage(images[(int)EntityType::BaseModule]);
	shieldMod->SetImage(images[(int)EntityType::ShieldModule]);
	laser->SetImage(images[(int)EntityType::LaserModule]);
	if(ability)ability->SetImage(images[ability->GetType()]);

	engine->				SetSize({8,8});
	cockpit->				SetSize({8,8});
	shieldMod->				SetSize({8,8});
	laser->					SetSize({8,8});
	if (ability)ability->	SetSize({8,8});
}
