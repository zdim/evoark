#pragma once
#include "../Ship.h"
#include "../../Leader.h"
#include "../../../Event System/IListener.h"
class CEnemy :
	public CShip, public Listener
{
	float turnRate;
	CShip* target = nullptr;
public:
	CEnemy();
	virtual ~CEnemy();

	CShip* GetTarget() {return target;}
	void SetTarget(CShip* newTarget);
	float GetTurnRate() { return turnRate; }
	void DetectShip(CShip* other);
	void Update(float dt) override;

	void HandleEvent(CCustomEvent* e) override;
};