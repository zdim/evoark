#pragma once
#include "Laser.h"
#include "../Ships/Ship.h"
#include "../../Event System/IListener.h"
class CEmitter;
class CParticleSystem; 
class CMissile :
	public CLaser, public Listener
{
	CShip* target = nullptr;

	CParticleSystem* m_pSystem;

public:
	CMissile();
	virtual ~CMissile();

	const CShip* GetTarget() {return target;}
	void SetTarget(CShip* newTarget);
	void Render();
	void Update(float dt);
	void HandleEvent(CCustomEvent* e) override;

	//stub it for now. We can ^^^ hardcode a target to test tracking, then implement a search
	void FindTarget(){};
	void SelfDestruct() override;
	//void HandleCollision(IEntity* other) override;
};


