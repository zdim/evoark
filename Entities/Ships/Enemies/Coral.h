#pragma once
#include "Enemy.h"
#include "../../Modules/LaserModule.h"
#include "../../Modules/MissileModule.h"
#include "../../Modules/PushModule.h"
#include "../../Modules/WellModule.h"
#include "../../Modules/WarpModule.h"
#include "../../Modules/ShieldModule.h"
#include "../../Modules/Engine.h"
#include <vector>

class CModuleShield;
struct EntityData;

class CCoral :
	public CEnemy
{
protected:
	enum moduleSlot{cockpit, shieldModule, engine, laser, ability, count};
	std::vector<SGD::Vector>modulePositions;
	std::vector<CModule*>modules;
	CModuleShield* m_pShield;

public:
	CCoral();
	virtual ~CCoral();

	virtual int GetType() override { return (int)EntityType::Coral; }

	virtual void Update(float dt)					override;
	virtual void Render()							override;
	virtual void HandleCollision(IEntity* other)	override;

	virtual void DestroyModule(CModule* mod, bool safe = false);
	virtual void DestroyAllModules();
	//virtual void SelfDestruct(void);

	virtual void SetImages(std::vector<SGD::HTexture>&images);
	void SetTarget(CShip* newTarget) override;
	void SetShield(CModuleShield* p) { m_pShield = p; }
	CModuleShield* GetShield()       { return m_pShield; }
	int RequestShield(int damage);
	std::vector<EntityData> GetModuleData();
	void SetModuleData(std::vector<EntityData> mods);
};