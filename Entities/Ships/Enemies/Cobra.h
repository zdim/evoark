#pragma once
#include "Copperhead.h"
#include "../../Leader.h"
class CEmitter;
class CCobra :
	public CCopperhead
{
	float warpTimer;
	float warpDelay;
	float warpDuration;
	float warpSpeed;

	CEmitter* m_Engine;
	SGD::Point  enginePos;

	CEmitter* m_Engine2;
	SGD::Point  enginePos2;

public:
	CCobra();
	virtual ~CCobra();

	int GetType() override { return (int)EntityType::Cobra; }
	void Render();
	void Update(float dt);
	void AddGrav(SGD::Vector);
	void Warp();
	void HandleCollision(IEntity* other) override;
	void TakeDamage(int damage, bool collision) override;
};

class CCobraCoord : public CCobra, public Coordinator
{
public:
	virtual ~CCobraCoord(){}
	bool IsCoordinator() override { return true; }
	void SelfDestruct() override {
		if (!destroying) { CCobra::SelfDestruct(); Coordinator::Unregister(); }
	}
};