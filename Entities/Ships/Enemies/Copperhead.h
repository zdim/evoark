#pragma once
#include "Enemy.h"
#include "../../Leader.h"
class CCopperhead :
	public CEnemy
{
protected:
	int damage;
	float laserTimer;
	float laserDelay;

	float m_fMissileDelay;
	float m_fMissileTimer;
	int   m_nMissileDamage;

public:
	CCopperhead();
	virtual ~CCopperhead();

	int GetType() override { return (int)EntityType::Copperhead; }
	void Update(float dt);
	void AddGrav(SGD::Vector grav) { gravVec += grav; }
	//void CCopperhead::TakeDamage(int damage) override;

	void CCopperhead::CreateLaser();
	void CCopperhead::CreateMissile();

	SGD::Vector AI(float dt); //Everything in the update, except move -- To simplify CCobra
};

class CCopperheadCoord : public CCopperhead, public Coordinator
{
public:
	virtual ~CCopperheadCoord(){}
	bool IsCoordinator() override { return true; }
};