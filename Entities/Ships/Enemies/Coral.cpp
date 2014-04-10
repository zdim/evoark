//
#include "Coral.h"
#include "../../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../EntityManager.h"
#include "../../../GameStates/GameplayState.h"
#include "../../Collidables/ModuleShield.h"
#include "../../Projectiles/Laser.h"

CCoral::CCoral()
{
	expValue = 50;
	modules.resize(count);
	modules[engine] = new CEngine();
	modules[cockpit] = new CModule();
	m_pShield = new CModuleShield();

	modules[shieldModule] = new CShieldModule();
	
	m_pShield->SetOwner(dynamic_cast<CShieldModule*>(modules[shieldModule]));
	m_pShield->SetOwnerShip(this);

	
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
			if ((i == laser && target) || (i >= ability && target))
				modules[i]->Activate();
			if (modules[i]->GetType() == (int)EntityType::WarpModule)
			{
				if (target)
				{
					if (dynamic_cast<CWarpModule*>(modules[i])->isActive())
					{
						SGD::Vector dir = target->GetPosition() - position;
						dir.Normalize();
						velocity += dir * 300;
					}
				}
			}
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
	if (other == m_pShield)
		return;
	if (other->GetType() == (int)EntityType::Laser || other->GetType() == (int)EntityType::Missile)
	{
		CLaser* l = dynamic_cast<CLaser*>(other);
		if (l->GetOwner() == this)
			return;
	}


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

void CCoral::DestroyModule(CModule* mod, bool safe)
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
			if (i == cockpit && !safe)
				SelfDestruct();
			if (i == shieldModule)
			{
				m_pShield->SelfDestruct();
				m_pShield = nullptr;
			}
				
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
	if (m_pShield)
		m_pShield->SetImage(images[(int)EntityType::Shield]);

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
	if (modules[shieldModule])
		return dynamic_cast<CShieldModule*>(modules[shieldModule])->RequestShield(damage);
	else
		return 0;

}

std::vector<EntityData> CCoral::GetModuleData()
{
	std::vector<EntityData> modData;
	for (unsigned int i = 0; i < modules.size(); i++)
	{
		EntityData mod;
		if (!modules[i])
		{
			//If the module is dead, just store tpye as baseclass
			mod.type = EntityType::BaseClass;
			modData.push_back(mod);
			continue;
		}
		mod.coord = false;
		mod.hull = modules[i]->GetHull();
		mod.position = {modules[i]->GetOffset().x, modules[i]->GetOffset().y};
		mod.type = (EntityType)modules[i]->GetType();
		if (mod.type == EntityType::ShieldModule)
		{
			mod.shield = dynamic_cast<CShieldModule*>(modules[i])->GetShield();
		}
		else
			mod.shield = 0;
		modData.push_back(mod);
	}
	return modData;
}

void CCoral::SetModuleData(std::vector<EntityData> mods)
{
	modules.resize(mods.size());
	for (unsigned int i = 0; i < mods.size(); i++)
	{
		//If this module is alive in object, but types don't match up
		if (modules[i] && (EntityType)modules[i]->GetType() != mods[i].type)
		{
			//Kill it, but kill it safely
			DestroyModule(modules[i], true);
		}

		//If this module is dead in object and alive in data
		if (mods[i].type != EntityType::BaseClass && !modules[i])
		{
			switch (mods[i].type)
			{
			case EntityType::BaseModule:
				modules[i] = new CModule;
				break;
			case EntityType::ShieldModule:
				modules[i] = new CShieldModule;
				break;
			case EntityType::EngineModule:
				modules[i] = new CEngine;
				break;
			case EntityType::LaserModule:
				modules[i] = new CLaserModule;
				break;
			case EntityType::MissileModule:
				modules[i] = new CMissileModule;
				break;
			case EntityType::WellModule:
				modules[i] = new CWellModule;
				break;
			case EntityType::PushModule:
				modules[i] = new CPushModule;
				break;
			case EntityType::WarpModule:
				modules[i] = new CWarpModule;
				break;
			}
			modules[i]->SetOffset(modulePositions[i]);
			modules[i]->SetOwner(this);
		}

		//If this module is dead in data
		if (mods[i].type == EntityType::BaseClass)
		{
			//We already killed it. Types wouldn't match up in this case.
			//Kill it in object
			//DestroyModule(modules[i], true);
			//We're done with this one
			continue;
		}

		//We should only hit this with a live module of a type that matches the one in data
		modules[i]->SetHull(mods[i].hull);
		if ((EntityType)modules[i]->GetType() == EntityType::Shield)
		{
			dynamic_cast<CShieldModule*>(modules[i])->SetShield(mods[i].shield);
		}
	}
}
