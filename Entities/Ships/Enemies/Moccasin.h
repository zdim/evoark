#pragma once
#include "Coral.h"
class CMoccasin :
	public CCoral
{
private:

	 int m_nLevel;
	float m_fAsteroidTimer;
	float m_fACD;


public:
	CMoccasin();
	virtual ~CMoccasin();
	void Init(int i);
	void Update(float dt);
	void HandleCollision(IEntity* other);
	void SelfDestruct() override;
	unsigned int GetModuleCount() { return modules.size(); }
	void AddModule();
	virtual int GetType() override { return (int)EntityType::Moccasin; }
	int GetLevel() { return m_nLevel; }
};