#pragma once
#include "Enemy.h"
#include "../../Leader.h"
class CEmitter;
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
	CEmitter* m_Engine;
	SGD::Point  enginePos;

public:
	CCopperhead();
	virtual ~CCopperhead();

	int GetType() override { return (int)EntityType::Copperhead; }
	void Update(float dt);
	void Render(); 
	void AddGrav(SGD::Vector grav) { gravVec += grav; }
	//void CCopperhead::TakeDamage(int damage) override;

	SGD::Point GetEnginePos() { return enginePos; }

	void CCopperhead::CreateLaser();
	void CCopperhead::CreateMissile();

	SGD::Vector AI(float dt); //Everything in the update, except move -- To simplify CCobra
};

class CCopperheadCoord : public CCopperhead, public Coordinator
{
public:
	virtual ~CCopperheadCoord(){}
	bool IsCoordinator() override { return true; }
	void SelfDestruct() override {
		if (!destroying) { CCopperhead::SelfDestruct(); Coordinator::Unregister();} }
};