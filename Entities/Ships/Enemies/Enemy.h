#pragma once
#include "../Ship.h"
//#include "../../Leader.h"
#include "../../../Event System/IListener.h"
class CLeader;
class CEnemy :
	public CShip, public Listener
{
protected:
	int expValue = 0;
	float turnRate;
	CShip* target = nullptr;
	SGD::Point destination;
	CLeader* leader = nullptr;
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
	void SetLeader(CLeader* lead) { if (!leader) leader = lead; }

	int GetExpValue() { return expValue; }
};