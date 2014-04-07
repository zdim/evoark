#pragma once
#include "Stationary.h"
class CShieldModule;
class CShip;
class CModuleShield : public Stationary
{
	CShieldModule* m_pOwner;
	CShip        * m_pOwnerShip;
public:
	CModuleShield(){ size = { 360, 360 }; }
	int GetType() override { return (int)EntityType::Shield; }
	bool IsCircle() override { return true; }
	void Update(float dt);
	void Render();
	void HandleCollision(IEntity* other) override;
	CShip* GetOwnerShip(void) {return m_pOwnerShip;}
	void SetOwner(CShieldModule* p) { m_pOwner = p; }
	void SetOwnerShip(CShip* p) { m_pOwnerShip = p;  }
};