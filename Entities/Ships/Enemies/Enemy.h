#pragma once
#include "../Ship.h"
#include "../../Leader.h"
#include "../../../Event System/IListener.h"
class CEnemy :
	public CShip, public Listener
{
protected:
	int expValue = 0;
	float turnRate;
	CShip* target = nullptr;
public:
	CEnemy();
	virtual ~CEnemy();

	CShip* GetTarget() {return target;}
	virtual void SetTarget(CShip* newTarget);
	float GetTurnRate() { return turnRate; }
	void DetectShip(CShip* other);
	void Update(float dt) override;
	void Render() override;
	virtual void TakeDamage(int damage, bool collision = false);
	void HandleEvent(CCustomEvent* e) override;

	int GetExpValue() { return expValue; }
};