#pragma once
#include "Copperhead.h"
#include "../../Leader.h"
class CMamba :
	public CCopperhead
{
private:
	float m_fMissileDelay;
	float m_fMissileTimer;
	int   m_nMissileDamage; 

public:
	CMamba();
	virtual ~CMamba();
	int GetType() override { return (int)EntityType::Mamba; }
	void Update(float dt);
	void AddGrav(SGD::Vector);
	void CreateMissile();
};

class CMambaCoord : public CMamba, public Coordinator
{

};

