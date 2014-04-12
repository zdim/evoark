#pragma once
#include "Stationary.h"
class CShip;
class CShield : public Stationary
{
	CShip* m_pOwner;
public:
	CShield(){ size = { 100, 100 }; }
	int GetType() override { return (int)EntityType::Shield; }
	bool IsCircle() override { return true; }
	void Update(float dt);
	void Render();
	void HandleCollision(IEntity* other) override;
	void SetOwner(CShip* p) { m_pOwner = p; }
	CShip*  GetOwner() { return m_pOwner; }
};