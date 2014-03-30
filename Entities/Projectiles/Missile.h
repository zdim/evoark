#pragma once
#include "Laser.h"
#include "../Ships/Ship.h"
class CEmitter;
class CMissile :
	public CLaser
{
	CShip* target = nullptr;
	CEmitter* m_eTrail;
public:
	CMissile();
	virtual ~CMissile();

	const CShip* GetTarget() {return target;}
	void SetTarget(CShip* newTarget);
	void Render();
	void Update(float dt);

	//stub it for now. We can ^^^ hardcode a target to test tracking, then implement a search
	void FindTarget(){};

	void HandleCollision(IEntity* other) override;
};


