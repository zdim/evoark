//
#include "Coral.h"
#include "../../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../EntityManager.h"
CCoral::CCoral()
{
	modules.resize(count);
	modules[engine] = new CEngine();
	modules[cockpit] = new CModule();
	modules[shieldModule] = new CShieldModule();
	modules[laser] = new CLaserModule();

	EntityType abilityMod = (EntityType)(rand()%4 + (int)EntityType::MissileModule);
	switch (abilityMod)
	{
	case EntityType::MissileModule:
		modules[ability] = new CMissileModule;
		break;
	case EntityType::WellModule:
		modules[ability] = new CWellModule;
		break;
	case EntityType::PushModule:
		modules[ability] = new CPushModule;
		break;
	case EntityType::WarpModule:
		modules[ability] = new CWarpModule;
		break;
	}

	modulePositions.resize(count);
	modulePositions[engine] = SGD::Vector{ 0, 40 };
	modulePositions[cockpit] = SGD::Vector{ 0, 0 };
	modulePositions[shieldModule] = SGD::Vector{ 40, 0 };
	modulePositions[laser] = SGD::Vector{ 0, -40 };
	modulePositions[ability] = SGD::Vector{ -40, 0 };

	for (unsigned int i = 0; i < modules.size(); i++)
	{
		modules[i]->SetOffset(modulePositions[i]);
		modules[i]->SetOwner(this);
	}
}


CCoral::~CCoral()
{
}

void CCoral::Update(float dt)
{
	CEnemy::Update(dt);

	for (unsigned int i = 0; i < modules.size(); i++)
	{
		if (modules[i])
		{
			modules[i]->Update(dt);
			if (i == laser && target)
				modules[i]->Activate();
		}
	}
	if (!modules[cockpit])
		SelfDestruct();
}

void CCoral::Render()
{
	CEntity::Render();
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		if (modules[i])
			modules[i]->Render();
	}
}

void CCoral::HandleCollision(IEntity* other)
{
	CEntityManager* EM = CEntityManager::GetInstance();
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		if (EM->ShapedCollisions(modules[i], other))
		{
			modules[i]->HandleCollision(other);
			other->HandleCollision(modules[i]);
		}
	}
}

void CCoral::DestroyModule(CModule* mod)
{
	if (mod == nullptr)
		return;
	mod->SetOwner(nullptr);
	mod->Release();
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		if (mod == modules[i])
		{
			modules[i] = nullptr;
			if (i == cockpit)
				SelfDestruct();
			break;
		}
	}
}

void CCoral::DestroyAllModules()
{
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		DestroyModule(modules[i]);
	}
}

void CCoral::SetImages(std::vector<SGD::HTexture>& images)
{
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		if (modules[i])
		{
			modules[i]->SetImage(images[modules[i]->GetType()]);
			modules[i]->SetSize({32,32});
		}
	}
}

void CCoral::SetTarget(CShip* newTarget)
{
	CEnemy::SetTarget(newTarget);
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		if (modules[i] && modules[i]->IsTurret())
		{
			dynamic_cast<CTurretModule*>(modules[i])->SetTarget(newTarget);
		}
	}
}

int CCoral::RequestShield(int damage)
{
	return dynamic_cast<CShieldModule*>(modules[shieldModule])->RequestShield(damage);
}