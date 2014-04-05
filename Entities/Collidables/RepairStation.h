#pragma once
#include "Stationary.h"
class CMoccasin;

class CRepairStation : public Stationary
{
	CMoccasin*      m_pOwner;

public:
	CRepairStation(){ size = { 64, 64 }; }
	int GetType() override { return (int)EntityType::RepairStation; }
	bool IsCircle() override { return true; }
	void Update(float dt) override;

	void HandleCollision(IEntity* other) override;

	CMoccasin* GetOwner() { return m_pOwner; }
	void SetOwner(CMoccasin* p) { m_pOwner = p; }

};
