#pragma once
#include "../Entity.h"
class CMoccasin;

class CRepairStation : public CEntity
{
	CMoccasin*      m_pOwner;
	int             hull;

public:
	CRepairStation();
	int GetType() override { return (int)EntityType::RepairStation; }
	bool IsCircle() override { return true; }
	void Update(float dt) override;

	void HandleCollision(IEntity* other) override;
	void TakeDamage(int damage);
	CMoccasin* GetOwner() { return m_pOwner; }
	void SetOwner(CMoccasin* p) { m_pOwner = p; }

};
