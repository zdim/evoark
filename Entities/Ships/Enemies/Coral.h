#pragma once
#include "Enemy.h"
#include "../../Modules/LaserModule.h"
#include "../../Modules/MissileModule.h"
#include "../../Modules/PushModule.h"
#include "../../Modules/WellModule.h"
#include "../../Modules/WarpModule.h"
#include "../../Modules/ShieldModule.h"
#include "../../Modules/Engine.h"

class CCoral :
	public CEnemy
{
protected:
	enum moduleSlot{cockpit, shieldModule, engine, laser, ability, count};
	std::vector<SGD::Vector>modulePositions;
	std::vector<CModule*>modules;

	int shield;
	int shieldMax;
	float shieldDelay;
	float shieldTimer;

public:
	CCoral();
	virtual ~CCoral();

	virtual int GetType() override { return (int)EntityType::Coral; }

	virtual void Update(float dt)					override;
	virtual void Render()							override;
	virtual void HandleCollision(IEntity* other)	override;

	virtual void DestroyModule(CModule* mod);
	virtual void DestroyAllModules();
	//virtual void SelfDestruct(void);

	virtual void SetImages(std::vector<SGD::HTexture>&images);
};