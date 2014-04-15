#pragma once
#include "../Entity.h"
#include "../../Event System/IListener.h"
class CMoccasin;

class CRepairStation : public CEntity, public Listener
{
	CMoccasin*      m_pOwner;
	int             hull;

public:
	CRepairStation();
	int GetType() override { return (int)EntityType::RepairStation; }
	bool IsCircle() override { return true; }
	void Update(float dt) override;
	void Render();
	void HandleCollision(IEntity* other) override;
	void TakeDamage(int damage);
	CMoccasin* GetOwner() { return m_pOwner; }
	void SetOwner(CMoccasin* p) { m_pOwner = p; }
	void HandleEvent(CCustomEvent* e) override;
};
