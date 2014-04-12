#pragma once
#include "Stationary.h"
class CShieldModule;
class CShip;
class CEmitter;
class CParticleSystem;
class CModuleShield : public Stationary
{
	CShieldModule* m_pOwner;
	CShip        * m_pOwnerShip;
	CEmitter* m_eShieldDown;
	CParticleSystem* m_pSystem;
public:
	CModuleShield(CShip* p);
	~CModuleShield();
	int GetType() override { return (int)EntityType::ModuleShield; }
	bool IsCircle() override { return true; }
	void Update(float dt);
	void Render();
	void HandleCollision(IEntity* other) override;
	CShip* GetOwnerShip(void) {return m_pOwnerShip;}
	void SetOwner(CShieldModule* p) { m_pOwner = p; }
	void SetOwnerShip(CShip* p) { m_pOwnerShip = p;  }
};