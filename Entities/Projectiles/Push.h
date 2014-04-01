#pragma once
#include "GravityProjectile.h"
class CPush :
	public CGravityProjectile
{
	SGD::Vector forward;
	IEntity* owner = nullptr;
public:
	CPush();
	virtual ~CPush();
	
	void SetOwner(IEntity* _owner);
	int GetType() override { return (int)EntityType::Push; }
	SGD::Vector GetForward() {return forward;}
	void SetForward(SGD::Vector newForward) {forward = newForward;}
	void HandleCollision(IEntity* other) override;

};

