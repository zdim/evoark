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
	CEngine* engine				= nullptr;
	CModule* cockpit			= nullptr;
	CShieldModule* shieldMod	= nullptr;
	CLaserModule* laser			= nullptr;
	CModule* ability			= nullptr;

	int shield;
	int shieldMax;
	float shieldDelay;
	float shieldTimer;

public:
	CCoral();
	virtual ~CCoral();

	virtual void Update(float dt)					override;
	virtual void Render()							override;
	virtual void HandleCollision(IEntity* other)	override;

	virtual void DestroyModule(CModule* mod);
	virtual void SelfDestruct(void);

	virtual void SetImages(std::vector<SGD::HTexture>&images);
};